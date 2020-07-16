/*
 * Copyright (C) 2020-2025 ASHINi corp. 
 * 
 * This library is free software; you can redistribute it and/or 
 * modify it under the terms of the GNU Lesser General Public 
 * License as published by the Free Software Foundation; either 
 * version 2.1 of the License, or (at your option) any later version. 
 * 
 * This library is distributed in the hope that it will be useful, 
 * but WITHOUT ANY WARRANTY; without even the implied warranty of 
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU 
 * Lesser General Public License for more details. 
 * 
 * You should have received a copy of the GNU Lesser General Public 
 * License along with this library; if not, write to the Free Software 
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA 
 * 
 */

#ifndef MANAGE_BASE_H__

#define MANAGE_BASE_H__

#include <iostream>
#include <string>
#include <pthread.h>
#include <map>

using namespace std;

//---------------------------------------------------------------------------
typedef struct _mgr_base_gkey
{
	_mgr_base_gkey()
	{
		nKey		= 0;
		nInitMode	= 0;
	}

	UINT64 nKey;
	UINT32 nInitMode;

	TListIDItor	tItorBegin;
	TListIDItor	tItorEnd;	
}MGR_BASE_GKEY, *PMGR_BASE_GKEY;

typedef map<UINT64, MGR_BASE_GKEY>		TMapMgrBaseGKey;
typedef TMapMgrBaseGKey::iterator		TMapMgrBaseGKeyItor;
//---------------------------------------------------------------------------
template <class _T>

class CManageBase

{
public:
	CManageBase(void);
	virtual ~CManageBase(void);

public :
	virtual INT32		AddItem(UINT32 nID, _T& data);
	virtual INT32		AddItem(_T& data);
	virtual INT32		EditItem(UINT32 nID, _T& data);
	virtual INT32		EditItem(_T& data);
	virtual INT32		DeleteItem(UINT32 nID);
	virtual INT32		ClearItem();
	virtual _T*			FindItem(UINT32 nID);
	virtual _T*			FirstItem();
	virtual _T*			LastItem();
	virtual UINT32		FirstID();
	virtual UINT32		LastID();
	virtual INT32		IsExistID(UINT32 nID, list<_T>& tUnitList);

	virtual UINT32 Count();	
	virtual UINT32 GetItem(INT32 nID, TListID &tListID);
	virtual UINT32 GetItemPtrList(INT32 nID, list<_T*>	&tListPtr);
	virtual UINT32 GetItemPtrArray(INT32 nID, vector <_T*> &tVecPtr);
	virtual UINT32 GetItemIDList(TListID& tListID);	
	virtual UINT32 GetItemPtrList(list<PVOID>	&tListPtr, UINT32& nStartID, UINT32 nLastID = 0, UINT32 nOnceNum = 0);
	virtual UINT32 GetItemPtrListByItor(list<PVOID>	&tListPtr, UINT32& nStartID, UINT32 nLastID = 0, UINT32 nOnceNum = 0);
	virtual UINT32 GetItemIDListByGKeyListItor(UINT64 nKey, TListID& tListID, UINT32 nStartID, UINT32 nLastID = 0, UINT32 nOnceNum = 0);

public:
	virtual	UINT32		AddKeyID(UINT32 nKey, UINT32 nID);
	virtual	UINT32		DelKeyID(UINT32 nKey);
	virtual	UINT32		FindKeyID(UINT32 nKey);
	virtual UINT32		IsExistKeyID(UINT32 nKey);
	virtual _T*			FindKeyItem(UINT32 nKey);
	virtual	UINT32		GetKeyIDList(TListID& tIDList);
	virtual	UINT32		ClearKeyID();
	virtual	UINT32		ConvertKeyID(TListID& tKeyList, TListID& tIDList);
	virtual	UINT32		LastKey();

public:
	virtual	UINT32		AddStrKeyID(String strKey, UINT32 nID);
	virtual	UINT32		DelStrKeyID(String strKey);
	virtual	UINT32		FindStrKeyID(String strKey);
	virtual _T*			FindStrKeyItem(String strKey);
	virtual UINT32		GetStrKeyList(TListStr& tKeyList);
	virtual	UINT32		ClearStrKeyID();
	virtual	UINT32		ConvertStrKeyID(TListStr& tStrKeyList, TListID& tIDList);

public:
	virtual	UINT32		AddKeyIDList(UINT32 nKey, UINT32 nID);
	virtual	UINT32		DelKeyIDList(UINT32 nKey);
	virtual	UINT32		DelKeyIDList(UINT32 nKey, UINT32 nID);
	virtual	UINT32		SetKeyIDList(UINT32 nKey, TListID& tIDList);
	virtual	UINT32		GetKeyIDList(UINT32 nKey, TListID& tIDList);
	virtual	UINT32		ClearKeyIDList();

public:
	virtual	UINT32		AddKeyIDMap(UINT32 nKey, UINT32 nID);
	virtual	UINT32		DelKeyIDMap(UINT32 nKey);
	virtual	UINT32		DelKeyIDMap(UINT32 nKey, UINT32 nID);
	virtual	UINT32		GetKeyIDMap(UINT32 nKey, TMapID& tIDMap);
	virtual	UINT32		GetKeyIDMap(UINT32 nKey, TMapID& tIDMap, UINT32 nLimited);
	virtual	UINT32		ClearKeyIDMap();

public:
	virtual	UINT32		AddPosKeyIDMap(UINT32 nKey, UINT32 nID, UINT32 nPos = 0);
	virtual	UINT32		DelPosKeyIDMap(UINT32 nKey, UINT32 nPos = 0);
	virtual	UINT32		DelPosKeyIDMap(UINT32 nKey, UINT32 nID, UINT32 nPos = 0);
	virtual	UINT32		GetPosKeyIDMap(UINT32 nKey, TMapID& tIDMap, UINT32 nPos = 0);
	virtual	UINT32		GetPosKeyIDMap(UINT32 nKey, TListID& tIDList, UINT32 nPos = 0);
	virtual	UINT32		GetPosKeyIDMap(TMapIDMap& tKeyIDMap, UINT32 nPos = 0);
	virtual	UINT32		GetPosKeyIDMap(TMapID& tIDMap, UINT32 nPos = 0);
	virtual	UINT32		ClearPosKeyIDMap(UINT32 nPos = 0);
	virtual	UINT32		ClearPosKeyIDMap_ALL();

public:
	virtual	UINT32		AddPosStrKeyID(String strKey, UINT32 nID, UINT32 nPos = 0);
	virtual	UINT32		DelPosStrKeyID(String strKey, UINT32 nPos = 0);
	virtual	UINT32		FindPosStrKeyID(String strKey, UINT32 nPos = 0);
	virtual	_T*			FindPosStrKeyItem(String strKey, UINT32 nPos = 0);
	virtual	UINT32		GetPosStrKeyIDMap(TMapStrID& tStrKeyIDMap, UINT32 nPos = 0);
	virtual	UINT32		GetPosStrKeyList(TListStr& tStrKeyList, UINT32 nPos = 0);	
	virtual	UINT32		ClearPosStrKeyID(UINT32 nPos = 0);
	virtual	UINT32		ClearPosStrKeyID_ALL();

public:
	virtual	UINT32		AddKeySubIDMap(UINT32 nKey, UINT32 nSubKey, UINT32 nID);
	virtual	UINT32		DelKeySubIDMap(UINT32 nKey);
	virtual	UINT32		DelKeySubIDMap(UINT32 nKey, UINT32 nSubKey);
	virtual	UINT32		GetKeySubIDMap(UINT32 nKey, TMapID& tIDMap);
	virtual	UINT32		GetKeySubIDMapSKey(UINT32 nKey, TListID& tSKeyList);
	virtual	UINT32		GetKeySubIDMapID(UINT32 nKey, TListID& tIDList);
	virtual UINT32		FindKeySubIDMapID(UINT32 nKey, UINT32 nSubKey);
	virtual _T*			FindKeySubIDMapItem(UINT32 nKey, UINT32 nSubKey);
	virtual	UINT32		ClearKeySubIDMap();

public:
	virtual	UINT32		AddPosKeySubIDMap(UINT32 nKey, UINT32 nSubKey, UINT32 nID, UINT32 nPos = 0);
	virtual	UINT32		DelPosKeySubIDMap(UINT32 nKey, UINT32 nPos = 0);
	virtual	UINT32		DelPosKeySubIDMap(UINT32 nKey, UINT32 nSubKey, UINT32 nPos = 0);
	virtual	UINT32		GetPosKeySubIDMap(UINT32 nKey, TMapID& tSubKeyMap, UINT32 nPos = 0);
	virtual	UINT32		GetPosKeySubIDMap(UINT32 nKey, TListID& tSubKeyList, UINT32 nPos = 0);
	virtual	UINT32		GetPosKeySubIDMap(UINT32 nKey, UINT32 nSubKey, UINT32 nPos = 0);
	virtual	UINT32		GetPosKeySubIDMap(TMapIDMap& tKeyIDMap, UINT32 nPos = 0);
	virtual	UINT32		CountPosKeySubIDMap(UINT32 nKey, UINT32 nPos = 0);
	virtual	UINT32		ClearPosKeySubIDMap(UINT32 nPos = 0);

public:
	virtual	UINT32		AddPosStrKeySubIDMap(String strKey, UINT32 nSubKey, UINT32 nID, UINT32 nPos = 0);
	virtual	UINT32		DelPosStrKeySubIDMap(String strKey, UINT32 nPos = 0);
	virtual	UINT32		DelPosStrKeySubIDMap(String strKey, UINT32 nSubKey, UINT32 nPos = 0);
	virtual	UINT32		GetPosStrKeySubIDMap(String strKey, TMapID& tSubKeyMap, UINT32 nPos = 0);
	virtual	UINT32		GetPosStrKeySubIDMap(String strKey, TListID& tSubKeyList, UINT32 nPos = 0);
	virtual	UINT32		GetPosStrKeySubIDMap(String strKey, UINT32 nSubKey, UINT32 nPos = 0);
	virtual	UINT32		GetPosStrKeySubIDMap(TMapStrMapID& tKeyStrMap, UINT32 nPos = 0);
	virtual	UINT32		ClearPosStrKeySubIDMap(UINT32 nPos = 0);

public:
	virtual	UINT32		AddKeyList(UINT32 nKey);
	virtual	UINT32		DelKeyList(UINT32 nKey);
	virtual	UINT32		ClearKeyList();
	virtual	UINT32		LastKeyList();
	virtual UINT32		GetKeyListCount();

public:
	virtual _T&			GetData();
	virtual _T*			GetPData();

public:
	virtual String		GetHash();

public:
	virtual void		PrintDbgInfo();

protected :
	map <UINT32, _T>	m_tMap;
	TMapID				m_tKeyMap;
	TMapStrID			m_tStrKeyMap;
	TMapIDList			m_tKeyListMap;
	TMapIDMap			m_tKeyMapMap;
	TMapIDMap			m_tKeySubIDMap;
	TMapIDMapMap		m_tPosKeyMapMap;
	TMapIDMapMap		m_tPosKeySubMapMap;
	TMapIDMapStrID		m_tPosStrKeyMap;
	TMapIDMapStrMapID	m_tPosStrKeySubMapMap;

	TListID				m_tKeyList;
	map<DWORD, _T>		m_tDataMap;

protected:
	list<_T>			m_tTempAddList;
	list<_T>			m_tTempEditList;
	list<UINT32>		m_tTempDelList;

private:
	pthread_mutex_t 	m_mutex;

protected:
	typename map <UINT32, _T>::iterator m_pMapItorFind;
	typename map <UINT32, _T>::iterator	m_pMapItorBegin;
	typename map <UINT32, _T>::iterator	m_pMapItorEnd;
	typename map <UINT32, _T>::reverse_iterator	m_pMapRItorBegin;
	typename map <UINT32, _T>::reverse_iterator	m_pMapRItorEnd;

	typename map <DWORD, _T>::iterator	m_pDataMapItorFind;

	typename list <_T>::iterator m_pListItorBegin;
	typename list <_T>::iterator m_pListItorEnd;

	UINT32						m_nInitGlobalIter;

public:
	virtual INT32		InitGlobalIter();
	virtual	INT32		FreeGlobalIter();
	virtual _T*			NextGlobalIter();
	virtual INT32		IsNextGlobalIter();
	virtual INT32		InitGlobalRIter();
	virtual	INT32		FreeGlobalRIter();
	virtual _T*			NextGlobalRIter();
	virtual INT32		IsNextGlobalRIter();
	virtual INT32		IsInitGlobalIter();

protected:
	typename map <UINT32, UINT32>::iterator m_pKeyItorFind;
	typename map <UINT32, UINT32>::iterator	m_pKeyItorBegin;
	typename map <UINT32, UINT32>::iterator	m_pKeyItorEnd;
	typename map <UINT32, UINT32>::reverse_iterator	m_pKeyRItorBegin;
	typename map <UINT32, UINT32>::reverse_iterator	m_pKeyRItorEnd;
	UINT32				m_nInitGlobalKeyIter;

public:
	virtual INT32		InitGlobalKeyIter();
	virtual	INT32		FreeGlobalKeyIter();
	virtual UINT32		NextGlobalKeyIter();
	virtual INT32		IsNextGlobalKeyIter();
	virtual INT32		IsInitGlobalKeyIter();

private:
	TMapMgrBaseGKey		m_tMgrBaseGKeyMap;

public:	
	virtual INT32		InitGlobalKeyListIter(UINT64 nKey);
	virtual	INT32		FreeGlobalKeyListIter(UINT64 nKey);
	virtual UINT32		NextGlobalKeyListIter(UINT64 nKey);
	virtual INT32		IsNextGlobalKeyListIter(UINT64 nKey);
	virtual INT32		IsInitGlobalKeyListIter(UINT64 nKey);
	virtual INT32		IsNextFreeGlobalKeyListIter(UINT64 nKey);

public:
	INT32				SetSyncDBMSType(UINT32 nType);
	INT32				IsSyncDBMS();

public:
	TMapID				m_tTempIDMap;
	INT32				AddTempID(UINT32 nID, UINT32 nValue);
	INT32				DelTempID(UINT32 nID);
	INT32				ClearTempID();
	INT32				GetTempIDList(TListID& tIDList);
	INT32				SetTempIDList(TListID& tIDList);
	INT32				SetTempIDList(TMapID& tIDMap);


public:
	UINT32		m_nRecvNum;
	UINT32		m_nTempClass;
	String		m_strFullHash;
	String		m_strHashValue;	

public:
	UINT32		m_nDBSyncType;
	UINT32		m_nDBSyncChkType;

public:
	INT32		m_nAutoClear;
};


#define	TEMPLATE template <class _T>

TEMPLATE	CManageBase<_T>::CManageBase(void)
{
	m_nTempClass			= 0;
	m_nRecvNum				= 0;

	m_nInitGlobalIter		= 0;
	m_nInitGlobalKeyIter	= 0;
	pthread_mutex_init(&m_mutex, NULL);
	m_nAutoClear			= 1;
	
}

TEMPLATE	CManageBase<_T>::~CManageBase(void)
{
	if(m_nAutoClear)
	{
		ClearItem();

		ClearStrKeyID();
		ClearKeyIDList();
		ClearKeyList();
		ClearKeyIDMap();
		ClearPosKeyIDMap_ALL();
		ClearPosStrKeyID_ALL();
		ClearKeySubIDMap();
		pthread_mutex_destroy(&m_mutex);
		m_nAutoClear = 0;
	}
}

TEMPLATE INT32		CManageBase<_T>::AddItem(UINT32 nID, _T& data)
{	
	pthread_mutex_lock (&m_mutex);
	m_tMap[nID] = data;
	pthread_mutex_unlock (&m_mutex);
	return 0;
}

TEMPLATE INT32		CManageBase<_T>::AddItem(_T& data)
{
	UINT32 nID = ((PDB_ID)&data)->nID;	
	return AddItem(nID, data);
}

TEMPLATE INT32		CManageBase<_T>::EditItem(UINT32 nID, _T& data)
{
	pthread_mutex_lock (&m_mutex);
	m_pMapItorFind = m_tMap.find(nID);
	if (m_pMapItorFind != m_tMap.end())
	{
		m_pMapItorFind->second = data;
	}
	pthread_mutex_unlock (&m_mutex);
	return 0;
}

TEMPLATE INT32		CManageBase<_T>::EditItem(_T& data)
{
	UINT32 nID = ((PDB_ID)&data)->nID;	
	return EditItem(nID, data);
}
	
TEMPLATE INT32		CManageBase<_T>::DeleteItem(UINT32 nID)
{
	INT32 nRtn = 0;
	pthread_mutex_lock (&m_mutex);
	m_pMapItorFind = m_tMap.find(nID);
	if (m_pMapItorFind != m_tMap.end())
	{
		m_tMap.erase(m_pMapItorFind);
	}
	else
	{
		nRtn = -1;
	}
	pthread_mutex_unlock (&m_mutex);
	return nRtn;
}

TEMPLATE INT32		CManageBase<_T>::ClearItem()
{
	pthread_mutex_lock (&m_mutex);
	m_tMap.clear();
	pthread_mutex_unlock (&m_mutex);
	return 0;
}

TEMPLATE _T*			CManageBase<_T>::FindItem(UINT32 nID)
{
	_T* pFind = NULL;
	pthread_mutex_lock (&m_mutex);
	m_pMapItorFind = m_tMap.find(nID);
	if (m_pMapItorFind != m_tMap.end())
	{
		pFind = &(m_pMapItorFind->second);
	}
	pthread_mutex_unlock (&m_mutex);
	return pFind;
}

TEMPLATE _T*			CManageBase<_T>::FirstItem()
{
	_T* pFind = NULL;
	pthread_mutex_lock (&m_mutex);
	m_pMapItorBegin = m_tMap.begin();
	if (m_pMapItorBegin != m_tMap.end())
	{
		pFind = &(m_pMapItorBegin->second);
	}
	pthread_mutex_unlock (&m_mutex);
	return pFind;
}

TEMPLATE _T*			CManageBase<_T>::LastItem()
{
	_T* pFind = NULL;
	pthread_mutex_lock (&m_mutex);
	m_pMapItorBegin = m_tMap.begin();
	m_pMapItorEnd = m_tMap.end();	
	if (m_pMapItorBegin != m_tMap.end())
	{
		pFind = &((--m_pMapItorEnd)->second);
	}
	pthread_mutex_unlock (&m_mutex);
	return pFind;
}

TEMPLATE UINT32			CManageBase<_T>::FirstID()
{
	UINT32 nID = 0;
	pthread_mutex_lock (&m_mutex);
	m_pMapItorBegin = m_tMap.begin();
	m_pMapItorEnd = m_tMap.end();	
	if (m_pMapItorBegin != m_pMapItorEnd)
	{
		nID = m_pMapItorBegin->first;
	}
	pthread_mutex_unlock (&m_mutex);
	return nID;
}

TEMPLATE UINT32			CManageBase<_T>::LastID()
{
	UINT32 nID = 0;

	pthread_mutex_lock (&m_mutex);
	m_pMapRItorBegin = m_tMap.rbegin();
	m_pMapRItorEnd = m_tMap.rend();	
	if (m_pMapRItorBegin != m_pMapRItorEnd)
	{
		nID = m_pMapRItorBegin->first;
	}
	pthread_mutex_unlock (&m_mutex);
	return nID;
}

TEMPLATE INT32	CManageBase<_T>::IsExistID(UINT32 nID, list<_T>& tUnitList)
{
	m_pListItorBegin = tUnitList.begin();
	m_pListItorEnd = tUnitList.end();
	for(m_pListItorBegin; m_pListItorBegin != m_pListItorEnd; m_pListItorBegin++)
	{
		if(m_pListItorBegin->nID == nID)
			return 1;
	}
	return 0;
}


TEMPLATE UINT32 CManageBase<_T>::Count()
{
	UINT32 nRtn = 0;
	pthread_mutex_lock (&m_mutex);

	nRtn = (UINT32)m_tMap.size();

	pthread_mutex_unlock (&m_mutex);
	return nRtn;
}

TEMPLATE UINT32 CManageBase<_T>::GetItemPtrList(INT32 nID, list<_T*>	&tListPtr)
{
	UINT32 nRtn = 0;
	pthread_mutex_lock (&m_mutex);
	m_pMapItorBegin = m_tMap.begin();
	m_pMapItorEnd = m_tMap.end();
	if (nID != -1)
	{
		for (; m_pMapItorBegin != m_pMapItorEnd; m_pMapItorBegin++)
		{
			if (m_pMapItorBegin->second.nID == nID)
			{		
				tListPtr.push_back(&(m_pMapItorBegin->second));
			}
		}
	}
	else
	{
		for (; m_pMapItorBegin != m_pMapItorEnd; m_pMapItorBegin++)
		{
			tListPtr.push_back(&(m_pMapItorBegin->second));
		}
	}
	nRtn = (UINT32)tListPtr.size();

	pthread_mutex_unlock (&m_mutex);
	return nRtn;
}

TEMPLATE UINT32 CManageBase<_T>::GetItemPtrArray(INT32 nID, vector <_T*> &tVecPtr)
{
	UINT32 nRtn = 0;

	pthread_mutex_lock (&m_mutex);
	m_pMapItorBegin = m_tMap.begin();
	m_pMapItorEnd = m_tMap.end();
	if (nID != -1)
	{
		for (; m_pMapItorBegin != m_pMapItorEnd; m_pMapItorBegin++)
		{
			if (m_pMapItorBegin->second.nID == nID)
			{		
				tVecPtr.push_back(&(m_pMapItorBegin->second));
			}
		}
	}
	else
	{
		for (; m_pMapItorBegin != m_pMapItorEnd; m_pMapItorBegin++)
		{
			tVecPtr.push_back(&(m_pMapItorBegin->second));
		}
	}
	nRtn = (UINT32)tVecPtr.size();

	pthread_mutex_unlock (&m_mutex);
	return nRtn;
}

TEMPLATE UINT32 CManageBase<_T>::GetItem(INT32 nID, TListID &tListID)
{
	UINT32 nRtn = 0;

	pthread_mutex_lock (&m_mutex);
	m_pMapItorBegin = m_tMap.begin();
	m_pMapItorEnd = m_tMap.end();

	if (nID != -1)
	{
		for (; m_pMapItorBegin != m_pMapItorEnd; m_pMapItorBegin++)
		{
			if (m_pMapItorBegin->second.nID == nID)
			{		
				tListID.push_back(m_pMapItorBegin->second.nID);
			}			
		}
	}
	else
	{
		for (; m_pMapItorBegin != m_pMapItorEnd; m_pMapItorBegin++)
		{
			tListID.push_back(m_pMapItorBegin->second.nID);
		}
	}
	nRtn = (UINT32)tListID.size();
	pthread_mutex_unlock (&m_mutex);
	return nRtn;
}

TEMPLATE	UINT32	CManageBase<_T>::GetItemIDList(TListID& tListID)
{
	UINT32 nRtn = 0;

	pthread_mutex_lock (&m_mutex);
	m_pMapItorBegin = m_tMap.begin();
	m_pMapItorEnd = m_tMap.end();
	for (; m_pMapItorBegin != m_pMapItorEnd; m_pMapItorBegin++)
	{			
		tListID.push_back(m_pMapItorBegin->second.nID);
	}
	nRtn = (UINT32)tListID.size();

	pthread_mutex_unlock (&m_mutex);
	return nRtn;
}


TEMPLATE	UINT32 CManageBase<_T>::GetItemPtrList(list<PVOID>	&tListPtr, UINT32& nStartID, UINT32 nLastID, UINT32 nOnceNum)
{
	UINT32 nRtn = 0;
	pthread_mutex_lock (&m_mutex);

	m_pMapItorBegin = m_tMap.begin();
	m_pMapItorEnd = m_tMap.end();
	for (; m_pMapItorBegin != m_pMapItorEnd; m_pMapItorBegin++)
	{			
		if(nStartID && m_pMapItorBegin->first <= nStartID)
			continue;
		if(nLastID && m_pMapItorBegin->first > nLastID)
			break;

		nStartID = m_pMapItorBegin->first;
		tListPtr.push_back(&(m_pMapItorBegin->second));

		if(nOnceNum && nOnceNum == tListPtr.size())
			break;
	}
	nRtn = (UINT32)tListPtr.size();
	pthread_mutex_unlock (&m_mutex);
	return nRtn;
}

TEMPLATE	UINT32 CManageBase<_T>::GetItemPtrListByItor(list<PVOID>	&tListPtr, UINT32& nStartID, UINT32 nLastID, UINT32 nOnceNum)
{
	_T* tUnit = NULL;
	if(!IsInitGlobalIter())
	{
		InitGlobalIter();
	}
	
	while(IsNextGlobalIter() && nOnceNum)
	{
		tUnit = NextGlobalIter();

		if(tUnit->nID <= nStartID)
			continue;
		if(nLastID && tUnit->nID > nLastID)
		{
			FreeGlobalIter();
			break;
		}

		nStartID = tUnit->nID;
		tListPtr.push_back(tUnit);
		nOnceNum -= 1;
	}
	return tListPtr.size();
}

TEMPLATE	UINT32 CManageBase<_T>::GetItemIDListByGKeyListItor(UINT64 nKey, TListID& tListID, UINT32 nStartID, UINT32 nLastID, UINT32 nOnceNum)
{
	if(!IsInitGlobalKeyListIter(nKey))
	{
		InitGlobalKeyListIter(nKey);
	}

	while(IsNextGlobalKeyListIter(nKey) && nOnceNum)
	{
		UINT32 nID = NextGlobalKeyListIter(nKey);
		if(nID <= nStartID)			continue;		
		if(FindItem(nID) == NULL)	continue;

		tListID.push_back(nID);
		nOnceNum -= 1;

		if(nLastID && nID == nLastID)
		{
			FreeGlobalKeyListIter(nKey);
			break;
		}
	}
	return tListID.size();
}
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

TEMPLATE	UINT32		CManageBase<_T>::AddKeyID(UINT32 nKey, UINT32 nID)
{
	pthread_mutex_lock (&m_mutex);
	m_tKeyMap[nKey] = nID;
	pthread_mutex_unlock (&m_mutex);
	return 0;
}

TEMPLATE	UINT32		CManageBase<_T>::DelKeyID(UINT32 nKey)
{
	pthread_mutex_lock (&m_mutex);
	m_tKeyMap.erase(nKey);
	pthread_mutex_unlock (&m_mutex);
	return 0;
}

TEMPLATE	UINT32		CManageBase<_T>::FindKeyID(UINT32 nKey)
{
	UINT32 nRtn = 0;
	
	pthread_mutex_lock (&m_mutex);
	m_pKeyItorFind = m_tKeyMap.find(nKey);
	if(m_pKeyItorFind != m_tKeyMap.end())
		nRtn = m_pKeyItorFind->second;
	pthread_mutex_unlock (&m_mutex);

	return nRtn;
}

TEMPLATE	UINT32		CManageBase<_T>::IsExistKeyID(UINT32 nKey)
{
	UINT32 nRtn = 0;
	pthread_mutex_lock (&m_mutex);
	m_pKeyItorFind = m_tKeyMap.find(nKey);
	if(m_pKeyItorFind != m_tKeyMap.end())
		nRtn = 1;
	pthread_mutex_unlock (&m_mutex);

	return nRtn;
}

TEMPLATE _T*			CManageBase<_T>::FindKeyItem(UINT32 nKey)
{
	UINT32 nID = FindKeyID(nKey);
	return FindItem(nID);
}

TEMPLATE	UINT32		CManageBase<_T>::GetKeyIDList(TListID& tIDList)
{
	pthread_mutex_lock (&m_mutex);
	m_pKeyItorBegin = m_tKeyMap.begin();
	m_pKeyItorEnd = m_tKeyMap.end();
	for(m_pKeyItorBegin; m_pKeyItorBegin != m_pKeyItorEnd; m_pKeyItorBegin++)
	{
		tIDList.push_back(m_pKeyItorBegin->first);
	}
	pthread_mutex_unlock (&m_mutex);

	return tIDList.size();
}

TEMPLATE	UINT32		CManageBase<_T>::ClearKeyID()
{
	pthread_mutex_lock (&m_mutex);
	m_tKeyMap.clear();
	pthread_mutex_unlock (&m_mutex);
	return 0;
}

TEMPLATE	UINT32		CManageBase<_T>::ConvertKeyID(TListID& tKeyList, TListID& tIDList)
{
	TListIDItor begin, end;
	pthread_mutex_lock (&m_mutex);
	begin = tKeyList.begin();	end = tKeyList.end();
	for(begin; begin != end; begin++)
	{
		m_pKeyItorFind = m_tKeyMap.find(*begin);
		if(m_pKeyItorFind == m_tKeyMap.end())
			continue;

		tIDList.push_back(m_pKeyItorFind->second);
	}
	pthread_mutex_unlock (&m_mutex);
	return 0;
}

TEMPLATE	UINT32		CManageBase<_T>::LastKey()
{
	UINT32 nKey = 0;

	pthread_mutex_lock (&m_mutex);
	m_pKeyRItorBegin = m_tKeyMap.rbegin();
	m_pKeyRItorEnd = m_tKeyMap.rend();	
	if (m_pKeyRItorBegin != m_pKeyRItorEnd)
	{
		nKey = m_pKeyRItorBegin->first;
	}
	pthread_mutex_unlock (&m_mutex);
	return nKey;
}
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

TEMPLATE	UINT32		CManageBase<_T>::AddStrKeyID(String strKey, UINT32 nID)
{
	pthread_mutex_lock (&m_mutex);
	m_tStrKeyMap[strKey] = nID;
	pthread_mutex_unlock (&m_mutex);
	return 0;
}

TEMPLATE	UINT32		CManageBase<_T>::DelStrKeyID(String strKey)
{
	pthread_mutex_lock (&m_mutex);
	m_tStrKeyMap.erase(strKey);
	pthread_mutex_unlock (&m_mutex);
	return 0;
}

TEMPLATE	UINT32		CManageBase<_T>::FindStrKeyID(String strKey)
{
	UINT32 nRtn = 0;
	TMapStrIDItor find;
	pthread_mutex_lock (&m_mutex);
	find = m_tStrKeyMap.find(strKey);
	if(find != m_tStrKeyMap.end())
		nRtn = find->second;
	pthread_mutex_unlock (&m_mutex);
	return nRtn;
}

TEMPLATE _T*			CManageBase<_T>::FindStrKeyItem(String strKey)
{
	UINT32 nID = FindStrKeyID(strKey);
	return FindItem(nID);
}

TEMPLATE	UINT32		CManageBase<_T>::GetStrKeyList(TListStr& tKeyList)
{
	UINT32 nRtn = 0;
	TMapStrIDItor begin, end;

	pthread_mutex_lock (&m_mutex);
	begin = m_tStrKeyMap.begin();	end = m_tStrKeyMap.end();
	for(begin; begin != end; begin++)
	{
		tKeyList.push_back(begin->first);
	}
	nRtn = tKeyList.size();
	pthread_mutex_unlock (&m_mutex);

	return nRtn;
}

TEMPLATE	UINT32		CManageBase<_T>::ClearStrKeyID()
{
	pthread_mutex_lock (&m_mutex);
	m_tStrKeyMap.clear();
	pthread_mutex_unlock (&m_mutex);
	return 0;
}

TEMPLATE	UINT32		CManageBase<_T>::ConvertStrKeyID(TListStr& tStrKeyList, TListID& tIDList)
{
	TListStrItor begin, end;
	TMapStrIDItor find;
	pthread_mutex_lock (&m_mutex);
	begin = tStrKeyList.begin();	end = tStrKeyList.end();
	for(begin; begin != end; begin++)
	{
		find = m_tStrKeyMap.find(*begin);
		if(find == m_tStrKeyMap.end())		continue;

		tIDList.push_back(find->second);
	}
	pthread_mutex_unlock (&m_mutex);
	return 0;
}
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

TEMPLATE	UINT32		CManageBase<_T>::AddKeyIDList(UINT32 nKey, UINT32 nID)
{
	TListID tIDList;
	TMapIDListItor find;
	pthread_mutex_lock (&m_mutex);
	find = m_tKeyListMap.find(nKey);
	if(find == m_tKeyListMap.end())
	{
		m_tKeyListMap[nKey] = tIDList;
		find = m_tKeyListMap.find(nKey);
	}
	find->second.push_back(nID);
	pthread_mutex_unlock (&m_mutex);
	return 0;
}

TEMPLATE	UINT32		CManageBase<_T>::DelKeyIDList(UINT32 nKey)
{
	TMapIDListItor find;
	pthread_mutex_lock (&m_mutex);
	find = m_tKeyListMap.find(nKey);
	if(find != m_tKeyListMap.end())
	{
		find->second.clear();
		m_tKeyListMap.erase(nKey);
	}	
	pthread_mutex_unlock (&m_mutex);
	return 0;
}

TEMPLATE	UINT32		CManageBase<_T>::DelKeyIDList(UINT32 nKey, UINT32 nID)
{
	TMapIDListItor find;
	pthread_mutex_lock (&m_mutex);
	find = m_tKeyListMap.find(nKey);
	if(find == m_tKeyListMap.end())
	{
		pthread_mutex_unlock (&m_mutex);
		return 0;
	}
	RemoveListID(find->second, nID);

	if(find->second.size() == 0)
	{
		m_tKeyListMap.erase(nKey);
	}
	pthread_mutex_unlock (&m_mutex);
	return 0;
}

TEMPLATE	UINT32		CManageBase<_T>::SetKeyIDList(UINT32 nKey, TListID& tIDList)
{
	TMapIDListItor find;
	pthread_mutex_lock (&m_mutex);

	find = m_tKeyListMap.find(nKey);
	if(find == m_tKeyListMap.end())
	{
		m_tKeyListMap[nKey] = tIDList;
		find = m_tKeyListMap.find(nKey);
	}

	find->second = tIDList;

	pthread_mutex_unlock (&m_mutex);
	return 0;
}

TEMPLATE	UINT32		CManageBase<_T>::GetKeyIDList(UINT32 nKey, TListID& tIDList)
{
	TMapIDListItor find;
	pthread_mutex_lock (&m_mutex);

	find = m_tKeyListMap.find(nKey);
	if(find != m_tKeyListMap.end())
	{
		tIDList = find->second;
	}

	pthread_mutex_unlock (&m_mutex);
	return 0;
}

TEMPLATE	UINT32		CManageBase<_T>::ClearKeyIDList()
{
	pthread_mutex_lock (&m_mutex);

	m_tKeyListMap.clear();

	pthread_mutex_unlock (&m_mutex);
	return 0;
}
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

TEMPLATE	UINT32		CManageBase<_T>::AddKeyIDMap(UINT32 nKey, UINT32 nID)
{
	TMapIDMapItor find;
	TMapID tIDMap;

	pthread_mutex_lock (&m_mutex);

	find = m_tKeyMapMap.find(nKey);
	if(find == m_tKeyMapMap.end())
	{
		m_tKeyMapMap[nKey] = tIDMap;
		find = m_tKeyMapMap.find(nKey);
	}

	find->second[nID] = 0;

	pthread_mutex_unlock (&m_mutex);
	return 0;
}

TEMPLATE	UINT32		CManageBase<_T>::DelKeyIDMap(UINT32 nKey)
{
	TMapIDMapItor find;
	pthread_mutex_lock (&m_mutex);

	find = m_tKeyMapMap.find(nKey);
	if(find != m_tKeyMapMap.end())
	{
		find->second.clear();
		m_tKeyMapMap.erase(nKey);
	}

	pthread_mutex_unlock (&m_mutex);

	return 0;
}


TEMPLATE	UINT32		CManageBase<_T>::DelKeyIDMap(UINT32 nKey, UINT32 nID)
{
	TMapIDMapItor find;
	pthread_mutex_lock (&m_mutex);

	find = m_tKeyMapMap.find(nKey);
	if(find != m_tKeyMapMap.end())
	{
		find->second.erase(nID);
	}

	pthread_mutex_unlock (&m_mutex);	
	return 0;
}

TEMPLATE	UINT32		CManageBase<_T>::GetKeyIDMap(UINT32 nKey, TMapID& tIDMap)
{
	UINT32 nRtn = 0;
	TMapIDMapItor find;
	pthread_mutex_lock (&m_mutex);

	find = m_tKeyMapMap.find(nKey);
	if(find != m_tKeyMapMap.end())
	{
		AppandMapToMap(find->second, tIDMap);
		nRtn = tIDMap.size();
	}

	pthread_mutex_unlock (&m_mutex);	
	return nRtn;
}

TEMPLATE	UINT32		CManageBase<_T>::GetKeyIDMap(UINT32 nKey, TMapID& tIDMap, UINT32 nLimited)
{
	UINT32 nRtn = 0;
	TMapIDMapItor find;
	TMapIDItor begin, end;

	pthread_mutex_lock (&m_mutex);
	find = m_tKeyMapMap.find(nKey);
	if(find != m_tKeyMapMap.end())
	{
		begin = find->second.begin();	end = find->second.end();
		for(begin; begin != end && nLimited--; begin++)
		{
			tIDMap[begin->first] = begin->second;
		}
		nRtn = tIDMap.size();
	}
	pthread_mutex_unlock (&m_mutex);	
	return nRtn;
}

TEMPLATE	UINT32		CManageBase<_T>::ClearKeyIDMap()
{
	pthread_mutex_lock (&m_mutex);
	m_tKeyMapMap.clear();
	pthread_mutex_unlock (&m_mutex);	
	return 0;
}
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////


TEMPLATE	UINT32		CManageBase<_T>::AddPosKeyIDMap(UINT32 nKey, UINT32 nID, UINT32 nPos)
{
	pthread_mutex_lock (&m_mutex);

	TMapIDMapMapItor find = m_tPosKeyMapMap.find(nPos);
	if(find == m_tPosKeyMapMap.end())
	{
		TMapIDMap tIDMapMap;
		m_tPosKeyMapMap[nPos] = tIDMapMap;

		find = m_tPosKeyMapMap.find(nPos);
	}

	TMapIDMapItor find_key = find->second.find(nKey);
	if(find_key == find->second.end())
	{		
		TMapID tIDMap;
		find->second[nKey] = tIDMap;
		find_key = find->second.find(nKey);
	}

	find_key->second[nID] = 0;
	pthread_mutex_unlock (&m_mutex);	
	return 0;
}

TEMPLATE	UINT32		CManageBase<_T>::DelPosKeyIDMap(UINT32 nKey, UINT32 nPos)
{
	pthread_mutex_lock (&m_mutex);

	TMapIDMapMapItor find = m_tPosKeyMapMap.find(nPos);
	if(find == m_tPosKeyMapMap.end())
	{
		pthread_mutex_unlock (&m_mutex);	
		return 0;
	}

	TMapIDMapItor find_key = find->second.find(nKey);
	if(find_key == find->second.end())
	{
		pthread_mutex_unlock (&m_mutex);	
		return 0;
	}

	find_key->second.clear();
	find->second.erase(nKey);
	pthread_mutex_unlock (&m_mutex);	
	return 0;
}


TEMPLATE	UINT32		CManageBase<_T>::DelPosKeyIDMap(UINT32 nKey, UINT32 nID, UINT32 nPos)
{
	pthread_mutex_lock (&m_mutex);
	TMapIDMapMapItor find = m_tPosKeyMapMap.find(nPos);
	if(find == m_tPosKeyMapMap.end())
	{
		pthread_mutex_unlock (&m_mutex);	
		return 0;
	}

	TMapIDMapItor find_key = find->second.find(nKey);
	if(find_key == find->second.end())
	{
		pthread_mutex_unlock (&m_mutex);	
		return 0;
	}

	find_key->second.erase(nID);
	pthread_mutex_unlock (&m_mutex);	
	return 0;
}

TEMPLATE	UINT32		CManageBase<_T>::GetPosKeyIDMap(UINT32 nKey, TMapID& tIDMap, UINT32 nPos)
{
	pthread_mutex_lock (&m_mutex);
	TMapIDMapMapItor find = m_tPosKeyMapMap.find(nPos);
	if(find == m_tPosKeyMapMap.end())
	{
		pthread_mutex_unlock (&m_mutex);	
		return 0;
	}

	TMapIDMapItor find_key = find->second.find(nKey);
	if(find_key == find->second.end())
	{
		pthread_mutex_unlock (&m_mutex);	
		return 0;
	}

	AppandMapToMap(find_key->second, tIDMap);
	
	pthread_mutex_unlock (&m_mutex);	

	return tIDMap.size();
}

TEMPLATE	UINT32		CManageBase<_T>::GetPosKeyIDMap(UINT32 nKey, TListID& tIDList, UINT32 nPos)
{
	pthread_mutex_lock (&m_mutex);
	TMapIDMapMapItor find = m_tPosKeyMapMap.find(nPos);
	if(find == m_tPosKeyMapMap.end())
	{
		pthread_mutex_unlock (&m_mutex);
		return 0;
	}

	TMapIDMapItor find_key = find->second.find(nKey);
	if(find_key == find->second.end())
	{
		pthread_mutex_unlock (&m_mutex);
		return 0;
	}

	ConvertMapToList(find_key->second, tIDList);
	pthread_mutex_unlock (&m_mutex);
	return tIDList.size();
}

TEMPLATE	UINT32		CManageBase<_T>::GetPosKeyIDMap(TMapIDMap& tKeyIDMap, UINT32 nPos)
{
	pthread_mutex_lock (&m_mutex);
	TMapIDMapMapItor find = m_tPosKeyMapMap.find(nPos);
	if(find == m_tPosKeyMapMap.end())
	{
		pthread_mutex_unlock (&m_mutex);
		return 0;
	}

	tKeyIDMap = find->second;
	pthread_mutex_unlock (&m_mutex);
	return tKeyIDMap.size();
}

TEMPLATE	UINT32		CManageBase<_T>::GetPosKeyIDMap(TMapID& tIDMap, UINT32 nPos)
{
	pthread_mutex_lock (&m_mutex);
	TMapIDMapMapItor find = m_tPosKeyMapMap.find(nPos);
	if(find == m_tPosKeyMapMap.end())
	{
		pthread_mutex_unlock (&m_mutex);
		return 0;
	}

	TMapIDMapItor begin, end;
	begin = find->second.begin();	end = find->second.end();
	for(begin; begin != end; begin++)
	{
		TMapIDItor begin_sub, end_sub;
		begin_sub = begin->second.begin();	end_sub = begin->second.end();
		for(begin_sub; begin_sub != end_sub; begin_sub++)
		{
			tIDMap[begin_sub->first] = 0;
		}
	}
	pthread_mutex_unlock (&m_mutex);
	return tIDMap.size();
}

TEMPLATE	UINT32		CManageBase<_T>::ClearPosKeyIDMap(UINT32 nPos)
{
	pthread_mutex_lock (&m_mutex);
	TMapIDMapMapItor find = m_tPosKeyMapMap.find(nPos);
	if(find == m_tPosKeyMapMap.end())
	{
		pthread_mutex_unlock (&m_mutex);
		return 0;
	}

	find->second.clear();
	pthread_mutex_unlock (&m_mutex);
	return 0;
}

TEMPLATE	UINT32		CManageBase<_T>::ClearPosKeyIDMap_ALL()
{
	pthread_mutex_lock (&m_mutex);
	m_tPosKeyMapMap.clear();
	pthread_mutex_unlock (&m_mutex);
	return 0;
}
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

TEMPLATE	UINT32		CManageBase<_T>::AddPosStrKeyID(String strKey, UINT32 nID, UINT32 nPos)
{
	pthread_mutex_lock (&m_mutex);
	TMapIDMapStrIDItor find = m_tPosStrKeyMap.find(nPos);
	if(find == m_tPosStrKeyMap.end())
	{
		TMapStrID tStrIDMap;
		m_tPosStrKeyMap[nPos] = tStrIDMap;

		find = m_tPosStrKeyMap.find(nPos);
	}
	
	find->second[strKey] = nID;
	pthread_mutex_unlock (&m_mutex);
	return 0;
}

TEMPLATE	UINT32		CManageBase<_T>::DelPosStrKeyID(String strKey, UINT32 nPos)
{
	pthread_mutex_lock (&m_mutex);
	TMapIDMapStrIDItor find = m_tPosStrKeyMap.find(nPos);
	if(find == m_tPosStrKeyMap.end())
	{
		pthread_mutex_unlock (&m_mutex);
		return 0;
	}

	find->second.erase(strKey);
	pthread_mutex_unlock (&m_mutex);
	return 0;
}

TEMPLATE	UINT32		CManageBase<_T>::FindPosStrKeyID(String strKey, UINT32 nPos)
{
	UINT32 nRtn = 0;
	pthread_mutex_lock (&m_mutex);

	TMapIDMapStrIDItor find = m_tPosStrKeyMap.find(nPos);
	if(find != m_tPosStrKeyMap.end())
	{
		TMapStrIDItor find_key = find->second.find(strKey);
		if(find_key != find->second.end())
		{
			nRtn = find_key->second;
		}	
	}
	pthread_mutex_unlock (&m_mutex);
	return nRtn;
}

TEMPLATE	_T*			CManageBase<_T>::FindPosStrKeyItem(String strKey, UINT32 nPos)
{
	UINT32 nID = FindPosStrKeyID(strKey, nPos);
	if(!nID)	return NULL;

	return FindItem(nID);
}

TEMPLATE	UINT32		CManageBase<_T>::GetPosStrKeyIDMap(TMapStrID& tKeyIDMap, UINT32 nPos)
{
	UINT32 nRtn = 0;
	pthread_mutex_lock (&m_mutex);

	TMapIDMapStrIDItor find = m_tPosStrKeyMap.find(nPos);
	if(find != m_tPosStrKeyMap.end())
	{
		tKeyIDMap = find->second;
	}

	pthread_mutex_unlock (&m_mutex);
	
	return tKeyIDMap.size();
}

TEMPLATE	UINT32		CManageBase<_T>::GetPosStrKeyList(TListStr& tStrKeyList, UINT32 nPos)
{
	pthread_mutex_lock (&m_mutex);

	TMapIDMapStrIDItor find = m_tPosStrKeyMap.find(nPos);
	if(find == m_tPosStrKeyMap.end())
	{
		pthread_mutex_unlock (&m_mutex);
		return 0;
	}

	TMapStrIDItor begin, end;
	begin = find->second.begin();	end = find->second.end();
	for(begin; begin != end; begin++)
	{
		tStrKeyList.push_back(begin->first);
	}
	pthread_mutex_unlock (&m_mutex);
	return tStrKeyList.size();
}

TEMPLATE	UINT32		CManageBase<_T>::ClearPosStrKeyID(UINT32 nPos)
{
	pthread_mutex_lock (&m_mutex);
	TMapIDMapStrIDItor find = m_tPosStrKeyMap.find(nPos);
	if(find != m_tPosStrKeyMap.end())
	{
		find->second.clear();
	}

	pthread_mutex_unlock (&m_mutex);	
	return 0;
}

TEMPLATE	UINT32		CManageBase<_T>::ClearPosStrKeyID_ALL()
{
	pthread_mutex_lock (&m_mutex);
	m_tPosStrKeyMap.clear();
	pthread_mutex_unlock (&m_mutex);	
	return 0;
}
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

TEMPLATE	UINT32		CManageBase<_T>::AddKeySubIDMap(UINT32 nKey, UINT32 nSubKey, UINT32 nID)
{
	pthread_mutex_lock (&m_mutex);

	TMapIDMapItor find = m_tKeySubIDMap.find(nKey);
	if(find == m_tKeySubIDMap.end())
	{
		TMapID tSubMap;
		m_tKeySubIDMap[nKey] = tSubMap;
		find = m_tKeySubIDMap.find(nKey);
	}

	find->second[nSubKey] = nID;
	pthread_mutex_unlock (&m_mutex);	
	return 0;
}

TEMPLATE	UINT32		CManageBase<_T>::DelKeySubIDMap(UINT32 nKey)
{
	pthread_mutex_lock (&m_mutex);

	TMapIDMapItor find = m_tKeySubIDMap.find(nKey);
	if(find != m_tKeySubIDMap.end())
	{
		find->second.clear();
		m_tKeySubIDMap.erase(nKey);
	}
	pthread_mutex_unlock (&m_mutex);	
	return 0;
}

TEMPLATE	UINT32		CManageBase<_T>::DelKeySubIDMap(UINT32 nKey, UINT32 nSubKey)
{
	pthread_mutex_lock (&m_mutex);
	TMapIDMapItor find = m_tKeySubIDMap.find(nKey);
	if(find != m_tKeySubIDMap.end())
	{
		find->second.erase(nSubKey);
	}
	pthread_mutex_unlock (&m_mutex);		
	return 0;
}

TEMPLATE	UINT32		CManageBase<_T>::GetKeySubIDMap(UINT32 nKey, TMapID& tIDMap)
{
	pthread_mutex_lock (&m_mutex);

	TMapIDMapItor find = m_tKeySubIDMap.find(nKey);
	if(find != m_tKeySubIDMap.end())
	{
		AppandMapToMap(find->second, tIDMap);
	}
	pthread_mutex_unlock (&m_mutex);		
	return 0;
}

TEMPLATE	UINT32		CManageBase<_T>::GetKeySubIDMapSKey(UINT32 nKey, TListID& tSKeyList)
{
	pthread_mutex_lock (&m_mutex);

	TMapIDMapItor find = m_tKeySubIDMap.find(nKey);
	if(find != m_tKeySubIDMap.end())
	{
		TMapIDItor begin, end;
		begin = find->second.begin();	end = find->second.end();
		for(begin; begin != end; begin++)
		{
			tSKeyList.push_back(begin->first);
		}
	}
	pthread_mutex_unlock (&m_mutex);		
	return 0;
}

TEMPLATE	UINT32		CManageBase<_T>::GetKeySubIDMapID(UINT32 nKey, TListID& tIDList)
{
	pthread_mutex_lock (&m_mutex);

	TMapIDMapItor find = m_tKeySubIDMap.find(nKey);
	if(find != m_tKeySubIDMap.end())
	{
		TMapIDItor begin, end;
		begin = find->second.begin();	end = find->second.end();
		for(begin; begin != end; begin++)
		{
			tIDList.push_back(begin->second);
		}
	}
	pthread_mutex_unlock (&m_mutex);		
	return 0;
}

TEMPLATE	UINT32		CManageBase<_T>::FindKeySubIDMapID(UINT32 nKey, UINT32 nSubKey)
{
	pthread_mutex_lock (&m_mutex);

	TMapIDMapItor find = m_tKeySubIDMap.find(nKey);
	if(find == m_tKeySubIDMap.end())
	{
		pthread_mutex_unlock (&m_mutex);	
		return 0;
	}

	TMapIDItor find_sub = find->second.find(nSubKey);
	if(find_sub == find->second.end())
	{
		pthread_mutex_unlock (&m_mutex);	
		return 0;
	}
	pthread_mutex_unlock (&m_mutex);	

	return find_sub->second;
}

TEMPLATE	_T*			CManageBase<_T>::FindKeySubIDMapItem(UINT32 nKey, UINT32 nSubKey)
{
	return FindItem(FindKeySubIDMapID(nKey, nSubKey));
}

TEMPLATE	UINT32		CManageBase<_T>::ClearKeySubIDMap()
{
	m_tKeySubIDMap.clear();
	return 0;
}
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////


TEMPLATE	UINT32		CManageBase<_T>::AddPosKeySubIDMap(UINT32 nKey, UINT32 nSubKey, UINT32 nID, UINT32 nPos)
{
	pthread_mutex_lock (&m_mutex);

	TMapIDMapMapItor find = m_tPosKeySubMapMap.find(nPos);
	if(find == m_tPosKeySubMapMap.end())
	{
		TMapIDMap tIDMapMap;
		m_tPosKeySubMapMap[nPos] = tIDMapMap;

		find = m_tPosKeySubMapMap.find(nPos);
	}

	TMapIDMapItor find_key = find->second.find(nKey);
	if(find_key == find->second.end())
	{		
		TMapID tIDMap;
		find->second[nKey] = tIDMap;
		find_key = find->second.find(nKey);
	}

	find_key->second[nSubKey] = nID;
	pthread_mutex_unlock (&m_mutex);	
	return 0;
}

TEMPLATE	UINT32		CManageBase<_T>::DelPosKeySubIDMap(UINT32 nKey, UINT32 nPos)
{
	pthread_mutex_lock (&m_mutex);

	TMapIDMapMapItor find = m_tPosKeySubMapMap.find(nPos);
	if(find == m_tPosKeySubMapMap.end())
	{
		pthread_mutex_unlock (&m_mutex);	
		return 0;
	}

	TMapIDMapItor find_key = find->second.find(nKey);
	if(find_key == find->second.end())
	{
		pthread_mutex_unlock (&m_mutex);	
		return 0;
	}

	find_key->second.clear();
	find->second.erase(nKey);
	pthread_mutex_unlock (&m_mutex);	
	return 0;
}


TEMPLATE	UINT32		CManageBase<_T>::DelPosKeySubIDMap(UINT32 nKey, UINT32 nSubKey, UINT32 nPos)
{
	pthread_mutex_lock (&m_mutex);
	TMapIDMapMapItor find = m_tPosKeySubMapMap.find(nPos);
	if(find == m_tPosKeySubMapMap.end())
	{
		pthread_mutex_unlock (&m_mutex);	
		return 0;
	}

	TMapIDMapItor find_key = find->second.find(nKey);
	if(find_key == find->second.end())
	{
		pthread_mutex_unlock (&m_mutex);	
		return 0;
	}

	find_key->second.erase(nSubKey);
	pthread_mutex_unlock (&m_mutex);	
	return 0;
}

TEMPLATE	UINT32		CManageBase<_T>::GetPosKeySubIDMap(UINT32 nKey, TMapID& tSubKeyMap, UINT32 nPos)
{
	pthread_mutex_lock (&m_mutex);
	TMapIDMapMapItor find = m_tPosKeySubMapMap.find(nPos);
	if(find == m_tPosKeySubMapMap.end())
	{
		pthread_mutex_unlock (&m_mutex);	
		return 0;
	}

	TMapIDMapItor find_key = find->second.find(nKey);
	if(find_key == find->second.end())
	{
		pthread_mutex_unlock (&m_mutex);	
		return 0;
	}

	AppandMapToMap(find_key->second, tSubKeyMap);

	pthread_mutex_unlock (&m_mutex);	

	return tSubKeyMap.size();
}

TEMPLATE	UINT32		CManageBase<_T>::GetPosKeySubIDMap(UINT32 nKey, TListID& tSubKeyList, UINT32 nPos)
{
	pthread_mutex_lock (&m_mutex);
	TMapIDMapMapItor find = m_tPosKeySubMapMap.find(nPos);
	if(find == m_tPosKeySubMapMap.end())
	{
		pthread_mutex_unlock (&m_mutex);
		return 0;
	}

	TMapIDMapItor find_key = find->second.find(nKey);
	if(find_key == find->second.end())
	{
		pthread_mutex_unlock (&m_mutex);
		return 0;
	}

	ConvertMapToList(find_key->second, tSubKeyList);
	pthread_mutex_unlock (&m_mutex);
	return tSubKeyList.size();
}

TEMPLATE	UINT32		CManageBase<_T>::GetPosKeySubIDMap(TMapIDMap& tKeyIDMap, UINT32 nPos)
{
	pthread_mutex_lock (&m_mutex);
	TMapIDMapMapItor find = m_tPosKeySubMapMap.find(nPos);
	if(find == m_tPosKeySubMapMap.end())
	{
		pthread_mutex_unlock (&m_mutex);
		return 0;
	}

	tKeyIDMap = find->second;
	pthread_mutex_unlock (&m_mutex);
	return tKeyIDMap.size();
}

TEMPLATE	UINT32		CManageBase<_T>::CountPosKeySubIDMap(UINT32 nKey, UINT32 nPos)
{
	UINT32 nRtn = 0;
	pthread_mutex_lock (&m_mutex);
	TMapIDMapMapItor find = m_tPosKeySubMapMap.find(nPos);
	if(find == m_tPosKeySubMapMap.end())
	{
		pthread_mutex_unlock (&m_mutex);	
		return 0;
	}

	TMapIDMapItor find_key = find->second.find(nKey);
	if(find_key == find->second.end())
	{
		pthread_mutex_unlock (&m_mutex);	
		return 0;
	}

	nRtn = find_key->second.size();

	pthread_mutex_unlock (&m_mutex);	

	return nRtn;
}

TEMPLATE	UINT32		CManageBase<_T>::ClearPosKeySubIDMap(UINT32 nPos)
{
	pthread_mutex_lock (&m_mutex);
	TMapIDMapMapItor find = m_tPosKeySubMapMap.find(nPos);
	if(find == m_tPosKeySubMapMap.end())
	{
		pthread_mutex_unlock (&m_mutex);
		return 0;
	}

	find->second.clear();
	pthread_mutex_unlock (&m_mutex);
	return 0;
}

TEMPLATE	UINT32		CManageBase<_T>::GetPosKeySubIDMap(UINT32 nKey, UINT32 nSubKey, UINT32 nPos)
{
	UINT32 nRtn = 0;
	pthread_mutex_lock (&m_mutex);
	TMapIDMapMapItor find = m_tPosKeySubMapMap.find(nPos);
	if(find == m_tPosKeySubMapMap.end())
	{
		pthread_mutex_unlock (&m_mutex);	
		return 0;
	}

	TMapIDMapItor find_key = find->second.find(nKey);
	if(find_key == find->second.end())
	{
		pthread_mutex_unlock (&m_mutex);	
		return 0;
	}

	TMapIDItor find_subkey = find_key->second.find(nSubKey);
	if(find_subkey == find_key->second.end())
	{
		pthread_mutex_unlock (&m_mutex);	
		return 0;
	}

	nRtn = find_subkey->second;

	pthread_mutex_unlock (&m_mutex);	

	return nRtn;
}
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////


TEMPLATE	UINT32		CManageBase<_T>::AddPosStrKeySubIDMap(String strKey, UINT32 nSubKey, UINT32 nID, UINT32 nPos)
{
	pthread_mutex_lock (&m_mutex);

	TMapIDMapStrMapIDItor find = m_tPosStrKeySubMapMap.find(nPos);
	if(find == m_tPosStrKeySubMapMap.end())
	{
		TMapStrMapID tIDMapMap;
		m_tPosStrKeySubMapMap[nPos] = tIDMapMap;

		find = m_tPosStrKeySubMapMap.find(nPos);
	}

	TMapStrMapIDItor find_key = find->second.find(strKey);
	if(find_key == find->second.end())
	{		
		TMapID tIDMap;
		find->second[strKey] = tIDMap;
		find_key = find->second.find(strKey);
	}

	find_key->second[nSubKey] = nID;
	pthread_mutex_unlock (&m_mutex);	
	return 0;
}

TEMPLATE	UINT32		CManageBase<_T>::DelPosStrKeySubIDMap(String strKey, UINT32 nPos)
{
	pthread_mutex_lock (&m_mutex);

	TMapIDMapStrMapIDItor find = m_tPosStrKeySubMapMap.find(nPos);
	if(find == m_tPosStrKeySubMapMap.end())
	{
		pthread_mutex_unlock (&m_mutex);	
		return 0;
	}

	TMapStrMapIDItor find_key = find->second.find(strKey);
	if(find_key == find->second.end())
	{
		pthread_mutex_unlock (&m_mutex);	
		return 0;
	}

	find_key->second.clear();
	find->second.erase(strKey);
	pthread_mutex_unlock (&m_mutex);	
	return 0;
}


TEMPLATE	UINT32		CManageBase<_T>::DelPosStrKeySubIDMap(String strKey, UINT32 nSubKey, UINT32 nPos)
{
	pthread_mutex_lock (&m_mutex);
	TMapIDMapStrMapIDItor find = m_tPosStrKeySubMapMap.find(nPos);
	if(find == m_tPosStrKeySubMapMap.end())
	{
		pthread_mutex_unlock (&m_mutex);	
		return 0;
	}

	TMapStrMapIDItor find_key = find->second.find(strKey);
	if(find_key == find->second.end())
	{
		pthread_mutex_unlock (&m_mutex);	
		return 0;
	}

	find_key->second.erase(nSubKey);
	pthread_mutex_unlock (&m_mutex);	
	return 0;
}

TEMPLATE	UINT32		CManageBase<_T>::GetPosStrKeySubIDMap(String strKey, TMapID& tSubKeyMap, UINT32 nPos)
{
	pthread_mutex_lock (&m_mutex);
	TMapIDMapStrMapIDItor find = m_tPosStrKeySubMapMap.find(nPos);
	if(find == m_tPosStrKeySubMapMap.end())
	{
		pthread_mutex_unlock (&m_mutex);	
		return 0;
	}

	TMapStrMapIDItor find_key = find->second.find(strKey);
	if(find_key == find->second.end())
	{
		pthread_mutex_unlock (&m_mutex);	
		return 0;
	}

	AppandMapToMap(find_key->second, tSubKeyMap);

	pthread_mutex_unlock (&m_mutex);	

	return tSubKeyMap.size();
}

TEMPLATE	UINT32		CManageBase<_T>::GetPosStrKeySubIDMap(String strKey, TListID& tSubKeyList, UINT32 nPos)
{
	pthread_mutex_lock (&m_mutex);
	TMapIDMapStrMapIDItor find = m_tPosStrKeySubMapMap.find(nPos);
	if(find == m_tPosStrKeySubMapMap.end())
	{
		pthread_mutex_unlock (&m_mutex);
		return 0;
	}

	TMapStrMapIDItor find_key = find->second.find(strKey);
	if(find_key == find->second.end())
	{
		pthread_mutex_unlock (&m_mutex);
		return 0;
	}

	ConvertMapToList(find_key->second, tSubKeyList);
	pthread_mutex_unlock (&m_mutex);
	return tSubKeyList.size();
}

TEMPLATE	UINT32		CManageBase<_T>::GetPosStrKeySubIDMap(TMapStrMapID& tKeyIDMap, UINT32 nPos)
{
	pthread_mutex_lock (&m_mutex);
	TMapIDMapStrMapIDItor find = m_tPosStrKeySubMapMap.find(nPos);
	if(find == m_tPosStrKeySubMapMap.end())
	{
		pthread_mutex_unlock (&m_mutex);
		return 0;
	}

	tKeyIDMap = find->second;
	pthread_mutex_unlock (&m_mutex);
	return tKeyIDMap.size();
}

TEMPLATE	UINT32		CManageBase<_T>::ClearPosStrKeySubIDMap(UINT32 nPos)
{
	pthread_mutex_lock (&m_mutex);
	TMapIDMapStrMapIDItor find = m_tPosStrKeySubMapMap.find(nPos);
	if(find == m_tPosStrKeySubMapMap.end())
	{
		pthread_mutex_unlock (&m_mutex);
		return 0;
	}

	find->second.clear();
	pthread_mutex_unlock (&m_mutex);
	return 0;
}

TEMPLATE	UINT32		CManageBase<_T>::GetPosStrKeySubIDMap(String strKey, UINT32 nSubKey, UINT32 nPos)
{
	UINT32 nRtn = 0;
	pthread_mutex_lock (&m_mutex);
	TMapIDMapStrMapIDItor find = m_tPosStrKeySubMapMap.find(nPos);
	if(find == m_tPosStrKeySubMapMap.end())
	{
		pthread_mutex_unlock (&m_mutex);	
		return 0;
	}

	TMapStrMapIDItor find_key = find->second.find(strKey);
	if(find_key == find->second.end())
	{
		pthread_mutex_unlock (&m_mutex);	
		return 0;
	}

	TMapIDItor find_subkey = find_key->second.find(nSubKey);
	if(find_subkey == find_key->second.end())
	{
		pthread_mutex_unlock (&m_mutex);	
		return 0;
	}

	nRtn = find_subkey->second;

	pthread_mutex_unlock (&m_mutex);	

	return nRtn;
}
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
TEMPLATE	UINT32		CManageBase<_T>::AddKeyList(UINT32 nKey)
{
	pthread_mutex_lock (&m_mutex);
	m_tKeyList.push_back(nKey);
	pthread_mutex_unlock (&m_mutex);
	return 0;
}
//-----------------------------------------------------------------------------

TEMPLATE	UINT32		CManageBase<_T>::DelKeyList(UINT32 nKey)
{
	pthread_mutex_lock (&m_mutex);
	TListIDItor begin, end;
	begin = m_tKeyList.begin();	end = m_tKeyList.end();
	for(begin; begin != end; begin++)
	{
		if(*begin == nKey)
		{
			m_tKeyList.erase(begin);
			break;
		}
	}
	pthread_mutex_unlock (&m_mutex);
	return 0;
}

//-----------------------------------------------------------------------------

TEMPLATE	UINT32		CManageBase<_T>::ClearKeyList()
{
	pthread_mutex_lock (&m_mutex);
	m_tKeyList.clear();
	pthread_mutex_unlock (&m_mutex);
	return 0;
}
//-----------------------------------------------------------------------------

TEMPLATE	UINT32		CManageBase<_T>::LastKeyList()
{
	UINT32 nKey = 0;
	pthread_mutex_lock (&m_mutex);

	TListIDRItor	begin = m_tKeyList.rbegin();
	TListIDRItor	end = m_tKeyList.rend();	

	if (begin != end)
	{
		nKey = *begin;
	}
	pthread_mutex_unlock (&m_mutex);
	return nKey;
}
//-----------------------------------------------------------------------------

TEMPLATE	UINT32		CManageBase<_T>::GetKeyListCount()
{
	UINT32 nCnt = 0;

	pthread_mutex_lock (&m_mutex);
	nCnt = m_tKeyList.size();
	pthread_mutex_unlock (&m_mutex);

	return nCnt;
}
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

TEMPLATE	INT32		CManageBase<_T>::InitGlobalIter()
{
	m_pMapItorBegin = m_tMap.begin();
	m_pMapItorEnd = m_tMap.end();
	m_nInitGlobalIter = 1;
	return 0;
}

TEMPLATE	INT32		CManageBase<_T>::FreeGlobalIter()
{
	m_nInitGlobalIter = 0;
	return 0;
}

TEMPLATE	_T*			CManageBase<_T>::NextGlobalIter()
{
	_T* pRtn = NULL;
	if(!m_nInitGlobalIter)
		return NULL;

	if(m_pMapItorBegin == m_pMapItorEnd)
	{
		FreeGlobalIter();
		return NULL;
	}
	pRtn = &(m_pMapItorBegin->second);
	m_pMapItorBegin++;
	return pRtn;
}

TEMPLATE	INT32		CManageBase<_T>::IsNextGlobalIter()
{
	if(!m_nInitGlobalIter)
		return 0;

	if(m_pMapItorBegin == m_pMapItorEnd)
	{
		FreeGlobalIter();
		return 0;
	}

	return 1;
}

TEMPLATE	INT32		CManageBase<_T>::InitGlobalRIter()
{
	m_pMapRItorBegin = m_tMap.rbegin();
	m_pMapRItorEnd = m_tMap.rend();
	m_nInitGlobalIter = 1;
	return 0;
}

TEMPLATE	INT32		CManageBase<_T>::FreeGlobalRIter()
{
	m_nInitGlobalIter = 0;
	return 0;
}

TEMPLATE	_T*			CManageBase<_T>::NextGlobalRIter()
{
	_T* pRtn = NULL;
	if(!m_nInitGlobalIter)
		return NULL;

	if(m_pMapRItorBegin == m_pMapRItorEnd)
	{
		FreeGlobalRIter();
		return NULL;
	}
	pRtn = &(m_pMapRItorBegin->second);
	m_pMapRItorBegin++;
	return pRtn;
}

TEMPLATE	INT32		CManageBase<_T>::IsNextGlobalRIter()
{
	if(!m_nInitGlobalIter)
		return 0;

	if(m_pMapRItorBegin == m_pMapRItorEnd)
	{
		FreeGlobalRIter();
		return 0;
	}

	return 1;
}

TEMPLATE	INT32		CManageBase<_T>::IsInitGlobalIter()
{
	return m_nInitGlobalIter;
}

///////////////////////////////////////////////////////////////////////////////

TEMPLATE	INT32		CManageBase<_T>::InitGlobalKeyIter()
{
	m_pKeyItorBegin = m_tKeyMap.begin();
	m_pKeyItorEnd = m_tKeyMap.end();
	m_nInitGlobalKeyIter = 1;
	return 0;
}

TEMPLATE	INT32		CManageBase<_T>::FreeGlobalKeyIter()
{
	m_nInitGlobalKeyIter = 0;
	return 0;
}

TEMPLATE	UINT32		CManageBase<_T>::NextGlobalKeyIter()
{
	UINT32 nRtn = 0;
	if(!m_nInitGlobalKeyIter)
		return NULL;

	if(m_pKeyItorBegin == m_pKeyItorEnd)
	{
		FreeGlobalKeyIter();
		return NULL;
	}
	nRtn = (m_pKeyItorBegin->first);
	m_pKeyItorBegin++;
	return nRtn;
}

TEMPLATE	INT32		CManageBase<_T>::IsNextGlobalKeyIter()
{
	if(!m_nInitGlobalKeyIter)
		return 0;

	if(m_pKeyItorBegin == m_pKeyItorEnd)
	{
		FreeGlobalKeyIter();
		return 0;
	}

	return 1;
}

TEMPLATE	INT32		CManageBase<_T>::IsInitGlobalKeyIter()
{
	return m_nInitGlobalKeyIter;
}

///////////////////////////////////////////////////////////////////////////////

TEMPLATE	INT32		CManageBase<_T>::InitGlobalKeyListIter(UINT64 nKey)
{
	MGR_BASE_GKEY tMBG;
	tMBG.tItorBegin	= m_tKeyList.begin();
	tMBG.tItorEnd	= m_tKeyList.end();
	tMBG.nInitMode	= 1;
	tMBG.nKey		= nKey;

	m_tMgrBaseGKeyMap[nKey] = tMBG;
	return 0;
}

TEMPLATE	INT32		CManageBase<_T>::FreeGlobalKeyListIter(UINT64 nKey)
{
	m_tMgrBaseGKeyMap.erase(nKey);
	return 0;
}

TEMPLATE	UINT32		CManageBase<_T>::NextGlobalKeyListIter(UINT64 nKey)
{
	TMapMgrBaseGKeyItor find = m_tMgrBaseGKeyMap.find(nKey);
	if(find == m_tMgrBaseGKeyMap.end())		return 0;

	if(!find->second.nInitMode)		return 0;

	if(find->second.tItorBegin == find->second.tItorEnd)
	{
		FreeGlobalKeyListIter(nKey);
		return 0;
	}
	UINT32 nRtn = *(find->second.tItorBegin);
	find->second.tItorBegin++;
	return nRtn;
}

TEMPLATE	INT32		CManageBase<_T>::IsNextGlobalKeyListIter(UINT64 nKey)
{
	TMapMgrBaseGKeyItor find = m_tMgrBaseGKeyMap.find(nKey);
	if(find == m_tMgrBaseGKeyMap.end())		return 0;

	if(!find->second.nInitMode)		return 0;

	if(find->second.tItorBegin == find->second.tItorEnd)
	{
		FreeGlobalKeyListIter(nKey);
		return 0;
	}

	return 1;
}

TEMPLATE	INT32		CManageBase<_T>::IsInitGlobalKeyListIter(UINT64 nKey)
{
	TMapMgrBaseGKeyItor find = m_tMgrBaseGKeyMap.find(nKey);
	if(find == m_tMgrBaseGKeyMap.end())		return 0;

	return find->second.nInitMode;
}

TEMPLATE	INT32		CManageBase<_T>::IsNextFreeGlobalKeyListIter(UINT64 nKey)
{
	INT32 nRtn = IsNextGlobalKeyListIter(nKey);
	if(!nRtn)	FreeGlobalKeyListIter(nKey);

	return nRtn;
}

///////////////////////////////////////////////////////////////////////////////

TEMPLATE	INT32		CManageBase<_T>::SetSyncDBMSType(UINT32 nType)
{
	m_nDBSyncChkType = nType;
	return m_nDBSyncChkType;
}
//-----------------------------------------------------------------------------

TEMPLATE	INT32		CManageBase<_T>::IsSyncDBMS()
{
	return (m_nDBSyncChkType & m_nDBSyncType);
}
//-----------------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////

TEMPLATE	INT32				CManageBase<_T>::AddTempID(UINT32 nID, UINT32 nValue)
{
	pthread_mutex_lock (&m_mutex);

	m_tTempIDMap[nID] = nValue;
	pthread_mutex_unlock (&m_mutex);
	return 0;
}
//-----------------------------------------------------------------------------

TEMPLATE	INT32				CManageBase<_T>::DelTempID(UINT32 nID)
{
	pthread_mutex_lock (&m_mutex);

	m_tTempIDMap.erase(nID);

	pthread_mutex_unlock (&m_mutex);
	return 0;
}
//-----------------------------------------------------------------------------

TEMPLATE	INT32				CManageBase<_T>::ClearTempID()
{
	pthread_mutex_lock (&m_mutex);

	m_tTempIDMap.clear();

	pthread_mutex_unlock (&m_mutex);
	return 0;
}
//-----------------------------------------------------------------------------

TEMPLATE	INT32				CManageBase<_T>::GetTempIDList(TListID& tIDList)
{
	UINT32 nRtn = 0;
	pthread_mutex_lock (&m_mutex);

	map <unsigned int, unsigned int>::iterator begin, end;
	begin = m_tTempIDMap.begin();	end = m_tTempIDMap.end();

	for (; begin != end; begin++)
	{			
		tIDList.push_back(begin->first);
	}
	nRtn = (UINT32)tIDList.size();

	pthread_mutex_unlock (&m_mutex);
	return nRtn;
}
//-----------------------------------------------------------------------------

TEMPLATE	INT32				CManageBase<_T>::SetTempIDList(TListID& tIDList)
{
	UINT32 nRtn = 0;
	pthread_mutex_lock (&m_mutex);
	m_tTempIDMap.clear();

	list <unsigned int>::iterator begin, end;
	begin = tIDList.begin();	end = tIDList.end();

	for (; begin != end; begin++)
	{			
		m_tTempIDMap[*begin] = 0;
	}
	nRtn = (UINT32)m_tTempIDMap.size();

	pthread_mutex_unlock (&m_mutex);
	return nRtn;
}
//-----------------------------------------------------------------------------

TEMPLATE	INT32				CManageBase<_T>::SetTempIDList(TMapID& tIDMap)
{
	UINT32 nRtn = 0;
	pthread_mutex_lock (&m_mutex);
	m_tTempIDMap.clear();

	map <unsigned int, unsigned int>::iterator begin, end;
	begin = tIDMap.begin();	end = tIDMap.end();

	for (; begin != end; begin++)
	{			
		m_tTempIDMap[begin->first] = 0;
	}
	nRtn = (UINT32)m_tTempIDMap.size();

	pthread_mutex_unlock (&m_mutex);
	return nRtn;
}
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////


TEMPLATE	void		CManageBase<_T>::PrintDbgInfo()
{
	return;
}
//-----------------------------------------------------------------------------

TEMPLATE String			CManageBase<_T>::GetHash()
{
	return m_strFullHash;
}
//-----------------------------------------------------------------------------

TEMPLATE _T&			CManageBase<_T>::GetData()
{
	_T* pData = NULL;
	_T tTemplate;
	DWORD dwThreadID = 0;
	pthread_mutex_lock (&m_mutex);
	dwThreadID = (DWORD)gettid();
	m_pDataMapItorFind = m_tDataMap.find(dwThreadID);
	if(m_pDataMapItorFind == m_tDataMap.end())
	{
		m_tDataMap[dwThreadID] = tTemplate;
		m_pDataMapItorFind = m_tDataMap.find(dwThreadID);
	}

	pData = &(m_pDataMapItorFind->second);
	pthread_mutex_unlock (&m_mutex);

	return (*pData);
}
//-----------------------------------------------------------------------------

TEMPLATE _T*			CManageBase<_T>::GetPData()
{
	_T* pData = NULL;
	_T tTemplate;
	DWORD dwThreadID = 0;
	pthread_mutex_lock (&m_mutex);

	dwThreadID = (DWORD)gettid();
	m_pDataMapItorFind = m_tDataMap.find(dwThreadID);
	if(m_pDataMapItorFind == m_tDataMap.end())
	{
		m_tDataMap[dwThreadID] = tTemplate;
		m_pDataMapItorFind = m_tDataMap.find(dwThreadID);
	}

	pData = &(m_pDataMapItorFind->second);
	pthread_mutex_unlock (&m_mutex);

	return pData;
}

#endif /*MANAGE_BASE_H__*/
//-----------------------------------------------------------------------------
