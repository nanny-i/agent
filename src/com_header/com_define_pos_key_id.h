
#ifndef COM_DEFINE_POS_KEY_ID_H_938EF200_F60B_452A_BD30_A10E8507EDCC
#define COM_DEFINE_POS_KEY_ID_H_938EF200_F60B_452A_BD30_A10E8507EDCC

//--------------------------------------------------------------------
//
#define POS_KEY_ID_POSITION_HOST_USERID_HID_MAP					0x00000001
//--------------------------------------------------------------------

#define POS_KEY_STR_POSITION_HOST_USER_UNICODEID_HID_MAP		0x00000001
//--------------------------------------------------------------------


#define POS_KEY_ID_POSITION_SITE_FILE_REF_HID_MAP		0x00000001
#define POS_KEY_ID_POSITION_SITE_FILE_REF_FID_MAP		0x00000002
//--------------------------------------------------------------------

#define POS_KEY_ID_POSITION_PTN_FILE_PO_FID_MAP			0x00000001
#define POS_KEY_ID_POSITION_PTN_FILE_PO_UID_MAP			0x00000002
//--------------------------------------------------------------------

#define POS_KEY_STR_POSITION_PTN_PATCH_GUID_MAP			0x00000001
//--------------------------------------------------------------------

#define POS_KEY_ID_POSITION_LOG_PATCH_SID_MAP			0x00000001
#define POS_KEY_ID_POSITION_LOG_PATCH_PID_MAP			0x00000002
//--------------------------------------------------------------------

#define POS_KEY_STR_POSITION_LOG_RS_BK_DIR_MAP			0x00000001
#define POS_KEY_STR_POSITION_LOG_RS_BK_DIR_FILE_MAP		0x00000002
//--------------------------------------------------------------------

#define POS_KEY_ID_POSITION_GROUP_CATEGORY_CID_MAP		0x00000001
#define POS_KEY_ID_POSITION_GROUP_CATEGORY_GID_MAP		0x00000002
#define POS_KEY_ID_POSITION_GROUP_CATEGORY_CGID_MAP		0x00000003
//--------------------------------------------------------------------

#define POS_KEY_ID_USER_UNICODE						1
#define POS_KEY_ID_USER_ACCOUNT_ID					2

//--------------------------------------------------------------------

#define POS_KEY_STR_POSITION_SITE_SW_KEY_MAP			0x00000001
#define POS_KEY_STR_POSITION_SITE_SW_KEY_VER_MAP		0x00000002

//--------------------------------------------------------------------

enum
{
	POS_KEY_ID_MON_CHART_DATA_REALTIME		= 0,
	POS_KEY_ID_MON_CHART_DATA_HOUR,
	POS_KEY_ID_MON_CHART_DATA_DAY,
	POS_KEY_ID_MON_CHART_DATA_WEEK,
	POS_KEY_ID_MON_CHART_DATA_MONTH,
	POS_KEY_ID_MON_CHART_DATA_FOREIGN_KEY,
};


//--------------------------------------------------------------------
#endif	//COM_DEFINE_POS_KEY_ID_H_938EF200_F60B_452A_BD30_A10E8507EDCC