
#ifndef COM_DEFINE_DB_PO_HOST_CLEAR_H_938EF200_F60B_452A_BD30_A10E8507EDCC
#define COM_DEFINE_DB_PO_HOST_CLEAR_H_938EF200_F60B_452A_BD30_A10E8507EDCC

//-------------------------------------------------------------------
//host clear [ nChkType ]

#define SS_PO_HOST_CLEAR_CHECK_OPTION_DISCON_DT				0x00000001 // 접근 종료 날짜
#define SS_PO_HOST_CLEAR_CHECK_OPTION_IP_ADDRESS			0x00000002 // 에이전트 주소 중복
//#define SS_PO_HOST_CLEAR_CHECK_OPTION_MAC_ADDRESS			0x00000004 // 에이전트 Mac 주소 중복

//-------------------------------------------------------------------
//host clear [ nDisposalType ]

#define SS_PO_HOST_CLEAR_DISPOSAL_TYPE_SLEEP				0x00000001 // 휴면 처리만 사용
#define SS_PO_HOST_CLEAR_DISPOSAL_TYPE_REMOVE				0x00000002 // 삭제 처리만 사용
#define SS_PO_HOST_CLEAR_DISPOSAL_TYPE_SLEEP_AND_REMOVE		0x00000004 // 휴면 후 삭제 처리 사용

//--------------------------------------------------------------------
#endif	//COM_DEFINE_DB_PO_HOST_CLEAR_H_938EF200_F60B_452A_BD30_A10E8507EDCC