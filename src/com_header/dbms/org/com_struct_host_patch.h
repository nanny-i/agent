#ifndef DB_HOST_PATCH_H_4D39CDDB_E289_4d56_9F98_FE42776F4467
#define DB_HOST_PATCH_H_4D39CDDB_E289_4d56_9F98_FE42776F4467

typedef struct _db_host_patch
{
	_db_host_patch()
	{
		nID						= 0;
		nUsedFlag				= USED_FLAG_TYPE_USED;
		nRegDate				= 0;

		nHostID					= 0;
		nFindType				= 0;
		nKBID					= 0;
		nNoRemove				= 0;
	} 

	UINT32				nID ;
	UINT32				nUsedFlag;
	UINT32				nRegDate;

	UINT32				nHostID;
	UINT32				nFindType;
	UINT32				nKBID;

	String				strCategory;
	String				strName;
	String				strPublisher;
	String				strInsDate;
	String				strGuid;
	UINT32				nNoRemove;
	String				strUninstall;
}DB_HOST_PATCH, *PDB_HOST_PATCH;

typedef list<DB_HOST_PATCH>				TListDBHostPatch;
typedef TListDBHostPatch::iterator		TListDBHostPatchItor;

typedef map<UINT32, DB_HOST_PATCH>		TMapDBHostPatch;
typedef TMapDBHostPatch::iterator		TMapDBHostPatchItor;

//-------------------------------------------------------------

#endif //DB_HOST_PATCH_H_4D39CDDB_E289_4d56_9F98_FE42776F4467



