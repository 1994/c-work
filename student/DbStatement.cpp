#include "DbStatement.h"
#include "DbException.h"
#include <string>
using namespace std;

const bool DONT_DELETE_MSG = false;
DbStatement::DbStatement()
{
	mpDB = 0;
	mpStmt = 0;
}

DbStatement::DbStatement(sqlite3 *pdb, sqlite3_stmt *pstmt)
{
	mpDB = pdb;
	mpStmt = pstmt;
}

DbStatement::DbStatement(const DbStatement &rStatement)
{
	mpDB = rStatement.mpDB;
	mpStmt = rStatement.mpStmt;
	const_cast<DbStatement &>(rStatement).mpStmt = 0;
}

DbStatement::~DbStatement()
{

}

DbStatement& DbStatement::operator = (const DbStatement &rStatement)
{
	mpDB = rStatement.mpDB;
	mpStmt = rStatement.mpStmt;
	const_cast<DbStatement &>(rStatement).mpStmt = 0;
	return *this;
}

int DbStatement::ExecDML()
{
	CheckDB();
	CheckStmt();

	const char *szError = 0;

	int nRet = sqlite3_step(mpStmt);

	if (nRet == SQLITE_DONE)
	{
		int nRowChanged = sqlite3_changes(mpDB);  //������Ӱ�������  

		nRet = sqlite3_reset(mpStmt);  //����sqlite3_stmt*����  
		if (nRet != SQLITE_OK)
		{
			szError = sqlite3_errmsg(mpDB);
			throw DbException(nRet, szError, DONT_DELETE_MSG);
		}

		return nRowChanged;
	}
	else
	{
		nRet = sqlite3_reset(mpStmt);
		szError = sqlite3_errmsg(mpDB);
		throw DbException(nRet, szError, DONT_DELETE_MSG);
	}
}


DbQuery DbStatement::ExecQuery()
{
	CheckDB();
	CheckStmt();

	int nRet = sqlite3_step(mpStmt);
	if (nRet == SQLITE_DONE)
	{
		return DbQuery(mpDB, mpStmt, true);//����һ����ѯ��û�в�ѯ�����������Ϊtrue  
	}
	else if (nRet == SQLITE_ROW)
	{
		return DbQuery(mpDB, mpStmt, false);//��ѯ���н���ģ�����false�����ⲻ����ɾ���β�ѯ����  
	}
	else
	{
		nRet = sqlite3_reset(mpStmt);
		const char* szError = sqlite3_errmsg(mpDB);
		throw DbException(nRet, szError, DONT_DELETE_MSG);
	}
}

void DbStatement::CheckDB()
{
	if (mpDB == 0)
	{
		throw DbException(CPPSQLITE_ERROR,
			"Database not open",
			DONT_DELETE_MSG);
	}
}

void DbStatement::CheckStmt()
{
	if (mpStmt == 0)
	{
		throw DbException(CPPSQLITE_ERROR,
			"Null stmt pointer",
			DONT_DELETE_MSG);
	}
}

void DbStatement::Reset()
{
	if (mpStmt)
	{
		int nRet = sqlite3_reset(mpStmt);

		if (nRet != SQLITE_OK)
		{
			const char* szError = sqlite3_errmsg(mpDB);
			throw DbException(nRet, szError, DONT_DELETE_MSG);
		}
	}
}

void DbStatement::Finalize()
{
	if (mpStmt)
	{
		int nRet = sqlite3_finalize(mpStmt);
		mpStmt = 0;

		if (nRet != SQLITE_OK)
		{
			const char* szError = sqlite3_errmsg(mpDB);
			throw DbException(nRet, szError, DONT_DELETE_MSG);
		}
	}
}