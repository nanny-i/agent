#ifndef DB_PO_HOST_NOTIFY_H_4D39CDDB_PO_E289_4d56_9F98_FE42776F4467
#define DB_PO_HOST_NOTIFY_H_4D39CDDB_PO_E289_4d56_9F98_FE42776F4467

typedef struct _db_po_host_notify
{
	_db_po_host_notify()
	{
		nMsgType		= 0;
	}

	DB_PO_HEADER		tDPH;

	UINT32				nMsgType;

}DB_PO_HOST_NOTIFY, *PDB_PO_HOST_NOTIFY;

typedef list<DB_PO_HOST_NOTIFY>				TListDBPoHostNotify;
typedef TListDBPoHostNotify::iterator			TListDBPoHostNotifyItor;

typedef map<UINT32, DB_PO_HOST_NOTIFY>		TMapDBPoHostNotify;
typedef TMapDBPoHostNotify::iterator			TMapDBPoHostNotifyItor;
//---------------------------------------------------------------------------

typedef struct _db_po_host_notify_pkg
{
	_db_po_host_notify_pkg()
	{
	}

	DB_PO_HEADER		tDPH;

}DB_PO_HOST_NOTIFY_PKG, *PDB_PO_HOST_NOTIFY_PKG;

typedef list<DB_PO_HOST_NOTIFY_PKG>				TListDBPoHostNotifyPkg;
typedef TListDBPoHostNotifyPkg::iterator			TListDBPoHostNotifyPkgItor;

typedef map<UINT32, DB_PO_HOST_NOTIFY_PKG>		TMapDBPoHostNotifyPkg;
typedef TMapDBPoHostNotifyPkg::iterator			TMapDBPoHostNotifyPkgItor;
//---------------------------------------------------------------------------

typedef struct _db_po_host_notify_unit
{
	_db_po_host_notify_unit()
	{
		nNotifyTime		= 0;
		nSchTime		= 0;
		nPosType		= 0;
		nShowTime		= 0;
		nShowSize		= 0;
		nShowPos		= 0;
		nMsgFmtType		= 0;
		strMsgInfo		= "";
	}

	DB_PO_HEADER		tDPH;

	UINT32				nNotifyTime;
	UINT32				nSchTime;
	UINT32				nPosType;
	UINT32				nShowSize;
	UINT32				nShowPos;
	UINT32				nShowTime;
	UINT32				nMsgFmtType;
	String				strMsgInfo;

}DB_PO_HOST_NOTIFY_UNIT, *PDB_PO_HOST_NOTIFY_UNIT;

typedef list<DB_PO_HOST_NOTIFY_UNIT>				TListDBPoHostNotifyUnit;
typedef TListDBPoHostNotifyUnit::iterator			TListDBPoHostNotifyUnitItor;

typedef map<UINT32, DB_PO_HOST_NOTIFY_UNIT>			TMapDBPoHostNotifyUnit;
typedef TMapDBPoHostNotifyUnit::iterator			TMapDBPoHostNotifyUnitItor;

#endif //DB_PO_HOST_NOTIFY_H_4D39CDDB_PO_E289_4d56_9F98_FE42776F4467



