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

	int id;
	char* NO;
	char* name;
	char* s_email;
	char* sex;
	int age;
	char* class_name;
	if (query.Eof())
	{
		query.GetIntValue(0, id);
		query.GetStringValue(1, NO);
		query.GetStringValue(2, name);
		query.GetStringValue(3, s_email);
		query.GetStringValue(4, sex);
		query.GetIntValue(5, age);
		query.GetStringValue(6, class_name);
		query.Finalize();
		return Student(id, NO, name, s_email, sex, age, class_name);
	}
	cout << "用户名或者密码错误" << endl;
	return Student();

	
}

bool StudentOpe::update(string update, string NO, int type)
{
	string base = "UPDATE student SET";
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
