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

        void setClickComponent(bool _drawing);  //设置鼠标点击标识
        bool getClickComponent(); //获取鼠标点击标识
        void setMarqueeIdf(bool Idf);//框选后标识
        void setMarkDialog(bool mark); //设置mark点打开界面标识
        //框选后标识
        void setBackgroundImage(const QPixmap& _pixmap, double _scaleX, double _scaleY);
    protected:
        void drawBackground(QPainter* painter, const QRectF& rect) override;

    signals:
        //鼠标响应事件位置发送
        void sendScenePosData(QPointF);
        //鼠标点击ng类型事件默认矩形位置发送
        void sendSubboxPosData(QPointF);
        //发送框选参数
        void sendSceneRectData(QRectF _t1);
        //界面坐标位置显示
        void sendScenePosLable(double dx, double dy);
    signals:
        //注册元件后右键元件框
        void sendRightComponent(QPointF pt);
        //注册元件后左键元件框
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
        EmDirection region(const QPointF& point);   //根据鼠标位置设置鼠标形状
        void sendFramePressEvent(const QPointF& mousePoint); //鼠标发送
        void sendFrameMoveEvent(const QPointF& mousePoint); //鼠标移动
        void changeFrameMouseShape(const QPointF& mousePoint); // 更改框架鼠标形状
        void sendFrameReleaseEvent(const QPointF& mousePoint); // 鼠标释放
    public slots:
        void mousePressEvent(QGraphicsSceneMouseEvent* event) override;//鼠标按下
        void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;//鼠标释放
        void mouseMoveEvent(QGraphicsSceneMouseEvent* event)override;//鼠标移动
        void mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event) override;//鼠标双击
        //void paintRect(const QPointF& current);
        bool getResponseEnable(); //获取鼠标相应
        void setResponseEnable(bool enable); //设置鼠标相应
        void setFrameEnable(bool enable); //设置鼠标启用
        void deleteFrameEnable(bool enable);
        void Rect_position(bool enable); //矩形位置

    private:
        bool m_bPainterPressed;        //是否正在绘制
        bool m_bMovedPressed;          //是否正在拖动
        bool m_bScalePressed;          //是否正在缩放大小

        QPointF m_paintStartPoint;      //绘制的初始位置
        QPointF m_moveStartPoint;       //拖动的初始位置
        QPointF m_mouseCurrentPoint; //鼠标当前位置
        EmDirection m_emCurDir;        //拖动的方向
        QRectF m_roiRect;                    //绘制的ROI
        QRectF m_roiRect_out;                    //绘制的ROI
        QRectF m_roiRect_inner;
        QRectF m_roiRect_temp;
        QPointF m_center;                  //ROI中心
        //鼠标当前形态
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

        bool mouseResponse;//鼠标响应
        bool mouseFrame;//鼠标框
        bool isRectangleDrawn_scene;//矩形绘制场景
        bool isRectangle_out; //矩形输出
        bool mouseClickComponent;
        bool marqueeIdf;//框选后标识

        bool markDialog = false;
    };
}