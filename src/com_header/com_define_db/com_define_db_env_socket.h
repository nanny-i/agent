
#ifndef COM_DEFINE_DB_ENV_SOCKET_H_938EF200_F60B_452A_BD30_A10E8507EDCC
#define COM_DEFINE_DB_ENV_SOCKET_H_938EF200_F60B_452A_BD30_A10E8507EDCC

//-------------------------------------------------------------------
//option ext
//-------------------------------------------------------------------
#define SS_ENV_SOCKET_AGT_ID_TYPE_MAC						0
#define SS_ENV_SOCKET_AGT_ID_TYPE_IP						1
//-------------------------------------------------------------------
//server type
#define SS_ENV_SOCKET_AGT_LGN_REG_MODE_DENY					0x00000000 // 
#define SS_ENV_SOCKET_AGT_LGN_REG_MODE_RETRY_REG			0x00000001 // 

//--------------------------------------------------------------------
//server open socket type
#define SS_ENV_SOCKET_OPEN_TYPE_LGN							1
#define SS_ENV_SOCKET_OPEN_TYPE_MGR							2
#define SS_ENV_SOCKET_OPEN_TYPE_UDT							3
#define SS_ENV_SOCKET_OPEN_TYPE_RPT							4

#define SS_ENV_SOCKET_OPEN_TYPE_SUB_LGN						11
#define SS_ENV_SOCKET_OPEN_TYPE_SUB_MGR						12
#define SS_ENV_SOCKET_OPEN_TYPE_SUB_UDT						13
#define SS_ENV_SOCKET_OPEN_TYPE_SUB_RPT						14
#define SS_ENV_SOCKET_OPEN_TYPE_SUB_MGR_DATA				15

#define SS_ENV_SOCKET_OPEN_TYPE_CON_CMD						100
#define SS_ENV_SOCKET_OPEN_TYPE_CON_DATA					101

//--------------------------------------------------------------------
//sub server mode
#define SS_ENV_SOCKET_SUB_SVR_TYPE_LGN							0x0001
#define SS_ENV_SOCKET_SUB_SVR_TYPE_MGR							0x0002
#define SS_ENV_SOCKET_SUB_SVR_TYPE_UDT							0x0004
#define SS_ENV_SOCKET_SUB_SVR_TYPE_RPT							0x0008
#define SS_ENV_SOCKET_SUB_SVR_TYPE_ALL							(SS_ENV_SOCKET_SUB_SVR_TYPE_LGN | SS_ENV_SOCKET_SUB_SVR_TYPE_MGR | \
																	SS_ENV_SOCKET_SUB_SVR_TYPE_UDT | SS_ENV_SOCKET_SUB_SVR_TYPE_RPT)

//-------------------------------------------------------------------

#define SS_ENV_SOCKET_OPTION_FLAGE_USE_KEEPALIVE				0x00000001 //ExtOption ..

//-------------------------------------------------------------------
#endif	//COM_DEFINE_DB_ENV_SOCKET_H_938EF200_F60B_452A_BD30_A10E8507EDCC