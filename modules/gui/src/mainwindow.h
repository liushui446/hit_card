#ifndef AS_MAINWINDOW_H
#define AS_MAINWINDOW_H
//Core
#include "as/CommonCore.hpp"

//dialog

//Process
#include "as/MainWindowProcess.hpp"

//QT
#include <QLabel>
#include <QMutex>
#include <QMainWindow>
#include <QStackedWidget>
#include <QTableWidget>
#include <QStringList>
#include <QLineEdit>
#include <QMenuBar>

using namespace std;

namespace Ui {
    class MainWindow;
}
namespace items
{
    class VisGraphicsScene;
    class VisGraphicsView;
}
// Qt
class QTimer;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    virtual ~MainWindow();
    //主界面UI初始化
    void iniUI();
    //界面内容Connect初始化
   
protected:
    Ui::MainWindow* m_ui;
    items::VisGraphicsScene* m_scene;          // 场景
    items::VisGraphicsView* m_graphicsView;    // 视窗
   
signals:

private slots:
    

private:
    //=================Dialog==================//
  

    //=================Process==================//
    as::MainWindowProcess m_cMainWindowProcess;    

    //=================Parameter================//
    string m_strCurGerberLayer;                   //当前Gerber层名称
    int m_CurGerLayerIndex;                       //当前选中Gerber层
    string m_stCurrentGroup;                      //当前组别名称
    vector<string> m_GroupArray;                  //组名列表
    

    //===============MenuContext================//
    QAction* m_Action_AllSelect;          //全选
    QAction* m_Action_AllNotSelect;       //全不选 
    QAction* m_Action_DirectionSelection; //反选
    QAction* m_Action_ActualSize;         //实际尺寸
    QAction* m_Action_Rotate;             //旋转

    QAction* m_Action_Rotate90;          //旋转90度
    QAction* m_Action_Rotate180;         //旋转180度
    QAction* m_Action_Rotate270;         //旋转270度

    bool isRectangleDrawn = false;
    bool m_isPushButton5Locked = false;

    bool m_coorbool = false;        //坐标对齐flag
    //选中的焊盘id存储
    vector<DWORD> m_SelectPad_Allid;
    //选中的cad框存储
    struct CADtemp
    {
        int m_CAD_block_id = -1;
        int m_CAD_array_id = -1;
        int m_CAD_compo_id = -1;
        as::Point m_CAD_compo_Pos;
    };
    CADtemp cad;

protected:
    as::PadShape shape;
    QPoint padpos;
    double angle;
    double height;
    double width;
    double indiameter;
    double outdiameter;
    double m_scale;//刻度 固定10

    double m_positionX;//move移动位置x
    double m_positionY;//move移动位置y

};

#endif