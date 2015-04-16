#include "DbQuery.h"
#include "DbException.h"
#include <string>

DbQuery::DbQuery()
{
	mpDB = 0;
	mpStmt = 0;
	mnCols = 0;
	mbEof = true;
}

DbQuery::DbQuery(sqlite3 *pdb, sqlite3_stmt *pStmt, bool bEof)
{
	mpDB = pdb;
	mpStmt = pStmt;
	mbEof = bEof;
	mnCols = sqlite3_column_count(pStmt);
}

DbQuery::DbQuery(const DbQuery &rQuery)
{
	mpStmt = rQuery.mpStmt;
	const_cast<DbQuery &>(rQuery).mpStmt = 0;
	mnCols = rQuery.mnCols;
	mbEof = rQuery.mbEof;
}

DbQuery& DbQuery::operator =(const DbQuery &rQuery)
{
	mpStmt = rQuery.mpStmt;
	const_cast<DbQuery &>(rQuery).mpStmt = 0;
	mnCols = rQuery.mnCols;
	mbEof = rQuery.mbEof;

	return *this;
}

DbQuery::~DbQuery()
{
	Finalize();
}

void DbQuery::CheckStmt()
{
	if (mpStmt == 0)
	{
		throw DbException(CPPSQLITE_ERROR,
			"Invalid Stmt Pointer",
			false);
	}
}

int DbQuery::FieldNums()
{
	CheckStmt();

	return mnCols;
}

//根据字段名返回列索引  
int DbQuery::FieldIndex(const char* szField)
{
	CheckStmt();

	if (szField)
	{
		for (int nField = 0; nField < mnCols; nField++)
		{
			//后面还有很多类似的函数，参数差不多，需要一个sqlite3_stmt*和列索引值，这应该是内部查询了之后返回的结果，而不是事先保存的  
			const char *szTemp = sqlite3_column_name(mpStmt, nField);
			if (strcmp(szTemp, szField) == 0)
			{
				return nField;
			}
		}
	}

	throw DbException(CPPSQLITE_ERROR,
		"Invalid field name requested",
		false);
}
const char* DbQuery::FieldName(int nField)
{
	CheckStmt();

	if (nField < 0 || nField > mnCols - 1)
	{
		throw DbException(CPPSQLITE_ERROR,
			"Invalid field index requested",
			false);
	}

	return sqlite3_column_name(mpStmt, nField);
}

int DbQuery::FieldDataType(int nField)
{
	CheckStmt();

	if (nField < 0 || nField > mnCols - 1)
	{
		throw DbException(CPPSQLITE_ERROR,
			"Invalid field index requested",
			false);
	}

	return sqlite3_column_type(mpStmt, nField);
}
const char* DbQuery::FieldDeclType(int nField)
{
	CheckStmt();

	if (nField < 0 || nField > mnCols - 1)
	{
		throw DbException(CPPSQLITE_ERROR,
			"Invalid field index requested",
			false);
	}

	return sqlite3_column_decltype(mpStmt, nField);
}

const char* DbQuery::FieldValue(int nField)
{
	CheckStmt();

	if (nField < 0 || nField > mnCols - 1)
	{
		throw DbException(CPPSQLITE_ERROR,
			"Invalid field index requested",
			false);
	}

	return (const char*)sqlite3_column_text(mpStmt, nField);

}

const char* DbQuery::FieldValue(const char *szField)
{
	int nField = FieldIndex(szField);
	return FieldValue(nField);
}

bool DbQuery::FieldIsNull(int nField)
{
	return (FieldDataType(nField) == SQLITE_NULL);
}

bool DbQuery::FieldIsNull(const char *szField)
{
	int nField = FieldIndex(szField);
	return (FieldDataType(nField) == SQLITE_NULL);
}

bool DbQuery::GetIntValue(int nField, int &rDest)
{
	if (FieldDataType(nField) == SQLITE_NULL)
	{
		return false;
	}
	else
	{
		rDest = sqlite3_column_int(mpStmt, nField);
		return true;
	}
}

bool DbQuery::GetIntValue(const char *szField, int &rDest)
{
	int nField = FieldIndex(szField);
	return GetIntValue(nField, rDest);
}

bool DbQuery::GetFloatValue(int nField, double &rDest)
{
	if (FieldDataType(nField) == SQLITE_NULL)
	{
		return false;
	}
	else
	{
		rDest = sqlite3_column_double(mpStmt, nField);
		return true;
	}
}
bool DbQuery::GetFloatValue(const char *szField, double &rDest)
{
	int nField = FieldIndex(szField);
	return GetFloatValue(nField, rDest);
}

bool DbQuery::GetStringValue(int nField, char *&rDest)
{
	if (FieldDataType(nField) == SQLITE_NULL)
	{
		return false;
	}
	else
	{
		rDest = const_cast<char *>((const char*)sqlite3_column_text(mpStmt, nField));
		return true;
	}
}
bool DbQuery::GetStringValue(const char *szField, char *&rDest)
{
	int nField = FieldIndex(szField);
	return GetStringValue(nField, rDest);
}

bool DbQuery::Eof()
{
	CheckStmt();

	return mbEof;
}

void DbQuery::NextRow()
{
	CheckStmt();

	int nRet = sqlite3_step(mpStmt);

	if (nRet == SQLITE_DONE)
	{
		// no rows  
		mbEof = true;
	}
	else if (nRet == SQLITE_ROW)
	{
		// more rows, nothing to do  
	}
	else
	{
		nRet = sqlite3_finalize(mpStmt);
		mpStmt = 0;
		const char* szError = sqlite3_errmsg(mpDB);
		throw DbException(nRet, szError, false);
	}
}

void DbQuery::Finalize()
{
	if (mpStmt)
	{
		int nRet = sqlite3_finalize(mpStmt);
		mpStmt = 0;
		if (nRet != SQLITE_OK)
		{
			const char* szError = sqlite3_errmsg(mpDB);
			throw DbException(nRet, szError, false);
		}
	}
}