#include "ImportCADDialog.h"
#include "ui_ImportCADDialog.h"
#include "as/LogManager.hpp"
//#include "module/common/OperationCheckDialog.h"
//QT
#include <QSettings>
#include <QFileDialog>
#include <QMenu>

ImportCADDialog::ImportCADDialog(std::string filepath, std::string seperator, int block_id, QWidget *parent) :
    QDialog(parent, Qt::CustomizeWindowHint | Qt::WindowTitleHint /*| Qt::FramelessWindowHint*/ ),
    ui(new Ui::ImportCADDialog),
    m_cadfile(filepath),
    m_blockid(block_id)
{
    ui->setupUi(this);
    iniDialog();
    iniConnect();
}

ImportCADDialog::~ImportCADDialog()
{
    as::OperateLogfunc::GetInstance().windowsCloseRecord("导入CAD文件", "CAD文件数据转换预览");
    delete ui;
}

//初始化会话框
void ImportCADDialog::iniDialog()
{
    this->setWindowTitle(QString::fromLocal8Bit("CAD文件数据转换"));
    
    // ======= 列表初始化显示 =======
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //导入文件预览
    openfiles(m_cadfile);

    // ======= 数据转换信息 =======
    // 转换前坐标系
    ui->comboBox_coor1->clear();
   
    ui->comboBox_coor2->blockSignals(false);
}

//初始化Connect函数
void ImportCADDialog::iniConnect()
{

    //导入操作
    if (m_blockid == !INT_MAX)
    {
        ui->PBtn_Turninto->setEnabled(false);
        //导入到块
        connect(ui->PBtn_ImportCAD, static_cast<void (QPushButton::*)(bool)>(&QPushButton::clicked), this, [this](bool checked)
            {
                as::OperateLogfunc::GetInstance().InfoClickRecord(ui->PBtn_ImportCAD->text().toLocal8Bit().data(), __LINE__);
                Q_UNUSED(checked);
                QVariant datavar;
                try
                {
                    
                }
                catch (...)
                {
                    this->reject();
                    as::SoftwareLogfunc::GetInstance().LeaveFunction("ImportCADDialog::iniConnect", "ImportCADialog.cpp", __LINE__);
                }
            });
    }
    else
    {
        ui->PBtn_ImportCAD->setEnabled(false);
        //转进
        connect(ui->PBtn_Turninto, static_cast<void (QPushButton::*)(bool)>(&QPushButton::clicked), this, [this](bool checked)
            {
                as::OperateLogfunc::GetInstance().InfoClickRecord(ui->PBtn_Turninto->text().toLocal8Bit().data(), __LINE__);
                Q_UNUSED(checked);
                try
                {
                    string fileformat = m_cadfile.substr(m_cadfile.size() - 3);
                    //将大写字母变为小写字母
                    transform(fileformat.begin(), fileformat.end(), fileformat.begin(), ::tolower);
                   
                }
                catch (...)
                {
                    this->reject();
                    as::SoftwareLogfunc::GetInstance().LeaveFunction("ImportCADDialog::iniConnect", "ImportCADialog.cpp", __LINE__);
                }
            });
    }

    //关闭窗口
    connect(ui->PBtn_cancel, static_cast<void (QPushButton::*)(bool)>(&QPushButton::clicked), this, [this](bool checked)
        {
            as::OperateLogfunc::GetInstance().InfoClickRecord(ui->PBtn_cancel->text().toLocal8Bit().data(), __LINE__);
            Q_UNUSED(checked);

            this->reject();
        });
    
}

as::APIErrCode ImportCADDialog::GetResult()
{
    return result_importCadresult;
}

//解析文件函数
void ImportCADDialog::openfiles(std::string FilePath)
{
    cad_file = FilePath;
    //获取文件类型
    string filetype = cad_file.substr(cad_file.size() - 3);
    //获取CAD文本
    shared_ptr<vector<vector<string>>> list;

    int max_size = 0;//声明最大列数
    for (int i = 0; i < list->size(); i++)
    {
        if (list->at(i).size() > max_size)
        {
            max_size = list->at(i).size();
        }
    }
    if (list == nullptr)
        return;
    //设置表格行数
    ui->tableWidget->setRowCount(list->size());
    ui->tableWidget->blockSignals(true);
    if (list->size() > 0)
    {
        //设置表格列数
        //ui->tableWidget->setColumnCount(list->at(0).size());
        ui->tableWidget->setColumnCount(max_size);
        for (size_t col = 0; col < ui->tableWidget->columnCount(); col++)
        {
           
        }
    }
    //刷新表格
    for (size_t row = 0; row < ui->tableWidget->rowCount(); row++)
    {
        for (size_t col = 0; col < ui->tableWidget->columnCount(); col++)
        {
            ui->tableWidget->setItem(row, col, new QTableWidgetItem(QString::fromLocal8Bit(list->at(row).at(col).c_str())));
            ui->tableWidget->item(row, col)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);  // 居中
        }
    }
    ui->tableWidget->blockSignals(false);
}
