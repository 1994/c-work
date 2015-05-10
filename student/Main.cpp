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
		std::cout << "ѡ���ɫ 0����Ա 1ѧ��" << endl;
		std::cin >> i;
		bool temp = (i == 0) ? true : false;

		//����Ա��½
		while (temp){
			cout << "�������û���" << endl;
			string username;
			cin >> username;
			bool nameCheck = Tool::checkUsername(username);
			if (!nameCheck){
				std::cout << "��������ȷ���û������û���Ϊ�����ʽ" << endl;
				continue;
			}

			cout << "����������" << endl;
			string password;
			cin >> password;
			int role = admin->login(username, password);
			if (role == -1)
				cout << "�������,��˶��˺�������" << endl;

			//��������Ա
			if (role == 0){
				adminMenu();
				int choice;
				cin >> choice;
				if (choice<1||choice>6){
					cout << "��������ȷ�����" << endl;
				}
				else {
					
					adminOperation(admin, choice);
				}
				
			}

			//��ͨ����Ա
			if (role == 1){
				admin2Menu();
				int choice;
				cin >> choice;

				if (choice<1 || choice>4){
					cout << "��������ȷ�����" << endl;
				}
				else {
					adminOperation(admin, choice + 1);
				}

			}
		}
		string stuEmail;
		string stuPass;
		cout << "������ѧ���˺�" << endl;
		cin >> stuEmail >> stuPass;
		if (!Tool::checkUsername(stuEmail)){
			cout << "��������ȷ���˺ţ���ʽΪemail" << endl;
		}
		else {
			Student loginStu = student->login(stuEmail, stuPass);
			if (loginStu.Id() == -1){
				cout << "�������" << endl;
			}
			else {
				cout << "ѧ��\t����\t����\t\t�Ա�\t����\t�༶\t����" << endl;
				cout << loginStu.Nunber() << '\t' << loginStu.Name() << '\t' << loginStu.Email() << '\t' << loginStu.Sex() << '\t' << loginStu.Age() << '\t' << loginStu.Class_name() << '\t' << loginStu.Password() << endl;
				cout << "�������޸�����" << endl;
				cout << "1.�޸�����" << endl;
				cout << "2.�޸��Ա�" << endl;
				cout << "3.�޸�����" << endl;
				cout << "4.�޸�����" << endl;
				int choice;
				cin >> choice;
				switch (choice){
				case 1:{
					string newString;
					cout << "�������µ�����" << endl;
					cin >> newString;
					bool temp = student->update(newString, loginStu.Nunber(), choice);
					if (temp){
						cout << "�޸ĳɹ�" << endl;
					}
					break;
				}
				case 2:{
					string newString;
					cout << "�������µ��Ա�" << endl;
					cin >> newString;
					bool temp = student->update(newString, loginStu.Nunber(), choice);
					if (temp){
						cout << "�޸ĳɹ�" << endl;
					}
					break;
				}
				case 3:{
					string newString;
					cout << "�������µ�����" << endl;
					cin >> newString;
					bool temp = student->update(newString, loginStu.Nunber(), choice);
					if (temp){
						cout << "�޸ĳɹ�" << endl;
					}
					break;
				}
				case 4:{
					string newString;
					cout << "�������µ�����" << endl;
					cin >> newString;
					bool temp = student->update(newString, loginStu.Nunber(), choice);
					if (temp){
						cout << "�޸ĳɹ�" << endl;
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

//��������Ա�˵�
void adminMenu(){
	cout << "���ã���������Ա" << endl;
	cout << "��ѡ�����" << endl;
	cout << "1.���ӹ���Ա" << endl;
	cout << "2.����ѧ��" << endl;
	cout << "3.��ѯȫ��ѧ��" << endl;
	cout << "4.����ѧ�Ų�ѯѧ��" << endl;
	cout << "5.����ѧ����Ϣ" << endl;
	cout << "6.ɾ��ѧ��" << endl;
}

//��ͨ����Ա�˵�
void admin2Menu(){
	cout << "���ã�����Ա" << endl;
	cout << "��ѡ�����" << endl;
	cout << "1.����ѧ��" << endl;
	cout << "2.��ѯȫ��ѧ��" << endl;
	cout << "3.����ѧ�Ų�ѯѧ��" << endl;
	cout << "4.����ѧ����Ϣ" << endl;
}


void studentMenu(Student *stu){
	cout << "ѧ��\t����\t����\t�Ա�\t����\t�༶\t����" << endl;
	cout << stu->Nunber() << '\t' << stu->Name() << '\t' << stu->Email() << '\t' << stu->Sex() << '\t' << stu->Age() << '\t' << stu->Class_name() << '\t' << stu->Password() << endl;
}

//����Ա����
void adminOperation(AdminOpe *admin, int choice){

	switch (choice)
	{
	case 1:{

		string adminEmail;
		string adminName;
		string adminPass;
		int adminRole;
		Admin a;

		cout << "����Ա����\t����\t����\t��ɫ" << endl;
		cin >> adminEmail >> adminName >> adminPass >> adminRole;
		a.setEmail(adminEmail);
		a.setPassword(adminPass);
		a.setRole(adminRole);
		a.setName(adminName);
		admin->addAdmin(a);
		cout << "��ӳɹ�" << endl;
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

		cout << "ѧ��\t����\t����\t�Ա�\t����\t�༶\t����" << endl;
		cin >> NO >> name >> email >> sex >> age >> class_name >> password;

		Student student(NO, name, email, sex, age, class_name);
		admin->addStudent(student);
		cout << "��ӳɹ�" << endl;
		break;
	}

	case 3:{
		cout << "��ѯȫ��ѧ��" << endl;
		list<Student> students = admin->getAll();
		cout << students.size()<< endl;
		list<Student>::iterator iter;
		cout << "ѧ��\t����\temail\t�Ա�\t����\t�༶\t" << endl;
		for (iter = students.begin(); iter != students.end(); iter++){
			cout << iter->Nunber() << '\t' << iter->Name() << '\t' << iter->Email() << '\t' << iter->Sex() << '\t' << iter->Age() << '\t' << iter->Class_name() << endl;
		}
		break;
	}

	case 4:
	{
		string number;
		cout << "���������ѯ��ѧ��" << endl;
		cin >> number;
		Student stu = admin->getByNO(number);
		if (stu.Id() == -1){
			cout << "���޴���" << endl;
		}
		else {
			cout << "ѧ��\t����\temail\t\t�Ա�\t����\t�༶\t" << endl;
			cout << stu.Nunber() << '\t' << stu.Name() << '\t' << stu.Email() << '\t' << stu.Sex() << '\t' << stu.Age() << '\t' << stu.Class_name() << endl;
		}
		break;
	}

	case 5:
	{
		int choice;
		string NO;
		cout << "����ѧ��" << endl;
		cin >> NO;
		cout << "��ѡ���������" << endl;
		cout << "1.�޸�����" << endl;
		cout << "2.�޸�email" << endl;
		cout << "3.�޸��Ա�" << endl;
		cout << "4.�޸�����" << endl;
		cout << "5.�޸İ༶" << endl;
		cout << "6.�޸�����" << endl;
		cin >> choice;
		switch (choice)
		{
		case 1:{
			string name;
			cout << "�����޸ĺ������" << endl;
			cin >> name;
			admin->updateStudent(name, NO, 1);
		}
		case 2:{
			string email;
			cout << "�����޸ĺ������" << endl;
			cin >> email;
			admin->updateStudent(email, NO, 2);
		}
		case 3:{
			string sex;
			cout << "�����޸ĺ���Ա�" << endl;
			cin >> sex;
			admin->updateStudent(sex, NO, 3);
		}
		case 4:{
			int age;
			cout << "�����޸ĺ���Ա�" << endl;
			cin >> age;
			break;
		}
		}

		break;
	}
	case 6:{
		string number;
		cout << "������Ҫɾ��ѧ����ѧ��" << endl;
		cin >> number;
		admin->deleteStudent(number);
		break;
	}
	}
}
