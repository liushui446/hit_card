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
    as::OperateLogfunc::GetInstance().windowsCloseRecord("����CAD�ļ�", "CAD�ļ�����ת��Ԥ��");
    delete ui;
}

//��ʼ���Ự��
void ImportCADDialog::iniDialog()
{
    this->setWindowTitle(QString::fromLocal8Bit("CAD�ļ�����ת��"));
    
    // ======= �б��ʼ����ʾ =======
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //�����ļ�Ԥ��
    openfiles(m_cadfile);

    // ======= ����ת����Ϣ =======
    // ת��ǰ����ϵ
    ui->comboBox_coor1->clear();
   
    ui->comboBox_coor2->blockSignals(false);
}

//��ʼ��Connect����
void ImportCADDialog::iniConnect()
{

    //�������
    if (m_blockid == !INT_MAX)
    {
        ui->PBtn_Turninto->setEnabled(false);
        //���뵽��
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
        //ת��
        connect(ui->PBtn_Turninto, static_cast<void (QPushButton::*)(bool)>(&QPushButton::clicked), this, [this](bool checked)
            {
                as::OperateLogfunc::GetInstance().InfoClickRecord(ui->PBtn_Turninto->text().toLocal8Bit().data(), __LINE__);
                Q_UNUSED(checked);
                try
                {
                    string fileformat = m_cadfile.substr(m_cadfile.size() - 3);
                    //����д��ĸ��ΪСд��ĸ
                    transform(fileformat.begin(), fileformat.end(), fileformat.begin(), ::tolower);
                   
                }
                catch (...)
                {
                    this->reject();
                    as::SoftwareLogfunc::GetInstance().LeaveFunction("ImportCADDialog::iniConnect", "ImportCADialog.cpp", __LINE__);
                }
            });
    }

    //�رմ���
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

//�����ļ�����
void ImportCADDialog::openfiles(std::string FilePath)
{
    cad_file = FilePath;
    //��ȡ�ļ�����
    string filetype = cad_file.substr(cad_file.size() - 3);
    //��ȡCAD�ı�
    shared_ptr<vector<vector<string>>> list;

    int max_size = 0;//�����������
    for (int i = 0; i < list->size(); i++)
    {
        if (list->at(i).size() > max_size)
        {
            max_size = list->at(i).size();
        }
    }
    if (list == nullptr)
        return;
    //���ñ������
    ui->tableWidget->setRowCount(list->size());
    ui->tableWidget->blockSignals(true);
    if (list->size() > 0)
    {
        //���ñ������
        //ui->tableWidget->setColumnCount(list->at(0).size());
        ui->tableWidget->setColumnCount(max_size);
        for (size_t col = 0; col < ui->tableWidget->columnCount(); col++)
        {
           
        }
    }
    //ˢ�±��
    for (size_t row = 0; row < ui->tableWidget->rowCount(); row++)
    {
        for (size_t col = 0; col < ui->tableWidget->columnCount(); col++)
        {
            ui->tableWidget->setItem(row, col, new QTableWidgetItem(QString::fromLocal8Bit(list->at(row).at(col).c_str())));
            ui->tableWidget->item(row, col)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);  // ����
        }
    }
    ui->tableWidget->blockSignals(false);
}
