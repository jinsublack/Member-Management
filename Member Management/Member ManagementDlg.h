
// Member ManagementDlg.h : ��� ����
//

#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include "Member.h"
#include <list>
#include <vector>
#include "DBConnection.h"

// CMemberManagementDlg ��ȭ ����
class CMemberManagementDlg : public CDialogEx
{
// �����Դϴ�.
public:
	CMemberManagementDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

	CMember m_member;
	CMember m_selected_member;



	//std::list<CMember> m_listMember;
	std::vector<CMember> m_vectorMember;


	//CMember m_inputMember;  // Editâ���� �Է¹��� ��� Ŭ����		
	
	//std::list<CMember> m_listMember;
	//vector
	//map
	

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MEMBERMANAGEMENT_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.


// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()


public:

	afx_msg void OnBnClickedRegister();
	afx_msg void OnBnClickedDelete();
	afx_msg void OnBnClickedModify();
	afx_msg void OnClickMember(NMHDR *pNMHDR, LRESULT *pResult);

	//���̾�α� ������ �� ����
	CListCtrl m_List;
	CString m_editName;
	CString m_editBirth;
	CString m_editNumber;
	CString m_editNote;
	int m_nrdoSex;
	int m_nrdoSearch;
	int m_nIndex;	//���̾�α� ���� �� ��ȣ


	// �����ͺ��̽� ������ ��� ����
	CString m_strCount;
	CString m_strName;
	CString m_strBirth;
	CString m_strGender;
	CString m_strNumber;
	CString m_strNote;
	CString m_editSearch;


	CString m_strId;// ������ ���̽� �ε��� ��


	int m_nSelectIndex; //������ ���̾�α� �ε��� ��


	void Member();
	int InputData();
	int ViewData();
	int Delete();
	int Modify();
	int State();
	int MandatoryCheck();
	void DlgClear();
	int SearchTable();
	

	CString m_PathConfig; // ���
	CString m_PathCur;

	afx_msg void OnBnClickedBtnClear();
	afx_msg void OnBnClickedBtnSearch();
};
