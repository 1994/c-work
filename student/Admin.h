#pragma once
#include <string>
using namespace std;

class Admin
{
private:
	//IDΪ���ݿ��Զ�����
	int id;
	string email;
	string name;
	string password;
	//0 ��ʾ��������Ա 1��ʾ��ͨ����Ա��Ĭ��Ϊ1
	int role;

public:
	Admin();
	Admin(string,string,string);
	void setID(int);
	void setEmail(string);
	void setName(string);
	void setPassword(string);
	void setRole(int);
	int getID();
	string getEmail();
	string getName();
	string getPassword();
	int getRole();
};

