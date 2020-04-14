#ifndef MANAGESYSTEM_H
#define MANAGESYSTEM_H

#include <QString>
#include <QVector>
#include <algorithm>
#include <utility>

class course
{
public:
	friend bool operator<(const course& c1, const course& c2) { return c1.course_id < c2.course_id; }
	friend bool operator==(const course& c1, const course& c2) { return c1.course_id == c2.course_id; }
	course(const unsigned teacher_id_,
		   const QString& course_name_,
		   const QString& classroom_addr_,
		   const unsigned course_capacity_) :
		course_id(how_many_course++),
		teacher_id(teacher_id_), course_name(course_name_), classroom_addr(classroom_addr_),
		course_capacity(course_capacity_), current_select(0) {}

	unsigned get_course_id() const { return course_id; }
	unsigned get_teacher_id() const { return teacher_id; }
	const QString& get_course_name() const { return course_name; }
	const QString& get_classroom_addr() const { return classroom_addr; }
	unsigned get_course_capacity() const { return course_capacity; }
	unsigned get_current_select() const { return current_select; }

	void select_this(const unsigned student_id) { students_select.push_back(student_id); current_select++; }
	void cancel_select(const unsigned student_id)
	{ students_select.erase(std::find(students_select.begin(), students_select.end(), student_id)); current_select--; }

private:
	unsigned course_id;
	unsigned teacher_id;
	QString course_name;
	QString classroom_addr;
	unsigned course_capacity;
	unsigned current_select;
	static unsigned how_many_course;
	QVector<unsigned> students_select;
};

class score
{
public:
	score(const unsigned course_id_, const unsigned student_id_, const double score_value_) :
		course_id(course_id_), student_id(student_id_), score_value(score_value_) {}
	unsigned get_course_id() const { return course_id; }
	unsigned get_student_id() const { return student_id; }
	unsigned get_score_value() const { return score_value; }
	double get_score_point() const {
		auto inrange = [](const int r1, const int r2, const int val) { return val >= r1 && val <= r2; };
		if(score_value < 60)
			return 0.0;
		else if(inrange(60, 69, score_value))
			return 1.0;
		else if(inrange(70, 79, score_value))
			return 2.0;
		else if(inrange(80, 89, score_value))
			return 3.0;
		else if(inrange(90, 99, score_value))
			return 4.0;
		else
			return 5.0;
	}
private:
	unsigned course_id;
	unsigned student_id;
	unsigned score_value;
};

class student
{
public:
	friend bool operator<(const student& s1, const student& s2) { return s1.student_id < s2.student_id; }
	friend bool operator==(const student& s1, const student& s2) { return s1.student_id == s2.student_id; }
	student(const QString& name_, const QString& tel_) : student_id(how_many_student++), name(name_), tel(tel_) {}

	unsigned get_student_id() const { return student_id; }
	const QString& get_name() const { return name; }
	const QString& get_tel() const { return tel; }
private:
	unsigned student_id;
	QString name;
	QString tel;
	static unsigned how_many_student;
};

class teacher
{
public:
	friend bool operator<(const teacher& t1, const teacher& t2) { return t1.worker_id < t2.worker_id; }
	friend bool operator==(const teacher& t1, const teacher& t2) { return t1.worker_id == t2.worker_id; }
	teacher(const QString& name_, const QString& tel_) : worker_id(how_many_teacher++), name(name_), tel(tel_) {}

	unsigned get_student_id() const { return worker_id; }
	const QString& get_name() const { return name; }
	const QString& get_tel() const { return tel; }
private:
	unsigned worker_id;
	QString name;
	QString tel;
	static unsigned how_many_teacher;
};

class user
{
public:
	friend bool operator==(const user& u1, const user& u2) { return (u1.id == u2.id) && (u1.is_teacher == u2.is_teacher); }
	user(const unsigned id_, const QString& pwd_, const bool is_teacher_) : id(id_), pwd(pwd_), is_teacher(is_teacher_) {}
	std::pair<unsigned, bool> get_user_info() const { return std::make_pair(id, is_teacher); }
	bool check_pwd(const QString& input_pwd) const { return pwd == input_pwd; }
private:
	unsigned id;
	QString pwd;
	bool is_teacher;
};

class user_pool
{
public:
	bool login_ok(const unsigned id, const bool isteacher, const QString& pwd) const;
};

#endif // MANAGESYSTEM_H
