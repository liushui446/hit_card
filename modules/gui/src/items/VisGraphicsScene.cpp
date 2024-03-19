#include "VisGraphicsView.h"
#include "VisGraphicsScene.h"
// Qt
#include <QPainter>
#include <QGraphicsView>
#include <QDebug>
#include <QtMath>
#include <QVector2D>
#include <QVector3D>
#include <as/core/def.h>

// 3rdpart

#define EDGPADDING       0.1        //���ܱ�Ե��������
#define CORPADDING       0.1        //�Ľǿ�������

#define MIN_WIDTH        0.1        //���������С���
#define MIN_HEIGHT       0.1        //���������С�߶�

#define POINT_WIDTH      0.3        //��Ե9��Ŀ��
#define POINT_HEIGHT     0.3         //��Ե9��ĸ߶�

#define EDGE_WIDTH       3        //�߿�Ŀ��
#define MIDDLELINE_WIDTH 2        //�����ߵĿ��

#define DRAW_TEN_POINT            //����ʮ����
#define DRAW_SUB_LINE            //���Ƹ�����

namespace items
{

    VisGraphicsScene::VisGraphicsScene(QWidget* parent)
        : QGraphicsScene(parent),
        marqueeIdf(false)
    {
        mouseResponse = false;
        mouseClickComponent = false;
        delta_x = 0;
        delta_y = 0;
    }

    void VisGraphicsScene::setBackgroundImage(const QPixmap& _pixmap, double _scaleX, double _scaleY)
    {
        m_scaleX = _scaleX;
        m_scaleY = _scaleY;
        tex.lock();
        m_pixmap = _pixmap.copy();
        tex.unlock();
        // �����Ӵ��Ĵ�С,����ͼԪ�϶�ʱ���ֵĲ�Ӱ
        if (this->views().isEmpty())
        {
            return;
        }

        QGraphicsView* pView = views().first();
        const QRect contentRect = pView->viewport()->contentsRect();
        const QRectF sceneRect = pView->mapToScene(contentRect).boundingRect();
        //QRectF sceneRectAnd = this->sceneRect() & sceneRect; // preventing access conflicts
        //pView->viewport()->update();
        this->update(sceneRect);
    }


    void VisGraphicsScene::drawBackground(QPainter* painter, const QRectF& rect)
    {
        Q_UNUSED(rect);
        // �����Ӵ��Ĵ�С,����ͼԪ�϶�ʱ���ֵĲ�Ӱ
        if (this->views().isEmpty())
        {
            return;
        }
        VisGraphicsView* view = qobject_cast<VisGraphicsView*>(views().first());
        if (!view)
        {
            return;
        }
        QRect contentRect = view->viewport()->contentsRect();
        QRectF sceneRect = view->mapToScene(contentRect).boundingRect();
       
		if (markDialog)
		{
			//����ָ��ͼƬ��Ϊ����
			if (m_pixmap.isNull())
			{
			    // ����ɫ
			    painter->save();
			    painter->setBrush(QBrush("#000000"));
			    painter->drawRect(sceneRect);
			    painter->restore();
			    
			}
			else
			{
			    //tex.lock();
                auto fragment = QPainter::PixmapFragment::create(QPointF(0.0, 0.0), m_pixmap.rect(), m_scaleX, m_scaleY);
			    painter->drawPixmapFragments(&fragment, 1, m_pixmap);
			    //tex.unlock();
			}
            return;
		}


        //����ɫ
        painter->save();
        painter->setBrush(QBrush("#000000"));
        painter->setPen(QPen(Qt::black, 10));
        QRectF rect1(-10000, -10000, 20000, 20000);
        QPixmap map_Image(2000, 2000);
        map_Image.fill(QColor(53, 168, 59));
        m_pixmap = map_Image;
        auto fragment = QPainter::PixmapFragment::create(QPointF(0, 0), m_pixmap.rect(), 10, 10);
        painter->drawPixmapFragments(&fragment, 1, m_pixmap);

        this->setSceneRect(rect1);
        painter->drawLine(-20, -20, 20, 20);
        painter->drawLine(-20, 20, 20, -20);

        painter->restore();

    }
    void VisGraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent* event)
    {
        if (isRectangleDrawn_scene)
        {
            m_roiRect = QRectF(0, 0, 0, 0);
        }
        if (mouseFrame == true)
        {
            if (event->buttons() == Qt::LeftButton)
            {
                sendFramePressEvent(event->scenePos());
            }
            else if (event->buttons() == Qt::RightButton)
            {
                // �ָ������ʽΪ��ͷ��״
                VisGraphicsView* view = qobject_cast<VisGraphicsView*>(this->views().first());
                view->viewport()->setCursor(Qt::ArrowCursor);
            }
        }
        else if (mouseClickComponent)
        {
            //if (event->button() == Qt::LeftButton && event->modifiers() == Qt::CTRL)
            //{
            //    setCtrl(true);
            //    emit multipleMouseSave(event->scenePos());
            //}
            //else if (event->button() == Qt::LeftButton)
            //{
            //    setCtrl(false);
            //    emit sendLeftComponent(event->scenePos());
            //}
            ///*else if (event->button() == Qt::MidButton)
            //{
            //}*/
            if (event->button() == Qt::LeftButton)
            {
                emit sendLeftComponent(event->scenePos());
            }
            else if (event->button() == Qt::RightButton)
            {
                emit sendRightComponent(event->scenePos());
            }
            // �ָ������ʽΪ��ͷ��״
            VisGraphicsView* view = qobject_cast<VisGraphicsView*>(this->views().first());
            view->viewport()->setCursor(Qt::ArrowCursor);
            QGraphicsScene::mousePressEvent(event);

            // TODO ��Ƕ�׵����������м������쳣
        }
        else
        {
            if (event->button() == Qt::LeftButton)
            {
                emit sendLeftComponent(event->scenePos());
            }
            // ���ֶ���ѡ����, ����ͼԪ�ƶ�
            QPointF mousePt = event->scenePos();
            QGraphicsScene::mousePressEvent(event);
        }

    }
    void VisGraphicsScene::sendFramePressEvent(const QPointF& mousePoint)
    {
        EmDirection dir = region(mousePoint);     //��ȡ��굱ǰ��λ��
        QRectF sceneRect = this->sceneRect();
        if (mousePoint.x() < sceneRect.topLeft().x() ||
            mousePoint.x() > sceneRect.bottomRight().x() ||
            mousePoint.y() < sceneRect.topLeft().y() ||
            mousePoint.y() > sceneRect.bottomRight().y())
        {
            m_paintStartPoint.setX(-1);
            m_paintStartPoint.setY(-1);
        }
        else if (dir == DIR_MIDDLE)
        {
            //����ھ�������λ��
            m_moveStartPoint = mousePoint;
            m_bMovedPressed = true;
        }
        else if (dir == DIR_NONE)
        {
            //����ھ����ⲿ
            m_bPainterPressed = true;
            m_paintStartPoint = mousePoint;
        }
        else
        {
            //����ھ��α�Ե
            m_moveStartPoint = mousePoint;
            m_bScalePressed = true;
            m_emCurDir = dir;
        }
        return;
    }
    VisGraphicsScene::EmDirection VisGraphicsScene::region(const QPointF& point)
    {
        double mouseX = point.x();
        double mouseY = point.y();
        QPointF roiTopLeft = m_roiRect.topLeft();
        QPointF roiBottomRight = m_roiRect.bottomRight();

        EmDirection dir = DIR_NONE;

        VisGraphicsView* view = qobject_cast<VisGraphicsView*>(this->views().first());
        if (m_roiRect.width() == 0 ||
            m_roiRect.height() == 0)
        {
            dir = DIR_NONE;
            return dir;
        }

        QRectF borderRoi(roiTopLeft.x() - CORPADDING, roiTopLeft.y() - CORPADDING, m_roiRect.width() + 2 * CORPADDING, m_roiRect.height() + 2 * CORPADDING);
        if (!m_roiRect.contains(point) && !m_roiRect_out.contains(point))
        {
            dir = DIR_NONE;
            return dir;
        }

        if (mouseX <= roiTopLeft.x() + CORPADDING &&
            mouseX >= roiTopLeft.x() - CORPADDING &&
            mouseY <= roiTopLeft.y() + CORPADDING &&
            mouseY >= roiTopLeft.y() - CORPADDING)
        {
            //���Ͻ�
            view->viewport()->setCursor(Qt::SizeFDiagCursor);
            dir = DIR_LEFTTOP;
        }
        else if (mouseX >= roiBottomRight.x() - CORPADDING &&
            mouseX <= roiBottomRight.x() + CORPADDING &&
            mouseY <= roiTopLeft.y() + CORPADDING &&
            mouseY >= roiTopLeft.y() - CORPADDING)
        {
            //���Ͻ�
            view->viewport()->setCursor(Qt::SizeBDiagCursor);
            dir = DIR_RIGHTTOP;
        }
        else if (mouseX <= roiTopLeft.x() + CORPADDING &&
            mouseX >= roiTopLeft.x() - CORPADDING &&
            mouseY >= roiBottomRight.y() - CORPADDING &&
            mouseY <= roiBottomRight.y() + CORPADDING)
        {
            //���½�
            view->viewport()->setCursor(Qt::SizeBDiagCursor);
            dir = DIR_LEFTBOTTOM;
        }
        else if (mouseX >= roiBottomRight.x() - CORPADDING &&
            mouseX <= roiBottomRight.x() + CORPADDING &&
            mouseY >= roiBottomRight.y() - CORPADDING &&
            mouseY <= roiBottomRight.y() + CORPADDING)
        {
            //���½�
            view->viewport()->setCursor(Qt::SizeFDiagCursor);
            dir = DIR_RIGHTBOTTOM;
        }
        else if (mouseX >= roiBottomRight.x() - EDGPADDING &&
            mouseX <= roiBottomRight.x() + EDGPADDING &&
            mouseY >= roiTopLeft.y() &&
            mouseY <= roiBottomRight.y())
        {
            //�ұ�
            view->viewport()->setCursor(Qt::SizeHorCursor);
            dir = DIR_RIGHT;
        }
        else if (mouseY <= roiTopLeft.y() + EDGPADDING &&
            mouseY >= roiTopLeft.y() - EDGPADDING &&
            mouseX >= roiTopLeft.x() &&
            mouseX <= roiBottomRight.x())
        {
            //�ϱ�
            view->viewport()->setCursor(Qt::SizeVerCursor);
            dir = DIR_TOP;
        }
        else if (mouseY >= roiBottomRight.y() - EDGPADDING &&
            mouseY <= roiBottomRight.y() + EDGPADDING &&
            mouseX >= roiTopLeft.x() &&
            mouseX <= roiBottomRight.x())
        {
            //�±�
            view->viewport()->setCursor(Qt::SizeVerCursor);
            dir = DIR_BOTTOM;
        }
        else if (mouseX <= roiTopLeft.x() + EDGPADDING &&
            mouseX >= roiTopLeft.x() - EDGPADDING &&
            mouseY >= roiTopLeft.y() &&
            mouseY <= roiBottomRight.y())
        {
            //���
            view->viewport()->setCursor(Qt::SizeHorCursor);
            dir = DIR_LEFT;
        }
        else if (m_roiRect.contains(point))
        {
            //�м�
            dir = DIR_MIDDLE;
        }

        return dir;
    }
    void VisGraphicsScene::sendFrameMoveEvent(const QPointF& mousePoint)
    {
        if (m_bPainterPressed)
        {
            //���ڻ���״̬
            m_mouseCurrentPoint = mousePoint;
            if (
                QRectF sceneRect = this->sceneRect();
                m_mouseCurrentPoint.x() < sceneRect.topLeft().x() ||
                m_mouseCurrentPoint.x() > sceneRect.bottomRight().x() ||
                m_mouseCurrentPoint.y() < sceneRect.topLeft().y() ||
                m_mouseCurrentPoint.y() > sceneRect.bottomRight().y() ||
                (m_paintStartPoint.x() == -1.0 && m_paintStartPoint.y() == -1.0))
            {
                return;
            }
            float width = std::abs(m_mouseCurrentPoint.x() - m_paintStartPoint.x());  //�ƶ��Ŀ��
            float height = std::abs(m_mouseCurrentPoint.y() - m_paintStartPoint.y());  //�ƶ��ĸ߶�

            float startpoint_x = MIN(m_mouseCurrentPoint.x(), m_paintStartPoint.x());
            float startpoint_y = MIN(m_mouseCurrentPoint.y(), m_paintStartPoint.y());

            QRectF roi(startpoint_x, startpoint_y, width, height);
            emit(sendSceneRectData(roi));
        }
        else if (m_bMovedPressed)
        {
            //�����ƶ�״̬
            m_mouseCurrentPoint = mousePoint;
            double delta_left = m_moveStartPoint.x() - m_roiRect.x();
            double delta_right = m_roiRect.x() + m_roiRect.width() - m_moveStartPoint.x();
            double delta_top = m_moveStartPoint.y() - m_roiRect.y();
            double delta_bottom = m_roiRect.y() + m_roiRect.height() - m_moveStartPoint.y();
            if (
                QRectF sceneRect = this->sceneRect();
                m_mouseCurrentPoint.x() < sceneRect.topLeft().x() + delta_left ||
                m_mouseCurrentPoint.x() > sceneRect.bottomRight().x() - delta_right ||
                m_mouseCurrentPoint.y() < sceneRect.topLeft().y() + delta_top ||
                m_mouseCurrentPoint.y() > sceneRect.bottomRight().y() - delta_bottom)
            {
                return;
            }
            double move_x = m_mouseCurrentPoint.x() - m_moveStartPoint.x();
            double move_y = m_mouseCurrentPoint.y() - m_moveStartPoint.y();
            QRectF ret;
            ret.setX(m_roiRect.x() + move_x);
            ret.setY(m_roiRect.y() + move_y);
            ret.setSize(m_roiRect.size());
            m_roiRect = ret;
            m_moveStartPoint = m_mouseCurrentPoint;
            emit(sendSceneRectData(m_roiRect));
        }
        else if (m_bScalePressed)
        {
            //�������Ŵ�С״̬
            m_mouseCurrentPoint = mousePoint;
            QRectF newRect(m_roiRect.topLeft(), m_roiRect.bottomRight());
            double width = m_mouseCurrentPoint.x() - m_moveStartPoint.x();  //�ƶ��Ŀ��
            double height = m_mouseCurrentPoint.y() - m_moveStartPoint.y();  //�ƶ��ĸ߶�

            QRectF sceneRect = this->sceneRect();
            if (
                m_mouseCurrentPoint.x() < sceneRect.topLeft().x())
            {
                m_mouseCurrentPoint.setX(sceneRect.topLeft().x());
            }
            else if (
                m_mouseCurrentPoint.x() > sceneRect.bottomRight().x())
            {
                m_mouseCurrentPoint.setX(sceneRect.bottomRight().x());
            }
            if (
                m_mouseCurrentPoint.y() < sceneRect.topLeft().y())
            {
                m_mouseCurrentPoint.setY(sceneRect.topLeft().y());
            }
            else if (
                m_mouseCurrentPoint.y() > sceneRect.bottomRight().y())
            {
                m_mouseCurrentPoint.setY(sceneRect.bottomRight().y());
            }

            //���ݵ�ǰ������״̬���ı���ε�λ�ô�С��Ϣ
            switch (m_emCurDir)
            {
            case DIR_LEFT:
                newRect.setLeft(m_mouseCurrentPoint.x());
                break;
            case DIR_RIGHT:
                newRect.setRight(m_mouseCurrentPoint.x());
                break;
            case DIR_TOP:
                newRect.setTop(m_mouseCurrentPoint.y());
                break;
            case DIR_BOTTOM:
                newRect.setBottom(m_mouseCurrentPoint.y());
                break;
            case DIR_LEFTTOP:
                newRect.setTopLeft(m_mouseCurrentPoint);
                break;
            case DIR_LEFTBOTTOM:
                newRect.setBottomLeft(m_mouseCurrentPoint);
                break;
            case DIR_RIGHTTOP:
                newRect.setTopRight(m_mouseCurrentPoint);
                break;
            case DIR_RIGHTBOTTOM:
                newRect.setBottomRight(m_mouseCurrentPoint);
                break;
            }

            if (newRect.width() < MIN_WIDTH || newRect.height() < MIN_HEIGHT)
            {
                //���ŵĴ�С����
                return;
            }

            m_roiRect = newRect;
            m_moveStartPoint = m_mouseCurrentPoint;   //����������ʼλ��
            emit(sendSceneRectData(m_roiRect));

        }
    }
    void VisGraphicsScene::sendFrameReleaseEvent(const QPointF& mousePoint)
    {
        if (m_bPainterPressed)
        {
            m_mouseCurrentPoint = mousePoint;
            if (
                QRectF sceneRect = this->sceneRect();
                m_mouseCurrentPoint.x() < sceneRect.topLeft().x() ||
                m_mouseCurrentPoint.x() > sceneRect.bottomRight().x() ||
                m_mouseCurrentPoint.y() < sceneRect.topLeft().y() ||
                m_mouseCurrentPoint.y() > sceneRect.bottomRight().y() ||
                (m_paintStartPoint.x() == -1.0 && m_paintStartPoint.y() == -1.0))
            {
                return;
            }
            double width = std::abs(m_mouseCurrentPoint.x() - m_paintStartPoint.x());  //�ƶ��Ŀ��
            double height = std::abs(m_mouseCurrentPoint.y() - m_paintStartPoint.y()); //�ƶ��ĸ߶�
            double startpoint_x = MIN(m_mouseCurrentPoint.x(), m_paintStartPoint.x());
            double startpoint_y = MIN(m_mouseCurrentPoint.y(), m_paintStartPoint.y());
            m_roiRect = QRectF(startpoint_x, startpoint_y, width, height);
        }
        m_paintStartPoint = QPoint();
        m_bMovedPressed = false;
        m_bPainterPressed = false;
        m_bScalePressed = false;

    }
    bool VisGraphicsScene::getm_bMovedPressed()
    {
        return m_bPainterPressed;
    }

    void VisGraphicsScene::mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event)
    {
        if (event->button() == Qt::LeftButton && mouseResponse == true) {
            QRectF sceneRect = this->sceneRect();
            QGraphicsSceneMouseEvent* pMouseEvent = reinterpret_cast<QGraphicsSceneMouseEvent*>(event);
            if (pMouseEvent->scenePos().x() < sceneRect.topLeft().x() || pMouseEvent->scenePos().x() > sceneRect.bottomRight().x()
                || pMouseEvent->scenePos().y() < sceneRect.topLeft().y() || pMouseEvent->scenePos().y() > sceneRect.bottomRight().y()) {
                delta_x = 0;
                delta_y = 0;
            }
            else {
                delta_x = pMouseEvent->scenePos().x();
                delta_y = pMouseEvent->scenePos().y();
                emit(sendScenePosData(QPointF(delta_x, delta_y)));
            }
            qDebug() << "pItemUnderMouse: " << delta_x << delta_y;
        }
        else {
            QGraphicsScene::mouseDoubleClickEvent(event);
        }
    }

    bool VisGraphicsScene::getResponseEnable() {
        return mouseResponse;

    }

    void VisGraphicsScene::setResponseEnable(bool enable) {
        mouseResponse = enable;

    }

    void VisGraphicsScene::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
    {
        if (mouseFrame == true)
        {
            sendFrameReleaseEvent(event->scenePos());
        }
        else {
            QGraphicsScene::mouseReleaseEvent(event);
        }
    }
    void VisGraphicsScene::setFrameEnable(bool enable) {
        mouseFrame = enable;

    }
    void VisGraphicsScene::deleteFrameEnable(bool enable) {
        isRectangleDrawn_scene = enable;
    }
    void VisGraphicsScene::Rect_position(bool enable) {
        isRectangle_out = enable;

    }
    void VisGraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
    {
        // �����ϵ���궯̬λ����ʾ
        delta_x = event->scenePos().x();
        delta_y = event->scenePos().y();
        emit sendScenePosLable(delta_x / 10, delta_y / 10);
        if (isRectangleDrawn_scene)
        {
            m_roiRect = QRectF(0, 0, 0, 0);
        }
        if (mouseFrame == true)
        {
            changeFrameMouseShape(event->scenePos());
            if (event->buttons() == Qt::LeftButton)
            {
                sendFrameMoveEvent(event->scenePos());
            }
        }
        else
        {
            // �ָ������ʽΪ��ͷ��״
            VisGraphicsView* view = qobject_cast<VisGraphicsView*>(this->views().first());
            view->viewport()->setCursor(Qt::ArrowCursor);
            if (event->buttons() == Qt::LeftButton)
            {
                QGraphicsScene::mouseMoveEvent(event);
            }
        }
    }
    void VisGraphicsScene::changeFrameMouseShape(const QPointF& mousePoint)
    {
        VisGraphicsScene::EmDirection dir = region(mousePoint);
        VisGraphicsView* view = qobject_cast<VisGraphicsView*>(this->views().first());

        if (dir == DIR_NONE || mouseFrame == false)
        {
            if (marqueeIdf)
            {
                //�����ʽΪʮ����״
                VisGraphicsView* view = qobject_cast<VisGraphicsView*>(this->views().first());
                view->viewport()->setCursor(Qt::CrossCursor);
            }
        }
        else if (dir == DIR_MIDDLE && isRectangleDrawn_scene == false)
        {
            view->viewport()->setCursor(Qt::SizeAllCursor);
        }
    }

    void VisGraphicsScene::setClickComponent(bool _drawing)
    {
        mouseClickComponent = _drawing;
    }
    bool VisGraphicsScene::getClickComponent()
    {
        return mouseClickComponent;
    }
    //��ѡ���ʶ
    void VisGraphicsScene::setMarqueeIdf(bool Idf)
    {
        marqueeIdf = Idf;
    }
    //����mark��򿪽����ʶ
    void VisGraphicsScene::setMarkDialog(bool mark)
    {
        markDialog = mark;
    }

} // namespace items
