#pragma once
class CMember
{
private:


	int m_nIndex;
	CString m_strName;		//이름
	CString m_strBirth;		//생년월일
	int m_nSex;				//성별
	CString m_strPhone;		//전화번호
	CString m_strNote;		//비고

public:
	CMember();
	~CMember();


	void SetIndex(int index);
	int GetIndex();

	

	void SetName(CString name);
	CString GetName();

	void SetBirth(CString birth);
	CString GetBirth();

	void SetSex(int sex);
	CString GetSex();
	int GetSexState();

	void SetPhone(CString phone);
	CString GetPhone();

	void SetNote(CString note);
	CString GetNote();

};

