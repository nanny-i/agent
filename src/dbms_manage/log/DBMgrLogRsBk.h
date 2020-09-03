//---------------------------------------------------------------------------

#ifndef DBMgrLogRsBkH
#define DBMgrLogRsBkH
//---------------------------------------------------------------------------

class CDBMgrLogRsBk : public CDBMgrBase
{
public:
	INT32			SetInitalize();

public:
	INT32			LoadDB(TListDBLogRsBk& tDBLogRsBkList);

public:
    INT32			InsertLogRsBk(DB_LOG_RS_BK& data);
    INT32			UpdateLogRsBk(DB_LOG_RS_BK& data);
    INT32			DeleteLogRsBk(UINT32 nID);    

public:
	virtual INT32	LoadExecute(PVOID lpTempletList);     
	virtual INT32	InsertExecute(PVOID lpTemplet);
	virtual INT32	UpdateExecute(PVOID lpTemplet);
	virtual INT32	DeleteExecute(UINT32 nID);

public:
	INT32			LoadDB(UINT32 nLogMode, UINT32 nLogNum, TListDBLogRsBk& tDBLogRsBkList);


public:
	CDBMgrLogRsBk();
    ~CDBMgrLogRsBk();
};

extern CDBMgrLogRsBk*		t_DBMgrLogRsBk;

#endif
