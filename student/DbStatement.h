#pragma once
#include "sqlite3.h"
#include "DbQuery.h"
class DbStatement
{
private:
	sqlite3 *mpDB;
	sqlite3_stmt *mpStmt;

	void CheckDB();
	void CheckStmt();
public:
	DbStatement();
	DbStatement(sqlite3 *pdb, sqlite3_stmt *pstmt);
	DbStatement(const DbStatement &rStatement);
	DbStatement& operator = (const DbStatement &rStatement);
	~DbStatement();

	int ExecDML();
	DbQuery ExecQuery();

	void Reset();

	void Finalize();
};

