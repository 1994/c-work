#include "AdminOpe.h"
#include "student.h"
#include "Dbhelper.h"
#include "Admin.h"
#include <iostream>
#include "Student.h"
using namespace std;


AdminOpe::AdminOpe(){
	db.Open("student.db");
}

bool AdminOpe::updateStudent(string update, string NO, int type)
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
		check = db.ExecDML(sql);
		break;

		//修改email
	case 2:
		base.append("email = '");
		base.append(update);
		base.append("' WHERE NO = '");
		base.append(NO);
		base.append("'");
		sql = const_cast<char*>(base.c_str());
		check = db.ExecDML(sql);
		break;

		//修改性别
	case 3:
		base.append("sex = '");
		base.append(update);
		base.append("' WHERE NO = '");
		base.append(NO);
		base.append("'");
		sql = const_cast<char*>(base.c_str());
		check = db.ExecDML(sql);
		break;

		//修改年龄
	case 4:
		base.append("age = '");
		base.append(update);
		base.append("' WHERE NO = '");
		base.append(NO);
		base.append("'");
		sql = const_cast<char*>(base.c_str());
		check = db.ExecDML(sql);
		break;

		//修改班级
	case 5:
		base.append("class_name = '");
		base.append(update);
		base.append("' WHERE NO = '");
		base.append(NO);
		base.append("'");
		sql = const_cast<char*>(base.c_str());
		check = db.ExecDML(sql);
		break;

	case 6:
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


bool AdminOpe::addStudent(Student student)
{
	string s = "INSERT INTO student(NO,name,email,sex,age,class_name,password) VALUES('";
	s.append(student.Nunber());
	s.append("','");
	s.append(student.Name());
	s.append("','");
	s.append(student.Email());
	s.append("','");
	s.append(student.Sex());
	s.append("','");
	s.append(to_string(student.Age()));
	s.append("','");
	s.append(student.Class_name());
	s.append("','");
	s.append(student.Password());
	s.append("');");
	char *sql = const_cast<char*>(s.c_str());
	int check = db.ExecDML(sql);
	if (check == 1)
		return true;
	else
		return false;
}


bool AdminOpe::addAdmin(Admin a){

	string s = "INSERT INTO admin(email,username,pass,role) VALUES('";
	s.append(a.getEmail());
	s.append("','");
	s.append(a.getName());
	s.append("','");
	s.append(a.getPassword());
	s.append("','");
	s.append(to_string(a.getRole()));
	s.append("');");
	//cout << s << endl;
	char *sql = const_cast<char*>(s.c_str());
	int check = db.ExecDML(sql);
	if (check == 1)
		return true;
	else
		return false;
}

int AdminOpe::login(string email, string pass){
	string s = "SELECT role FROM admin WHERE email = '";
	s.append(email);
	s.append("' and pass = '");
	s.append(pass);
	s.append("';");
	char *sql = const_cast<char*>(s.c_str());
	//cout << sql << endl;
	DbQuery query = db.ExecQuery(sql);

	if (query.FieldIsNull(0))
	{
		query.Finalize();
		return -1;
	}

	else
	{	
		int role;
		query.GetIntValue(0, role);
		query.Finalize();
		return role;
	}

}

list<Student> AdminOpe::getAll(){
	cout << "ok" << endl;
	const char *sql = "SELECT * FROM student";
	DbQuery query = db.ExecQuery(sql);
	list<Student> students;
	int id;
	char* NO;
	char* name;
	char* email;
	char* sex;
	int age;
	char* class_name;
	while (!query.Eof())
	{
		query.GetIntValue(0, id);
		query.GetStringValue(1, NO);
		query.GetStringValue(2, name);
		query.GetStringValue(3, email);
		query.GetStringValue(4, sex);
		query.GetIntValue(5, age);
		query.GetStringValue(6, class_name);
		Student s(id, NO, name, email, sex, age, class_name);
		students.push_front(s);
		query.NextRow();
	}

	return students;
}

Student AdminOpe::getByNO(string number)
{
	string s = "SELECT * FROM student WHERE NO = '";
	s.append(number);
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
		//string pass = query.GetString(7);
		query.Finalize();

		return Student(number, name, email, sex, age, className);
	}
	//cout << "用户名或者密码错误" << endl;
	else
	{
		Student stu;
		stu.Id(-1);
		return stu;
	}
}

bool AdminOpe::deleteStudent(string number){
	string s = "DELETE FROM student WHERE number = '";
	s.append(number);
	s.append("'");

	char *sql = const_cast<char*>(s.c_str());
	int check = db.ExecDML(sql);
	if (check == 1)
		return true;
	else
		return false;
}
