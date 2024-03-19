#include "BenchmarkDialog.h"
#include "ui_BenchmarkDialog.h"
//#include "src/module/common/OperationCheckDialog.h"
#include <QtConcurrent/qtconcurrentrun.h>
#include <QFuture>
#include <Qtimer>
#include <QStandardItemModel>
#include "as/LogManager.hpp"

using namespace items;
//#include "signal_transmitter.h"
//#include "as/IniPara.hpp"

BenchmarkDialog::BenchmarkDialog(QWidget *parent)
    : ASQDialog(parent, Qt::CustomizeWindowHint | Qt::WindowTitleHint), 
	m_ui(new Ui::BenchmarkDialog),
    mark_fov_graphicsView(new VisGraphicsView(this)),
    mark_fov_scene(new VisGraphicsScene(this))
{
	m_ui->setupUi(this);
    mark_fov_scene->setMarkDialog(true);
    InitUI();
    InitConnect();
}

BenchmarkDialog::~BenchmarkDialog()
{
	delete m_ui;
}

void BenchmarkDialog::InitUI()
{
    //================块拼初始化===============//

    //外光内光数值初始化
    m_ui->label_10->setText(QString::number(0));
    m_ui->label_26->setText(QString::number(0));

    //旋转角度初始化
    m_ui->comboBox_Rotate->addItem(QString::number(0));
    m_ui->comboBox_Rotate->addItem(QString::number(90));
    m_ui->comboBox_Rotate->addItem(QString::number(180));
    m_ui->comboBox_Rotate->addItem(QString::number(270));
    m_ui->comboBox_Rotate->setCurrentIndex(0);

    //================按钮初始化设置===============//
    //确认按钮图标设置
    m_ui->toolButton_ok->setIconSize(QSize(32, 32));
    m_ui->toolButton_ok->setIcon(QIcon("res/button/checkall.svg"));
    m_ui->toolButton_ok->setText(QString::fromLocal8Bit("更新"));
    m_ui->toolButton_ok->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    //取消按钮图标设置
    m_ui->toolButton_cancel->setIconSize(QSize(32, 32));
    m_ui->toolButton_cancel->setIcon(QIcon("res/button/cancel.svg"));
    m_ui->toolButton_cancel->setText(QString::fromLocal8Bit("取消"));
    m_ui->toolButton_cancel->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    //===================Mark点形状====================//
    m_ui->comboBox_Shape->addItems(MarkTypeList);

    //=============== MARK点类型 ==================//
    m_ui->comboBox_positioningType->addItem(QIcon(QString::fromLocal8Bit("res/dialog/Board/位置类型1.png")), "");
    m_ui->comboBox_positioningType->addItem(QIcon(QString::fromLocal8Bit("res/dialog/Board/位置类型2.png")), "");
    m_ui->comboBox_positioningType->addItem(QIcon(QString::fromLocal8Bit("res/dialog/Board/位置类型3.png")), "");
    m_ui->comboBox_positioningType->addItem(QIcon(QString::fromLocal8Bit("res/dialog/Board/位置类型4.png")), "");
    m_ui->comboBox_positioningType->addItem(QIcon(QString::fromLocal8Bit("res/dialog/Board/位置类型5.png")), "");
    m_ui->comboBox_positioningType->addItem(QIcon(QString::fromLocal8Bit("res/dialog/Board/位置类型6.png")), "");
    m_ui->comboBox_positioningType->addItem(QIcon(QString::fromLocal8Bit("res/dialog/Board/位置类型7.png")), "");
    m_ui->comboBox_positioningType->addItem(QIcon(QString::fromLocal8Bit("res/dialog/Board/位置类型8.png")), "");
    m_ui->comboBox_positioningType->addItem(QIcon(QString::fromLocal8Bit("res/dialog/Board/位置类型9.png")), "");
    m_ui->comboBox_positioningType->setIconSize(QSize(38, 38));
    m_ui->comboBox_positioningType->setSizeAdjustPolicy(QComboBox::AdjustToContents);

    // 位置类型(使能界面功能)
    as::BoardMarkType index;
    int mark_num = 0;
    if (index == as::BoardMarkType::FIDUCIAL_NONE)
    {
        m_ui->toolButton_move->setEnabled(false);
        m_ui->toolButton_move->setEnabled(false);
        m_ui->toolButton_get->setEnabled(false);
        m_ui->lineEdit_Score->setEnabled(false);
        m_ui->lineEdit_CriticalValue->setEnabled(false);
        m_ui->pushButton_Binary->setEnabled(false);
        m_ui->checkBox_auto->setEnabled(false);
        m_ui->lineEdit_ShapeX->setEnabled(false);
        m_ui->lineEdit_ShapeY->setEnabled(false);
        m_ui->lineEdit_Arm->setEnabled(false);
        m_ui->comboBox_Polarity->setEnabled(false);
        m_ui->lineEdit_Thickness->setEnabled(false);
        m_ui->comboBox_Rotate->setEnabled(false);
        m_ui->lineEdit_AreaX->setEnabled(false);
        m_ui->lineEdit_AreaY->setEnabled(false);
        m_ui->lineEdit_AreaWidth->setEnabled(false);
        m_ui->lineEdit_AreaHeight->setEnabled(false);
        m_ui->pushButton_Outline->setEnabled(false);
        m_ui->pushButton_Scan->setEnabled(false);
        m_ui->pushButton_AutoAdjust->setEnabled(false);
        m_ui->pushButton_Test->setEnabled(false);
        m_ui->lineEdit_Position->setEnabled(false);
        m_ui->comboBox_cantilever->setEnabled(false);
        m_ui->horizontalSlider_InLight->setEnabled(false);
        m_ui->horizontalSlider_OutLight->setEnabled(false);
        m_ui->label_10->setEnabled(false);
        m_ui->label_26->setEnabled(false);
    }
    else
    {
        m_ui->tableWidget_MarkPos->selectRow(0); //设置第1行为选中行
        m_ui->toolButton_move->setEnabled(true);
        m_ui->toolButton_get->setEnabled(true);
        m_ui->lineEdit_Score->setEnabled(true);
        m_ui->lineEdit_CriticalValue->setEnabled(true);
        m_ui->pushButton_Binary->setEnabled(true);
        m_ui->checkBox_auto->setEnabled(true);
        m_ui->lineEdit_ShapeX->setEnabled(true);
        m_ui->lineEdit_ShapeY->setEnabled(true);
        m_ui->lineEdit_Arm->setEnabled(true);
        m_ui->comboBox_Polarity->setEnabled(true);
        m_ui->lineEdit_Thickness->setEnabled(true);
        m_ui->comboBox_Rotate->setEnabled(true);
        m_ui->lineEdit_AreaX->setEnabled(true);
        m_ui->lineEdit_AreaY->setEnabled(true);
        m_ui->lineEdit_AreaWidth->setEnabled(true);
        m_ui->lineEdit_AreaHeight->setEnabled(true);
        m_ui->pushButton_Outline->setEnabled(true);
        m_ui->pushButton_Scan->setEnabled(true);
        m_ui->pushButton_AutoAdjust->setEnabled(true);
        m_ui->pushButton_Test->setEnabled(true);
        m_ui->lineEdit_Position->setEnabled(true);
        m_ui->comboBox_cantilever->setEnabled(true);
        m_ui->horizontalSlider_InLight->setEnabled(true);
        m_ui->horizontalSlider_OutLight->setEnabled(true);
        m_ui->label_10->setEnabled(true);
        m_ui->label_26->setEnabled(true);
    }

    //===================== mark点位置表格 ======================//
    //设置列宽
    m_ui->tableWidget_MarkPos->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    //========================== FOV ===========================//
    mark_fov_graphicsView->fitInView(mark_fov_graphicsView->sceneRect(), Qt::KeepAspectRatio);	 // 将视窗的大小调整为适合内容的大小
    mark_fov_graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);//不显示滑条
    mark_fov_graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);//不显示滑条
    mark_fov_graphicsView->setFrameShape(QFrame::NoFrame);
    mark_fov_graphicsView->setScene(mark_fov_scene);//view,scene连接
    mark_fov_graphicsView->setSceneRect(mark_fov_scene->itemsBoundingRect());	// 设置视窗的场景矩形范围以包含整个内容
    mark_fov_graphicsView->setAlignment(Qt::AlignCenter);
    m_ui->horizontalLayout->addWidget(mark_fov_graphicsView);

}

void BenchmarkDialog::InitConnect()
{
    // ==== 位置类型 下拉选择 更新标记位置 ====
    connect(m_ui->comboBox_positioningType, static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged), this, [this]()
        {
            as::OperateLogfunc::GetInstance().InfoComRecord("位置类型", QString::number(m_ui->comboBox_positioningType->currentIndex()).toStdString(), __LINE__);
            //m_ui->tableWidget_Markdata->removeCellWidget(prerow, precol);
            int block_id = m_ui->comboBox_Block->currentIndex() + 1;
            int array_id = m_ui->comboBox_Array->currentText().toInt();
            int num = m_ui->comboBox_positioningType->currentIndex();
            while (num > 4)		num -= 4;
            int posType_index = m_ui->comboBox_positioningType->currentIndex();
            //板子Mark类型
            as::BoardMarkType boardtype;
            if (posType_index == 0)
            {
                boardtype = as::BoardMarkType::FIDUCIAL_NONE;
                m_ui->toolButton_move->setEnabled(false);
                m_ui->toolButton_get->setEnabled(false);
                m_ui->lineEdit_Score->setEnabled(false);
                m_ui->lineEdit_CriticalValue->setEnabled(false);
                m_ui->pushButton_Binary->setEnabled(false);
                m_ui->checkBox_auto->setEnabled(false);
                m_ui->lineEdit_ShapeX->setEnabled(false);
                m_ui->lineEdit_ShapeY->setEnabled(false);
                m_ui->lineEdit_Arm->setEnabled(false);
                m_ui->comboBox_Polarity->setEnabled(false);
                m_ui->lineEdit_Thickness->setEnabled(false);
                m_ui->comboBox_Rotate->setEnabled(false);
                m_ui->lineEdit_AreaX->setEnabled(false);
                m_ui->lineEdit_AreaY->setEnabled(false);
                m_ui->lineEdit_AreaWidth->setEnabled(false);
                m_ui->lineEdit_AreaHeight->setEnabled(false);
                m_ui->pushButton_Outline->setEnabled(false);
                m_ui->pushButton_Scan->setEnabled(false);
                m_ui->pushButton_AutoAdjust->setEnabled(false);
                m_ui->pushButton_Test->setEnabled(false);
                m_ui->lineEdit_Position->setEnabled(false);
                m_ui->comboBox_cantilever->setEnabled(false);
                m_ui->horizontalSlider_InLight->setEnabled(false);
                m_ui->horizontalSlider_OutLight->setEnabled(false);
                m_ui->label_10->setEnabled(false);
                m_ui->label_26->setEnabled(false);
               
            }
            else if (posType_index > 4)
            {
                boardtype = as::BoardMarkType::FIDUCIAL_ARRAY;
                m_ui->toolButton_move->setEnabled(true);
                m_ui->toolButton_get->setEnabled(true);
                m_ui->lineEdit_Score->setEnabled(true);
                m_ui->lineEdit_CriticalValue->setEnabled(true);
                m_ui->pushButton_Binary->setEnabled(true);
                m_ui->checkBox_auto->setEnabled(true);
                m_ui->lineEdit_ShapeX->setEnabled(true);
                m_ui->lineEdit_ShapeY->setEnabled(true);
                m_ui->lineEdit_Arm->setEnabled(true);
                m_ui->comboBox_Polarity->setEnabled(true);
                m_ui->lineEdit_Thickness->setEnabled(true);
                m_ui->comboBox_Rotate->setEnabled(true);
                m_ui->lineEdit_AreaX->setEnabled(true);
                m_ui->lineEdit_AreaY->setEnabled(true);
                m_ui->lineEdit_AreaWidth->setEnabled(true);
                m_ui->lineEdit_AreaHeight->setEnabled(true);
                m_ui->pushButton_Outline->setEnabled(true);
                m_ui->pushButton_Scan->setEnabled(true);
                m_ui->pushButton_AutoAdjust->setEnabled(true);
                m_ui->pushButton_Test->setEnabled(true);
                m_ui->lineEdit_Position->setEnabled(true);
                m_ui->comboBox_cantilever->setEnabled(true);
                m_ui->horizontalSlider_InLight->setEnabled(true);
                m_ui->horizontalSlider_OutLight->setEnabled(true);
                m_ui->label_10->setEnabled(true);
                m_ui->label_26->setEnabled(true);
            }
            else
            {
                boardtype = as::BoardMarkType::FIDUCIAL_GLOBAL;
                m_ui->toolButton_move->setEnabled(true);
                m_ui->toolButton_get->setEnabled(true);
                m_ui->lineEdit_Score->setEnabled(true);
                m_ui->lineEdit_CriticalValue->setEnabled(true);
                m_ui->pushButton_Binary->setEnabled(true);
                m_ui->checkBox_auto->setEnabled(true);
                m_ui->lineEdit_ShapeX->setEnabled(true);
                m_ui->lineEdit_ShapeY->setEnabled(true);
                m_ui->lineEdit_Arm->setEnabled(true);
                m_ui->comboBox_Polarity->setEnabled(true);
                m_ui->lineEdit_Thickness->setEnabled(true);
                m_ui->comboBox_Rotate->setEnabled(true);
                m_ui->lineEdit_AreaX->setEnabled(true);
                m_ui->lineEdit_AreaY->setEnabled(true);
                m_ui->lineEdit_AreaWidth->setEnabled(true);
                m_ui->lineEdit_AreaHeight->setEnabled(true);
                m_ui->pushButton_Outline->setEnabled(true);
                m_ui->pushButton_Scan->setEnabled(true);
                m_ui->pushButton_AutoAdjust->setEnabled(true);
                m_ui->pushButton_Test->setEnabled(true);
                m_ui->lineEdit_Position->setEnabled(true);
                m_ui->comboBox_cantilever->setEnabled(true);
                m_ui->horizontalSlider_InLight->setEnabled(true);
                m_ui->horizontalSlider_OutLight->setEnabled(true);
                m_ui->label_10->setEnabled(true);
                m_ui->label_26->setEnabled(true);
            }
        });

        //==== 块选择 刷新界面 ====
        connect(m_ui->comboBox_Block, QOverload<int>::of(&QComboBox::currentIndexChanged), [=](int index)
            {
                as::OperateLogfunc::GetInstance().InfoComRecord("块选择", m_ui->comboBox_Block->currentText().toLocal8Bit().data(), __LINE__);
            });


        //临界值
        connect(m_ui->lineEdit_CriticalValue, static_cast<void (QLineEdit::*)()>(&QLineEdit::editingFinished), this, [this]()
            {
                as::OperateLogfunc::GetInstance().InfoDataChangeRecord("临界值", m_ui->lineEdit_CriticalValue->text().toDouble(), __LINE__);
                int val = m_ui->lineEdit_CriticalValue->text().toDouble();
                //m_cBenchMarkProcess.
            });

        //自动
        connect(m_ui->checkBox_auto, static_cast<void (QCheckBox::*)(int)>(&QCheckBox::stateChanged), this, [this](int value)
            {
                as::OperateLogfunc::GetInstance().InfoClickRecord(m_ui->checkBox_auto->text().toLocal8Bit().data(), __LINE__);
                int val = value;

            });

        //位置
        connect(m_ui->lineEdit_Position, static_cast<void (QLineEdit::*)()>(&QLineEdit::editingFinished), this, [this]()
            {
                as::OperateLogfunc::GetInstance().InfoDataChangeRecord("位置", m_ui->lineEdit_Position->text().toDouble(), __LINE__);
                int val = m_ui->lineEdit_Position->text().toDouble();

            });

        //===================== 表格操作 =========================//
        //鼠标双击事件
        connect(m_ui->tableWidget_MarkPos, &QTableWidget::cellDoubleClicked, this, [&](int row, int col)
            {
                as::OperateLogfunc::GetInstance().InfoListChangeRecord("基准点位置", __LINE__);
                if (precol < 0 || prerow < 0)
                {
                    prerow = 0;
                    precol = 0;
                }
                if (col > 0)
                {
                    switch (col)
                    {
                    case 1:
                    case 2:
                    {
                        edit = new QLineEdit(this);
                        //this->edit->installEventFilter(this);
                        edit->setAttribute(Qt::WA_QuitOnClose);
                        QRegExp rx("^-?(99999|(([1-9]([0-9]?\\d{0,3}))|[0])(\\.\\d{1,3})?)$");
                        //edit->setStyleSheet("QLineEdit{border-width:0;border-style:outset}");
                        edit->setValidator(new QRegExpValidator(rx, this));
                        edit->setFocus();
                        QTimer::singleShot(0, edit, &QLineEdit::selectAll);
                        edit->setText(m_ui->tableWidget_MarkPos->item(row, col)->text());
                        edit->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);  // 居中
                        connect(edit, &QLineEdit::textChanged, this, [&](QString a)
                            {
                                m_ui->tableWidget_MarkPos->setItem(prerow, precol, new QTableWidgetItem(QString::number(a.toDouble(), 10, 3)));
                                m_ui->tableWidget_MarkPos->item(prerow, precol)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);  // 居中
                                int blockid = m_ui->comboBox_Block->currentIndex() + 1;
                                int arrayid = m_ui->comboBox_Array->currentIndex() + 1;
                                as::Point pos;
                                pos.x = m_ui->tableWidget_MarkPos->item(prerow, 1)->text().toDouble();
                                pos.y = m_ui->tableWidget_MarkPos->item(prerow, 2)->text().toDouble();
                               
                            });
                    }
                    break;
                    case 3:
                    {
                        edit = new QLineEdit(this);
                        this->edit->installEventFilter(this);
                        edit->setAttribute(Qt::WA_QuitOnClose);
                        QRegExp rx("^(40|([1-3]{1}[0-9]?)|[4-9]\d)$");
                        edit->setStyleSheet("QLineEdit{border-width:0;border-style:outset}");
                        edit->setValidator(new QRegExpValidator(rx, this));
                        edit->setFocus();
                        QTimer::singleShot(0, edit, &QLineEdit::selectAll);
                        edit->setText(m_ui->tableWidget_MarkPos->item(row, col)->text());
                        edit->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);  // 居中
                        connect(edit, &QLineEdit::textChanged, this, [&](QString a)
                            {
                                m_ui->tableWidget_MarkPos->setItem(prerow, precol, new QTableWidgetItem(QString::number(a.toDouble())));
                                m_ui->tableWidget_MarkPos->item(prerow, precol)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);  // 居中
                                int blockid = m_ui->comboBox_Block->currentIndex() + 1;
                                int arrayid = m_ui->comboBox_Array->currentIndex() + 1;
                                int mark_id = m_ui->tableWidget_MarkPos->item(prerow, 3)->text().toInt();
                                if (mark_id == 0)
                                {
                                    mark_id = 1;
                                    m_ui->tableWidget_MarkPos->item(prerow, 3)->setText(QString::number(1));
                                }
                                
                                OperateLogfunc::GetInstance().InfoDataChangeRecord("块" + to_string(blockid) + "拼板" + to_string(arrayid) + "基准点" + to_string(prerow + 1) + "类型", mark_id, __LINE__);
                                
                            });
                    }
                    break;
                    default:
                        break;
                    }
                    m_ui->tableWidget_MarkPos->removeCellWidget(prerow, precol);
                    m_ui->tableWidget_MarkPos->setCellWidget(row, col, edit);
                    prerow = row;//保存上一次点击的坐标
                    precol = col;
                }
                else if (col == 0)
                {
                    if (precol != 0)
                    {
                        m_ui->tableWidget_MarkPos->removeCellWidget(prerow, precol);
                        m_ui->tableWidget_MarkPos->clearFocus();
                    }
                    if (row != prerow || precol != col)
                    {
                        m_ui->tableWidget_MarkPos->removeCellWidget(prerow, precol);
                    }
                    prerow = row;//保存上一次点击的坐标
                    precol = col;
                }
            });

            //鼠标单击事件
            connect(m_ui->tableWidget_MarkPos, &QTableWidget::cellClicked, this, [&](int row, int col)
                {
                    if (col == 0)
                    {
                        m_ui->tableWidget_MarkPos->selectRow(row);
                    }
                    if (row != prerow || precol != col)
                    {
                        m_ui->tableWidget_MarkPos->removeCellWidget(prerow, precol);
                    }
                    
                    int current_block_id = m_ui->comboBox_Block->currentText().toInt();
                    int current_array_id = m_ui->comboBox_Array->currentText().toInt();
                    //emit ClickTableShowMark(current_block_id, current_array_id, row, m_MarkSettinProcess.GetMarkListData(current_block_id, current_array_id, row));
                });

        //===================== 操作按钮 =======================//
        //Move
        connect(m_ui->toolButton_move, static_cast<void (QToolButton::*)(bool)>(&QToolButton::clicked), this, [this](bool checked)
            {
                Q_UNUSED(checked);
                as::OperateLogfunc::GetInstance().InfoClickRecord(m_ui->toolButton_move->text().toLocal8Bit().data(), __LINE__);
                
            });

        //Get
        connect(m_ui->toolButton_get, static_cast<void (QToolButton::*)(bool)>(&QToolButton::clicked), this, [this](bool checked)
            {
                Q_UNUSED(checked);
                as::OperateLogfunc::GetInstance().InfoClickRecord(m_ui->toolButton_get->text().toLocal8Bit().data(), __LINE__);
                // 块|拼|元件
                int current_block_id = m_ui->comboBox_Block->currentText().toInt();
                int current_array_id = m_ui->comboBox_Array->currentText().toInt();
                int current_row = m_ui->tableWidget_MarkPos->currentRow();
                as::OperateLogfunc::GetInstance().InfoClickRecord(m_ui->toolButton_get->text().toLocal8Bit().data(), __LINE__);
                if (!as::CommonCheck::StateMachineCheck(false))
                {
                    return;
                }
                
                int item_row = m_ui->tableWidget_MarkPos->currentRow();
                int item_col = m_ui->tableWidget_MarkPos->currentColumn();
                if (item_row < 0)
                {
                    item_row = 0;
                }
                as::Point pos_get;
                //m_cBenchMarkProcess.GetMarkPos(m_intProgPanelSetProcess.GetBoardInitTheta(), current_block_id, current_array_id, aoi::CoordinateSystem::MechanicalCoorSystem, pos_get);
                if (item_col > 0 && item_col <= 3)
                {
                    m_ui->tableWidget_MarkPos->removeCellWidget(item_row, item_col);
                }
                double x = 0;
                double y = 0;
                as::Point roi_pos;
                double width = 0;
                double height = 0;
                //坐标转换
                //todo

                m_ui->tableWidget_MarkPos->item(item_row, 1)->setText(QString::number(pos_get.getPintX(), 10, 3));
                m_ui->tableWidget_MarkPos->item(item_row, 2)->setText(QString::number(pos_get.getPintY(), 10, 3));

                //保存
                int blockid = current_block_id + 1;
                as::Point pos;
                pos.x = m_ui->tableWidget_MarkPos->item(item_row, 1)->text().toDouble();
                pos.y = m_ui->tableWidget_MarkPos->item(item_row, 2)->text().toDouble();
                //m_cBenchMarkProcess.(blockid, item_row, pos.x);
                
                int mark_id = m_ui->tableWidget_MarkPos->item(item_row, 3)->text().toInt();
            });

        //Update
        connect(m_ui->toolButton_ok, static_cast<void (QToolButton::*)(bool)>(&QToolButton::clicked), this, [this](bool checked)
            {
                Q_UNUSED(checked);
                as::OperateLogfunc::GetInstance().InfoClickRecord(m_ui->toolButton_ok->text().toLocal8Bit().data(), __LINE__);
                m_cBenchMarkProcess.Update();
                this->accept();
            });

        //Cancel
        connect(m_ui->toolButton_cancel, static_cast<void (QToolButton::*)(bool)>(&QToolButton::clicked), this, [this](bool checked)
            {
                Q_UNUSED(checked);
                as::OperateLogfunc::GetInstance().InfoClickRecord(m_ui->toolButton_cancel->text().toLocal8Bit().data(), __LINE__);
                this->reject();
            });

        //Scan
        connect(m_ui->pushButton_Scan, static_cast<void (QPushButton::*)(bool)>(&QPushButton::clicked), this, [this](bool checked)
            {
                Q_UNUSED(checked);
                as::OperateLogfunc::GetInstance().InfoClickRecord(m_ui->pushButton_Scan->text().toLocal8Bit().data(), __LINE__);
            });

        //Test
        connect(m_ui->pushButton_Test, static_cast<void (QPushButton::*)(bool)>(&QPushButton::clicked), this, [this](bool checked)
            {
                Q_UNUSED(checked);
                as::OperateLogfunc::GetInstance().InfoClickRecord(m_ui->pushButton_Test->text().toLocal8Bit().data(), __LINE__);
            });

        //AutoAdjust
        connect(m_ui->pushButton_AutoAdjust, static_cast<void (QPushButton::*)(bool)>(&QPushButton::clicked), this, [this](bool checked)
            {
                Q_UNUSED(checked);
                as::OperateLogfunc::GetInstance().InfoClickRecord(m_ui->pushButton_AutoAdjust->text().toLocal8Bit().data(), __LINE__);
            });

        //Outline
        connect(m_ui->pushButton_Outline, static_cast<void (QPushButton::*)(bool)>(&QPushButton::clicked), this, [this](bool checked)
            {
                Q_UNUSED(checked);
                as::OperateLogfunc::GetInstance().InfoClickRecord(m_ui->toolButton_cancel->text().toLocal8Bit().data(), __LINE__);
            });


        //二进位
        connect(m_ui->pushButton_Binary, static_cast<void (QPushButton::*)(bool)>(&QPushButton::clicked), this, [this](bool checked)
            {
                Q_UNUSED(checked);
                as::OperateLogfunc::GetInstance().InfoClickRecord(m_ui->pushButton_Binary->text().toLocal8Bit().data(), __LINE__);
            });
}

