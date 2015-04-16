#include "Admin.h"
#include <string>
using namespace std;

Admin::Admin()
{
	this->role = 1;
	this->id = 0;
}

Admin::Admin(string email,string password,string name)
{
	this->email = email;
	this->password = password;
	this->name = name;
	this->role = 1;
}

void Admin::setID(int id){
	this->id = id;
}

void Admin::setEmail(string email){
	this->email = email;
}

void Admin::setName(string name){
	this->name = name;
}

void Admin::setPassword(string password){
	this->password = password;
}

void Admin::setRole(int role){
	this->role = role;
}

int Admin::getID(){
	return id;
}

string Admin::getEmail(){
	return email;
}

string Admin::getName(){
	return name;
}

string Admin::getPassword(){
	return password;
}

int Admin::getRole(){
	return role;
}
