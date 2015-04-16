#include "Admin.h"


Admin::Admin()
{
	this->role = 1;
}

Admin::Admin(string email,string password,string name)
{
	this->email = email;
	this->password = password;
	this->name = name;
	this->role = 1;
}

Admin::~Admin()
{
}
