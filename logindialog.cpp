#include <QMessageBox>
#include <QDebug>
#include "logindialog.h"
#include "ui_logindialog.h"
#include "manage-system.h"

extern std::optional<user_pool> g_upool;

loginDialog::loginDialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::loginDialog)
{
	ui->setupUi(this);
	ui->widget->setWindowTitle("教务系统登陆");
	this->adjustSize();
}

loginDialog::~loginDialog()
{
	delete ui;
}

void loginDialog::on_loginButtons_accepted()
{
	auto id = ui->loginID->text().toUInt();
	auto pwd = ui->loginPwd->text();
	bool isteacher = (ui->teacherStu->itemText(ui->teacherStu->currentIndex()) == QString("教师"));
	login_success_state = g_upool->login_ok(id, isteacher, pwd);
	if(!login_success_state)
	{
		QMessageBox::critical(this, "登录错误", "用户信息错误！");
		ui->loginID->clear();
		ui->loginPwd->clear();
		ui->loginID->setFocus();
	}
}

void loginDialog::on_loginButtons_rejected()
{
	exit(0);
}
