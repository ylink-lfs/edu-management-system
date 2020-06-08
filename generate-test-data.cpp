#include <QVector>
#include <QString>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QDir>
#include <fstream>
#include <iostream>
#include "manage-system.h"

void generate_schema()
{
	//The default executing dir is complicated. So using absolute path here
	//std::fstream f("schema/table-schemas.sql", std::ios_base::in);
	std::fstream f("/Users/bytedance/edu-management/schema/user-table-schema.sql", std::ios_base::in);
	if(!f.is_open())
	{
		qDebug() << "Open schema file failed";
		throw("Open schema file failed");
	}
	std::string q;
	QSqlQuery query;
	while(std::getline(f, q, ';') && q != "\n")
	{
		if(!query.exec(QString::fromStdString(q)))
		{
			qDebug() << query.lastError();
		}
	}
}

void generate_login_user_data()
{
	QSqlQuery query;
	bool exec_res = query.prepare(
		"INSERT INTO "
		"system_user "
		"VALUES(:user_id,:pwd,:is_teacher)"
	);
	if(!exec_res)
	{
		qDebug() << query.lastError();
		throw("Generate user info failed");
	}
	const int pair_user_num = 10;

	std::fstream f("/Users/bytedance/edu-management/login-user-info.txt", std::ios_base::out | std::ios_base::trunc);
	f << std::boolalpha;
	f << "user_id\tpwd\tis_teacher\n";

	for(unsigned i = 0; i < pair_user_num; i++)
	{
		user teacher_u{i, QString::number(i), true}, student_u{i, QString::number(i), false};
		f << i << '\t' << std::to_string(i) << '\t' << true << '\n';
		f << i << '\t' << std::to_string(i) << '\t' << false << '\n';
		query.bindValue(":user_id", i);
		query.bindValue(":pwd", QString::number(i));
		query.bindValue(":is_teacher", int(true));
		exec_res = query.exec();
		if(!exec_res)
		{
			qDebug() << query.lastError();
			throw("Generate user info failed");
		}
		query.bindValue(":is_teacher", int(false));
		query.exec();
		if(!exec_res)
		{
			qDebug() << query.lastError();
			throw("Generate user info failed");
		}
	}
}

void generate_test_data()
{
	try {
		generate_schema();
		generate_login_user_data();
	} catch(std::exception& e) {
		std::cerr << e.what();
	}
}
