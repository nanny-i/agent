
#ifndef COM_DEFINE_DB_PO_FA_CLEAR_H_938EF200_F60B_452A_BD30_A10E8507EDCC
#define COM_DEFINE_DB_PO_FA_CLEAR_H_938EF200_F60B_452A_BD30_A10E8507EDCC


//-------------------------------------------------------------------
//fa clear file ptn type
#define SS_PO_FA_CLEAR_PTN_TYPE_GLOBAL						0 // 
#define SS_PO_FA_CLEAR_PTN_TYPE_LOCAL						1 // 

//-------------------------------------------------------------------
//fa clear scan type
#define SS_PO_FA_CLEAR_SCAN_TYPE_AUTO						0
#define SS_PO_FA_CLEAR_SCAN_TYPE_DEMAND						1

//-------------------------------------------------------------------
//fa clear file check type
#define SS_PO_FA_CLEAR_FILE_CHK_TYPE_CREATE_DT				0	// 생성 시간 기준
#define SS_PO_FA_CLEAR_FILE_CHK_TYPE_MODIFY_DT				1	// 수정 시간 기준
#define SS_PO_FA_CLEAR_FILE_CHK_TYPE_ACCESS_DT				2	// 접근 시간 기준
#define SS_PO_FA_CLEAR_FILE_CHK_TYPE_MANUAL					3	// 사용자 선택

//--------------------------------------------------------------------

#define SS_PO_FA_CLEAR_UNIT_OPTION_FLAG_SCAN_DOC_FILE_FMT				0x00000001 // 문서 포멧 검사 지원
#define SS_PO_FA_CLEAR_UNIT_OPTION_FLAG_EXCLUDE_DEFAULT_PATH			0x00000002 // 기본 예외 경로 ( 기본 예외 경로옵션은 해당 옵션이 있을경우 사용안함/ 없을 경우에는 사용함 )
#define SS_PO_FA_CLEAR_UNIT_OPTION_FLAG_EXCLUDE_ALL_PATH				0x00000004 // 기본 예외를 모든 경로 예외
#define SS_PO_FA_CLEAR_UNIT_OPTION_FLAG_SCAN_TYPE_DEMAND_NON_FIND_AUTO	0x00000008 // 스캔 타입이 사용자 삭제일경우 정책에 의해서 자동스캔 되지 않고 사용자 스캔 창만 출력.
#define SS_PO_FA_CLEAR_UNIT_OPTION_FLAG_NOTIFY_EXCEPT_DOC_DEL_END		0x00000010 // 알림 제외 여부
#define SS_PO_FA_CLEAR_UNIT_OPTION_FLAG_NOTIFY_EXCEPT_SCH_INFO			0x00000020 // 알림 제외 여부


//--------------------------------------------------------------------
//net drive mode
#define SS_PO_FA_CLEAR_UNIT_NET_DRIVE_TYPE_EXCLUDE			0
#define SS_PO_FA_CLEAR_UNIT_NET_DRIVE_TYPE_INCLUDE			1
#define SS_PO_FA_CLEAR_UNIT_NET_DRIVE_TYPE_SINGLE_SELECT	10


//--------------------------------------------------------------------
//po fa clear extoption
#define SS_PO_FA_CLEAR_EXT_OPTION_FLAG_SHOW_MANUAL_DEL_BY_USER_TO_AGENT			0x00000001	// 사용자 정의 수동삭제 옵션

//-------------------------------------------------------------------
//po fa clear delete method
#define SS_PO_FA_CLEAR_OPTION_DEL_METHOD_SDELETE						0x00000000 // SDELETE
#define SS_PO_FA_CLEAR_OPTION_DEL_METHOD_WIPE							0x00000001 // FAST WIPE

//--------------------------------------------------------------------

#endif	//COM_DEFINE_DB_PO_FA_CLEAR_H_938EF200_F60B_452A_BD30_A10E8507EDCC