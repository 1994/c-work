#pragma once
#include "Admin.h"
#include "Dbhelper.h"
#include <list>
#include "Student.h"

class AdminOpe
{
private:
	DbHelper db;
public:
	bool addStudent(Student s);
	bool addAdmin(Admin a);
	bool login(string,string);
	//查找出全部的学生
	list<Student> getAll();
	//根据学号查找学生
	Student getByNO(string);
	//修改学生信息
	bool updateStudent(string,string,int);
	AdminOpe();

};

