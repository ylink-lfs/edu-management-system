-- Teacher:
CREATE TABLE teacher(
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    name VARCHAR(20) NOT NULL,
    tel CHAR(11) NOT NULL
);

-- Student:
CREATE TABLE student(
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    name VARCHAR(20) NOT NULL,
    tel CHAR(11) NOT NULL
);

-- Course:
CREATE TABLE course(
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    teacher_id INTEGER NOT NULL,
    FOREIGN KEY(teacher_id) REFERENCES teacher(id),
    name VARCHAR(50) NOT NULL,
    classroom VARCHAR(30) NOT NULL,
    capacity INTEGER NOT NULL,
    current_select INTEGER
);

-- Taking course relationship
CREATE TABLE take(
    student_id INTEGER NOT NULL,
    FOREIGN KEY(student_id) REFERENCES student(id),
    course_id INTEGER NOT NULL,
    FOREIGN KEY(course_id) REFERENCES course(id),
    score INTEGER
);

-- Login user info
CREATE TABLE system_user(
    user_id INTEGER NOT NULL,
    pwd VARCHAR(100) NOT NULL,
    is_teacher INTEGER
);
