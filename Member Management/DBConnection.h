#pragma once
//#define TABLE_CUST_INFO 1
//#define TABLE_FC_DATA_FRONT 2
//#define TABLE_DC_DATA_LEFT_RIGHT 3
//#define TABLE_FC_PICTURE 4
//#define TABLE_FC_POS 5
//#define TABLE_SIF_DATA 10
//#define TABLE_SIF_QA 11

#include "TestTable.h"

class CDBConnection
{
public:
	CDBConnection(CString strPathDB);
	~CDBConnection();

	CCommand<CAccessor<CTestTableAccessor> > m_testtable;



	CSession m_session;
	operator const CSession&()
	{
		return m_session;

	}


public:
	class Exception
	{
	private:
		int ErrorCode;
		HRESULT ErrorHr;

	public:
		Exception(int err, HRESULT errhr) : ErrorCode(err), ErrorHr(errhr) {}
		int GetErrorCode() { return ErrorCode; }
		HRESULT GetErrorHr() { return ErrorHr; }
		CString ReportError()
		{
			switch (ErrorCode)
			{
			case 1:
				return L"Database Source Open Failed. (Database)";
			case 2:
				return L"Table Open Failed. (Database)";
			case 3:
				return L"Session Open Failed. (Database)";
			case 4:
				return L"Transaction Failed. (Database)";
			case 5:
				return L"Commit Failed. (Database)";
			default:
				return L"Not Define Error. (Database)";
			}
		}
	};

public:
	CString m_strPathDBFile;
	HRESULT OpenSession(CDataSource* db);
	int CommandOpen(CCommand<CAccessor<CTestTableAccessor> >& accessor, CString strCommand, bool bBind = false);

	int CommandOpen(CCommand<CNoAccessor>& accessor, CString strCommand);
	void CloseSession();

	void InsertAddCommand(CString& strCommand, CString strField, CString strVal);
	void InsertAddCommand(CString& strCommand, CString strField, int iVal);
	void InsertAddCommand(CString& strCommand, CString strField, long lVal);
	void InsertAddCommand(CString& strCommand, CString strField, double dVal);

	void UpdateAddCommand(CString& strCommand, CString strField, CString strVal);
	void UpdateAddCommand(CString& strCommand, CString strField, int iVal);
	void UpdateAddCommand(CString& strCommand, CString strField, long lVal);
	void UpdateAddCommand(CString& strCommand, CString strField, double dVal);

	CString ConvertUniEncoding2CString(CString strVal);

	long CommandGetCountDataFront(long lSerial, long lMeasureno);

};

