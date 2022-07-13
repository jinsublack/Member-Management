#pragma once
class CDBDataSource
{
public:
	CDBDataSource();
	~CDBDataSource();
	CString m_strPathDB;
private:
	CDataSource m_db;
public:
	CDataSource* GetDataSource();
	HRESULT OpenDataSource(CString strPathDB);
	void CloseDataSource();
};


