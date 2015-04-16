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
	const_cast<DbTable&>(rTable).mpaszResults = 0; //当表复制时，销毁原来的表，防止丢失修改  
}

DbTable::DbTable(char **paszResults, int nRows, int nCols)
{
	mpaszResults = paszResults; //给出一个一维指针数组，初始化一个表  
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
		sqlite3_free_table(mpaszResults);  //利用库函数销毁表存储内容  
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

	return mpaszResults[nField]; //一位数组的头mnCols个元素存放的是表的字段名称，存储具体位置是mpaszResults[0,,,mnCols-1]。  
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

	//根据要查询的当前行与列值算出在一位数组中的索引下标，额外加一个mnCols是第一行存储的是字段名  
	int nIndex = mnCurrentRow*mnCols + mnCols + nField;
	return mpaszResults[nIndex];
}

//根据字段名称来访问某一列的数据  
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

//这里的获取具体类型数值函数，需要用户对数据库中的表有一定的了解，知道哪些字段存储的是什么内容  
//并且使用的是外部传递引用的形式  
bool DbTable::GetIntField(int nField, int &rDest)
{
	if (FieldIsNull(nField))
	{
		return false;
	}
	else
	{
		//atoi()函数是C库函数，讲数值型字符串转换为整型值  
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
		//C库函数，将数值型字符串转换为浮点数  
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

//在每一次需要获取数据的时候都要设置要访问的行值  
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
