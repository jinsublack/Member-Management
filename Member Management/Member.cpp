#include "stdafx.h"
#include "Member.h"


CMember::CMember()
{
}
CMember::~CMember()
{
}

void CMember::SetIndex(int index)
{
	m_nIndex = index;
}
int CMember::GetIndex()
{
	return m_nIndex;
}

void CMember::SetName(CString name)
{
	m_strName = name;
}
CString CMember::GetName()
{
	return m_strName;
}


void CMember::SetBirth(CString birth)
{
	m_strBirth = birth;
}
CString CMember::GetBirth()
{
	return m_strBirth;
}

void CMember::SetSex(int sex) 
{
	m_nSex = sex;
}
CString CMember::GetSex()
{
	switch (m_nSex)
	{
	case 0: return L"남성"; break;
	case 1: return L"여성"; break;
	}
	return L"";
}
int CMember::GetSexState()
{
	return m_nSex;
}


void CMember::SetPhone(CString phone)
{
	m_strPhone = phone;
}
CString CMember::GetPhone()
{
	return m_strPhone;
}

void CMember::SetNote(CString note)
{
	m_strNote = note;
}
CString CMember::GetNote()
{
	return m_strNote;
}

