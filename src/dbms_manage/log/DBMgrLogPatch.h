//---------------------------------------------------------------------------

#ifndef DBMgrLogPatchH
#define DBMgrLogPatchH
//---------------------------------------------------------------------------

class CDBMgrLogPatch : public CDBMgrBase
{
public:
	INT32			SetInitalize();

public:
	INT32			LoadDB(TListDBLogPatch& tDBLogPatchList);

public:
    INT32			InsertLogPatch(DB_LOG_PATCH& data);
    INT32			UpdateLogPatch(DB_LOG_PATCH& data);
    INT32			DeleteLogPatch(UINT32 nID);    

public:
	virtual INT32	LoadExecute(PVOID lpTempletList);     
	virtual INT32	InsertExecute(PVOID lpTemplet);
	virtual INT32	UpdateExecute(PVOID lpTemplet);
	virtual INT32	DeleteExecute(UINT32 nID);

public:
	INT32			LoadDB(UINT32 nLogMode, UINT32 nLogNum, TListDBLogPatch& tDBLogPatchList);


public:
	CDBMgrLogPatch();
    ~CDBMgrLogPatch();
};

extern CDBMgrLogPatch*		t_DBMgrLogPatch;

#endif
