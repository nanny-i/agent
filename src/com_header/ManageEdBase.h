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

#pragma once

template <class _T>
class CManageEdBase
{
public:
	CManageEdBase(void);
	virtual ~CManageEdBase(void);

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

	virtual UINT32 Count();	
	virtual UINT32 GetItem(INT32 nID, TListID &tListID);
	virtual UINT32 GetItemPtrList(INT32 nID, list<_T*>	&tListPtr);
	virtual UINT32 GetItemPtrArray(INT32 nID, vector <_T*> &tVecPtr);
	virtual UINT32 GetItemIDList(TListID& tListID);	

public:
	virtual INT32		SetEditDataMap(UINT32 nID);
	virtual INT32		AddEditDataMap(_T& data);
	virtual INT32		EditEditDataMap(_T& data);
	virtual INT32		DelEditDataMap(UINT32 nEditID);
	virtual _T*			FindEditData(UINT32 nEditID);
	virtual INT32		GetEditDataIDList(TListID& tEIDList);


public:
	virtual	UINT32		AddKeyID(UINT32 nKey, UINT32 nID);
	virtual	UINT32		DelKeyID(UINT32 nKey);
	virtual	UINT32		FindKeyID(UINT32 nKey);
	virtual _T*			FindKeyItem(UINT32 nKey);
	virtual	UINT32		GetKeyIDList(TListID& tIDList);
	virtual	UINT32		ClearKeyID();
	virtual	UINT32		ConvertKeyID(TListID& tKeyList, TListID& tIDList);

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
	virtual	UINT32		GetKeyIDList(UINT32 nKey, TListID& tIDList);
	virtual	UINT32		ClearKeyIDList();

public:
	virtual	UINT32		AddKeyIDMap(UINT32 nKey, UINT32 nID);
	virtual	UINT32		DelKeyIDMap(UINT32 nKey);
	virtual	UINT32		DelKeyIDMap(UINT32 nKey, UINT32 nID);
	virtual	UINT32		GetKeyIDMap(UINT32 nKey, TMapID& tIDMap);
	virtual	UINT32		ClearKeyIDMap();

public:
	virtual	UINT32		AddPosKeyIDMap(UINT32 nKey, UINT32 nID, UINT32 nPos = 0);
	virtual	UINT32		DelPosKeyIDMap(UINT32 nKey, UINT32 nPos = 0);
	virtual	UINT32		DelPosKeyIDMap(UINT32 nKey, UINT32 nID, UINT32 nPos = 0);
	virtual	UINT32		GetPosKeyIDMap(UINT32 nKey, TMapID& tIDMap, UINT32 nPos = 0);
	virtual	UINT32		GetPosKeyIDMap(UINT32 nKey, TListID& tIDList, UINT32 nPos = 0);
	virtual	UINT32		GetPosKeyIDMap(TMapIDMap& tKeyIDMap, UINT32 nPos = 0);
	virtual	UINT32		ClearPosKeyIDMap(UINT32 nPos = 0);

public:
	virtual	UINT32		AddPosStrKeyID(String strKey, UINT32 nID, UINT32 nPos = 0);
	virtual	UINT32		DelPosStrKeyID(String strKey, UINT32 nPos = 0);
	virtual	UINT32		FindPosStrKeyID(String strKey, UINT32 nPos = 0);
	virtual	_T*			FindPosStrKeyItem(String strKey, UINT32 nPos = 0);
	virtual	UINT32		GetPosStrKeyIDMap(TMapStrID& tStrKeyIDMap, UINT32 nPos = 0);
	virtual	UINT32		GetPosStrKeyList(TListStr& tStrKeyList, UINT32 nPos = 0);	
	virtual	UINT32		ClearPosStrKeyID(UINT32 nPos = 0);

public:
	virtual	UINT32		AddKeySubIDMap(UINT32 nKey, UINT32 nSubKey, UINT32 nID);
	virtual	UINT32		DelKeySubIDMap(UINT32 nKey);
	virtual	UINT32		DelKeySubIDMap(UINT32 nKey, UINT32 nSubKey);
	virtual	UINT32		GetKeySubIDMap(UINT32 nKey, TMapID& tIDMap);
	virtual _T*			FindKeySubItem(UINT32 nKey, UINT32 nSubKey);
	virtual	UINT32		ClearKeySubIDMap();

public:
	virtual	UINT32		AddPosKeySubIDMap(UINT32 nKey, UINT32 nSubKey, UINT32 nID, UINT32 nPos = 0);
	virtual	UINT32		DelPosKeySubIDMap(UINT32 nKey, UINT32 nPos = 0);
	virtual	UINT32		DelPosKeySubIDMap(UINT32 nKey, UINT32 nSubKey, UINT32 nPos = 0);
	virtual	UINT32		GetPosKeySubIDMap(UINT32 nKey, TMapID& tSubKeyMap, UINT32 nPos = 0);
	virtual	UINT32		GetPosKeySubIDMap(UINT32 nKey, TListID& tSubKeyList, UINT32 nPos = 0);
	virtual	UINT32		GetPosKeySubIDMap(UINT32 nKey, UINT32 nSubKey, UINT32 nPos = 0);
	virtual	UINT32		GetPosKeySubIDMap(TMapIDMap& tKeyIDMap, UINT32 nPos = 0);
	virtual	UINT32		ClearPosKeySubIDMap(UINT32 nPos = 0);

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

protected :
	_T					m_tEditData;
	TMapID				m_tEditPkgIDMap;
	map <UINT32, _T>	m_tEditDataMap;
	UINT32				m_nEditID;

private:
	CMutexExt			m_tMutexSingle;

protected:

	typename map <UINT32, _T>::iterator	g_begin;
	typename map <UINT32, _T>::iterator	g_end;
	UINT32						m_nInitGlobalIter;

public:
	virtual INT32		InitGlobalIter();
	virtual	INT32		FreeGlobalIter();
	virtual _T*			NextGlobalIter();
	virtual INT32		IsNextGlobalIter();
	virtual INT32		IsInitGlobalIter();

public:
	UINT32		m_nRecvNum;
	UINT32		m_nTempClass;
};


#define	TEMPLATE template <class _T>

TEMPLATE	CManageEdBase<_T>::CManageEdBase(void)
{
	m_nTempClass		= 0;
	m_nRecvNum			= 0;
	m_nInitGlobalIter	= 0;
	m_nEditID	= 0;
}

TEMPLATE	CManageEdBase<_T>::~CManageEdBase(void)
{
}

TEMPLATE INT32		CManageEdBase<_T>::AddItem(UINT32 nID, _T& data)
{	
	m_tMutexSingle.Lock();

	m_tMap[nID] = data;

	m_tMutexSingle.UnLock();
	return 0;
}

TEMPLATE INT32		CManageEdBase<_T>::AddItem(_T& data)
{
	UINT32 nID = ((PDB_ID)&data)->nID;	
	return AddItem(nID, data);
}

TEMPLATE INT32		CManageEdBase<_T>::EditItem(UINT32 nID, _T& data)
{
	m_tMutexSingle.Lock();

	map <unsigned int, _T>::iterator	find = m_tMap.find(nID);
	if (find != m_tMap.end())
	{
		find->second = data;
	}

	m_tMutexSingle.UnLock();
	return 0;
}

TEMPLATE INT32		CManageEdBase<_T>::EditItem(_T& data)
{
	UINT32 nID = ((PDB_ID)&data)->nID;	
	return EditItem(nID, data);
}
	
TEMPLATE INT32		CManageEdBase<_T>::DeleteItem(UINT32 nID)
{
	INT32 nRtn = 0;
	m_tMutexSingle.Lock();

	map <unsigned int, _T>::iterator	find = m_tMap.find(nID);
	if (find != m_tMap.end())
	{
		m_tMap.erase(find);
	}
	else
	{
		nRtn = -1;
	}

	m_tMutexSingle.UnLock();
	return nRtn;
}

TEMPLATE INT32		CManageEdBase<_T>::ClearItem()
{
	m_tMutexSingle.Lock();
	m_tMap.clear();
	m_tMutexSingle.UnLock();
	return 0;
}

TEMPLATE _T*			CManageEdBase<_T>::FindItem(UINT32 nID)
{
	_T* pFind = NULL;

	m_tMutexSingle.Lock();
	map <unsigned int, _T>::iterator	find = m_tMap.find(nID);
	if (find != m_tMap.end())
	{
		pFind = &(find->second);
	}
	m_tMutexSingle.UnLock();
	return pFind;
}

TEMPLATE _T*			CManageEdBase<_T>::FirstItem()
{
	_T* pFind = NULL;

	m_tMutexSingle.Lock();
	map <unsigned int, _T>::iterator	begin = m_tMap.begin();
	if (begin != m_tMap.end())
	{
		pFind = &(begin->second);
	}
	m_tMutexSingle.UnLock();
	return pFind;
}

TEMPLATE _T*			CManageEdBase<_T>::LastItem()
{
	_T* pFind = NULL;
	m_tMutexSingle.Lock();

	map <unsigned int, _T>::iterator	begin = m_tMap.begin();
	map <unsigned int, _T>::iterator	end = m_tMap.end();	
	
	if (begin != m_tMap.end())
	{
		pFind = &((--end)->second);
	}
	m_tMutexSingle.UnLock();
	return pFind;
}

TEMPLATE UINT32 CManageEdBase<_T>::Count()
{
	UINT32 nRtn = 0;
	m_tMutexSingle.Lock();

	nRtn = (UINT32)m_tMap.size();

	m_tMutexSingle.UnLock();
	return nRtn;
}

TEMPLATE UINT32 CManageEdBase<_T>::GetItemPtrList(INT32 nID, list<_T*>	&tListPtr)
{
	UINT32 nRtn = 0;
	m_tMutexSingle.Lock();

	map <unsigned int, _T>::iterator begin, end;
	begin = m_tMap.begin();	end = m_tMap.end();

	if (nID != -1)
	{
		for (; begin != end; begin++)
		{
			if (begin->second.nID == nID)
			{		
				tListPtr.push_back(&(begin->second));
			}
		}
	}
	else
	{
		for (; begin != end; begin++)
		{
			tListPtr.push_back(&(begin->second));
		}
	}
	nRtn = (UINT32)tListPtr.size();

	m_tMutexSingle.UnLock();
	return nRtn;
}

TEMPLATE UINT32 CManageEdBase<_T>::GetItemPtrArray(INT32 nID, vector <_T*> &tVecPtr)
{
	UINT32 nRtn = 0;
	m_tMutexSingle.Lock();

	map <unsigned int, _T>::iterator begin, end;
	begin = m_tMap.begin();	end = m_tMap.end();

	if (nID != -1)
	{
		for (; begin != end; begin++)
		{
			if (begin->second.nID == nID)
			{		
				tVecPtr.push_back(&(begin->second));
			}
		}
	}
	else
	{
		for (; begin != end; begin++)
		{
			tVecPtr.push_back(&(begin->second));
		}
	}
	nRtn = (UINT32)tVecPtr.size();

	m_tMutexSingle.UnLock();
	return nRtn;
}

TEMPLATE UINT32 CManageEdBase<_T>::GetItem(INT32 nID, TListID &tListID)
{
	UINT32 nRtn = 0;
	m_tMutexSingle.Lock();

	map <unsigned int, _T>::iterator begin, end;
	begin = m_tMap.begin();	end = m_tMap.end();

	if (nID != -1)
	{
		for (; begin != end; begin++)
		{
			if (begin->second.nID == nID)
			{		
				tListID.push_back(begin->second.nID);
			}			
		}
	}
	else
	{
		for (; begin != end; begin++)
		{
			tListID.push_back(begin->second.nID);
		}
	}
	nRtn = (UINT32)tListID.size();

	m_tMutexSingle.UnLock();
	return nRtn;
}

TEMPLATE	UINT32	CManageEdBase<_T>::GetItemIDList(TListID& tListID)
{
	UINT32 nRtn = 0;
	m_tMutexSingle.Lock();

	map <unsigned int, _T>::iterator begin, end;
	begin = m_tMap.begin();	end = m_tMap.end();
	
	for (; begin != end; begin++)
	{			
		tListID.push_back(begin->second.nID);
	}
	nRtn = (UINT32)tListID.size();

	m_tMutexSingle.UnLock();
	return nRtn;
}
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

TEMPLATE	UINT32		CManageEdBase<_T>::AddKeyID(UINT32 nKey, UINT32 nID)
{
	m_tMutexSingle.Lock();
	m_tKeyMap[nKey] = nID;
	m_tMutexSingle.UnLock();
	return 0;
}

TEMPLATE	UINT32		CManageEdBase<_T>::DelKeyID(UINT32 nKey)
{
	m_tMutexSingle.Lock();
	m_tKeyMap.erase(nKey);
	m_tMutexSingle.UnLock();
	return 0;
}

TEMPLATE	UINT32		CManageEdBase<_T>::FindKeyID(UINT32 nKey)
{
	UINT32 nRtn = 0;

	m_tMutexSingle.Lock();
	TMapIDItor find = m_tKeyMap.find(nKey);
	if(find != m_tKeyMap.end())	nRtn = find->second;
	m_tMutexSingle.UnLock();

	return nRtn;
}

TEMPLATE _T*			CManageEdBase<_T>::FindKeyItem(UINT32 nKey)
{
	UINT32 nID = FindKeyID(nKey);
	return FindItem(nID);
}

TEMPLATE	UINT32		CManageEdBase<_T>::GetKeyIDList(TListID& tIDList)
{
	m_tMutexSingle.Lock();
	TMapIDItor begin, end;
	begin = m_tKeyMap.begin();	end = m_tKeyMap.end();
	for(begin; begin != end; begin++)
	{
		tIDList.push_back(begin->first);
	}
	m_tMutexSingle.UnLock();

	return tIDList.size();
}

TEMPLATE	UINT32		CManageEdBase<_T>::ClearKeyID()
{
	m_tMutexSingle.Lock();
	m_tKeyMap.clear();
	m_tMutexSingle.UnLock();
	return 0;
}

TEMPLATE	UINT32		CManageEdBase<_T>::ConvertKeyID(TListID& tKeyList, TListID& tIDList)
{
	m_tMutexSingle.Lock();

	TListIDItor begin, end;
	begin = tKeyList.begin();	end = tKeyList.end();
	for(begin; begin != end; begin++)
	{
		TMapIDItor find = m_tKeyMap.find(*begin);
		if(find == m_tKeyMap.end())		continue;

		tIDList.push_back(find->second);
	}
	m_tMutexSingle.UnLock();
	return 0;
}
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

TEMPLATE	UINT32		CManageEdBase<_T>::AddStrKeyID(String strKey, UINT32 nID)
{
	m_tMutexSingle.Lock();
	m_tStrKeyMap[strKey] = nID;
	m_tMutexSingle.UnLock();
	return 0;
}

TEMPLATE	UINT32		CManageEdBase<_T>::DelStrKeyID(String strKey)
{
	m_tMutexSingle.Lock();
	m_tStrKeyMap.erase(strKey);
	m_tMutexSingle.UnLock();
	return 0;
}

TEMPLATE	UINT32		CManageEdBase<_T>::FindStrKeyID(String strKey)
{
	UINT32 nRtn = 0;

	m_tMutexSingle.Lock();
	TMapStrIDItor find = m_tStrKeyMap.find(strKey);
	if(find != m_tStrKeyMap.end())	nRtn = find->second;
	m_tMutexSingle.UnLock();
	return nRtn;
}

TEMPLATE _T*			CManageEdBase<_T>::FindStrKeyItem(String strKey)
{
	UINT32 nID = FindStrKeyID(strKey);
	return FindItem(nID);
}

TEMPLATE	UINT32		CManageEdBase<_T>::GetStrKeyList(TListStr& tKeyList)
{
	UINT32 nRtn = 0;
	m_tMutexSingle.Lock();

	TMapStrIDItor begin, end;
	begin = m_tStrKeyMap.begin();	end = m_tStrKeyMap.end();
	for(begin; begin != end; begin++)
	{
		tKeyList.push_back(begin->first);
	}

	nRtn = tKeyList.size();
	m_tMutexSingle.UnLock();

	return nRtn;
}

TEMPLATE	UINT32		CManageEdBase<_T>::ClearStrKeyID()
{
	m_tMutexSingle.Lock();
	m_tStrKeyMap.clear();
	m_tMutexSingle.UnLock();
	return 0;
}

TEMPLATE	UINT32		CManageEdBase<_T>::ConvertStrKeyID(TListStr& tStrKeyList, TListID& tIDList)
{
	m_tMutexSingle.Lock();
	TListStrItor begin, end;
	begin = tStrKeyList.begin();	end = tStrKeyList.end();
	for(begin; begin != end; begin++)
	{
		TMapStrIDItor find = m_tStrKeyMap.find(*begin);
		if(find == m_tStrKeyMap.end())		continue;

		tIDList.push_back(find->second);
	}
	m_tMutexSingle.UnLock();
	return 0;
}
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

TEMPLATE	UINT32		CManageEdBase<_T>::AddKeyIDList(UINT32 nKey, UINT32 nID)
{
	m_tMutexSingle.Lock();
	TMapIDListItor find = m_tKeyListMap.find(nKey);
	if(find == m_tKeyListMap.end())
	{
		TListID tIDList;
		m_tKeyListMap[nKey] = tIDList;
		find = m_tKeyListMap.find(nKey);
	}

	find->second.push_back(nID);
	m_tMutexSingle.UnLock();
	return 0;
}

TEMPLATE	UINT32		CManageEdBase<_T>::DelKeyIDList(UINT32 nKey)
{
	m_tMutexSingle.Lock();
	TMapIDListItor find = m_tKeyListMap.find(nKey);
	if(find != m_tKeyListMap.end())
	{
		find->second.clear();
		m_tKeyListMap.erase(nKey);
	}	
	m_tMutexSingle.UnLock();
	return 0;
}

TEMPLATE	UINT32		CManageEdBase<_T>::DelKeyIDList(UINT32 nKey, UINT32 nID)
{
	m_tMutexSingle.Lock();
	TMapIDListItor find = m_tKeyListMap.find(nKey);
	if(find == m_tKeyListMap.end())
	{
		m_tMutexSingle.UnLock();
		return 0;
	}

	RemoveListID(find->second, nID);

	if(find->second.size() == 0)
	{
		m_tKeyListMap.erase(nKey);
	}
	m_tMutexSingle.UnLock();
	return 0;
}

TEMPLATE	UINT32		CManageEdBase<_T>::GetKeyIDList(UINT32 nKey, TListID& tIDList)
{
	m_tMutexSingle.Lock();

	TMapIDListItor find = m_tKeyListMap.find(nKey);
	if(find != m_tKeyListMap.end())
	{
		tIDList = find->second;
	}

	m_tMutexSingle.UnLock();
	return 0;
}

TEMPLATE	UINT32		CManageEdBase<_T>::ClearKeyIDList()
{
	m_tMutexSingle.Lock();

	m_tKeyListMap.clear();

	m_tMutexSingle.UnLock();
	return 0;
}
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

TEMPLATE	UINT32		CManageEdBase<_T>::AddKeyIDMap(UINT32 nKey, UINT32 nID)
{
	m_tMutexSingle.Lock();

	TMapIDMapItor find = m_tKeyMapMap.find(nKey);
	if(find == m_tKeyMapMap.end())
	{
		TMapID tIDMap;
		m_tKeyMapMap[nKey] = tIDMap;
		find = m_tKeyMapMap.find(nKey);
	}

	find->second[nID] = 0;

	m_tMutexSingle.UnLock();
	return 0;
}

TEMPLATE	UINT32		CManageEdBase<_T>::DelKeyIDMap(UINT32 nKey)
{
	m_tMutexSingle.Lock();

	TMapIDMapItor find = m_tKeyMapMap.find(nKey);
	if(find != m_tKeyMapMap.end())
	{
		find->second.clear();
		m_tKeyMapMap.erase(nKey);
	}

	m_tMutexSingle.UnLock();

	return 0;
}


TEMPLATE	UINT32		CManageEdBase<_T>::DelKeyIDMap(UINT32 nKey, UINT32 nID)
{
	m_tMutexSingle.Lock();

	TMapIDMapItor find = m_tKeyMapMap.find(nKey);
	if(find != m_tKeyMapMap.end())
	{
		find->second.erase(nID);
	}

	m_tMutexSingle.UnLock();	
	return 0;
}

TEMPLATE	UINT32		CManageEdBase<_T>::GetKeyIDMap(UINT32 nKey, TMapID& tIDMap)
{
	UINT32 nRtn = 0;
	m_tMutexSingle.Lock();

	TMapIDMapItor find = m_tKeyMapMap.find(nKey);
	if(find != m_tKeyMapMap.end())
	{
		AppandMapToMap(find->second, tIDMap);
		nRtn = tIDMap.size();
	}

	m_tMutexSingle.UnLock();	
	return nRtn;
}

TEMPLATE	UINT32		CManageEdBase<_T>::ClearKeyIDMap()
{
	m_tMutexSingle.Lock();
	m_tKeyMapMap.clear();
	m_tMutexSingle.UnLock();	
	return 0;
}
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////


TEMPLATE	UINT32		CManageEdBase<_T>::AddPosKeyIDMap(UINT32 nKey, UINT32 nID, UINT32 nPos)
{
	m_tMutexSingle.Lock();

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
	m_tMutexSingle.UnLock();	
	return 0;
}

TEMPLATE	UINT32		CManageEdBase<_T>::DelPosKeyIDMap(UINT32 nKey, UINT32 nPos)
{
	m_tMutexSingle.Lock();

	TMapIDMapMapItor find = m_tPosKeyMapMap.find(nPos);
	if(find == m_tPosKeyMapMap.end())
	{
		m_tMutexSingle.UnLock();	
		return 0;
	}

	TMapIDMapItor find_key = find->second.find(nKey);
	if(find_key == find->second.end())
	{
		m_tMutexSingle.UnLock();	
		return 0;
	}

	find_key->second.clear();
	find->second.erase(nKey);
	m_tMutexSingle.UnLock();	
	return 0;
}


TEMPLATE	UINT32		CManageEdBase<_T>::DelPosKeyIDMap(UINT32 nKey, UINT32 nID, UINT32 nPos)
{
	m_tMutexSingle.Lock();
	TMapIDMapMapItor find = m_tPosKeyMapMap.find(nPos);
	if(find == m_tPosKeyMapMap.end())
	{
		m_tMutexSingle.UnLock();	
		return 0;
	}

	TMapIDMapItor find_key = find->second.find(nKey);
	if(find_key == find->second.end())
	{
		m_tMutexSingle.UnLock();	
		return 0;
	}

	find_key->second.erase(nID);
	m_tMutexSingle.UnLock();	
	return 0;
}

TEMPLATE	UINT32		CManageEdBase<_T>::GetPosKeyIDMap(UINT32 nKey, TMapID& tIDMap, UINT32 nPos)
{
	m_tMutexSingle.Lock();
	TMapIDMapMapItor find = m_tPosKeyMapMap.find(nPos);
	if(find == m_tPosKeyMapMap.end())
	{
		m_tMutexSingle.UnLock();	
		return 0;
	}

	TMapIDMapItor find_key = find->second.find(nKey);
	if(find_key == find->second.end())
	{
		m_tMutexSingle.UnLock();	
		return 0;
	}

	AppandMapToMap(find_key->second, tIDMap);
	
	m_tMutexSingle.UnLock();	

	return tIDMap.size();
}

TEMPLATE	UINT32		CManageEdBase<_T>::GetPosKeyIDMap(UINT32 nKey, TListID& tIDList, UINT32 nPos)
{
	m_tMutexSingle.Lock();
	TMapIDMapMapItor find = m_tPosKeyMapMap.find(nPos);
	if(find == m_tPosKeyMapMap.end())
	{
		m_tMutexSingle.UnLock();
		return 0;
	}

	TMapIDMapItor find_key = find->second.find(nKey);
	if(find_key == find->second.end())
	{
		m_tMutexSingle.UnLock();
		return 0;
	}

	ConvertMapToList(find_key->second, tIDList);
	m_tMutexSingle.UnLock();
	return tIDList.size();
}

TEMPLATE	UINT32		CManageEdBase<_T>::GetPosKeyIDMap(TMapIDMap& tKeyIDMap, UINT32 nPos)
{
	m_tMutexSingle.Lock();
	TMapIDMapMapItor find = m_tPosKeyMapMap.find(nPos);
	if(find == m_tPosKeyMapMap.end())
	{
		m_tMutexSingle.UnLock();
		return 0;
	}

	tKeyIDMap = find->second;
	m_tMutexSingle.UnLock();
	return tKeyIDMap.size();
}

TEMPLATE	UINT32		CManageEdBase<_T>::ClearPosKeyIDMap(UINT32 nPos)
{
	m_tMutexSingle.Lock();
	TMapIDMapMapItor find = m_tPosKeyMapMap.find(nPos);
	if(find == m_tPosKeyMapMap.end())
	{
		m_tMutexSingle.UnLock();
		return 0;
	}

	find->second.clear();
	m_tMutexSingle.UnLock();
	return 0;
}
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

TEMPLATE	UINT32		CManageEdBase<_T>::AddPosStrKeyID(String strKey, UINT32 nID, UINT32 nPos)
{
	m_tMutexSingle.Lock();
	TMapIDMapStrIDItor find = m_tPosStrKeyMap.find(nPos);
	if(find == m_tPosStrKeyMap.end())
	{
		TMapStrID tStrIDMap;
		m_tPosStrKeyMap[nPos] = tStrIDMap;

		find = m_tPosStrKeyMap.find(nPos);
	}
	
	find->second[strKey] = nID;
	m_tMutexSingle.UnLock();
	return 0;
}

TEMPLATE	UINT32		CManageEdBase<_T>::DelPosStrKeyID(String strKey, UINT32 nPos)
{
	m_tMutexSingle.Lock();
	TMapIDMapStrIDItor find = m_tPosStrKeyMap.find(nPos);
	if(find == m_tPosStrKeyMap.end())
	{
		m_tMutexSingle.UnLock();
		return 0;
	}

	find->second.erase(strKey);
	m_tMutexSingle.UnLock();
	return 0;
}

TEMPLATE	UINT32		CManageEdBase<_T>::FindPosStrKeyID(String strKey, UINT32 nPos)
{
	UINT32 nRtn = 0;
	m_tMutexSingle.Lock();

	TMapIDMapStrIDItor find = m_tPosStrKeyMap.find(nPos);
	if(find != m_tPosStrKeyMap.end())
	{
		TMapStrIDItor find_key = find->second.find(strKey);
		if(find_key != find->second.end())
		{
			nRtn = find_key->second;
		}	
	}
	m_tMutexSingle.UnLock();
	return nRtn;
}

TEMPLATE	_T*			CManageEdBase<_T>::FindPosStrKeyItem(String strKey, UINT32 nPos)
{
	UINT32 nID = FindPosStrKeyID(strKey, nPos);
	if(!nID)	return NULL;

	return FindItem(nID);
}

TEMPLATE	UINT32		CManageEdBase<_T>::GetPosStrKeyIDMap(TMapStrID& tKeyIDMap, UINT32 nPos)
{
	UINT32 nRtn = 0;
	m_tMutexSingle.Lock();

	TMapIDMapStrIDItor find = m_tPosStrKeyMap.find(nPos);
	if(find != m_tPosStrKeyMap.end())
	{
		tKeyIDMap = find->second;
	}

	m_tMutexSingle.UnLock();
	
	return tKeyIDMap.size();
}

TEMPLATE	UINT32		CManageEdBase<_T>::GetPosStrKeyList(TListStr& tStrKeyList, UINT32 nPos)
{
	m_tMutexSingle.Lock();

	TMapIDMapStrIDItor find = m_tPosStrKeyMap.find(nPos);
	if(find == m_tPosStrKeyMap.end())
	{
		m_tMutexSingle.UnLock();
		return 0;
	}

	TMapStrIDItor begin, end;
	begin = find->second.begin();	end = find->second.end();
	for(begin; begin != end; begin++)
	{
		tStrKeyList.push_back(begin->first);
	}
	m_tMutexSingle.UnLock();
	return tStrKeyList.size();
}

TEMPLATE	UINT32		CManageEdBase<_T>::ClearPosStrKeyID(UINT32 nPos)
{
	m_tMutexSingle.Lock();
	TMapIDMapStrIDItor find = m_tPosStrKeyMap.find(nPos);
	if(find != m_tPosStrKeyMap.end())
	{
		find->second.clear();
	}

	m_tMutexSingle.UnLock();	
	return 0;
}
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

TEMPLATE	UINT32		CManageEdBase<_T>::AddKeySubIDMap(UINT32 nKey, UINT32 nSubKey, UINT32 nID)
{
	m_tMutexSingle.Lock();

	TMapIDMapItor find = m_tKeySubIDMap.find(nKey);
	if(find == m_tKeySubIDMap.end())
	{
		TMapID tSubMap;
		m_tKeySubIDMap[nKey] = tSubMap;
		find = m_tKeySubIDMap.find(nKey);
	}

	find->second[nSubKey] = nID;
	m_tMutexSingle.UnLock();	
	return 0;
}

TEMPLATE	UINT32		CManageEdBase<_T>::DelKeySubIDMap(UINT32 nKey)
{
	m_tMutexSingle.Lock();

	TMapIDMapItor find = m_tKeySubIDMap.find(nKey);
	if(find != m_tKeySubIDMap.end())
	{
		find->second.clear();
		m_tKeySubIDMap.erase(nKey);
	}
	m_tMutexSingle.UnLock();	
	return 0;
}

TEMPLATE	UINT32		CManageEdBase<_T>::DelKeySubIDMap(UINT32 nKey, UINT32 nSubKey)
{
	m_tMutexSingle.Lock();
	TMapIDMapItor find = m_tKeySubIDMap.find(nKey);
	if(find != m_tKeySubIDMap.end())
	{
		find->second.erase(nSubKey);
	}
	m_tMutexSingle.UnLock();		
	return 0;
}

TEMPLATE	UINT32		CManageEdBase<_T>::GetKeySubIDMap(UINT32 nKey, TMapID& tIDMap)
{
	m_tMutexSingle.Lock();

	TMapIDMapItor find = m_tKeySubIDMap.find(nKey);
	if(find != m_tKeySubIDMap.end())
	{
		AppandMapToMap(find->second, tIDMap);
	}
	m_tMutexSingle.UnLock();		
	return 0;
}

TEMPLATE	_T*			CManageEdBase<_T>::FindKeySubItem(UINT32 nKey, UINT32 nSubKey)
{
	m_tMutexSingle.Lock();

	TMapIDMapItor find = m_tKeySubIDMap.find(nKey);
	if(find == m_tKeySubIDMap.end())
	{
		m_tMutexSingle.UnLock();	
		return NULL;
	}

	TMapIDItor find_sub = find->second.find(nSubKey);
	if(find_sub == find->second.end())
	{
		m_tMutexSingle.UnLock();	
		return NULL;
	}
	m_tMutexSingle.UnLock();	

	return FindItem(find_sub->second);
}

TEMPLATE	UINT32		CManageEdBase<_T>::ClearKeySubIDMap()
{
	m_tKeySubIDMap.clear();
	return 0;
}
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////


TEMPLATE	UINT32		CManageEdBase<_T>::AddPosKeySubIDMap(UINT32 nKey, UINT32 nSubKey, UINT32 nID, UINT32 nPos)
{
	m_tMutexSingle.Lock();

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
	m_tMutexSingle.UnLock();	
	return 0;
}

TEMPLATE	UINT32		CManageEdBase<_T>::DelPosKeySubIDMap(UINT32 nKey, UINT32 nPos)
{
	m_tMutexSingle.Lock();

	TMapIDMapMapItor find = m_tPosKeySubMapMap.find(nPos);
	if(find == m_tPosKeySubMapMap.end())
	{
		m_tMutexSingle.UnLock();	
		return 0;
	}

	TMapIDMapItor find_key = find->second.find(nKey);
	if(find_key == find->second.end())
	{
		m_tMutexSingle.UnLock();	
		return 0;
	}

	find_key->second.clear();
	find->second.erase(nKey);
	m_tMutexSingle.UnLock();	
	return 0;
}


TEMPLATE	UINT32		CManageEdBase<_T>::DelPosKeySubIDMap(UINT32 nKey, UINT32 nSubKey, UINT32 nPos)
{
	m_tMutexSingle.Lock();
	TMapIDMapMapItor find = m_tPosKeySubMapMap.find(nPos);
	if(find == m_tPosKeySubMapMap.end())
	{
		m_tMutexSingle.UnLock();	
		return 0;
	}

	TMapIDMapItor find_key = find->second.find(nKey);
	if(find_key == find->second.end())
	{
		m_tMutexSingle.UnLock();	
		return 0;
	}

	find_key->second.erase(nSubKey);
	m_tMutexSingle.UnLock();	
	return 0;
}

TEMPLATE	UINT32		CManageEdBase<_T>::GetPosKeySubIDMap(UINT32 nKey, TMapID& tSubKeyMap, UINT32 nPos)
{
	m_tMutexSingle.Lock();
	TMapIDMapMapItor find = m_tPosKeySubMapMap.find(nPos);
	if(find == m_tPosKeySubMapMap.end())
	{
		m_tMutexSingle.UnLock();	
		return 0;
	}

	TMapIDMapItor find_key = find->second.find(nKey);
	if(find_key == find->second.end())
	{
		m_tMutexSingle.UnLock();	
		return 0;
	}

	AppandMapToMap(find_key->second, tSubKeyMap);

	m_tMutexSingle.UnLock();	

	return tSubKeyMap.size();
}

TEMPLATE	UINT32		CManageEdBase<_T>::GetPosKeySubIDMap(UINT32 nKey, TListID& tSubKeyList, UINT32 nPos)
{
	m_tMutexSingle.Lock();
	TMapIDMapMapItor find = m_tPosKeySubMapMap.find(nPos);
	if(find == m_tPosKeySubMapMap.end())
	{
		m_tMutexSingle.UnLock();
		return 0;
	}

	TMapIDMapItor find_key = find->second.find(nKey);
	if(find_key == find->second.end())
	{
		m_tMutexSingle.UnLock();
		return 0;
	}

	ConvertMapToList(find_key->second, tSubKeyList);
	m_tMutexSingle.UnLock();
	return tSubKeyList.size();
}

TEMPLATE	UINT32		CManageEdBase<_T>::GetPosKeySubIDMap(TMapIDMap& tKeyIDMap, UINT32 nPos)
{
	m_tMutexSingle.Lock();
	TMapIDMapMapItor find = m_tPosKeySubMapMap.find(nPos);
	if(find == m_tPosKeySubMapMap.end())
	{
		m_tMutexSingle.UnLock();
		return 0;
	}

	tKeyIDMap = find->second;
	m_tMutexSingle.UnLock();
	return tKeyIDMap.size();
}

TEMPLATE	UINT32		CManageEdBase<_T>::ClearPosKeySubIDMap(UINT32 nPos)
{
	m_tMutexSingle.Lock();
	TMapIDMapMapItor find = m_tPosKeySubMapMap.find(nPos);
	if(find == m_tPosKeySubMapMap.end())
	{
		m_tMutexSingle.UnLock();
		return 0;
	}

	find->second.clear();
	m_tMutexSingle.UnLock();
	return 0;
}

TEMPLATE	UINT32		CManageEdBase<_T>::GetPosKeySubIDMap(UINT32 nKey, UINT32 nSubKey, UINT32 nPos)
{
	UINT32 nRtn = 0;
	m_tMutexSingle.Lock();
	TMapIDMapMapItor find = m_tPosKeySubMapMap.find(nPos);
	if(find == m_tPosKeySubMapMap.end())
	{
		m_tMutexSingle.UnLock();	
		return 0;
	}

	TMapIDMapItor find_key = find->second.find(nKey);
	if(find_key == find->second.end())
	{
		m_tMutexSingle.UnLock();	
		return 0;
	}

	TMapIDItor find_subkey = find_key->second.find(nSubKey);
	if(find_subkey == find_key->second.end())
	{
		m_tMutexSingle.UnLock();	
		return 0;
	}

	nRtn = find_subkey->second;

	m_tMutexSingle.UnLock();	

	return nRtn;
}
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

TEMPLATE	INT32		CManageEdBase<_T>::SetEditDataMap(UINT32 nID)
{
	m_tEditDataMap.clear();
	m_nEditID = 0;

	return m_tEditDataMap.size();
}

TEMPLATE	INT32		CManageEdBase<_T>::AddEditDataMap(_T& data)
{
	data.nEditID = ++m_nEditID;
	m_tEditDataMap[data.nEditID] = data;
	return m_tEditDataMap.size();
}

TEMPLATE	INT32		CManageEdBase<_T>::EditEditDataMap(_T& data)
{
	m_tEditDataMap[data.nEditID] = data;
	return m_tEditDataMap.size();	
}

TEMPLATE	INT32		CManageEdBase<_T>::DelEditDataMap(UINT32 nEditID)
{
	m_tEditDataMap.erase(nEditID);
	return m_tEditDataMap.size();	
}

TEMPLATE	_T*			CManageEdBase<_T>::FindEditData(UINT32 nEditID)
{
	map <unsigned int, _T>::iterator find;

	find = m_tEditDataMap.find(nEditID);
	if(find == m_tEditDataMap.end())	return NULL;

	return &(find->second);
}

TEMPLATE	INT32		CManageEdBase<_T>::GetEditDataIDList(TListID& tEIDList)
{
	map <unsigned int, _T>::iterator begin, end;
	begin = m_tEditDataMap.begin();	end = m_tEditDataMap.end();

	for (; begin != end; begin++)
	{			
		tEIDList.push_back(begin->second.nEditID);
	}
	return tEIDList.size();
}
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

TEMPLATE	INT32		CManageEdBase<_T>::InitGlobalIter()
{
	g_begin = m_tMap.begin();
	g_end = m_tMap.end();
	m_nInitGlobalIter = 1;
	return 0;
}

TEMPLATE	INT32		CManageEdBase<_T>::FreeGlobalIter()
{
	m_nInitGlobalIter = 0;
	return 0;
}

TEMPLATE	_T*			CManageEdBase<_T>::NextGlobalIter()
{
	if(!m_nInitGlobalIter)	return NULL;

	if(g_begin == g_end)
	{
		FreeGlobalIter();
		return NULL;
	}
	_T* pRtn = &(g_begin->second);
	g_begin++;
	return pRtn;
}

TEMPLATE	INT32		CManageEdBase<_T>::IsNextGlobalIter()
{
	if(!m_nInitGlobalIter)	return 0;

	if(g_begin == g_end)
	{
		FreeGlobalIter();
		return 0;
	}

	return 1;
}

TEMPLATE	INT32		CManageEdBase<_T>::IsInitGlobalIter()
{
	return m_nInitGlobalIter;
}

///////////////////////////////////////////////////////////////////////////////

TEMPLATE	void		CManageEdBase<_T>::PrintDbgInfo()
{
	return;
}