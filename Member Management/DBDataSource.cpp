#include "stdafx.h"
#include "DBDataSource.h"


CDBDataSource::CDBDataSource()
{
}


CDBDataSource::~CDBDataSource()
{
}

CDataSource * CDBDataSource::GetDataSource()
{
	CComVariant var;
	HRESULT hr;
	hr = m_db.GetProperty(DBPROPSET_DATASOURCEINFO, DBPROP_PROVIDERNAME, &var);
	if (FAILED(hr))
	{
#ifdef _DEBUG
		AtlTraceErrorRecords(hr);
#endif

		hr = OpenDataSource(m_strPathDB);
		if (FAILED(hr))
		{
#ifdef _DEBUG
			AtlTraceErrorRecords(hr);
#endif
			return nullptr;
		}
	}

	return &m_db;
}

//데이터 베이스 연결
HRESULT CDBDataSource::OpenDataSource(CString strPathDB)
{
	m_strPathDB = strPathDB;
	CString strPathDBFile;
	strPathDBFile = strPathDB + L"\\TestDatabase.piead";
	HRESULT hr = S_OK;
	CString strPassword(L"pie1234!");
	//char buff[8] = { 0x70,0x69,0x65,0x39,0x31,0x33,0x30,0x7E };
	//for (int i = 0; i < 8; i++)
		//strPassword += buff[i];
	CString strConnection(L"");
	strConnection.Format(L"Provider=Microsoft.ACE.OLEDB.12.0;User ID=Admin;Data Source=%s;Mode=Share Deny None;OLE DB Services=-5;Extended Properties=\"\";Jet OLEDB:Database Password=%s"
		, strPathDBFile, strPassword);
	hr = m_db.OpenFromInitializationString(strConnection);
	if (FAILED(hr))
	{
#ifdef _DEBUG
		AtlTraceErrorRecords(hr);
#endif
		return hr;
	}

	return hr;
}

void CDBDataSource::CloseDataSource()
{
	m_db.Close();
}
