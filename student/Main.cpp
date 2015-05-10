#include "iostream"
#include "AdminOpe.h"
#include "StudentOpe.h"
#include "Tool.h"
#include "string"
#include "Admin.h"
#include "list"
#include "Student.h"

using namespace std;

int main(){
	void adminMenu();
	void admin2Menu();
	void adminOperation(AdminOpe *admin, int choice);
	void login();
	void studentMenu(Student *);

	AdminOpe *admin = new AdminOpe;
	StudentOpe *student = new StudentOpe;
	while (true){
		int i;
		std::cout << "选择角色 0管理员 1学生" << endl;
		std::cin >> i;
		bool temp = (i == 0) ? true : false;

		//管理员登陆
		while (temp){
			cout << "请输入用户名" << endl;
			string username;
			cin >> username;
			bool nameCheck = Tool::checkUsername(username);
			if (!nameCheck){
				std::cout << "请输入正确的用户名，用户名为邮箱格式" << endl;
				continue;
			}

			cout << "请输入密码" << endl;
			string password;
			cin >> password;
			int role = admin->login(username, password);
			if (role == -1)
				cout << "密码错误,请核对账号与密码" << endl;

			//超级管理员
			if (role == 0){
				adminMenu();
				int choice;
				cin >> choice;
				if (choice<1||choice>6){
					cout << "请输入正确的序号" << endl;
				}
				else {
					
					adminOperation(admin, choice);
				}
				
			}

			//普通管理员
			if (role == 1){
				admin2Menu();
				int choice;
				cin >> choice;

				if (choice<1 || choice>4){
					cout << "请输入正确的序号" << endl;
				}
				else {
					adminOperation(admin, choice + 1);
				}

			}
		}
		string stuEmail;
		string stuPass;
		cout << "请输入学生账号" << endl;
		cin >> stuEmail >> stuPass;
		if (!Tool::checkUsername(stuEmail)){
			cout << "请输入正确的账号，格式为email" << endl;
		}
		else {
			Student loginStu = student->login(stuEmail, stuPass);
			if (loginStu.Id() == -1){
				cout << "密码错误" << endl;
			}
			else {
				cout << "学号\t姓名\t邮箱\t\t性别\t年龄\t班级\t密码" << endl;
				cout << loginStu.Nunber() << '\t' << loginStu.Name() << '\t' << loginStu.Email() << '\t' << loginStu.Sex() << '\t' << loginStu.Age() << '\t' << loginStu.Class_name() << '\t' << loginStu.Password() << endl;
				cout << "请输入修改内容" << endl;
				cout << "1.修改名字" << endl;
				cout << "2.修改性别" << endl;
				cout << "3.修改年龄" << endl;
				cout << "4.修改密码" << endl;
				int choice;
				cin >> choice;
				switch (choice){
				case 1:{
					string newString;
					cout << "请输入新的名字" << endl;
					cin >> newString;
					bool temp = student->update(newString, loginStu.Nunber(), choice);
					if (temp){
						cout << "修改成功" << endl;
					}
					break;
				}
				case 2:{
					string newString;
					cout << "请输入新的性别" << endl;
					cin >> newString;
					bool temp = student->update(newString, loginStu.Nunber(), choice);
					if (temp){
						cout << "修改成功" << endl;
					}
					break;
				}
				case 3:{
					string newString;
					cout << "请输入新的年龄" << endl;
					cin >> newString;
					bool temp = student->update(newString, loginStu.Nunber(), choice);
					if (temp){
						cout << "修改成功" << endl;
					}
					break;
				}
				case 4:{
					string newString;
					cout << "请输入新的密码" << endl;
					cin >> newString;
					bool temp = student->update(newString, loginStu.Nunber(), choice);
					if (temp){
						cout << "修改成功" << endl;
					}
					break;
				}

				}
			}
		}

		delete admin, student;
		return 0;
	}
}

//超级管理员菜单
void adminMenu(){
	cout << "您好，超级管理员" << endl;
	cout << "请选择操作" << endl;
	cout << "1.增加管理员" << endl;
	cout << "2.增加学生" << endl;
	cout << "3.查询全部学生" << endl;
	cout << "4.根据学号查询学生" << endl;
	cout << "5.更新学生信息" << endl;
	cout << "6.删除学生" << endl;
}

//普通管理员菜单
void admin2Menu(){
	cout << "您好，管理员" << endl;
	cout << "请选择操作" << endl;
	cout << "1.增加学生" << endl;
	cout << "2.查询全部学生" << endl;
	cout << "3.根据学号查询学生" << endl;
	cout << "4.更新学生信息" << endl;
}


void studentMenu(Student *stu){
	cout << "学号\t姓名\t邮箱\t性别\t年龄\t班级\t密码" << endl;
	cout << stu->Nunber() << '\t' << stu->Name() << '\t' << stu->Email() << '\t' << stu->Sex() << '\t' << stu->Age() << '\t' << stu->Class_name() << '\t' << stu->Password() << endl;
}

//管理员操作
void adminOperation(AdminOpe *admin, int choice){

	switch (choice)
	{
	case 1:{

		string adminEmail;
		string adminName;
		string adminPass;
		int adminRole;
		Admin a;

		cout << "管理员邮箱\t名字\t密码\t角色" << endl;
		cin >> adminEmail >> adminName >> adminPass >> adminRole;
		a.setEmail(adminEmail);
		a.setPassword(adminPass);
		a.setRole(adminRole);
		a.setName(adminName);
		admin->addAdmin(a);
		cout << "添加成功" << endl;
		break;
	}
	case 2:
	{
		string NO;
		string name;
		string email;
		string sex;
		int age;
		string class_name;
		string password;

		cout << "学号\t姓名\t邮箱\t性别\t年龄\t班级\t密码" << endl;
		cin >> NO >> name >> email >> sex >> age >> class_name >> password;

		Student student(NO, name, email, sex, age, class_name);
		admin->addStudent(student);
		cout << "添加成功" << endl;
		break;
	}

	case 3:{
		cout << "查询全部学生" << endl;
		list<Student> students = admin->getAll();
		cout << students.size()<< endl;
		list<Student>::iterator iter;
		cout << "学号\t姓名\temail\t性别\t年龄\t班级\t" << endl;
		for (iter = students.begin(); iter != students.end(); iter++){
			cout << iter->Nunber() << '\t' << iter->Name() << '\t' << iter->Email() << '\t' << iter->Sex() << '\t' << iter->Age() << '\t' << iter->Class_name() << endl;
		}
		break;
	}

	case 4:
	{
		string number;
		cout << "请输入想查询的学号" << endl;
		cin >> number;
		Student stu = admin->getByNO(number);
		if (stu.Id() == -1){
			cout << "查无此人" << endl;
		}
		else {
			cout << "学号\t姓名\temail\t\t性别\t年龄\t班级\t" << endl;
			cout << stu.Nunber() << '\t' << stu.Name() << '\t' << stu.Email() << '\t' << stu.Sex() << '\t' << stu.Age() << '\t' << stu.Class_name() << endl;
		}
		break;
	}

	case 5:
	{
		int choice;
		string NO;
		cout << "输入学号" << endl;
		cin >> NO;
		cout << "请选择更新内容" << endl;
		cout << "1.修改名字" << endl;
		cout << "2.修改email" << endl;
		cout << "3.修改性别" << endl;
		cout << "4.修改年龄" << endl;
		cout << "5.修改班级" << endl;
		cout << "6.修改密码" << endl;
		cin >> choice;
		switch (choice)
		{
		case 1:{
			string name;
			cout << "输入修改后的名字" << endl;
			cin >> name;
			admin->updateStudent(name, NO, 1);
		}
		case 2:{
			string email;
			cout << "输入修改后的邮箱" << endl;
			cin >> email;
			admin->updateStudent(email, NO, 2);
		}
		case 3:{
			string sex;
			cout << "输入修改后的性别" << endl;
			cin >> sex;
			admin->updateStudent(sex, NO, 3);
		}
		case 4:{
			int age;
			cout << "输入修改后的性别" << endl;
			cin >> age;
			break;
		}
		}

		break;
	}
	case 6:{
		string number;
		cout << "请输入要删除学生的学号" << endl;
		cin >> number;
		admin->deleteStudent(number);
		break;
	}
	}
}
