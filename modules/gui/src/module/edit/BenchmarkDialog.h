#ifndef AS_BENCHMARKDIALOG_H
#define AS_BENCHMARKDIALOG_H

#include "common/CommonPart.h"
#include "as/CommonCore.hpp"
#include "as/common/UiCallback.h"
#include "as/MarkCore.hpp"
#include "as/common/CommonProcess.h"
#include "as/edit/BenchmarkProcess.hpp"

#include "items/VisGraphicsScene.h"
#include "items/VisGraphicsView.h"

#include <QLineEdit>

namespace Ui
{
	class BenchmarkDialog;
}
using namespace as;

class BenchmarkDialog : public ASQDialog
{
    Q_OBJECT
public:
	BenchmarkDialog(QWidget* parent = nullptr);
	~BenchmarkDialog();

	void InitUI();
	
	void InitConnect();
	
signals:

private slots:

private:
    Ui::BenchmarkDialog *m_ui;
	BenchMarkProcess m_cBenchMarkProcess;

	as::CommonCheck statecheck;

	items::VisGraphicsScene* mark_fov_scene;          // 场景
	items::VisGraphicsView* mark_fov_graphicsView;    // 视窗

	//9种Mark类型
	QStringList MarkTypeList = { QString::fromLocal8Bit("圆形"), QString::fromLocal8Bit("钻石型"), QString::fromLocal8Bit("长方形"),
		QString::fromLocal8Bit("长方形2"), QString::fromLocal8Bit("三角形"), QString::fromLocal8Bit("十字光标"),
		QString::fromLocal8Bit("蝴蝶形"), QString::fromLocal8Bit("井字形"), QString::fromLocal8Bit("椭圆") };

	//鼠标点击表格事件中存储的与上个点击的行列
	int precol = -1;
	int prerow = -1;
	QLineEdit* edit = nullptr;   //表格编辑器
	QObject* prewatch = NULL;
};

#endif
