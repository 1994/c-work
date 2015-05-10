#pragma once
#include <string>
using namespace std;

class Student
{
private:
	int id;

	string NO;
	
	string name;
	
	string email;
	
	string sex;
	
	int age;
	
	string class_name;

	string password;
	
public:
	int Id() const { return id; }

	void Id(int val) { id = val; }

	string Nunber() const { return NO; }
	void Nunber(string val) { NO = val; }

	string Name() const { return name; }

	void Name(string val) { name = val; }

	string Email() const { return email; }

	void Email(string val) { email = val; }

	string Sex() const { return sex; }

	void Sex(string val) { sex = val; }

	int Age() const { return age; }

	void Age(int val) { age = val; }

	string Class_name() const { return class_name; }

	void Class_name(string val) { class_name = val; }

	string Password() const { return password; }

	void Password(string val) { password = val; }

	Student();

	Student(string, string, string, string, int, string);

	Student(string, string, string, string, int, string,string);

	Student(int,string, string, string, string, int, string);
};

