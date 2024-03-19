#ifndef AS_IMPORTCADDIALOG_H
#define AS_IMPORTCADDIALOG_H

#include <QDialog>
#include "as/Common/CommonProcess.h"
#include "as/file/CADImportProcess.hpp"
#include "as/Common/UiCallback.h"
#include <QVariant>

namespace Ui {
class ImportCADDialog;
}

class ImportCADDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ImportCADDialog(std::string filepath, std::string seperator, int block_id, QWidget *parent = nullptr);
    ~ImportCADDialog();

    void iniDialog();

    void iniConnect();

    as::APIErrCode GetResult();

    void openfiles(std::string FilePath);

signals:
    //void SendUnlinkCompdata(vector<aoi::MainWindowProcess::DetectData> data);
    //void SendUnlinkCompdata(QVariant);
private:
    Ui::ImportCADDialog *ui;
    QString lineEdit;
    std::string cad_file; //cad文件路径
    std::string m_cadfile;
    int m_blockid;
    as::CADImportProcess m_cCADImportProcess;
    as::APIErrCode result_importCadresult;
    //vector<aoi::MainWindowProcess::DetectData> vec_UnenrolledComplist;  //cad文件未注册元件列表
};

#endif // IMPORTDIALOG_H
