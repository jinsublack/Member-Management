
// Member ManagementDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "Member Management.h"
#include "Member ManagementDlg.h"
#include "afxdialogex.h"

#include "DBConnection.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

// �����Դϴ�.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMemberManagementDlg ��ȭ ����



CMemberManagementDlg::CMemberManagementDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MEMBERMANAGEMENT_DIALOG, pParent)
	, m_editName(_T(""))
	, m_editBirth(_T(""))
	, m_editNumber(_T(""))
	, m_nrdoSex(0)
	, m_editNote(_T(""))
	, m_PathConfig(_T(""))
	, m_PathCur(_T(""))
	, m_nrdoSearch(0)
	, m_editSearch(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMemberManagementDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MEMBER, m_List);
	DDX_Text(pDX, IDC_EDIT_NAME, m_editName);
	DDV_MaxChars(pDX, m_editName, 50);
	DDX_Text(pDX, IDC_EDIT_BIRTH, m_editBirth);
	DDV_MaxChars(pDX, m_editBirth, 8);
	DDX_Text(pDX, IDC_EDIT_NUMBER, m_editNumber);
	DDV_MaxChars(pDX, m_editNumber, 20);
	DDX_Radio(pDX, IDC_RADIO_MALE, m_nrdoSex);
	DDX_Text(pDX, IDC_EDIT_NOTE, m_editNote);
	DDV_MaxChars(pDX, m_editNote, 500);
	DDX_Radio(pDX, IDC_RADIO_SEARCH_NAME, m_nrdoSearch);
	DDX_Text(pDX, IDC_EDIT_SEARCH, m_editSearch);
}

BEGIN_MESSAGE_MAP(CMemberManagementDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_REGISTER, &CMemberManagementDlg::OnBnClickedRegister)
	ON_BN_CLICKED(IDC_DELETE, &CMemberManagementDlg::OnBnClickedDelete)
	ON_NOTIFY(NM_CLICK, IDC_MEMBER, &CMemberManagementDlg::OnClickMember)
	ON_BN_CLICKED(IDC_MODIFY, &CMemberManagementDlg::OnBnClickedModify)
	ON_BN_CLICKED(IDC_BTN_CLEAR, &CMemberManagementDlg::OnBnClickedBtnClear)
	ON_BN_CLICKED(IDC_BTN_SEARCH, &CMemberManagementDlg::OnBnClickedBtnSearch)
END_MESSAGE_MAP()


// CMemberManagementDlg �޽��� ó����

BOOL CMemberManagementDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �ý��� �޴��� "����..." �޴� �׸��� �߰��մϴ�.

	// IDM_ABOUTBOX�� �ý��� ��� ������ �־�� �մϴ�.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// �� ��ȭ ������ �������� �����մϴ�.  ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

	wchar_t szCurrentPath[MAX_PATH] = { 0, };
	GetModuleFileName(NULL, szCurrentPath, MAX_PATH);
	PathRemoveFileSpec(szCurrentPath);
	m_PathCur = szCurrentPath;
	m_PathConfig = m_PathCur + L"\\Config";

	//������ ���̽� ����
	HRESULT hr = S_OK;
	hr = g_DataSource.OpenDataSource(m_PathConfig);
	if (FAILED(hr))
	{
		CString str;
		str.Format(L"(Open Failed CustDB) \nError : 0x%08X", hr);
		AfxMessageBox(str);
		return TRUE;
	}

	Member();
	DlgClear();
	ViewData();
	
	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
}

void CMemberManagementDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�.  ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CMemberManagementDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
HCURSOR CMemberManagementDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//���� ��ư
void CMemberManagementDlg::OnBnClickedRegister()
{
	UpdateData(TRUE);
	if (MandatoryCheck() == FALSE) {
		return;
	}
	InputData();		//1. ������ �Է�
	ViewData();			//2. ������ ���
	DlgClear();			//3. ���̾�α� ����
	UpdateData(FALSE);
	
}
//���� ��ư
void CMemberManagementDlg::OnBnClickedDelete()
{
	UpdateData(TRUE);
	Delete();
	ViewData();
	DlgClear();
	UpdateData(FALSE);
	AfxMessageBox(L"ȸ�������� ���� �Ǿ����ϴ�.");
}
//���� ��ư
void CMemberManagementDlg::OnBnClickedModify()
{
	UpdateData(TRUE);
	if (MandatoryCheck() == FALSE) {
		return;
	}
	Modify();
	ViewData();
	DlgClear();
	UpdateData(FALSE);
}
void CMemberManagementDlg::OnBnClickedBtnClear()
{
	UpdateData(TRUE);
	DlgClear();
	UpdateData(FALSE);
}
//����Ʈ��Ʈ�� Ŭ�� �̺�Ʈ
void CMemberManagementDlg::OnClickMember(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;

	m_nIndex = pNMListView->iItem;	// ����Ʈ ��Ʈ�� ������ �ε��� �� 
	m_nSelectIndex = _ttoi(m_List.GetItemText(m_nIndex, 0)); // �ش� �ε����� ��������.

  //int idx = pNMListView -> iItem;// ���õ� �����۰��� �������� (0,1 ... n ��° �ε���) �Ѱ� �����´�.
 //CString sIndexValue;sIndexValue = m_listDataTable.GetItemText(idx, 1);
	UpdateData(TRUE);
	State();
	UpdateData(FALSE);

	*pResult = 0;
}
void CMemberManagementDlg::OnBnClickedBtnSearch()
{
	UpdateData(TRUE);
	SearchTable();
	UpdateData(FALSE);
}

void CMemberManagementDlg::Member()		
{
	CRect rect;
	m_List.GetClientRect(&rect);
	m_List.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);	 //ǥ �� ��ü ����, ǥ �׸� 
	m_List.InsertColumn(0, _T("INDEX"), LVCFMT_CENTER, 50);
	m_List.InsertColumn(1, _T("NO"), LVCFMT_CENTER, 50);
	m_List.InsertColumn(2, _T("�̸�"), LVCFMT_CENTER, 50 );
	m_List.InsertColumn(3, _T("�������"), LVCFMT_CENTER, 100);
	m_List.InsertColumn(4, _T("����"), LVCFMT_CENTER, 50);
	m_List.InsertColumn(5, _T("��ȭ��ȣ"), LVCFMT_CENTER, 100);
	m_List.InsertColumn(6, _T("���"), LVCFMT_CENTER, 100);
}

int CMemberManagementDlg::InputData()
{
	try
	{
		CDBConnection dbconn(m_PathConfig);
		dbconn.OpenSession(g_DataSource.GetDataSource());

		CString strGender;
		if (m_nrdoSex == 0) strGender.Format(L"����");
		else if (m_nrdoSex == 1) strGender.Format(L"����");
		
		CString strCommand(L"insert into TestTable () values ()");
		
		CString strCheckNum;
		for (int i = 0; i < m_editBirth.GetAllocLength(); i++)
		{
			char ch = m_editBirth.GetAt(i);
			if (ch >= '0'&& ch <= '9')
			{
				strCheckNum += ch;
			}
		}

		if (strCheckNum.GetLength() >= 8) {
			AfxMessageBox(L"��������� 8�� ���Ϸ� �Է��� �ּ���.");
			return 0; 
		}


		dbconn.InsertAddCommand(strCommand, L"GuestName", m_editName);
		dbconn.InsertAddCommand(strCommand, L"Birth", strCheckNum);
		dbconn.InsertAddCommand(strCommand, L"Gender", strGender);
		dbconn.InsertAddCommand(strCommand, L"PhoneNumber", m_editNumber);
		dbconn.InsertAddCommand(strCommand, L"Note", m_editNote);

		CCommand<CNoAccessor> accessor;
		dbconn.CommandOpen(accessor, strCommand);
		accessor.Close();

		AfxMessageBox(L"ȸ�������� ��� �Ǿ����ϴ�.");
		return TRUE;
	}
	catch (CDBConnection::Exception &e)
	{
		AfxMessageBox(e.ReportError());
		return FALSE;
	}

	//���� ���� 

	//int nItemNum;
	//if (m_vectorMember.size() == 0)
	//	nItemNum = 0;
	//else
	//{
	//	auto var = m_vectorMember.back();
	//	nItemNum = var.GetIndex() + 1;
	//}

	//int nIndex;
	//nIndex = m_member.GetIndex();

	//CString strIndex;
	//strIndex.Format(L"%d", nIndex);

	//m_member.SetIndex(nItemNum);
	//m_member.SetName(m_editName);
	//m_member.SetBirth(m_editBirth);
	//m_member.SetSex(m_nrdoSex);
	//m_member.SetPhone(m_editNumber);
	//m_member.SetNote(m_editNote);

	////m_listMember.push_back(m_member);
	//m_vectorMember.push_back(m_member);

}

// ����Ʈ ��Ʈ�ѿ� �����͸� ������
int CMemberManagementDlg::ViewData()
{
	try
	{
		CDBConnection dbconn(m_PathConfig);
		dbconn.OpenSession(g_DataSource.GetDataSource());

		CString strCommand;
		strCommand.Format(L"select * from TestTable");
		dbconn.CommandOpen(dbconn.m_testtable, strCommand, true); // ������ �� ����

		m_List.DeleteAllItems();

		CString strCount;
		int count = 0;
		while (dbconn.m_testtable.MoveNext() == S_OK)
		{
			strCount.Format(L"%d", count + 1);
			// ������ ���̽� �� ������.
			m_strId.Format(L"%d", dbconn.m_testtable.m_ID);
			m_strName = dbconn.m_testtable.m_GuestName;
			m_strBirth = dbconn.m_testtable.m_Birth;
			m_strGender = dbconn.m_testtable.m_Gender;
			m_strNumber = dbconn.m_testtable.m_PhoneNumber;
			m_strNote = dbconn.m_testtable.m_Note;
			//����Ʈ ��Ʈ�ѿ� �� ������
			m_List.InsertItem(count, m_strId);
			m_List.SetItemText(count, 1, strCount);
			m_List.SetItemText(count, 2, m_strName);
			m_List.SetItemText(count, 3, m_strBirth);
			m_List.SetItemText(count, 4, m_strGender);
			m_List.SetItemText(count, 5, m_strNumber);
			m_List.SetItemText(count, 6, m_strNote);
			count++;
		}
		return TRUE;
	}
	catch (CDBConnection::Exception &e)
	{
		AfxMessageBox(e.ReportError());
		return FALSE;
	}

	// ���� ����
	/*for (auto itr = m_vectorMember.begin(); itr != m_vectorMember.end(); itr++)
	{
		int index;
		index = itr->GetIndex();

		CString strIndex;
		strIndex.Format(L"%d", index);

		CString strCount;
		strCount.Format(L"%d", count + 1);
		m_List.InsertItem(count, strIndex);
		m_List.SetItemText(count, 1, strCount);
		m_List.SetItemText(count, 2, itr->GetName());
		m_List.SetItemText(count, 3, itr->GetBirth());
		m_List.SetItemText(count, 4, itr->GetSex());
		m_List.SetItemText(count, 5, itr->GetPhone());
		m_List.SetItemText(count, 6, itr->GetNote());
		count++;
	}*/
}
int CMemberManagementDlg::Delete()
{
	try
	{
		CDBConnection dbconn(m_PathConfig);
		dbconn.OpenSession(g_DataSource.GetDataSource());
		CCommand<CNoAccessor> accessor;

		CString strCommand;
		strCommand.Format(L"delete from TestTable where ID = %ld ", m_nSelectIndex);
		dbconn.CommandOpen(accessor, strCommand);

		accessor.Close();

		return TRUE;
	}
	catch (CDBConnection::Exception &e)
	{
		AfxMessageBox(e.ReportError());
		return FALSE;
	}
	//���� ����
	/*for (auto iter = m_vectorMember.begin(); iter != m_vectorMember.end(); iter++)

	{
		if (m_nSelectIndex == iter->GetIndex())
		{
			m_vectorMember.erase(iter);
			break;

		}
	}*/
}
int CMemberManagementDlg::Modify()
{
	try
	{
		CDBConnection dbconn(m_PathConfig);
		dbconn.OpenSession(g_DataSource.GetDataSource());

		CString strCommand;
		strCommand.Format(L"update TestTable set where ID = %ld", m_nSelectIndex);

		CString strGender;
		if (m_nrdoSex == 0) strGender.Format(L"����");
		else if (m_nrdoSex == 1) strGender.Format(L"����");

		CString strCheckNum;
		for (int i = 0; i < m_editBirth.GetAllocLength(); i++)	//���ڸ� ����
		{
			char ch = m_editBirth.GetAt(i);
			if (ch >= '0'&& ch <= '9')
			{
				strCheckNum += ch;
			}
		}
		if (strCheckNum.GetLength() >= 8) {
			AfxMessageBox(L"��������� 8�� ���Ϸ� �Է��� �ּ���.");
			return 0;
		}

		dbconn.UpdateAddCommand(strCommand, L"[GuestName]", m_editName);
		dbconn.UpdateAddCommand(strCommand, L"[Birth]", m_editBirth);
		dbconn.UpdateAddCommand(strCommand, L"[Gender]", strGender);
		dbconn.UpdateAddCommand(strCommand, L"[PhoneNumber]", m_editNumber);
		dbconn.UpdateAddCommand(strCommand, L"[Note]", m_editNote);

		CCommand<CNoAccessor> accessor;
		dbconn.CommandOpen(accessor, strCommand);
		accessor.Close();
		
		AfxMessageBox(L"ȸ�������� ���� �Ǿ����ϴ�.");
		return TRUE;
	}
	catch (CDBConnection::Exception &e)
	{
		AfxMessageBox(e.ReportError());
		return FALSE;
	}

	//���� ������
	//for (auto iter = m_vectorMember.begin(); iter != m_vectorMember.end(); iter++)

	//{
	//	if (m_nSelectIndex == iter->GetIndex())
	//	{

	//		iter->SetName(m_editName);
	//		iter->SetBirth(m_editBirth);
	//		iter->SetSex(m_nrdoSex);
	//		iter->SetPhone(m_editNumber);
	//		iter->SetNote(m_editNote);
	//		ViewData();

	//		AfxMessageBox(L"ȸ�������� ���� �Ǿ����ϴ�.");

	//		break;
	//	}
	//}
}
// ���� ����Ȱ� ��Ʈ�ѿ� ������
int CMemberManagementDlg::State()
{
	try
	{
		CDBConnection dbconn(m_PathConfig);
		dbconn.OpenSession(g_DataSource.GetDataSource());

		CString strCommand;
		strCommand.Format(L"select * from TestTable where ID = %ld", m_nSelectIndex);

		dbconn.CommandOpen(dbconn.m_testtable, strCommand, true); // ������ �� ����

		int nGender;
		CString strGender;

		if (dbconn.m_testtable.MoveNext() == S_OK)
		{
			strGender = dbconn.m_testtable.m_Gender;
			if (strGender == L"����") nGender = 0;
			else if (strGender == L"����") nGender = 1;
			else nGender = 0;

			m_editName = dbconn.m_testtable.m_GuestName;
			m_editBirth = dbconn.m_testtable.m_Birth;
			m_nrdoSex = nGender;
			m_editNumber = dbconn.m_testtable.m_PhoneNumber;
			m_editNote = dbconn.m_testtable.m_Note;
		}
	}
	catch (CDBConnection::Exception &e)
	{
		AfxMessageBox(e.ReportError());
		return FALSE;
	}
	//���� ���
	//for each (auto var in m_vectorMember)
	//{
	//	if (m_nSelectIndex == var.GetIndex())	// �ε�����
	//	{
	//		m_editName = var.GetName();
	//		m_editBirth = var.GetBirth();
	//		m_editNumber = var.GetPhone();
	//		m_nrdoSex = var.GetSexState();
	//		m_editNote = var.GetNote();
	//	}
	//}
}
int CMemberManagementDlg::MandatoryCheck()
{
	if (m_editName.IsEmpty() == TRUE)
	{
		AfxMessageBox(L"�̸��� �Է��ϼ���.");
		return FALSE;
	}
	else if (m_editBirth.IsEmpty() != FALSE) {
		AfxMessageBox(L"������ �Է��ϼ���.");
		return FALSE;
	}
	else if (m_editNumber.IsEmpty() != FALSE) {
		AfxMessageBox(L"��ȭ��ȣ�� �Է��ϼ���.");
		return FALSE;
	}
	return TRUE;
}
void CMemberManagementDlg::DlgClear()
{
	CButton *pCheck;
	pCheck = (CButton*)GetDlgItem(IDC_RADIO_SEARCH_NAME);
	pCheck->SetCheck(FALSE);
	pCheck = (CButton*)GetDlgItem(IDC_RADIO_MALE);
	pCheck->SetCheck(FALSE);
	m_nrdoSex = -1;				// ���������� ��ư�ʱ�ȭ�� ���� ����...
	m_nrdoSearch = -1;

	m_editName = L"";
	m_editBirth = L"";
	m_editNumber = L"";
	m_editNote = L"";
	m_editSearch = L"";
}
int CMemberManagementDlg::SearchTable()
{
	try
	{
		CDBConnection dbconn(m_PathConfig);
		dbconn.OpenSession(g_DataSource.GetDataSource());

		m_List.DeleteAllItems();

		CString strCommand;
	
		if (m_nrdoSearch == 0)strCommand.Format(L"select * from TestTable where GuestName like '%%%s%%'", m_editSearch);
		else if (m_nrdoSearch == 1)	strCommand.Format(L"select * from TestTable where GuestName like '%s'", m_editSearch);
		else strCommand.Format(L"select * from TestTable");

		//strCommand.Format(L"select * from TestTable where GuestName like '%%%s%%'",m_editSearch);
		//strCommand.Insert(field_start + 1, m_editSearch); // ���� �Է� 
		dbconn.CommandOpen(dbconn.m_testtable, strCommand, true); // ������ �� ����

		CString strCount;
		int count = 0;
		while (dbconn.m_testtable.MoveNext() == S_OK)
		{
			strCount.Format(L"%d", count + 1);
			// ������ ���̽� �� ������.
			m_strId.Format(L"%d", dbconn.m_testtable.m_ID);
			m_strName = dbconn.m_testtable.m_GuestName;
			m_strBirth = dbconn.m_testtable.m_Birth;
			m_strGender = dbconn.m_testtable.m_Gender;
			m_strNumber = dbconn.m_testtable.m_PhoneNumber;
			m_strNote = dbconn.m_testtable.m_Note;
			//����Ʈ ��Ʈ�ѿ� �� ������
			m_List.InsertItem(count, m_strId);
			m_List.SetItemText(count, 1, strCount);
			m_List.SetItemText(count, 2, m_strName);
			m_List.SetItemText(count, 3, m_strBirth);
			m_List.SetItemText(count, 4, m_strGender);
			m_List.SetItemText(count, 5, m_strNumber);
			m_List.SetItemText(count, 6, m_strNote);
			count++;
		}
		CCommand<CNoAccessor> accessor;
		dbconn.CommandOpen(accessor, strCommand);
		accessor.Close();
		return TRUE;
	}
	catch (CDBConnection::Exception &e)
	{
		AfxMessageBox(e.ReportError());
		return FALSE;
	}
}



