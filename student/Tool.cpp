#include "Tool.h"
#include <regex>

Tool::~Tool()
{
}

bool Tool::checkUsername(const string &username){
	const  regex pattern("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+");
	return regex_match(username,pattern);
}

bool Tool::checkPass(const string &password){
	if (password.length() < 6 || password.length() > 18)
		return false;
	return true;
}

const string Tool::convertMD5(const string &password){
	return password;
}

bool Tool::checkName(const string &name){
	const  regex pattern("([\u4e00-\u9fa5]{2,4})");
	return regex_match(name, pattern);
}
