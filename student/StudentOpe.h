#pragma once
#include "DbHelper.h"
#include "Student.h"
class StudentOpe
{
private:
	DbHelper db;
public:
	StudentOpe();
	Student login(string,string);
	bool update(string, string, int);
};

