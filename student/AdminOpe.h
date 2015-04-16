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
	//���ҳ�ȫ����ѧ��
	list<Student> getAll();
	//����ѧ�Ų���ѧ��
	Student getByNO(string);
	//�޸�ѧ����Ϣ
	bool updateStudent(string,string,int);
	AdminOpe();

};

