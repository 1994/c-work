#include "DbHelper.h"
#include "DbException.h"
#include "DbStatement.h"
#include "DbTable.h"
#include <string>
using namespace std;

DbHelper::DbHelper()
{
	mpDB = 0;
}

DbHelper::DbHelper(const DbHelper &rDB)
{
	mpDB = rDB.mpDB;
}

DbHelper::~DbHelper()
{
	Close();
}

DbHelper& DbHelper::operator =(const DbHelper &rDB)
{
	mpDB = rDB.mpDB;
	return *this;
}

void DbHelper::CheckDB()
{
	if (!mpDB)
	{
		throw DbException(CPPSQLITE_ERROR,
			"Database not open",
			false);
	}
}

sqlite3_stmt* DbHelper::Compile(const char * szSQL)
{
	CheckDB();

	const char * szTail = 0;
	sqlite3_stmt *pStmt;

	int nRet = sqlite3_prepare(mpDB, szSQL, -1, &pStmt, &szTail);

	if (nRet != SQLITE_OK)
	{
		const char * szError = sqlite3_errmsg(mpDB);
		throw DbException(nRet, szError, false);
	}

	return pStmt;
}

void DbHelper::Open(const char * szFileName)
{
	int nRet = sqlite3_open(szFileName, &mpDB);
	if (nRet != SQLITE_OK)
	{
		const char * szError = sqlite3_errmsg(mpDB);
		throw DbException(nRet, szError, false);
	}
}

void DbHelper::Close()
{
	if (mpDB)
	{
		if (sqlite3_close(mpDB) == SQLITE_OK)
		{
			mpDB = 0; //一旦关闭数据库指针，要置为0，防止多次关闭出错  
		}
		else
		{
			throw DbException(CPPSQLITE_ERROR,
				"Unable to close database",
				false);
		}
	}
}

int DbHelper::ExecDML(const char * szSQL)
{
	CheckDB();

	char* szError = 0;

	int nRet = sqlite3_exec(mpDB, szSQL, 0, 0, &szError);

	if (nRet == SQLITE_OK)
	{
		return sqlite3_changes(mpDB);  //返回这个执行影响的行数  
	}
	else
	{
		throw DbException(nRet, szError, false);
	}
}

DbQuery DbHelper::ExecQuery(const char * szSQL)
{
	CheckDB();

	//编译一条指针对象，用临时变量存储，传递给DbQuery后，  
	//这个临时sqlite3_stmt*对象会自动消失，最后只有一份保留在DbQuery中  
	sqlite3_stmt *pStmt = Compile(szSQL);

	int nRet = sqlite3_step(pStmt);

	if (nRet == SQLITE_DONE) //表明这个查询没有返回结果  
	{
		return DbQuery(mpDB, pStmt, true); //所以将第三个字段设置为true，表明到达查询结果末尾处  
	}
	else if (nRet == SQLITE_ROW) //这个查询中至少有一行记录  
	{
		return DbQuery(mpDB, pStmt, false); //false表明没有到达查询结果末尾  
	}
	else
	{
		nRet = sqlite3_finalize(pStmt);
		const char * szError = sqlite3_errmsg(mpDB);
		throw DbException(nRet, szError, false);
	}
}

DbTable DbHelper::GetTable(const char * szSQL)
{
	CheckDB();

	char* szError = 0;
	char** paszResults = 0;
	int nRet;
	int nRows(0);
	int nCols(0);

	nRet = sqlite3_get_table(mpDB, szSQL, &paszResults, &nRows, &nCols, &szError);

	if (nRet == SQLITE_OK)
	{
		return DbTable(paszResults, nRows, nCols);
	}
	else
	{
		throw DbException(nRet, szError, false);
	}
}

DbStatement DbHelper::CompileStatement(const char * szSQL)
{
	CheckDB();

	sqlite3_stmt *pStmt = Compile(szSQL);
	return DbStatement(mpDB, pStmt);
}
