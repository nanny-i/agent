//---------------------------------------------------------------------------

#ifndef DBMgrLogRsH
#define DBMgrLogRsH
//---------------------------------------------------------------------------

class CDBMgrLogRs : public CDBMgrBase
{
public:
	INT32			SetInitalize();

public:
	INT32			LoadDB(TListDBLogRs& tDBLogRsList);

public:
    INT32			InsertLogRs(DB_LOG_RS& data);
    INT32			UpdateLogRs(DB_LOG_RS& data);
    INT32			DeleteLogRs(UINT32 nID);    

public:
	virtual INT32	LoadExecute(PVOID lpTempletList);     
	virtual INT32	InsertExecute(PVOID lpTemplet);
	virtual INT32	UpdateExecute(PVOID lpTemplet);
	virtual INT32	DeleteExecute(UINT32 nID);

public:
	INT32			LoadDB(UINT32 nLogMode, UINT32 nLogNum, TListDBLogRs& tDBLogRsList);


public:
	CDBMgrLogRs();
    ~CDBMgrLogRs();
};

extern CDBMgrLogRs*		t_DBMgrLogRs;

#endif
