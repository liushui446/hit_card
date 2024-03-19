#include "mainwindow.h"
#include "ui_mainwindow.h"

//界面


//3rdpart
#include "items/VisGraphicsScene.h"
#include "items/VisGraphicsView.h"
#include "as/LogManager.hpp"

// Qt
#include <QTimer>
#include <QMenuBar>
#include <QDebug>
#include <QFileDialog>
#include <QMainWindow>
#include <QToolBar>
#include <QWheelEvent>
#include <QtMath>
#include <QGraphicsSceneMouseEvent>
#include <QHeaderView>
#include <QFuture>
#include <QtConcurrent/QtConcurrent>
#include <QDesktopWidget>
#include <QPolygonF>
#include <QStatusBar>
#include <QApplication>
#include <QTableWidgetItem>

// OpenCV
#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/opencv.hpp>

//其他
#include "as/CommonCore.hpp"
#include "as/common/CommonProcess.h"
#include "utils/include/AutoLoadQss.h"
#include <direct.h>
#include <memory>
#include <qlayout.h>


using namespace items;
using namespace cv;

MainWindow::MainWindow(QWidget* parent) :
	QMainWindow(parent),
	m_ui(new Ui::MainWindow),
	m_scene(new VisGraphicsScene(this)),
	m_graphicsView(new VisGraphicsView(this)),
	m_scale(10)
{
	m_ui->setupUi(this);
	//主界面UI初始化
	iniUI();
	QScreen* screen = QGuiApplication::primaryScreen();
	//QRect screenRect = screen->availableVirtualGeometry();//自适应
	this->move(0, 0);
	setWindowState(Qt::WindowMaximized);
}

MainWindow::~MainWindow()
{
	delete m_ui;
}

//主界面UI初始化
void MainWindow::iniUI()
{
	auto qssLoader = new as::AutoLoadQss(this);
	qssLoader->bindAppAndQss(this, "res/SpiStyleSheet.qss");

	//组别名添加
	m_GroupArray.push_back("PadGroup");
	m_GroupArray.push_back("PartGroup");
	m_GroupArray.push_back("ArrayGroup");
	m_GroupArray.push_back("PackageGroup");
	m_GroupArray.push_back("MarkGroup");
	m_GroupArray.push_back("SamePadGroup");
	m_GroupArray.push_back("SameArrayGroup");
	m_GroupArray.push_back("PadAreaGroup");
	m_stCurrentGroup = m_GroupArray[0];
	//手动框选绘制ROI
	//===================菜单栏=======================//
	//m_ui->menu_1->menuAction()->setVisible(false);
	m_ui->action_Algorithm->setVisible(false);
	m_ui->action_ImportImg->setVisible(false);

	//====================视窗=====================//
	m_graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	m_graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	m_graphicsView->setFrameShape(QFrame::NoFrame);
	m_graphicsView->setScene(m_scene);
	m_graphicsView->setAlignment(Qt::AlignCenter);
	m_ui->verticalLayout->addWidget(m_graphicsView);
	m_graphicsView->setContextMenuPolicy(Qt::CustomContextMenu);

	m_graphicsView->setZoom(150);
	//m_graphicsView->centerOn(0, 0);
}
