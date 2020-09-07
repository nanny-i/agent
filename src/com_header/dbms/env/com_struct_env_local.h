#ifndef DB_ENV_LOCAL_H_4D39CDDB_PO_E289_4d56_9F98_FE42776F4467
#define DB_ENV_LOCAL_H_4D39CDDB_PO_E289_4d56_9F98_FE42776F4467

typedef struct _db_env_local
{
	_db_env_local()
	{
		nID				= 0;
		nUsedFlag		= 1;
		nRegDate		= 0;

		nChkType		= 0;
		nChkCode		= 0;
	}

	UINT32				nID;
	UINT32				nUsedFlag;
	UINT32				nRegDate;


	UINT32				nChkType;
	UINT32				nChkCode;
	TMapID				tNValueMap;
	TMapIDStr			tSValueMap;

}DB_ENV_LOCAL, *PDB_ENV_LOCAL;

typedef list<DB_ENV_LOCAL>					TListDBEnvLocal;
typedef TListDBEnvLocal::iterator			TListDBEnvLocalItor;

typedef map<UINT32, DB_ENV_LOCAL>			TMapDBEnvLocal;
typedef TMapDBEnvLocal::iterator			TMapDBEnvLocalItor;

#endif //DB_ENV_LOCAL_H_4D39CDDB_PO_E289_4d56_9F98_FE42776F4467



