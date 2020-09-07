
#ifndef COM_DEFINE_DB_PO_HOST_RUN_H_938EF200_F60B_452A_BD30_A10E8507EDCC
#define COM_DEFINE_DB_PO_HOST_RUN_H_938EF200_F60B_452A_BD30_A10E8507EDCC

//-------------------------------------------------------------------
//host run option
#define SS_PO_HOST_RUN_OPTION_FLAG_SUPPORT_SAFE_MODE				0x00000001 // 안정모드 지원 여부
#define SS_PO_HOST_RUN_OPTION_FLAG_SUPPORT_ASI_DEPLOY_SVR			0x00000002 // ASI 배포 서버를 통한 파일 배포(업데이트 파일)
#define SS_PO_HOST_RUN_OPTION_FLAG_SUPPORT_ASI_LICENSE_SVR			0x00000004 // ASI LICENSE 서버를 통한 Lgn 접근 정보 검사
#define SS_PO_HOST_RUN_OPTION_FLAG_SUPPORT_PTOP						0x00000008 // PtoP를 이용한 다운로드 지원
#define SS_PO_HOST_RUN_OPTION_FLAG_SUPPORT_BOOT_APPLY				0x00000010 // 부팅시 정책 적용
#define SS_PO_HOST_RUN_OPTION_FLAG_SUPPORT_ALLOW_MGR_CLOSE			0x00000020 // MGR 종료 허용여부
#define SS_PO_HOST_RUN_OPTION_FLAG_SUPPORT_ALLOW_MGR_LOGIN			0x00000040 // MGR 로그인 보이기 여부
#define	SS_PO_HOST_RUN_OPTION_FLAG_SUPPORT_ALLOW_MGR_MANUAL_DEL		0x00000080 // MGR_수동삭제 보이기 여부
#define	SS_PO_HOST_RUN_OPTION_FLAG_SUPPORT_RESTART_SVC				0x00000100 // 서비스 재시작 주기
#define SS_PO_HOST_RUN_OPTION_FLAG_SUPPORT_ALLOW_MGR_LOGIN_ID		0x00000200 // MGR 로그인 보이기 여부 (ID로만 로그인 )

//-------------------------------------------------------------------
//host mgr show type
#define SS_PO_HOST_RUN_MGR_SHOW_TYPE_NOT_USED						0 // Agt Mgr 표시 안함
#define SS_PO_HOST_RUN_MGR_SHOW_TYPE_NORMAL							1 // Agt Mgr 표시
#define SS_PO_HOST_RUN_MGR_SHOW_TYPE_HIDE_START						2 // Agt Mgr 프로세스 실행

//-------------------------------------------------------------------
//system boot chk type
#define SS_PO_HOST_RUN_BOOT_CHK_TYPE_AUTO							0
#define SS_PO_HOST_RUN_BOOT_CHK_TYPE_START_SVC						1


//--------------------------------------------------------------------
#endif	//COM_DEFINE_DB_PO_HOST_RUN_H_938EF200_F60B_452A_BD30_A10E8507EDCC