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
    //������UI��ʼ��
    void iniUI();
    //��������Connect��ʼ��
   
protected:
    Ui::MainWindow* m_ui;
    items::VisGraphicsScene* m_scene;          // ����
    items::VisGraphicsView* m_graphicsView;    // �Ӵ�
   
signals:

private slots:
    

private:
    //=================Dialog==================//
  

    //=================Process==================//
    as::MainWindowProcess m_cMainWindowProcess;    

    //=================Parameter================//
    string m_strCurGerberLayer;                   //��ǰGerber������
    int m_CurGerLayerIndex;                       //��ǰѡ��Gerber��
    string m_stCurrentGroup;                      //��ǰ�������
    vector<string> m_GroupArray;                  //�����б�
    

    //===============MenuContext================//
    QAction* m_Action_AllSelect;          //ȫѡ
    QAction* m_Action_AllNotSelect;       //ȫ��ѡ 
    QAction* m_Action_DirectionSelection; //��ѡ
    QAction* m_Action_ActualSize;         //ʵ�ʳߴ�
    QAction* m_Action_Rotate;             //��ת

    QAction* m_Action_Rotate90;          //��ת90��
    QAction* m_Action_Rotate180;         //��ת180��
    QAction* m_Action_Rotate270;         //��ת270��

    bool isRectangleDrawn = false;
    bool m_isPushButton5Locked = false;

    bool m_coorbool = false;        //�������flag
    //ѡ�еĺ���id�洢
    vector<DWORD> m_SelectPad_Allid;
    //ѡ�е�cad��洢
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
    double m_scale;//�̶� �̶�10

    double m_positionX;//move�ƶ�λ��x
    double m_positionY;//move�ƶ�λ��y

};

#endif