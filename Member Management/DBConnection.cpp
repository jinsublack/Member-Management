#include "stdafx.h"
#include "DBConnection.h"

#include <string>
#include <vector>

#include "Member ManagementDlg.h"

CDBConnection::CDBConnection(CString strPathDB)
	: m_strPathDBFile(_T(""))
{
	m_strPathDBFile = strPathDB + L"\\TestDatabase.piead";
}


CDBConnection::~CDBConnection()
{
	CloseSession();
}


HRESULT CDBConnection::OpenSession(CDataSource* db)
{
	if (db == nullptr)
	{
		throw Exception(1, E_FAIL);
	}
	HRESULT hr;
	hr = m_session.Open(*db);
	if (FAILED(hr))
	{
#ifdef _DEBUG
		AtlTraceErrorRecords(hr);
#endif
		throw Exception(3, hr);

	}
	return hr;


}


void CDBConnection::CloseSession()
{
	try
	{

		m_session.Close();
	}
	catch (CException* ex)
	{
		TCHAR szMsg[1024] = { 0, };
		ex->GetErrorMessage(szMsg, 1024);
		CString strMsg(szMsg);
		AfxMessageBox(strMsg);
	}
}

int CDBConnection::CommandOpen(CCommand<CAccessor<CTestTableAccessor> >& accessor, CString strCommand, bool bBind)
{
	HRESULT hr = S_OK;
	hr = accessor.Open(m_session, strCommand, NULL, NULL, DBGUID_DEFAULT, bBind);
	if (FAILED(hr))
	{
#ifdef _DEBUG
		AtlTraceErrorRecords(hr);
#endif
		throw Exception(2, hr);
	}
	else
		return TRUE;

}

int CDBConnection::CommandOpen(CCommand<CNoAccessor>& accessor, CString strCommand)
{
	HRESULT hr = S_OK;
	hr = accessor.Open(m_session, strCommand, NULL, NULL, DBGUID_DEFAULT, false);
	if (FAILED(hr))
	{
#ifdef _DEBUG
		AtlTraceErrorRecords(hr);
#endif
		throw Exception(2, hr);
	}
	else
		return TRUE;
}

void CDBConnection::InsertAddCommand(CString& strCommand, CString strField, CString strVal)
{
	//insert into FC_DATA_FRONT () values ()
	CString strtmp = strCommand;
	int field_start = strtmp.Find(')');

	CString str(strtmp.GetAt(field_start - 1));
	if (str == L"(")
	{
		strField.Insert(0, L"[");
		strField.Insert(strField.GetLength(), L"]");
		strtmp.Insert(field_start, strField);
		int value_start = strtmp.ReverseFind(')');
		strVal.Insert(0, L"'");
		strVal.Insert(strVal.GetLength(), L"'");
		strtmp.Insert(value_start, strVal);
	}
	else
	{
		strField.Insert(0, L"[");
		strField.Insert(strField.GetLength(), L"]");
		strField.Insert(0, L",");
		strtmp.Insert(field_start, strField);
		int value_start = strtmp.ReverseFind(')');
		strVal.Insert(0, L"'");
		strVal.Insert(strVal.GetLength(), L"'");
		strVal.Insert(0, L",");
		strtmp.Insert(value_start, strVal);
	}
	strCommand = strtmp;
}
void CDBConnection::InsertAddCommand(CString& strCommand, CString strField, int iVal)
{
	//insert into FC_DATA_FRONT () values ()
	CString strtmp = strCommand;
	int field_start = strtmp.Find(')');

	CString str(strtmp.GetAt(field_start - 1));
	if (str == L"(")
	{
		strField.Insert(0, L"[");
		strField.Insert(strField.GetLength(), L"]");
		strtmp.Insert(field_start, strField);
		strtmp.Insert(field_start, strField);
		int value_start = strtmp.ReverseFind(')');
		CString strVal;
		strVal.Format(L"%d", iVal);
		strtmp.Insert(value_start, strVal);
	}
	else
	{
		strField.Insert(0, L"[");
		strField.Insert(strField.GetLength(), L"]");
		strField.Insert(0, L",");
		strtmp.Insert(field_start, strField);
		int value_start = strtmp.ReverseFind(')');
		CString strVal;
		strVal.Format(L"%d", iVal);
		strVal.Insert(0, L",");
		strtmp.Insert(value_start, strVal);
	}
	strCommand = strtmp;
}
void CDBConnection::InsertAddCommand(CString& strCommand, CString strField, long lVal)
{
	//insert into FC_DATA_FRONT () values ()
	CString strtmp = strCommand;
	int field_start = strtmp.Find(')');

	CString str(strtmp.GetAt(field_start - 1));
	if (str == L"(")
	{
		strField.Insert(0, L"[");
		strField.Insert(strField.GetLength(), L"]");
		strtmp.Insert(field_start, strField);
		strtmp.Insert(field_start, strField);
		int value_start = strtmp.ReverseFind(')');
		CString strVal;
		strVal.Format(L"%ld", lVal);
		strtmp.Insert(value_start, strVal);
	}
	else
	{
		strField.Insert(0, L"[");
		strField.Insert(strField.GetLength(), L"]");
		strField.Insert(0, L",");
		strtmp.Insert(field_start, strField);
		int value_start = strtmp.ReverseFind(')');
		CString strVal;
		strVal.Format(L"%ld", lVal);
		strVal.Insert(0, L",");
		strtmp.Insert(value_start, strVal);
	}
	strCommand = strtmp;
}
void CDBConnection::InsertAddCommand(CString& strCommand, CString strField, double dVal)
{
	//insert into FC_DATA_FRONT () values ()
	CString strtmp = strCommand;
	int field_start = strtmp.Find(')');

	CString str(strtmp.GetAt(field_start - 1));
	if (str == L"(")
	{
		strField.Insert(0, L"[");
		strField.Insert(strField.GetLength(), L"]");
		strtmp.Insert(field_start, strField);
		strtmp.Insert(field_start, strField);
		int value_start = strtmp.ReverseFind(')');
		CString strVal;
		strVal.Format(L"%lf", dVal);
		strtmp.Insert(value_start, strVal);
	}
	else
	{
		strField.Insert(0, L"[");
		strField.Insert(strField.GetLength(), L"]");
		strField.Insert(0, L",");
		strtmp.Insert(field_start, strField);
		int value_start = strtmp.ReverseFind(')');
		CString strVal;
		strVal.Format(L"%lf", dVal);
		strVal.Insert(0, L",");
		strtmp.Insert(value_start, strVal);
	}
	strCommand = strtmp;
}

void CDBConnection::UpdateAddCommand(CString& strCommand, CString strField, CString strVal)
{
	//update FC_DATA_FRONT set ~ where ~
	CString strtmp = strCommand;
	int field_start = strtmp.Find(L"where");

	CString str(strtmp.GetAt(field_start - 2));
	if (str == L"t")
	{
		CString strSet(L"t");
		strSet.Format(L"%s='%s' ", strField, strVal);
		strtmp.Insert(field_start, strSet);
	}
	else
	{
		CString strSet(L"");
		strSet.Format(L",%s='%s' ", strField, strVal);
		strtmp.Insert(field_start, strSet);
	}
	strCommand = strtmp;
}
void CDBConnection::UpdateAddCommand(CString& strCommand, CString strField, int iVal)
{
	//update FC_DATA_FRONT set ~ where ~
	CString strtmp = strCommand;
	int field_start = strtmp.Find(L"where");

	CString str(strtmp.GetAt(field_start - 2));
	if (str == L"t")
	{
		CString strSet(L"");
		strSet.Format(L"%s=%d ", strField, iVal);
		strtmp.Insert(field_start, strSet);
	}
	else
	{
		CString strSet(L"");
		strSet.Format(L",%s=%d ", strField, iVal);
		strtmp.Insert(field_start, strSet);
	}
	strCommand = strtmp;
}
void CDBConnection::UpdateAddCommand(CString& strCommand, CString strField, long lVal)
{
	//update FC_DATA_FRONT set ~ where ~
	CString strtmp = strCommand;
	int field_start = strtmp.Find(L"where");

	CString str(strtmp.GetAt(field_start - 2));
	if (str == L"t")
	{
		CString strSet(L"");
		strSet.Format(L"%s=%ld ", strField, lVal);
		strtmp.Insert(field_start, strSet);
	}
	else
	{
		CString strSet(L"");
		strSet.Format(L",%s=%ld ", strField, lVal);
		strtmp.Insert(field_start, strSet);
	}
	strCommand = strtmp;
}
void CDBConnection::UpdateAddCommand(CString& strCommand, CString strField, double dVal)
{
	//update FC_DATA_FRONT set ~ where ~
	CString strtmp = strCommand;
	int field_start = strtmp.Find(L"where");

	CString str(strtmp.GetAt(field_start - 2));
	if (str == L"t")
	{
		CString strSet(L"");
		strSet.Format(L"%s=%lf ", strField, dVal);
		strtmp.Insert(field_start, strSet);
	}
	else
	{
		CString strSet(L"");
		strSet.Format(L",%s=%lf ", strField, dVal);
		strtmp.Insert(field_start, strSet);
	}
	strCommand = strtmp;
}


CString CDBConnection::ConvertUniEncoding2CString(CString strVal)
{
	CString unicode = L"";
	CString strCust = strVal;

	std::wstring ws(strCust);
	int wch_len = (int)ws.size();
	if (wch_len < 4)
		return strVal;

	std::wstring ws_dst;

	for (int i = 0; i < wch_len; i += 4)
	{
		std::wstring ws_hex(ws, i, 4);
		wchar_t wch = (wchar_t)(unsigned long)std::stoul(ws_hex.c_str(), NULL, 16);
		ws_dst.push_back(wch);
	}

	return CString(ws_dst.c_str());
}

long CDBConnection::CommandGetCountDataFront(long lSerial, long lMeasureno)
{
	long value = 0;
	CCommand<CAccessor<CTestTableAccessor> > accessor;
	HRESULT hr = S_OK;
	CString strCommand(L"");
	//strCommand.Format(L"select COUNT(MEASURE_NO) as SERIAL from FC_POS_FRONT where SERIAL = %ld and MEASURE_NO = %ld", lSerial, lMeasureno);
	strCommand.Format(L"select COUNT(MEASURE_NO) as ID from TestTable where SERIAL = %ld and MEASURE_NO = %ld", lSerial, lMeasureno);
	hr = accessor.Open(m_session, strCommand, NULL, NULL, DBGUID_DEFAULT, true);
	if (FAILED(hr))
	{
#ifdef _DEBUG
		AtlTraceErrorRecords(hr);
#endif
		throw Exception(2, hr);
	}
	else
	{
		if (accessor.MoveNext() == S_OK)
			value = accessor.m_ID;

	}
	accessor.Close();
	accessor.ReleaseCommand();

	return value;
}