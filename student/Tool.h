#pragma once
#include <string>

using namespace std;
class Tool
{
public:
	//检查用户名是否合法
	static bool checkUsername(const string &);
	//检查密码是否合法
	static bool checkPass(const string &);
	//进行MD5加密
	static const string convertMD5(const string &);
	//检查是否是中文
	static bool checkName(const string &);
	~Tool();
};

