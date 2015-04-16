#pragma once
#include "sqlite3.h"
class DbQuery
{
private:
	sqlite3 *mpDB;
	sqlite3_stmt *mpStmt;
	bool mbEof;
	int mnCols;

	void CheckStmt();
public:
	DbQuery();
	DbQuery(sqlite3 *pdb, sqlite3_stmt *pStmt, bool bEof);
	DbQuery(const DbQuery &rQuery);
	DbQuery& operator= (const DbQuery &rQuery);
	~DbQuery();

	int FieldNums();

	int FieldIndex(const char* szField);
	const char* FieldName(int nField);

	int FieldDataType(int nField);
	const char* FieldDeclType(int nField);

	const char* FieldValue(int nField);
	const char* FieldValue(const char *szField);

	bool FieldIsNull(int nField);
	bool FieldIsNull(const char *szField);

	bool GetIntValue(int nField, int &rDest);
	bool GetIntValue(const char *szField, int &rDest);

	bool GetFloatValue(int nField, double &rDest);
	bool GetFloatValue(const char *szField, double &rDest);

	bool GetStringValue(int nField, char *&rDest);
	bool GetStringValue(const char *szField, char *&rDest);

	bool Eof();

	void NextRow();

	void Finalize();
};

