//---------------------------------------------------------------------------

#ifndef DBMgrDocDeleteInfoH
#define DBMgrDocDeleteInfoH
//---------------------------------------------------------------------------

class CDBMgrDocDeleteInfo : public CDBMgrBase
{
public:
	INT32			SetInitalize();

public:
	INT32			LoadDB(TListDBDocDeleteInfo& tDBDocDeleteInfoList);

public:
    INT32			InsertDocDeleteInfo(DB_DOC_DELETE_INFO& dddi);
    INT32			UpdateDocDeleteInfo(DB_DOC_DELETE_INFO& dddi);
    INT32			DeleteDocDeleteInfo(UINT32 nID); 

public:
	virtual INT32	LoadExecute(PVOID lpTempletList);     
	virtual INT32	InsertExecute(PVOID lpTemplet);
	virtual INT32	UpdateExecute(PVOID lpTemplet);
	virtual INT32	DeleteExecute(UINT32 nID);


public:
	CDBMgrDocDeleteInfo();
    ~CDBMgrDocDeleteInfo();
};

extern CDBMgrDocDeleteInfo*		t_DBMgrDocDeleteInfo;

#endif
