//---------------------------------------------------------------------------

#ifndef DBMgrEnvSocketH
#define DBMgrEnvSocketH
//---------------------------------------------------------------------------

class CDBMgrEnvSocket : public CDBMgrBase
{
public:
	INT32			SetInitalize();

public:
	INT32			LoadDB(TListDBEnvSocket& tDBEnvSocketList);

public:
    INT32			InsertEnvSocket(DB_ENV_SOCKET& des);
    INT32			UpdateEnvSocket(DB_ENV_SOCKET& des);

public:
	virtual INT32	LoadExecute(PVOID lpTempletList);     
	virtual INT32	InsertExecute(PVOID lpTemplet);
	virtual INT32	UpdateExecute(PVOID lpTemplet);
	virtual INT32	DeleteExecute(UINT32 nID);


public:
	CDBMgrEnvSocket();
    ~CDBMgrEnvSocket();
};

extern CDBMgrEnvSocket*		t_DBMgrEnvSocket;

#endif
