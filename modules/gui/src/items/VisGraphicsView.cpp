#include "VisGraphicsView.h"
// Qt
#include <QWheelEvent>
#include <QtMath>
#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include <qapplication.h>
#include <src/mainwindow.h>
namespace items
{
	VisGraphicsView::VisGraphicsView(QWidget* parent)
		: QGraphicsView(parent)
		, drag_lock(false)
        , end_drawing(false)
        , m_thumbnail(false)
        , zoom(100)
	{
		this->setDragMode(QGraphicsView::NoDrag);
		this->setOptimizationFlags(QGraphicsView::DontSavePainterState);
		this->setViewportUpdateMode(QGraphicsView::SmartViewportUpdate);
		this->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
		this->setRenderHint(QPainter::Antialiasing, false);
		this->setStyleSheet("QGraphicsView{background-color: rgb(53, 168, 59);}");
	}

	VisGraphicsView::~VisGraphicsView()
	{
    }

    void VisGraphicsView::setZoom(int _zoom)
    {
        qreal scale = qPow(qreal(2), (_zoom - 250) / qreal(50));
        //if (scale > 800 || scale < 1.5) { return; }
        QTransform tf = QTransform::fromScale(scale, scale);
        this->setTransform(tf);
        zoom = _zoom;
        this->update();
    }

    int VisGraphicsView::getZoom() const
    {
        return zoom;
    }

	void VisGraphicsView::wheelEvent(QWheelEvent* event)
	{
		QRectF rectView = this->rect();
		// ��������
		// ��ȡ�����ֵľ���
		int wheelDeltaValue = event->delta();

		// ���Ϲ������Ŵ�
		if (wheelDeltaValue > 0)
		{
			this->scale(1.2, 1.2);
		}

		// ���¹�������С
		else
		{
			this->scale(1.0 / 1.2, 1.0 / 1.2);
		}
		event->accept();

	}

    void VisGraphicsView::mousePressEvent(QMouseEvent* event)
    {
        setPos(event->pos());//���ݵ�ǰ���λ��
        // �л����ƽ��
        if (drag_lock)
        {
            //&& QApplication::keyboardModifiers() == Qt::ControlModifier
            if (event->button() == Qt::LeftButton && drag_head)
            {
                setInteractive(false); // ��item�ϵ����м�Ҳ��ƽ��
                setDragMode(QGraphicsView::ScrollHandDrag);
                event->accept();
                QMouseEvent e(event->type(), event->localPos(), Qt::LeftButton, Qt::LeftButton, Qt::NoModifier);
                QGraphicsView::mousePressEvent(&e);
            }

            else if (event->button() == Qt::MidButton)
            {
            }
            else if (event->button() == Qt::RightButton)
            {
                emit sendData(event->screenPos());
            }

            QGraphicsView::mousePressEvent(event);
            // TODO ��Ƕ�׵����������м������쳣
        }
        //�л��м�ƽ��
        else if (!drag_lock)
        {
            if (event->button() == Qt::MidButton) {
                setInteractive(false); // ��item�ϵ����м�Ҳ��ƽ��
                setDragMode(QGraphicsView::ScrollHandDrag);
                event->accept();
                QMouseEvent e(event->type(), event->localPos(), Qt::LeftButton, Qt::LeftButton, Qt::NoModifier);
                QGraphicsView::mousePressEvent(&e);
            }
            else if (event->button() == Qt::LeftButton)
            {
            }
            else if (event->button() == Qt::RightButton)
            {
                emit sendData(event->screenPos());
            }

            QGraphicsView::mousePressEvent(event);
            // TODO ��Ƕ�׵����������м������쳣
        }

    }

    void VisGraphicsView::mouseReleaseEvent(QMouseEvent* event)
    {
        setPos(event->pos());//���ݵ�ǰ���λ��
        if (drag_lock)
        {
            if (event->button() == Qt::LeftButton)
            {
                event->accept();
                QMouseEvent e(event->type(), event->localPos(), Qt::LeftButton, Qt::LeftButton, Qt::NoModifier);
                QGraphicsView::mouseReleaseEvent(&e);
                setDragMode(QGraphicsView::NoDrag);
                setInteractive(true);
            }
            else
            {
                QGraphicsView::mouseReleaseEvent(event);
            }
        }
        else if (!drag_lock)
        {
            if (event->button() == Qt::MidButton)
            {
                event->accept();
                QMouseEvent e(event->type(), event->localPos(), Qt::LeftButton, Qt::LeftButton, Qt::NoModifier);
                QGraphicsView::mouseReleaseEvent(&e);
                setDragMode(QGraphicsView::NoDrag);
                setInteractive(true);
            }
            else
            {
                QGraphicsView::mouseReleaseEvent(event);
            }
        }
        emit MouseReleaseCorrespondingEvent(event->pos());
    }
    void VisGraphicsView::setLock(bool _lock) {
        drag_lock = _lock;
    }

    bool VisGraphicsView::getLock() {
        return drag_lock;
    }
    void VisGraphicsView::setHand(bool _hand) {
        drag_head =_hand;
    }
    
    bool VisGraphicsView::getHand() {
        return drag_head;
    }

    void VisGraphicsView::setPos(QPoint pos) 
    {
        m_pos = pos;
    }
    QPoint VisGraphicsView::getPos() 
    {
        return m_pos;
    }

    void VisGraphicsView::setThumbnailZoom(bool thumbnail) 
    {
        m_thumbnail = thumbnail;
    }

    void VisGraphicsView::slot_reset(QRectF rectItem)
    {
        this->fitInView(rectItem, Qt::KeepAspectRatio);
    }

}
