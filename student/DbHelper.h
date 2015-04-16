#pragma once
#include "sqlite3.h"
#include "DbQuery.h"
#include "DbTable.h"
#include "DbStatement.h"
#include <string>
using namespace std;

class DbHelper
{
private:
	sqlite3 *mpDB;
	sqlite3_stmt *mpStmt;

	void CheckDB();
	DbHelper(const DbHelper &rDB);
	DbHelper& operator = (const DbHelper &rDB);

	sqlite3_stmt* Compile(const char * szSQL);

public:
	DbHelper();
	~DbHelper();

	void Open(const char * szFileName);
	void Close();

	int ExecDML(const char * szSQL);
	DbQuery ExecQuery(const char * szSQL);

	DbTable GetTable(const char * szSQL);

	DbStatement CompileStatement(const char * szSQL);

};

