#ifndef DB_LOG_DEVICE_H_348683B5_F316_4a4d_842D_63E68B189A5D
#define DB_LOG_DEVICE_H_348683B5_F316_4a4d_842D_63E68B189A5D

typedef struct _db_log_device
{
    _db_log_device()
    {
        _init();        
    }

	void _init()
	{
		nID 				= 0;
		nUsedFlag			= 1;
		nRegDate			= 0;
		nEvtTime 			= 0;
		nEvtErrCode			= ERR_SUCCESS;
		nSkipTarget			= 0;

		nNotifyType 		= 0;
		nNotifyID			= 0;

		nHostID				= 0;
		nUserID				= 0;
		nPolicyType			= 0;
		nOpType				= 0;
		nRegSvrID			= 0;
		nSyncSvrStep		= 0;

		nBlockType 			= 0;
		strDvInstanceID		= "";		
	}
  
	UINT32		nID;
	UINT32		nUsedFlag;
	UINT32		nRegDate;
	UINT32		nEvtTime;
	UINT32		nEvtErrCode;
	UINT32		nSkipTarget;

	UINT32		nNotifyType;
	UINT32		nNotifyID;

	UINT32		nHostID;
	UINT32		nUserID;
	UINT32		nPolicyType;
	UINT32		nOpType;
	UINT32		nRegSvrID;
	UINT32		nSyncSvrStep;

	UINT32		nBlockType;
	String		strDvInstanceID;

}DB_LOG_DEVICE, *PDB_LOG_DEVICE;

typedef list<DB_LOG_DEVICE>			TListDBLogDevice;
typedef TListDBLogDevice::iterator	TListDBLogDeviceItor;

typedef map<UINT32, DB_LOG_DEVICE>	TMapDBLogDevice;
typedef TMapDBLogDevice::iterator	TMapDBLogDeviceItor;

#endif //DB_LOG_DEVICE_H_348683B5_F316_4a4d_842D_63E68B189A5D



