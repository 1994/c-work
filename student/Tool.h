#pragma once
#include <string>

using namespace std;
class Tool
{
public:
	//����û����Ƿ�Ϸ�
	static bool checkUsername(const string &);
	//��������Ƿ�Ϸ�
	static bool checkPass(const string &);
	//����MD5����
	static const string convertMD5(const string &);
	//����Ƿ�������
	static bool checkName(const string &);
	~Tool();
};

