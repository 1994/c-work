#include "DbTable.h"
#include "sqlite3.h"
#include "DbException.h"
#include <string>

DbTable::DbTable()
{
	mnCols = 0;
	mnRows = 0;
	mnCurrentRow = 0;
	mpaszResults = 0;
}

DbTable::DbTable(const DbTable &rTable)
{
	mnCols = rTable.mnCols;
	mnRows = rTable.mnRows;
	mnCurrentRow = rTable.mnCurrentRow;
	mpaszResults = rTable.mpaszResults;
	const_cast<DbTable&>(rTable).mpaszResults = 0; //������ʱ������ԭ���ı���ֹ��ʧ�޸�  
}

DbTable::DbTable(char **paszResults, int nRows, int nCols)
{
	mpaszResults = paszResults; //����һ��һάָ�����飬��ʼ��һ����  
	mnCols = nCols;
	mnRows = nRows;
	mnCurrentRow = 0;
}

DbTable::~DbTable()
{
	finalize();
}

DbTable& DbTable::operator= (const DbTable &rTable)
{
	finalize();

	mpaszResults = rTable.mpaszResults;
	const_cast<DbTable &>(rTable).mpaszResults = 0;
	mnCols = rTable.mnCols;
	mnRows = rTable.mnRows;
	mnCurrentRow = rTable.mnCurrentRow;

	return *this;
}

void DbTable::finalize()
{
	if (mpaszResults)
	{
		sqlite3_free_table(mpaszResults);  //���ÿ⺯�����ٱ�洢����  
		mpaszResults = 0;
	}
}

int DbTable::NumOfFields()
{
	CheckResluts();

	return mnCols;
}

int DbTable::NumOfRows()
{
	CheckResluts();

	return mnRows;
}

const char* DbTable::NameOfField(int nField)
{
	CheckResluts();

	if (nField < 0 || nField > mnCols - 1)
	{
		throw DbException(CPPSQLITE_ERROR,
			"Invalid field index requested",
			false);
	}

	return mpaszResults[nField]; //һλ�����ͷmnCols��Ԫ�ش�ŵ��Ǳ���ֶ����ƣ��洢����λ����mpaszResults[0,,,mnCols-1]��  
}

const char* DbTable::ValueOfField(int nField)
{
	CheckResluts();

	if (nField < 0 || nField > mnCols - 1)
	{
		throw DbException(CPPSQLITE_ERROR,
			"Invalid field index requested",
			false);
	}

	//����Ҫ��ѯ�ĵ�ǰ������ֵ�����һλ�����е������±꣬�����һ��mnCols�ǵ�һ�д洢�����ֶ���  
	int nIndex = mnCurrentRow*mnCols + mnCols + nField;
	return mpaszResults[nIndex];
}

//�����ֶ�����������ĳһ�е�����  
const char* DbTable::ValueOfField(const char *szField)
{
	CheckResluts();

	if (szField)
	{
		for (int nField = 0; nField < mnCols; nField++)
		{
			if (strcmp(szField, mpaszResults[nField]) == 0)
			{
				int nIndex = mnCurrentRow*mnCols + mnCols + nField;
				return mpaszResults[nIndex];
			}
		}
	}

	throw DbException(CPPSQLITE_ERROR,
		"Invalid field name requested",
		false);
}

bool DbTable::FieldIsNull(int nField)
{
	CheckResluts();

	return (ValueOfField(nField) == 0);
}

bool DbTable::FieldIsNull(const char* szField)
{
	CheckResluts();

	return (ValueOfField(szField) == 0);
}

//����Ļ�ȡ����������ֵ��������Ҫ�û������ݿ��еı���һ�����˽⣬֪����Щ�ֶδ洢����ʲô����  
//����ʹ�õ����ⲿ�������õ���ʽ  
bool DbTable::GetIntField(int nField, int &rDest)
{
	if (FieldIsNull(nField))
	{
		return false;
	}
	else
	{
		//atoi()������C�⺯��������ֵ���ַ���ת��Ϊ����ֵ  
		rDest = atoi(ValueOfField(nField));
		return true;
	}
}

bool DbTable::GetIntField(const char *szField, int &rDest)
{
	if (FieldIsNull(szField))
	{
		return false;
	}
	else
	{
		rDest = atoi(ValueOfField(szField));
		return true;
	}
}

bool DbTable::GetFloatField(int nField, double &rDest)
{
	if (FieldIsNull(nField))
	{
		return false;
	}
	else
	{
		//C�⺯��������ֵ���ַ���ת��Ϊ������  
		rDest = atof(ValueOfField(nField));
		return true;
	}
}

bool DbTable::GetFloatField(const char *szField, double &rDest)
{
	if (FieldIsNull(szField))
	{
		return false;
	}
	else
	{
		rDest = atof(ValueOfField(szField));
		return true;
	}
}

bool DbTable::GetStringField(int nField, char *&rDest)
{
	if (FieldIsNull(nField))
	{
		return false;
	}
	else
	{
		rDest = const_cast<char *>(ValueOfField(nField));
		return true;
	}
}
bool DbTable::GetStringField(const char *szField, char *&rDset)
{
	if (FieldIsNull(szField))
	{
		return false;
	}
	else
	{
		rDset = const_cast<char *>(ValueOfField(szField));
		return true;
	}
}

//��ÿһ����Ҫ��ȡ���ݵ�ʱ��Ҫ����Ҫ���ʵ���ֵ  
void DbTable::SetRow(int nRow)
{
	CheckResluts();

	if (nRow < 0 || nRow > mnCols - 1)
	{
		throw DbException(CPPSQLITE_ERROR,
			"Invalid row index requested",
			false);
	}

	mnCurrentRow = nRow;
}

void DbTable::CheckResluts()
{
	if (mpaszResults == 0)
	{
		throw DbException(CPPSQLITE_ERROR,
			"Null Results pointer",
			false);
	}
}
