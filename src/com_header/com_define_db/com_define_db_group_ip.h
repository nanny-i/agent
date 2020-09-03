
#ifndef COM_DEFINE_DB_DB_GROUP_IP_H_938EF200_F60B_452A_BD30_A10E8507EDCC
#define COM_DEFINE_DB_DB_GROUP_IP_H_938EF200_F60B_452A_BD30_A10E8507EDCC

//-------------------------------------------------------------------
//set ip match type
#define SS_GROUP_IP_MATCH_TYPE_NAT_IP			0x00000000 // 
#define SS_GROUP_IP_MATCH_TYPE_PRI_IP			0x00000001 // 
#define SS_GROUP_IP_MATCH_TYPE_NAT_AND_PRI_IP	0x00000002 //

//-------------------------------------------------------------------
//set ip match chk flag
#define SS_GROUP_IP_MATCH_FLAG_NAT_IP			0x00000001 // 
#define SS_GROUP_IP_MATCH_FLAG_PRI_IP			0x00000002 // 
#define SS_GROUP_IP_MATCH_FLAG_NAT_AND_PRI_IP	(SS_GROUP_IP_MATCH_FLAG_NAT_IP | SS_GROUP_IP_MATCH_FLAG_PRI_IP) //


//-------------------------------------------------------------------
//--------------------------------------------------------------------
//--------------------------------------------------------------------
#endif	//COM_DEFINE_DB_DB_GROUP_IP_H_938EF200_F60B_452A_BD30_A10E8507EDCC