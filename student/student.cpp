#include "Student.h"


Student::Student()
{
	this->password = "";
}

Student::Student(int id, string NO, string name, string email, string sex, int age, string class_name){
	this->id = id;
	this->NO = NO;
	this->name = name;
	this->email = email;
	this->sex = sex;
	this->age = age;
	this->class_name = class_name;
}

