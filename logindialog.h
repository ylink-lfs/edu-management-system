#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>

namespace Ui {
class loginDialog;
}

class loginDialog : public QDialog
{
	Q_OBJECT

public:
	explicit loginDialog(QWidget *parent = nullptr);
	~loginDialog();
	bool get_login_state() const { return login_success_state; }

private slots:
	void on_loginButtons_accepted();

	void on_loginButtons_rejected();

private:
	Ui::loginDialog *ui;
	bool login_success_state = false;
};

#endif // LOGINDIALOG_H
