#pragma once
#define CPPSQLITE_ERROR 1000
class DbException
{
private:
	int mnErrCode;
	char *mpszErrMessage;

public:
	DbException(const int nErrNode,
		const char *szErrMess,
		bool bDeleteMess);
	DbException(const DbException &e);
	~DbException();

	const int ErrorCode() { return mnErrCode; }
	const char *ErrorMessage() { return mpszErrMessage; }

	static const char* ErrorCodeAsString(const int nErrCode);
};

