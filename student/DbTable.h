#pragma once
class DbTable
{
private:
	int mnCurrentRow;
	int mnRows;
	int mnCols;
	char **mpaszResults;

	void CheckResluts();

public:
	DbTable();
	DbTable(const DbTable &rTable);
	DbTable(char **paszResults, int nRows, int nCols);
	~DbTable();

	DbTable& operator= (const DbTable &rTable);

	int NumOfFields();
	int NumOfRows();

	const char* NameOfField(int nField);

	const char* ValueOfField(int nField);
	const char* ValueOfField(const char *szField);

	bool FieldIsNull(int nField);
	bool FieldIsNull(const char *szField);

	bool GetIntField(int nField, int &rDest);
	bool GetIntField(const char *szField, int &rDest);

	bool GetFloatField(int nField, double &rDest);
	bool GetFloatField(const char *szField, double &rDest);

	bool GetStringField(int nField, char *&rDest);
	bool GetStringField(const char *szField, char *&rDset);

	void SetRow(int nRow);

	void finalize();
};

