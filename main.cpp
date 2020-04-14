#include <QApplication>
#include <QFile>
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlError>
#include <optional>
#include "mainwindow.h"
#include "logindialog.h"
#include "manage-system.h"

std::optional<user_pool> g_upool;

void generate_test_data();

void create_database_conn()
{
	//Create a new database every time running the program
	bool delete_ok = QFile::remove("reverse-square.db");
	if(delete_ok)
		qDebug() << "Info: Remove old database before creating new.";

	QSqlDatabase dbobj(QSqlDatabase::addDatabase("QSQLITE"));
	dbobj.setDatabaseName("reverse-square.db");
	if(!dbobj.open())
	{
		qDebug() << "Error: Failed to connect database." << dbobj.lastError();
		throw("Error: Failed to connect database");
	}
	else
	{
		//Connection set. Return from the func
	}
}

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	create_database_conn();
	generate_test_data();

	loginDialog ld;
	ld.setWindowFlags(ld.windowFlags() &~ (Qt::WindowMinMaxButtonsHint | Qt::WindowCloseButtonHint));
	do {
		ld.exec();
	} while(!ld.get_login_state());

	MainWindow w;
    w.show();
    return a.exec();
}
