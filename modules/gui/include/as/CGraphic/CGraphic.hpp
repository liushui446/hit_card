#include <QObject>
#include <QGraphicsObject>
#include <QGraphicsSceneEvent>
#include <QPainter>
#include <QCursor>
#include <QMouseEvent>
#include "as/CommonCore.hpp"
#include <QtCore/qmath.h>
#include "as\ImportPadData.hpp"
namespace as
{
	// ָ����ǰ�����ͼԪ����
	enum class MyItemType
	{
		My_Item = QGraphicsItem::UserType + 1
		, My_Scatter
		, My_Roi
	};

	class AS_EXPORTS CGraphic: public QGraphicsObject
	{
		Q_OBJECT 

	public:
		CGraphic(QGraphicsItem* parentItem = nullptr);
		~CGraphic() override;

		void SetColor(QColor color);

		QRectF miniboundingRect() const;
		void SetParameters(double sx, double sy, double width, double height);

		void SetAngle(double angle);
		std::vector<double> GetParameter(void);

		std::vector<CGraphic*>& GetCGraphics();

		inline double GetSceneTLx(void) { return m_SceneTLx; }
		inline double GetSceneTLy(void) { return m_SceneTLy; }
		inline double GetSceneWidth(void) { return m_SceneWidth; }
		inline double GetSceneHeight(void) { return m_SceneHeight; }
		inline double GetSceneAngle(void) { return m_SceneAngle; }
	protected:
		QColor m_color;

		double m_SceneTLx;// �����Ѿ�ת��Ϊ�����е����Ͻ�����
		double m_SceneTLy;
		double m_SceneWidth;
		double m_SceneHeight;
		double m_SceneAngle;
		double m_OffsetX;
		double m_OffsetY;

	protected:
		//���ڴ洢���ƶ�������о�����
		std::vector<CGraphic*> m_pgAllCGraphic;

	public:
		void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
		void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
		void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;


	};

	class CGraphicRect : public CGraphic
	{
		Q_OBJECT

	public:
		CGraphicRect(QRectF rt, QGraphicsItem* parentItem = nullptr);
		CGraphicRect() = default;
		~CGraphicRect() override;

		virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);

		void SetParameter(double sx, double sy, double width, double height);
		QRectF GetParameter();
		QRectF boundingRect() const override;


	protected:
		double m_SceneTLx;// �����Ѿ�ת��Ϊ�����е����Ͻ�����
		double m_SceneTLy;
		double m_SceneWidth;
		double m_SceneHeight;

	public:
		/*void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
		void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
		void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;*/

	};

	class CGraphicCircle :public CGraphic
	{
		Q_OBJECT

	public:
		CGraphicCircle(QRectF circle, QGraphicsItem* parentItem = nullptr);
		CGraphicCircle() = default;
		~CGraphicCircle()override;
		virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);
		void SetParameter(double sx, double sy, double width, double height);
		QRectF boundingRect() const override;

	protected:
		double m_dCenterx; //x��������
		double m_dCentery; //y��������
		double m_dIndiameter; //�⾶
		double m_dOutdiameter; //�ھ�
	};

	class CGraphicOval :public CGraphic
	{
		Q_OBJECT

	public:
		CGraphicOval(QRectF oval, QGraphicsItem* parentItem = nullptr);
		CGraphicOval() = default;
		~CGraphicOval()override;
		virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);
		void SetParameter(double sx, double sy, double width, double height);
		QRectF boundingRect() const override;

	protected:
		double m_dCenterx; //x��������
		double m_dCentery; //y��������
		double m_dWidth; //��Բ��
		double m_dHeight; //��Բ��
	};

	class CGraphicPolygon : public CGraphic
	{
		Q_OBJECT
	public:
		CGraphicPolygon(QRectF polygon, QGraphicsItem* parentItem = nullptr);
		~CGraphicPolygon()override;
		virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);
		void SetParameter(double sx, double sy, double width, double height);
		QRectF boundingRect() const override;

	protected:
		double m_dCenterx;//x��������
		double m_dCentery;
		double m_dWidth;
		double m_dHeight;
	};

	class CGraphicLine : public CGraphic
	{
		Q_OBJECT
	public:
		CGraphicLine(QRectF line, QGraphicsItem* parentItem = nullptr);
		~CGraphicLine()override;
		virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);
		void SetParameter(double sx, double sy, double width, double height);
		QRectF boundingRect() const override;

	protected:
		double m_SceneTLx = 5;// �����Ѿ�ת��Ϊ�����е����Ͻ�����
		double m_SceneTLy = 5;
		double m_SceneWidth = 5;
		double m_SceneHeight = 5;
	};
}
