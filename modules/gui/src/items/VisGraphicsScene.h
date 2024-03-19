#pragma once

#include "items_global.h"
// Qt
#include <QGraphicsScene>
#include <QMutex>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsScene>

namespace items
{
    /***************************************Fov Sence***********************************************/
    class VisGraphicsScene : public QGraphicsScene
    {
        Q_OBJECT

    public:
        explicit VisGraphicsScene(QWidget* parent = nullptr);
        bool getm_bMovedPressed();

        void setClickComponent(bool _drawing);  //�����������ʶ
        bool getClickComponent(); //��ȡ�������ʶ
        void setMarqueeIdf(bool Idf);//��ѡ���ʶ
        void setMarkDialog(bool mark); //����mark��򿪽����ʶ
        //��ѡ���ʶ
        void setBackgroundImage(const QPixmap& _pixmap, double _scaleX, double _scaleY);
    protected:
        void drawBackground(QPainter* painter, const QRectF& rect) override;

    signals:
        //�����Ӧ�¼�λ�÷���
        void sendScenePosData(QPointF);
        //�����ng�����¼�Ĭ�Ͼ���λ�÷���
        void sendSubboxPosData(QPointF);
        //���Ϳ�ѡ����
        void sendSceneRectData(QRectF _t1);
        //��������λ����ʾ
        void sendScenePosLable(double dx, double dy);
    signals:
        //ע��Ԫ�����Ҽ�Ԫ����
        void sendRightComponent(QPointF pt);
        //ע��Ԫ�������Ԫ����
        void sendLeftComponent(QPointF pt);

    private:
        enum EmDirection
        {
            DIR_TOP = 0,
            DIR_BOTTOM,
            DIR_LEFT,
            DIR_RIGHT,
            DIR_LEFTTOP,
            DIR_LEFTBOTTOM,
            DIR_RIGHTTOP,
            DIR_RIGHTBOTTOM,
            DIR_MIDDLE,
            DIR_NONE
        };
        EmDirection region(const QPointF& point);   //�������λ�����������״
        void sendFramePressEvent(const QPointF& mousePoint); //��귢��
        void sendFrameMoveEvent(const QPointF& mousePoint); //����ƶ�
        void changeFrameMouseShape(const QPointF& mousePoint); // ���Ŀ�������״
        void sendFrameReleaseEvent(const QPointF& mousePoint); // ����ͷ�
    public slots:
        void mousePressEvent(QGraphicsSceneMouseEvent* event) override;//��갴��
        void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;//����ͷ�
        void mouseMoveEvent(QGraphicsSceneMouseEvent* event)override;//����ƶ�
        void mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event) override;//���˫��
        //void paintRect(const QPointF& current);
        bool getResponseEnable(); //��ȡ�����Ӧ
        void setResponseEnable(bool enable); //���������Ӧ
        void setFrameEnable(bool enable); //�����������
        void deleteFrameEnable(bool enable);
        void Rect_position(bool enable); //����λ��

    private:
        bool m_bPainterPressed;        //�Ƿ����ڻ���
        bool m_bMovedPressed;          //�Ƿ������϶�
        bool m_bScalePressed;          //�Ƿ��������Ŵ�С

        QPointF m_paintStartPoint;      //���Ƶĳ�ʼλ��
        QPointF m_moveStartPoint;       //�϶��ĳ�ʼλ��
        QPointF m_mouseCurrentPoint; //��굱ǰλ��
        EmDirection m_emCurDir;        //�϶��ķ���
        QRectF m_roiRect;                    //���Ƶ�ROI
        QRectF m_roiRect_out;                    //���Ƶ�ROI
        QRectF m_roiRect_inner;
        QRectF m_roiRect_temp;
        QPointF m_center;                  //ROI����
        //��굱ǰ��̬
        enum ScatterCursorShape {
            ITEM_NO_SELECT,
            ITEM_SELECT,
            MOVE_CURSOR,
            ROTATE_ASSURE_CURSOR,

        };
    private:
        QPixmap m_pixmap;
        double m_scaleX; ///< mm per pixel
        double m_scaleY;
        QMutex tex;
        double delta_x;
        double delta_y;

        bool mouseResponse;//�����Ӧ
        bool mouseFrame;//����
        bool isRectangleDrawn_scene;//���λ��Ƴ���
        bool isRectangle_out; //�������
        bool mouseClickComponent;
        bool marqueeIdf;//��ѡ���ʶ

        bool markDialog = false;
    };
}