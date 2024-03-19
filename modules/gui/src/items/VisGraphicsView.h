#pragma once

#include "items_global.h"
// Qt
#include <QGraphicsView>

namespace items
{
	//VisFrame
	class VisGraphicsView : public QGraphicsView
	{
		Q_OBJECT
	public:
		VisGraphicsView(QWidget* parent = nullptr);
		VisGraphicsView::~VisGraphicsView();
		void setZoom(int _zoom);
		int getZoom(void) const;
		void setLock(bool _lock);
		bool getLock();
		void setHand(bool _hand);
		bool getHand();
		void setPos(QPoint pos);
		QPoint getPos();
		void setThumbnailZoom(bool thumbnail);
		void slot_reset(QRectF rectItem);
		//void setDrawing(bool _drawing);
		//bool getDrawing();
		//点击按钮实现鼠标左键拖动
	signals:
		void sendData(QPointF);
		void sendScale(double);
		void sendIndex(double);
		//鼠标松开相应信号
		void MouseReleaseCorrespondingEvent(QPoint pt);

	public slots:
		void mousePressEvent(QMouseEvent* event);
	protected:
		void wheelEvent(QWheelEvent*) override;
		void mouseReleaseEvent(QMouseEvent* event) override;
	private:
		int zoom;
		bool drag_lock;
		bool drag_head;
		bool end_drawing;
		bool m_thumbnail;
		QPoint m_pos;
	};
} // namespace items