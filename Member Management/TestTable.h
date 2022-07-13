
// TestTable.h : CTestTable의 선언입니다.

#pragma once

// 코드 생성 위치 2022년 5월 10일 화요일, 오후 12:07

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

	// 다음 마법사 생성 데이터 멤버에는  열 맵의 해당 
	// 필드에 대한 상태 값이 들어 있습니다. 이 값을
	// 사용하여 데이터베이스에서반환하는 NULL 값을
	// 보유하거나 컴파일러에서 오류를 반환할 때
	// 오류 정보를 보유할 수 있습니다. 이러한 필드 사용에
	// 대한 자세한 내용은 Visual C++ 설명서의
	//  "마법사 생성 접근자"에서 "필드 상태 데이터 멤버"를 참조하십시오.
	// 참고: 데이터를 설정/삽입하기 전에 이들 필드를 초기화해야 합니다.

	DBSTATUS m_dwBirthStatus;
	DBSTATUS m_dwGenderStatus;
	DBSTATUS m_dwGuestNameStatus;
	DBSTATUS m_dwIDStatus;
	DBSTATUS m_dwNoteStatus;
	DBSTATUS m_dwPhoneNumberStatus;

	// 다음 마법사 생성 데이터 멤버에는 열 맵의 해당 필드에 대한
	// 길이 값이 들어 있습니다.
	// 참고: 가변 길이 열의 경우 데이터를 설정/삽입하기 전에 
//       이러한 	 필드를 초기화해야 합니다.

	DBLENGTH m_dwBirthLength;
	DBLENGTH m_dwGenderLength;
	DBLENGTH m_dwGuestNameLength;
	DBLENGTH m_dwIDLength;
	DBLENGTH m_dwNoteLength;
	DBLENGTH m_dwPhoneNumberLength;

	//데이터 추가 갱신 연결 클래스
	void GetRowsetProperties(CDBPropSet* pPropSet)
	{
		pPropSet->AddProperty(DBPROP_CANFETCHBACKWARDS, true, DBPROPOPTIONS_OPTIONAL);
		pPropSet->AddProperty(DBPROP_CANSCROLLBACKWARDS, true, DBPROPOPTIONS_OPTIONAL);
		// pPropSet->AddProperty(DBPROP_ISequentialStream, true);
		pPropSet->AddProperty(DBPROP_IRowsetChange, true, DBPROPOPTIONS_OPTIONAL);
		pPropSet->AddProperty(DBPROP_UPDATABILITY, DBPROPVAL_UP_CHANGE | DBPROPVAL_UP_INSERT | DBPROPVAL_UP_DELETE);
	}


// 이 테이블/명령에는 ISequentialStream 인터페이스를 통해
// 액세스할 수 있는 열이 들어 있습니다. 그러나 모든 공급자가
// 이 기능을 지원하는 것은 아니며 이 기능을 지원하는 공급자도
// 보통 하나의 행 집합에 단 하나의 ISequentialStream만 지정하도록 제한을 받습니다.
// 이 접근자의 스트림을 사용하려면 아래의 예제 코드를 사용하고
// DBPROP_ISequentialStream 행 집합 속성을 true로 설정하십시오.
// 그러면 Read() 메서드를 사용하여 데이터를 읽거나
// Write() 메서드를 사용하여 데이터를 쓸 수 있습니다.
// 이렇게 하려면 STGM_READ 스트림 속성을 STGM_WRITE 또는 STGM_READWRITE로
// 변경해야 합니다.
// ISequentialStream 바인딩에 대한 자세한 내용은 설명서를 참조하십시오.
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


