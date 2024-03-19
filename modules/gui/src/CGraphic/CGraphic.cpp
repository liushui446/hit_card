#include "as/CGraphic/CGraphic.hpp"
#include <QPen>
#include <QPainter>
#include <QtWidgets>


using namespace as;

CGraphic::CGraphic(QGraphicsItem* parentItem)
	:QGraphicsObject(parentItem)
{
	m_color = QColor(255, 255, 255);
	m_SceneAngle = 0;
}

CGraphic::~CGraphic() 
{
	for (vector<CGraphic*>::iterator iter = GetCGraphics().begin(); iter != GetCGraphics().end(); iter++)
	{
		delete* iter;
		*iter = NULL;
	}
	m_pgAllCGraphic.clear();
}

void CGraphic::SetColor(QColor color)
{
	m_color = color;
}

QRectF CGraphic::miniboundingRect() const
{
	// 生成与单个框大小相同的区域
	QRectF bg = QRectF(QPointF(m_SceneTLx, m_SceneTLy), QSizeF(m_SceneWidth, m_SceneHeight));
	return bg;
}

void CGraphic::SetParameters(double sx, double sy, double width, double height)
{
	m_SceneTLx = sx;
	m_SceneTLy = sy;
	m_SceneWidth = width;
	m_SceneHeight = height;
}

void as::CGraphic::SetAngle(double angle)
{
	m_SceneAngle = angle;
}

std::vector<double> CGraphic::GetParameter(void)
{
	std::vector<double> vec;
	//if (m_SceneTLx == 0 && m_SceneTLy == 0 && m_SceneWidth == 0 && m_SceneHeight == 0)return vec;
	vec.push_back(m_SceneTLx);
	vec.push_back(m_SceneTLy);
	vec.push_back(m_SceneWidth);
	vec.push_back(m_SceneHeight);

	return vec;
}

std::vector<CGraphic*>& CGraphic::GetCGraphics()
{
	return m_pgAllCGraphic;
}

void CGraphic::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
	QGraphicsItem::mousePressEvent(event);
}

void CGraphic::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
	QGraphicsItem::mouseMoveEvent(event);
}

void CGraphic::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
	QGraphicsItem::mouseReleaseEvent(event);
}


//---------------------------CGraphicRectangle---------------------------------------------
CGraphicRect::CGraphicRect(QRectF rt, QGraphicsItem* parentItem) :CGraphic(parentItem)
{
	//setFlag(ItemIsMovable);     // 允许移动
	//setFlag(ItemIsSelectable);  // 允许选择
	m_SceneTLx = rt.x();
	m_SceneTLy = rt.y();
	m_SceneWidth = rt.width();
	m_SceneHeight = rt.height();
}

CGraphicRect::~CGraphicRect() {}

void CGraphicRect::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
	QRectF tpDrawRect = QRectF(QPointF(m_SceneTLx, m_SceneTLy), QSizeF(m_SceneWidth, m_SceneHeight));
	painter->save();
	painter->setPen(QPen(m_color, 0.05));
	painter->setBrush(QBrush(m_color));
	painter->translate(tpDrawRect.center());
	painter->rotate(m_SceneAngle);
	painter->translate(-tpDrawRect.center());
	painter->drawRect(tpDrawRect);
	painter->restore();
}

void CGraphicRect::SetParameter(double sx, double sy, double width, double height)
{
	m_SceneTLx = sx;
	m_SceneTLy = sy;
	m_SceneWidth = width;
	m_SceneHeight = height;
}

QRectF as::CGraphicRect::GetParameter()
{
	return QRectF(m_SceneTLx, m_SceneTLy, m_SceneWidth, m_SceneHeight);
}

QRectF CGraphicRect::boundingRect() const
{
	// 生成新的边界区域, 减小边界框, 避免碰撞冲突
	double update_m_SceneTLx = m_SceneTLx - m_SceneWidth;
	double update_m_SceneTLy = m_SceneTLy - m_SceneHeight;
	QRectF bg = QRectF(QPointF(update_m_SceneTLx, update_m_SceneTLy), QSizeF(m_SceneWidth * 3.0, m_SceneHeight * 3.0));

	return bg;
}

//void CGraphicRect::mousePressEvent(QGraphicsSceneMouseEvent* event)
//{
//	CGraphic::mousePressEvent(event);
//}
//
//void CGraphicRect::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
//{
//	QGraphicsItem::mouseMoveEvent(event);
//}
//
//void CGraphicRect::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
//{
//	QGraphicsItem::mouseReleaseEvent(event);
//}

//---------------------------CGraphicCircle---------------------------------------------
CGraphicCircle::CGraphicCircle(QRectF circle, QGraphicsItem* parentItem) :CGraphic(parentItem)
{

	//圆形传入中心点坐标，X\Y\内圆半径\外圆半径。
	m_dCenterx = circle.x();
	m_dCentery = circle.y();
	m_dIndiameter = circle.width();
	m_dOutdiameter = circle.height();
}

CGraphicCircle::~CGraphicCircle() {}

void CGraphicCircle::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
	painter->save();
	if (m_dOutdiameter > 0.0)
	{
		painter->setPen(QPen(m_color, 0.05));
		painter->setBrush(QBrush(m_color));
		painter->drawEllipse(m_dCenterx - m_dOutdiameter / 2, m_dCentery - m_dOutdiameter / 2, m_dOutdiameter, m_dOutdiameter);
	}
	if (m_dIndiameter > 0.0)
	{
		painter->setPen(QPen(Qt::black, 1));
		painter->setBrush(Qt::black);
		painter->drawEllipse(m_dCenterx - m_dIndiameter / 2, m_dCentery - m_dIndiameter / 2, m_dIndiameter, m_dIndiameter);
	}
	painter->restore();
}

void CGraphicCircle::SetParameter(double sx, double sy, double width, double height)
{
	m_dCenterx = sx;
	m_dCentery = sy;
	m_dIndiameter = width;
	m_dOutdiameter = height;
}

QRectF CGraphicCircle::boundingRect() const
{
	// 计算矩形的左上角坐标
	qreal left = m_dCenterx - m_dOutdiameter / 2.0;
	qreal top = m_dCentery - m_dOutdiameter / 2.0;

	// 计算矩形的宽度和高度
	qreal width = m_dOutdiameter;
	qreal height = m_dOutdiameter;

	// 返回边界矩形
	return QRectF(left, top, width, height);
}

//---------------------------CGraphicOval---------------------------------------------
CGraphicOval::CGraphicOval(QRectF oval, QGraphicsItem* parentItem) :CGraphic(parentItem)
{
	m_dCenterx = oval.x();
	m_dCentery = oval.y();
	m_dWidth = oval.width();
	m_dHeight = oval.height();
}

CGraphicOval::~CGraphicOval() {}

void CGraphicOval::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
	// 计算矩形参数
	double rectX = m_dCenterx - m_dWidth / 2.0;
	double rectY = m_dCentery - m_dHeight / 2.0;

	// 设置画笔和填充颜色为红色
	painter->save();
	painter->setPen(QPen(m_color, 0.05));
	painter->setBrush(QBrush(m_color));
	
	double min = MIN(m_dWidth, m_dHeight);
	// 绘制矩形，圆角的弯曲度为矩形高度的一半
	QRectF rectangle(rectX, rectY, m_dWidth, m_dHeight);
	double cornerRadius = m_dHeight / 2.0;

	painter->translate(rectangle.center());
	painter->rotate(m_SceneAngle);
	painter->translate(-rectangle.center());
	painter->drawRoundedRect(rectangle, min / 2, min / 2, Qt::AbsoluteSize);
	painter->restore();// 恢复画笔和填充设置
	
}

void CGraphicOval::SetParameter(double sx, double sy, double width, double height)
{
	m_dCenterx = sx;
	m_dCentery = sy;
	m_dWidth = width;
	m_dHeight = height;
}

QRectF CGraphicOval::boundingRect() const
{
	// 计算矩形的左上角坐标
	qreal left = m_dCenterx - m_dWidth / 2.0;
	qreal top = m_dCentery - m_dHeight / 2.0;

	// 计算矩形的宽度和高度
	qreal width = m_dWidth;
	qreal height = m_dHeight;

	// 返回边界矩形
	return QRectF(left, top, width, height);
}

//---------------------------CGraphicPolygon---------------------------------------------
CGraphicPolygon::CGraphicPolygon(QRectF polygon,QGraphicsItem* parentItem) :CGraphic(parentItem)
{
	m_dCenterx = polygon.x();
	m_dCentery = polygon.y();
	m_dWidth = polygon.width();
	m_dHeight = polygon.height();
}

CGraphicPolygon::~CGraphicPolygon() {}

void CGraphicPolygon::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
	QRectF tpDrawRect = QRectF(QPointF(m_dCenterx, m_dCentery), QSizeF(m_dWidth, m_dHeight));
	// 设置画笔和填充颜色为红色
	painter->save();
	painter->setPen(QPen(m_color, 0.05));
	painter->setBrush(QBrush(m_color));

	painter->translate(tpDrawRect.center());
	painter->rotate(m_SceneAngle);
	painter->translate(-tpDrawRect.center());
	painter->drawLine(-10, -10, 10, 10);
	painter->drawLine(-10, 10, 10, -10);
	painter->restore();
}

void CGraphicPolygon::SetParameter(double sx, double sy, double width, double height)
{
	m_dCenterx = sx;
	m_dCentery = sy;
	m_dWidth = width;
	m_dHeight = height;
}

QRectF CGraphicPolygon::boundingRect() const
{
	return QRectF(-10, -10, 20, 20);
}

//---------------------------CGraphicLine---------------------------------------------
CGraphicLine::CGraphicLine(QRectF line,QGraphicsItem* parentItem) :CGraphic(parentItem)
{
	m_SceneTLx = line.x();
	m_SceneTLy = line.y();
	m_SceneWidth = line.width();
	m_SceneHeight = line.height();
}

CGraphicLine::~CGraphicLine() {}

void CGraphicLine::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
	// 设置画笔和填充颜色为红色
	painter->save();
	painter->setPen(QPen(m_color, 2));
	painter->setBrush(QBrush(m_color));

	//计算两个线的位置
	as::Point p1(m_SceneTLx - m_SceneWidth, m_SceneTLy - m_SceneHeight);
	as::Point p2(m_SceneTLx + m_SceneWidth, m_SceneTLy + m_SceneHeight);
	as::Point p3(m_SceneTLx - m_SceneWidth, m_SceneTLy + m_SceneHeight);
	as::Point p4(m_SceneTLx + m_SceneWidth, m_SceneTLy - m_SceneHeight);

	painter->drawLine(p1.x, p1.y, p2.x, p2.y);
	painter->drawLine(p3.x, p3.y, p4.x, p4.y);

	painter->restore();
}

void CGraphicLine::SetParameter(double sx, double sy, double width, double height)
{
	m_SceneTLx = sx;
	m_SceneTLy = sy;
	m_SceneWidth = width;
	m_SceneHeight = height;
}

QRectF CGraphicLine::boundingRect() const
{
	return QRectF(m_SceneTLx, m_SceneTLy, m_SceneWidth, m_SceneHeight);
}

