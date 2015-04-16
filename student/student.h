#pragma once
#include <string>
using namespace std;

class student
{
private:
	int number;
	string name;
	string sex;
	
public:
	student();
	void display();
	virtual ~student();
};

