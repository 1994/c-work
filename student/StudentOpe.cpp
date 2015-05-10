#include "StudentOpe.h"
#include <iostream>
using namespace std;

StudentOpe::StudentOpe()
{
	db.Open("student.db");
}

Student StudentOpe::login(string email, string pass)
{
	string s = "SELECT * FROM student WHERE email = '";
	s.append(email);
	s.append("' and password = '");
	s.append(pass);
	s.append("';");
	char *sql = const_cast<char*>(s.c_str());
	//cout << sql << endl;
	DbQuery query = db.ExecQuery(sql);

	if (!query.Eof())
	{	

		string number = query.GetString(1);
		string name = query.GetString(2);;
		string email = query.GetString(3);
		string sex = query.GetString(4);
		int age;
		query.GetIntValue(5, age);
		string className = query.GetString(6);
		string pass = query.GetString(7);
		query.Finalize();
	
		return Student(number, name, email, sex, age, className, pass);
	}
	//cout << "用户名或者密码错误" << endl;
	else
	{
		Student stu;
		stu.Id(-1);
		return stu;
	}
		//return Student();
}

bool StudentOpe::update(string update, string NO, int type)
{
	string base = "UPDATE student SET ";
	//char *sql = "UPDATE student SET name = '' WHERE NO = ''";
	int check = 0;
	char *sql;
	switch (type)
	{
		//修改名字
	case 1:
		base.append("name = '");
		base.append(update);
		base.append("' WHERE NO = '");
		base.append(NO);
		base.append("'");
		sql = const_cast<char*>(base.c_str());
		//cout << sql << endl;
		check = db.ExecDML(sql);
		break;


		//修改性别
	case 2:
		base.append("sex = '");
		base.append(update);
		base.append("' WHERE NO = '");
		base.append(NO);
		base.append("'");
		sql = const_cast<char*>(base.c_str());
		check = db.ExecDML(sql);
		break;

		//修改年龄
	case 3:
		base.append("age = '");
		base.append(update);
		base.append("' WHERE NO = '");
		base.append(NO);
		base.append("'");
		sql = const_cast<char*>(base.c_str());
		check = db.ExecDML(sql);
		break;

	case 4:
		base.append("password = '");
		base.append(update);
		base.append("' WHERE NO = '");
		base.append(NO);
		base.append("'");
		sql = const_cast<char*>(base.c_str());
		check = db.ExecDML(sql);
		break;
	}

	if (check == 1)
		return true;
	else
		return false;
}
