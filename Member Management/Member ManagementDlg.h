
// Member ManagementDlg.h : 헤더 파일
//

#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include "Member.h"
#include <list>
#include <vector>
#include "DBConnection.h"

// CMemberManagementDlg 대화 상자
class CMemberManagementDlg : public CDialogEx
{
// 생성입니다.
public:
	CMemberManagementDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

	CMember m_member;
	CMember m_selected_member;



	//std::list<CMember> m_listMember;
	std::vector<CMember> m_vectorMember;


	//CMember m_inputMember;  // Edit창에서 입력받은 멤버 클래스		
	
	//std::list<CMember> m_listMember;
	//vector
	//map
	

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MEMBERMANAGEMENT_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
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

	//다이얼로그 데이터 값 받음
	CListCtrl m_List;
	CString m_editName;
	CString m_editBirth;
	CString m_editNumber;
	CString m_editNote;
	int m_nrdoSex;
	int m_nrdoSearch;
	int m_nIndex;	//다이얼로그 선택 행 번호


	// 데이터베이스 데이터 멤버 변수
	CString m_strCount;
	CString m_strName;
	CString m_strBirth;
	CString m_strGender;
	CString m_strNumber;
	CString m_strNote;
	CString m_editSearch;


	CString m_strId;// 데이터 베이스 인덱스 값


	int m_nSelectIndex; //선택한 다이얼로그 인덱스 값


	void Member();
	int InputData();
	int ViewData();
	int Delete();
	int Modify();
	int State();
	int MandatoryCheck();
	void DlgClear();
	int SearchTable();
	

	CString m_PathConfig; // 경로
	CString m_PathCur;

	afx_msg void OnBnClickedBtnClear();
	afx_msg void OnBnClickedBtnSearch();
};
