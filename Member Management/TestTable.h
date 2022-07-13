
// TestTable.h : CTestTable�� �����Դϴ�.

#pragma once

// �ڵ� ���� ��ġ 2022�� 5�� 10�� ȭ����, ���� 12:07

class CTestTableAccessor
{
public:
	TCHAR m_Birth[256];
	TCHAR m_Gender[256];
	TCHAR m_GuestName[256];
	LONG m_ID;
	// ISequentialStream* m_Note;
	TCHAR m_Note[8000];
	TCHAR m_PhoneNumber[256];

	// ���� ������ ���� ������ �������  �� ���� �ش� 
	// �ʵ忡 ���� ���� ���� ��� �ֽ��ϴ�. �� ����
	// ����Ͽ� �����ͺ��̽�������ȯ�ϴ� NULL ����
	// �����ϰų� �����Ϸ����� ������ ��ȯ�� ��
	// ���� ������ ������ �� �ֽ��ϴ�. �̷��� �ʵ� ��뿡
	// ���� �ڼ��� ������ Visual C++ ������
	//  "������ ���� ������"���� "�ʵ� ���� ������ ���"�� �����Ͻʽÿ�.
	// ����: �����͸� ����/�����ϱ� ���� �̵� �ʵ带 �ʱ�ȭ�ؾ� �մϴ�.

	DBSTATUS m_dwBirthStatus;
	DBSTATUS m_dwGenderStatus;
	DBSTATUS m_dwGuestNameStatus;
	DBSTATUS m_dwIDStatus;
	DBSTATUS m_dwNoteStatus;
	DBSTATUS m_dwPhoneNumberStatus;

	// ���� ������ ���� ������ ������� �� ���� �ش� �ʵ忡 ����
	// ���� ���� ��� �ֽ��ϴ�.
	// ����: ���� ���� ���� ��� �����͸� ����/�����ϱ� ���� 
//       �̷��� 	 �ʵ带 �ʱ�ȭ�ؾ� �մϴ�.

	DBLENGTH m_dwBirthLength;
	DBLENGTH m_dwGenderLength;
	DBLENGTH m_dwGuestNameLength;
	DBLENGTH m_dwIDLength;
	DBLENGTH m_dwNoteLength;
	DBLENGTH m_dwPhoneNumberLength;

	//������ �߰� ���� ���� Ŭ����
	void GetRowsetProperties(CDBPropSet* pPropSet)
	{
		pPropSet->AddProperty(DBPROP_CANFETCHBACKWARDS, true, DBPROPOPTIONS_OPTIONAL);
		pPropSet->AddProperty(DBPROP_CANSCROLLBACKWARDS, true, DBPROPOPTIONS_OPTIONAL);
		// pPropSet->AddProperty(DBPROP_ISequentialStream, true);
		pPropSet->AddProperty(DBPROP_IRowsetChange, true, DBPROPOPTIONS_OPTIONAL);
		pPropSet->AddProperty(DBPROP_UPDATABILITY, DBPROPVAL_UP_CHANGE | DBPROPVAL_UP_INSERT | DBPROPVAL_UP_DELETE);
	}


// �� ���̺�/��ɿ��� ISequentialStream �������̽��� ����
// �׼����� �� �ִ� ���� ��� �ֽ��ϴ�. �׷��� ��� �����ڰ�
// �� ����� �����ϴ� ���� �ƴϸ� �� ����� �����ϴ� �����ڵ�
// ���� �ϳ��� �� ���տ� �� �ϳ��� ISequentialStream�� �����ϵ��� ������ �޽��ϴ�.
// �� �������� ��Ʈ���� ����Ϸ��� �Ʒ��� ���� �ڵ带 ����ϰ�
// DBPROP_ISequentialStream �� ���� �Ӽ��� true�� �����Ͻʽÿ�.
// �׷��� Read() �޼��带 ����Ͽ� �����͸� �аų�
// Write() �޼��带 ����Ͽ� �����͸� �� �� �ֽ��ϴ�.
// �̷��� �Ϸ��� STGM_READ ��Ʈ�� �Ӽ��� STGM_WRITE �Ǵ� STGM_READWRITE��
// �����ؾ� �մϴ�.
// ISequentialStream ���ε��� ���� �ڼ��� ������ ������ �����Ͻʽÿ�.
	BEGIN_COLUMN_MAP(CTestTableAccessor)
		COLUMN_ENTRY_LENGTH_STATUS(3, m_Birth, m_dwBirthLength, m_dwBirthStatus)
		COLUMN_ENTRY_LENGTH_STATUS(4, m_Gender, m_dwGenderLength, m_dwGenderStatus)
		COLUMN_ENTRY_LENGTH_STATUS(2, m_GuestName, m_dwGuestNameLength, m_dwGuestNameStatus)
		COLUMN_ENTRY_LENGTH_STATUS(1, m_ID, m_dwIDLength, m_dwIDStatus)
		// BLOB_ENTRY_LENGTH_STATUS(6, IID_ISequentialStream, STGM_READ, m_Note, m_dwNoteLength, m_dwNoteStatus)
		COLUMN_ENTRY_LENGTH_STATUS(6, m_Note, m_dwNoteLength, m_dwNoteStatus)
		COLUMN_ENTRY_LENGTH_STATUS(5, m_PhoneNumber, m_dwPhoneNumberLength, m_dwPhoneNumberStatus)
	END_COLUMN_MAP()
};


