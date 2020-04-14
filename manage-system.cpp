#include <QSqlQuery>
#include <QSqlError>
#include <QString>
#include <QDebug>
#include "manage-system.h"

unsigned course::how_many_course = 0;
unsigned student::how_many_student = 0;
unsigned teacher::how_many_teacher = 0;

bool user_pool::login_ok(const unsigned int id, const bool isteacher, const QString& pwd) const
{
	QSqlQuery qu;
	qu.prepare(
		"SELECT pwd "
		"FROM system_user "
		"WHERE user_id = :id AND is_teacher = :isteacher"
	);
	qu.bindValue(":id", id);
	qu.bindValue(":isteacher", int(isteacher));
	if(!qu.exec())
	{
		qDebug() << qu.lastError();
		throw("Fetch user info failed");
	}
	else
	{
		while(qu.next())
		{
			return qu.value(0).toString() == pwd;
		}
		//No matching record. Return false;
		qDebug() << "No matching record in login_ok SELECT";
		return false;
	}
}
