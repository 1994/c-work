#include "Tool.h"
#include <iostream>
#include "DbHelper.h"
#include "DbQuery.h"
#include "DbTable.h"
using namespace std;


int main(){
	
	DbHelper db;
	db.Open("student.db");
	//char s[100] = "create table teacher (t_id int, t_age int, t_sex char);";
	//db.ExecDML(s);
	//db.ExecDML("insert into teacher values(124, 30, 'M');");
	DbTable table = db.GetTable("SELECT * FROM admin");
	int row;
	int id;
	char *username;
	char *pass;
	for (row = 0; row < table.NumOfRows(); row++){
		table.SetRow(row);
		table.GetIntField(0, id);
		table.GetStringField(1, username);
		table.GetStringField(2, pass);
		cout << id << '\t' << username << '\t' << pass << endl;
	}
	return 0;
}