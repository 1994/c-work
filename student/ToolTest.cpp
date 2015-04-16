#include "Tool.h"
#include <iostream>
#include "DbHelper.h"
#include "DbQuery.h"
#include "DbTable.h"
#include "AdminOpe.h"
#include "Admin.h"

using namespace std;


int main(){
	
	AdminOpe a1;
	Admin a("d", "f", "yt");
	//a1.addAdmin(a);
	cout << a1.login("123@gmail.com", "r") << endl;
	return 0;
}