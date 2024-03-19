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
		// 滚轮缩放
		// 获取鼠标滚轮的距离
		int wheelDeltaValue = event->delta();

		// 向上滚动，放大
		if (wheelDeltaValue > 0)
		{
			this->scale(1.2, 1.2);
		}

		// 向下滚动，缩小
		else
		{
			this->scale(1.0 / 1.2, 1.0 / 1.2);
		}
		event->accept();

	}

    void VisGraphicsView::mousePressEvent(QMouseEvent* event)
    {
        setPos(event->pos());//传递当前鼠标位置
        // 切换左键平移
        if (drag_lock)
        {
            //&& QApplication::keyboardModifiers() == Qt::ControlModifier
            if (event->button() == Qt::LeftButton && drag_head)
            {
                setInteractive(false); // 在item上单击中键也能平移
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
            // TODO 若嵌套单击，则导致中键功能异常
        }
        //切换中键平移
        else if (!drag_lock)
        {
            if (event->button() == Qt::MidButton) {
                setInteractive(false); // 在item上单击中键也能平移
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
            // TODO 若嵌套单击，则导致中键功能异常
        }

    }

    void VisGraphicsView::mouseReleaseEvent(QMouseEvent* event)
    {
        setPos(event->pos());//传递当前鼠标位置
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
