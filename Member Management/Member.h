#pragma once
class CMember
{
private:


	int m_nIndex;
	CString m_strName;		//�̸�
	CString m_strBirth;		//�������
	int m_nSex;				//����
	CString m_strPhone;		//��ȭ��ȣ
	CString m_strNote;		//���

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

