#pragma once
#include <string>
using namespace std;

class Admin
{
private:
	//ID为数据库自动生成
	int id;
	string email;
	string name;
	string password;
	//0 表示超级管理员 1表示普通管理员。默认为1
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

