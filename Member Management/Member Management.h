
// Member Management.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once
#include "DBDataSource.h"

extern CDBDataSource g_DataSource;

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CMemberManagementApp:
// �� Ŭ������ ������ ���ؼ��� Member Management.cpp�� �����Ͻʽÿ�.
//

class CMemberManagementApp : public CWinApp
{
public:
	CMemberManagementApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CMemberManagementApp theApp;