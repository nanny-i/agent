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

//-------------------------------------------------------------------------
typedef struct _mem_mb_edit_data
{
	_mem_mb_edit_data()
	{
		nID			= 0;
		nSubID		= 0;
		nValue		= 0;
	}

	void _set_value(UINT32 nIdx, UINT32 _nValue)
	{
		tValueMap[nIdx] = _nValue;
		return;
	}

	UINT32 _get_value(UINT32 nIdx)
	{
		TMapIDItor find = tValueMap.find(nIdx);
		if(find == tValueMap.end())		return 0;

		return find->second;
	}
	union
	{
		UINT32 nID;
		UINT32 nUnitID;
	};

	union
	{
		UINT32 nSubID;
		UINT32 nPkgID;
	};
	UINT32 nValue;
	TMapID tValueMap;
}MEM_MB_EDIT_DATA, *PMEM_MB_EDIT_DATA, *PMMED;

typedef map<UINT32, MEM_MB_EDIT_DATA>		TMapMemMBEditData;
typedef TMapMemMBEditData::iterator			TMapMemMBEditDataItor;
//-------------------------------------------------------------------------

template <class _T>
class CManagePoBase
{
public:
	CManagePoBase(void);
	virtual ~CManagePoBase(void);

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
	virtual _T*			GetDefaultItem();
	virtual INT32		IsExistID(UINT32 nID, list<_T>& tUnitList);

	virtual INT32		SetEditDataID(UINT32 nID);
	virtual INT32		SetEditData(UINT32 nID, UINT32 nMultiPkg = 0);
	virtual INT32		SetEditData(_T* pData, UINT32 nMultiPkg = 0);
	virtual INT32		SetEditData(UINT32 nUnitID, UINT32 nPkgID, UINT32 nMultiPkg = 0);
	virtual INT32		ClearEditData();
	virtual INT32		ChgEditPkgIDList(TListID tIDList);
	virtual INT32		ChgEditPkgIDList(UINT32 nKey, TListID tIDList);
	virtual _T*			GetEditData();
	virtual INT32		GetEditDataID();
	virtual INT32		GetEditPkgIDMap(TMapID& tPkgIDMap);
	virtual INT32		GetEditPkgIDMap(UINT32 nKey, TMapID& tPkgIDMap);
	virtual INT32		IsExistEditPkgIDMap(UINT32 nUnitID);
	virtual INT32		AddEditPkgIDTempMap(UINT32 nUnitID);
	virtual INT32		DelEditPkgIDTempMap(UINT32 nUnitID);
	virtual INT32		IsExistEditPkgIDTempMap(UINT32 nUnitID);
	virtual INT32		CopyEditPkgIDTempMap();
	virtual INT32		MergeEditPkgIDTempMap();

	virtual INT32		SetEditDataMap(UINT32 nID);
	virtual INT32		AddEditDataMap(_T& data);
	virtual INT32		EditEditDataMap(_T& data);
	virtual INT32		DelEditDataMap(UINT32 nEditID);
	virtual _T*			FindEditData(UINT32 nEditID);
	virtual INT32		GetEditDataIDList(TListID& tEIDList);

	virtual INT32		ClearEditMMED();
	virtual INT32		SetEditMMED(UINT32 nID);
	virtual INT32		SetEditMMED(_T* pData);
	virtual INT32		SetEditMMED(MEM_MB_EDIT_DATA& data);
	virtual INT32		MakeEditMMED();
	virtual _T*			GetEditMMED();
	virtual INT32		GetEditMMEDID();
	virtual INT32		GetEditMMEDIDList(TListID& tIDList);
	virtual PMMED		FindEditMMED(UINT32 nID);
	virtual INT32		IsExistEditMMEDTemp(UINT32 nUnitID);
	virtual INT32		AddEditMMEDTemp(MEM_MB_EDIT_DATA& data);
	virtual INT32		EditEditMMEDTemp(MEM_MB_EDIT_DATA& data);
	virtual INT32		DelEditMMEDTemp(UINT32 nUnitID);
	virtual PMMED		FindEditMMEDTemp(UINT32 nID);
	virtual INT32		MergeEditMMEDTemp();



	virtual UINT32 Count();
	virtual UINT32 GetItem(INT32 nID, TListID &tListID);
	virtual UINT32 GetItemPtrList(INT32 nID, list<_T*>	&tListPtr);
	virtual UINT32 GetItemPtrArray(INT32 nID, vector <_T*> &tVecPtr);
	virtual UINT32 GetItemIDList(TListID& tListID);
	virtual UINT32 GetItemIDListByPoID(UINT32 nPoID, TListID& tListID);
	virtual UINT32 GetItemIDListByUnitID(UINT32 nUnitID, TListID& tListID);
	virtual UINT32 GetPoIDFromPkgList(UINT32 nUnitID, TListID& tListID);
	virtual UINT32 GetPoIDFromPkgMap(UINT32 nUnitID, TMapID& tMapID);


public:
	virtual	UINT32		AddKeyID(UINT32 nKey, UINT32 nID);
	virtual	UINT32		DelKeyID(UINT32 nKey);
	virtual	UINT32		FindKeyID(UINT32 nKey);
	virtual _T*			FindKeyItem(UINT32 nKey);
	virtual	UINT32		ClearKeyID();
	virtual	UINT32		ConvertKeyID(TListID& tKeyList, TListID& tIDList);

public:
	virtual	UINT32		AddStrKeyID(String strKey, UINT32 nID);
	virtual	UINT32		DelStrKeyID(String strKey);
	virtual	UINT32		FindStrKeyID(String strKey);
	virtual _T*			FindStrKeyItem(String strKey);
	virtual	UINT32		ClearStrKeyID();
	virtual	UINT32		ConvertStrKeyID(TListStr& tStrKeyList, TListID& tIDList);

public:
	virtual	UINT32		AddKeyIDList(UINT32 nKey, UINT32 nID);
	virtual	UINT32		AddKeyIDList(_T* t);
	virtual	UINT32		DelKeyIDList(UINT32 nKey);
	virtual	UINT32		DelKeyIDList(UINT32 nKey, UINT32 nID);
	virtual	UINT32		DelKeyIDList(_T* t);
	virtual	UINT32		GetKeyIDList(UINT32 nKey, TListID& tIDList);
	virtual	UINT32		IsExistKeyIDList(UINT32 nKey, UINT32 nUnit);
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
	virtual	UINT32		GetPosKeyIDMap(TListID& tKeyList, UINT32 nPos = 0);
	virtual	UINT32		ClearPosKeyIDMap(UINT32 nPos = 0);

public:
	virtual	UINT32		AddKeySubIDMap(UINT32 nKey, UINT32 nSubKey, UINT32 nID);
	virtual	UINT32		DelKeySubIDMap(UINT32 nKey);
	virtual	UINT32		DelKeySubIDMap(UINT32 nKey, UINT32 nSubKey);
	virtual	UINT32		GetKeySubIDMap(UINT32 nKey, TMapID& tIDMap);
	virtual	UINT32		ClearKeySubIDMap();

public:
	virtual	UINT32		AddPosKeySubIDMap(UINT32 nKey, UINT32 nSubKey, UINT32 nID, UINT32 nPos = 0);
	virtual	UINT32		DelPosKeySubIDMap(UINT32 nKey, UINT32 nPos = 0);
	virtual	UINT32		DelPosKeySubIDMap(UINT32 nKey, UINT32 nSubKey, UINT32 nPos = 0);
	virtual	UINT32		FindPosKeySubIDMap(UINT32 nKey, UINT32 nSubKey, UINT32 nPos = 0);
	virtual	UINT32		GetPosKeySubIDMap(UINT32 nKey, TMapID& tSubKeyMap, UINT32 nPos = 0);
	virtual	UINT32		GetPosKeySubIDMap(UINT32 nKey, TListID& tSubKeyList, UINT32 nPos = 0);
	virtual	UINT32		GetPosKeySubIDMap(UINT32 nKey, UINT32 nSubKey, UINT32 nPos = 0);
	virtual	UINT32		GetPosKeySubIDMap(TMapIDMap& tKeyIDMap, UINT32 nPos = 0);
	virtual	UINT32		ClearPosKeySubIDMap(UINT32 nPos = 0);

public:
	virtual void		PrintDbgInfo();


public:
	virtual String			GetName(UINT32 nID);
	virtual PDB_PO_HEADER	GetPoHdr(UINT32 nID);
	virtual	UINT32			GetPoHdrList(TListDBPoHeader& tListDBPoHeader);
	virtual String			GetHdrHashInfo(_T* data);
	virtual String			GetHdrHashInfoNoLink(_T* data);
	virtual INT32			SetPkt(UINT32 nID, MemToken& SendToken);
	virtual INT32			IsMultiUsedUnit(UINT32 nPolicyID, UINT32 nUnitID);
	virtual String			GetHash();


protected :
	map <UINT32, _T>	m_tMap;
	TMapID				m_tKeyMap;
	TMapStrID			m_tStrKeyMap;
	TMapIDList			m_tKeyListMap;
	TMapIDMap			m_tKeyMapMap;
	TMapIDMap			m_tKeySubIDMap;
	TMapIDMapMap		m_tPosKeyMapMap;
	TMapIDMapMap		m_tPosKeySubMapMap;

protected :
	UINT32				m_nEditDataID;
	_T					m_tEditData;
	TMapID				m_tEditPkgIDMap;
	TMapID				m_tEditPkgIDTempMap;
	map <UINT32, _T>	m_tEditDataMap;
	UINT32				m_nEditID;

	_T					m_tEditMMED;
	UINT32				m_nEditMMEDID;
	TMapMemMBEditData	m_tEditMMEDMap;
	TMapMemMBEditData	m_tEditMMEDTempMap;

	typename map <UINT32, _T>::iterator m_pMapItorFind;
	typename map <UINT32, _T>::iterator m_pMapItorBegin;
	typename map <UINT32, _T>::iterator m_pMapItorEnd;
	typename list <_T>::iterator m_pListItorBegin;
	typename list <_T>::iterator m_pListItorEnd;
	typename map <UINT32, _T>::iterator	m_pDataMapItorFind;
	typename map <UINT32, _T>::iterator m_pDataMapItorBegin;
	typename map <UINT32, _T>::iterator m_pDataMapItorEnd;

public:
	INT32				SetSyncDBMSType(UINT32 nType);
	INT32				IsSyncDBMS();

public:
	UINT32		m_nRecvNum;
	String		m_strFullHash;
	String		m_strHashValue;

public:
	UINT32		m_nDBSyncType;
	UINT32		m_nDBSyncChkType;
};

#define	TEMPLATE template <class _T>

TEMPLATE	CManagePoBase<_T>::CManagePoBase(void)
{
	m_nRecvNum			= 0;
	m_nEditDataID		= 0;
	m_nEditID			= 0;
	m_nEditMMEDID		= 0;
}

TEMPLATE	CManagePoBase<_T>::~CManagePoBase(void)
{
}

TEMPLATE INT32		CManagePoBase<_T>::AddItem(UINT32 nID, _T& data)
{
	m_tMap[nID] = data;
	return 0;
}

TEMPLATE INT32		CManagePoBase<_T>::AddItem(_T& data)
{
	UINT32 nID = ((PDB_ID)&data)->nID;
	return AddItem(nID, data);
}

TEMPLATE INT32		CManagePoBase<_T>::EditItem(UINT32 nID, _T& data)
{
	m_pMapItorFind = m_tMap.find(nID);
	if (m_pMapItorFind == m_tMap.end())
		return 0;

	m_pMapItorFind->second = data;
	return 0;
}

TEMPLATE INT32		CManagePoBase<_T>::EditItem(_T& data)
{
	UINT32 nID = ((PDB_ID)&data)->nID;
	return EditItem(nID, data);
}

TEMPLATE INT32		CManagePoBase<_T>::DeleteItem(UINT32 nID)
{
	m_pMapItorFind = m_tMap.find(nID);

	if (m_pMapItorFind == m_tMap.end())
		return -1;

	m_tMap.erase(m_pMapItorFind);
	return 0;
}

TEMPLATE INT32		CManagePoBase<_T>::ClearItem()
{
	m_tMap.clear();
	return 0;
}

TEMPLATE _T*			CManagePoBase<_T>::FindItem(UINT32 nID)
{
	m_pMapItorFind = m_tMap.find(nID);
	if (m_pMapItorFind == m_tMap.end())
		return NULL;

	return &(m_pMapItorFind->second);
}

TEMPLATE _T*			CManagePoBase<_T>::FirstItem()
{
	m_pMapItorBegin = m_tMap.begin();
	if (m_pMapItorBegin == m_tMap.end())
		return NULL;

	return &(m_pMapItorBegin->second);
}

TEMPLATE _T*			CManagePoBase<_T>::LastItem()
{
	m_pMapItorBegin = m_tMap.begin();
	m_pMapItorEnd = m_tMap.end();

	if (m_pMapItorBegin == m_tMap.end())
		return NULL;

	return &((--m_pMapItorEnd)->second);
}

TEMPLATE _T*			CManagePoBase<_T>::GetDefaultItem()
{
	return FindItem(DEFAULT_ID);
}

TEMPLATE INT32	CManagePoBase<_T>::IsExistID(UINT32 nID, list<_T>& tUnitList)
{
	m_pListItorBegin = tUnitList.begin();
	m_pListItorEnd = tUnitList.end();
	for(m_pListItorBegin; m_pListItorBegin != m_pListItorEnd; m_pListItorBegin++)
	{
		if(m_pListItorBegin->tDPH.nID == nID)
			return 1;
	}
	return 0;
}

TEMPLATE UINT32 CManagePoBase<_T>::Count()
{
	return (UINT32)m_tMap.size();
}

TEMPLATE UINT32 CManagePoBase<_T>::GetItemPtrList(INT32 nID, list<_T*>	&tListPtr)
{
	m_pMapItorBegin = m_tMap.begin();
	m_pMapItorEnd = m_tMap.end();

	if (nID != -1)
	{
		for (; m_pMapItorBegin != m_pMapItorEnd; m_pMapItorBegin++)
		{
			if (m_pMapItorBegin->second.tDPH.nID == nID)
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

	return (UINT32)tListPtr.size();
}

TEMPLATE UINT32 CManagePoBase<_T>::GetItemPtrArray(INT32 nID, vector <_T*> &tVecPtr)
{
	m_pMapItorBegin = m_tMap.begin();
	m_pMapItorEnd = m_tMap.end();

	if (nID != -1)
	{
		for (; m_pMapItorBegin != m_pMapItorEnd; m_pMapItorBegin++)
		{
			if (m_pMapItorBegin->second.tDPH.nID == nID)
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

	return (UINT32)tVecPtr.size();
}

TEMPLATE UINT32 CManagePoBase<_T>::GetItem(INT32 nID, TListID &tListID)
{
	m_pMapItorBegin = m_tMap.begin();
	m_pMapItorEnd = m_tMap.end();

	if (nID != -1)
	{
		for (; m_pMapItorBegin != m_pMapItorEnd; m_pMapItorBegin++)
		{
			if (m_pMapItorBegin->second.tDPH.nID == nID)
			{
				tListID.push_back(m_pMapItorBegin->second.tDPH.nID);
			}
		}
	}
	else
	{
		for (; m_pMapItorBegin != m_pMapItorEnd; m_pMapItorBegin++)
		{
			tListID.push_back(m_pMapItorBegin->second.tDPH.nID);
		}
	}

	return (UINT32)tListID.size();
}

TEMPLATE	UINT32	CManagePoBase<_T>::GetItemIDList(TListID& tListID)
{
	m_pMapItorBegin = m_tMap.begin();
	m_pMapItorEnd = m_tMap.end();

	for (; m_pMapItorBegin != m_pMapItorEnd; m_pMapItorBegin++)
	{
		tListID.push_back(m_pMapItorBegin->second.tDPH.nID);
	}

	return	(UINT32)tListID.size();
}

TEMPLATE	UINT32 CManagePoBase<_T>::GetItemIDListByPoID(UINT32 nPoID, TListID& tListID)
{
	m_pMapItorBegin = m_tMap.begin();
	m_pMapItorEnd = m_tMap.end();

	for (; m_pMapItorBegin != m_pMapItorEnd; m_pMapItorBegin++)
	{
		if(m_pMapItorBegin->second.tDPH.nPolicyID != nPoID)
			continue;

		tListID.push_back(m_pMapItorBegin->second.tDPH.nID);
	}

	return	(UINT32)tListID.size();
}

TEMPLATE	UINT32 CManagePoBase<_T>::GetItemIDListByUnitID(UINT32 nUnitID, TListID& tListID)
{
	m_pMapItorBegin = m_tMap.begin();
	m_pMapItorEnd = m_tMap.end();

	for (; m_pMapItorBegin != m_pMapItorEnd; m_pMapItorBegin++)
	{
		if(m_pMapItorBegin->second.tDPH.nUnitID != nUnitID)
			continue;

		tListID.push_back(m_pMapItorBegin->second.tDPH.nID);
	}

	return	(UINT32)tListID.size();
}

TEMPLATE	UINT32 CManagePoBase<_T>::GetPoIDFromPkgList(UINT32 nUnitID, TListID& tListID)
{
	m_pMapItorBegin = m_tMap.begin();
	m_pMapItorEnd = m_tMap.end();

	for (; m_pMapItorBegin != m_pMapItorEnd; m_pMapItorBegin++)
	{
		if(m_pMapItorBegin->second.tDPH.nUnitID != nUnitID)
			continue;

		tListID.push_back(m_pMapItorBegin->second.tDPH.nPolicyID);
	}

	return	(UINT32)tListID.size();
}

TEMPLATE	UINT32 CManagePoBase<_T>::GetPoIDFromPkgMap(UINT32 nUnitID, TMapID& tMapID)
{
	m_pMapItorBegin = m_tMap.begin();
	m_pMapItorEnd = m_tMap.end();

	for (; m_pMapItorBegin != m_pMapItorEnd; m_pMapItorBegin++)
	{
		if(m_pMapItorBegin->second.tDPH.nUnitID != nUnitID)
			continue;

		tMapID[m_pMapItorBegin->second.tDPH.nPolicyID] = m_pMapItorBegin->second.tDPH.nID;
	}

	return	(UINT32)tMapID.size();
}
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

TEMPLATE	UINT32		CManagePoBase<_T>::AddKeyID(UINT32 nKey, UINT32 nID)
{
	m_tKeyMap[nKey] = nID;
	return 0;
}

TEMPLATE	UINT32		CManagePoBase<_T>::DelKeyID(UINT32 nKey)
{
	m_tKeyMap.erase(nKey);
	return 0;
}

TEMPLATE	UINT32		CManagePoBase<_T>::FindKeyID(UINT32 nKey)
{
	TMapIDItor find = m_tKeyMap.find(nKey);
	if(find == m_tKeyMap.end())	return 0;
	return find->second;
}

TEMPLATE _T*			CManagePoBase<_T>::FindKeyItem(UINT32 nKey)
{
	UINT32 nID = FindKeyID(nKey);
	return FindItem(nID);
}

TEMPLATE	UINT32		CManagePoBase<_T>::ClearKeyID()
{
	m_tKeyMap.clear();
	return 0;
}

TEMPLATE	UINT32		CManagePoBase<_T>::ConvertKeyID(TListID& tKeyList, TListID& tIDList)
{
	TListIDItor begin, end;
	begin = tKeyList.begin();	end = tKeyList.end();
	for(begin; begin != end; begin++)
	{
		TMapIDItor find = m_tKeyMap.find(*begin);
		if(find == m_tKeyMap.end())		continue;

		tIDList.push_back(find->second);
	}
	return 0;
}
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

TEMPLATE	UINT32		CManagePoBase<_T>::AddStrKeyID(String strKey, UINT32 nID)
{
	m_tStrKeyMap[strKey] = nID;
	return 0;
}

TEMPLATE	UINT32		CManagePoBase<_T>::DelStrKeyID(String strKey)
{
	m_tStrKeyMap.erase(strKey);
	return 0;
}

TEMPLATE	UINT32		CManagePoBase<_T>::FindStrKeyID(String strKey)
{
	TMapStrIDItor find = m_tStrKeyMap.find(strKey);
	if(find == m_tStrKeyMap.end())	return 0;
	return find->second;
}

TEMPLATE _T*			CManagePoBase<_T>::FindStrKeyItem(String strKey)
{
	UINT32 nID = FindStrKeyID(strKey);
	return FindItem(nID);
}

TEMPLATE	UINT32		CManagePoBase<_T>::ClearStrKeyID()
{
	m_tStrKeyMap.clear();
	return 0;
}

TEMPLATE	UINT32		CManagePoBase<_T>::ConvertStrKeyID(TListStr& tStrKeyList, TListID& tIDList)
{
	TListStrItor begin, end;
	begin = tStrKeyList.begin();	end = tStrKeyList.end();
	for(begin; begin != end; begin++)
	{
		TMapStrIDItor find = m_tStrKeyMap.find(*begin);
		if(find == m_tStrKeyMap.end())		continue;

		tIDList.push_back(find->second);
	}
	return 0;
}
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

TEMPLATE	UINT32		CManagePoBase<_T>::AddKeyIDList(UINT32 nKey, UINT32 nID)
{
	TMapIDListItor find = m_tKeyListMap.find(nKey);
	if(find == m_tKeyListMap.end())
	{
		TListID tIDList;
		m_tKeyListMap[nKey] = tIDList;
		find = m_tKeyListMap.find(nKey);
	}

	find->second.push_back(nID);
	return 0;
}


TEMPLATE	UINT32		CManagePoBase<_T>::AddKeyIDList(_T* t)
{
	PDB_PO_HEADER pDPH = (PDB_PO_HEADER)t;
	return AddKeyIDList(pDPH->nPolicyID, pDPH->nUnitID);
}


TEMPLATE	UINT32		CManagePoBase<_T>::DelKeyIDList(UINT32 nKey)
{
	TMapIDListItor find = m_tKeyListMap.find(nKey);
	if(find == m_tKeyListMap.end())
	{
		return 0;
	}

	find->second.clear();
	m_tKeyListMap.erase(nKey);
	return 0;
}

TEMPLATE	UINT32		CManagePoBase<_T>::DelKeyIDList(UINT32 nKey, UINT32 nID)
{
	TMapIDListItor find = m_tKeyListMap.find(nKey);
	if(find == m_tKeyListMap.end())
	{
		return 0;
	}

	RemoveListID(find->second, nID);

	if(find->second.size() == 0)
	{
		m_tKeyListMap.erase(nKey);
	}
	return 0;
}

TEMPLATE	UINT32		CManagePoBase<_T>::DelKeyIDList(_T* t)
{
	PDB_PO_HEADER pDPH = (PDB_PO_HEADER)t;
	return DelKeyIDList(pDPH->nPolicyID, pDPH->nUnitID);
}

TEMPLATE	UINT32		CManagePoBase<_T>::GetKeyIDList(UINT32 nKey, TListID& tIDList)
{
	TMapIDListItor find = m_tKeyListMap.find(nKey);
	if(find == m_tKeyListMap.end())
	{
		return 0;
	}

	tIDList = find->second;
	return 0;
}

TEMPLATE	UINT32		CManagePoBase<_T>::IsExistKeyIDList(UINT32 nKey, UINT32 nUnit)
{
	TListID tListID;
	GetKeyIDList(nKey, tListID);

	TListIDItor begin, end;
	begin = tListID.begin();		end = tListID.end();

	for(begin; begin != end; begin++)
	{
		if(*begin == nUnit)	return 1;
	}

	return 0;
}

TEMPLATE	UINT32		CManagePoBase<_T>::ClearKeyIDList()
{
	m_tKeyListMap.clear();
	return 0;
}
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

TEMPLATE	UINT32		CManagePoBase<_T>::AddKeyIDMap(UINT32 nKey, UINT32 nID)
{
	TMapIDMapItor find = m_tKeyMapMap.find(nKey);
	if(find == m_tKeyMapMap.end())
	{
		TMapID tIDMap;
		m_tKeyMapMap[nKey] = tIDMap;
		find = m_tKeyMapMap.find(nKey);
	}

	find->second[nID] = 0;
	return 0;
}

TEMPLATE	UINT32		CManagePoBase<_T>::DelKeyIDMap(UINT32 nKey)
{
	TMapIDMapItor find = m_tKeyMapMap.find(nKey);
	if(find == m_tKeyMapMap.end())
	{
		return 0;
	}

	find->second.clear();
	m_tKeyMapMap.erase(nKey);
	return 0;
}


TEMPLATE	UINT32		CManagePoBase<_T>::DelKeyIDMap(UINT32 nKey, UINT32 nID)
{
	TMapIDMapItor find = m_tKeyMapMap.find(nKey);
	if(find != m_tKeyMapMap.end())
	{
		return 0;
	}

	find->second.erase(nID);
	return 0;
}

TEMPLATE	UINT32		CManagePoBase<_T>::GetKeyIDMap(UINT32 nKey, TMapID& tIDMap)
{
	TMapIDMapItor find = m_tKeyMapMap.find(nKey);
	if(find == m_tKeyMapMap.end())
	{
		return 0;
	}

	AppandMapToMap(find->second, tIDMap);
	return tIDMap.size();
}

TEMPLATE	UINT32		CManagePoBase<_T>::ClearKeyIDMap()
{
	m_tKeyMapMap.clear();
	return 0;
}
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////


TEMPLATE	UINT32		CManagePoBase<_T>::AddPosKeyIDMap(UINT32 nKey, UINT32 nID, UINT32 nPos)
{
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
	return 0;
}

TEMPLATE	UINT32		CManagePoBase<_T>::DelPosKeyIDMap(UINT32 nKey, UINT32 nPos)
{
	TMapIDMapMapItor find = m_tPosKeyMapMap.find(nPos);
	if(find == m_tPosKeyMapMap.end())
	{
		return 0;
	}

	TMapIDMapItor find_key = find->second.find(nKey);
	if(find_key == find->second.end())
	{
		return 0;
	}

	find_key->second.clear();
	find->second.erase(nKey);
	return 0;
}


TEMPLATE	UINT32		CManagePoBase<_T>::DelPosKeyIDMap(UINT32 nKey, UINT32 nID, UINT32 nPos)
{
	TMapIDMapMapItor find = m_tPosKeyMapMap.find(nPos);
	if(find == m_tPosKeyMapMap.end())
	{
		return 0;
	}

	TMapIDMapItor find_key = find->second.find(nKey);
	if(find_key == find->second.end())
	{
		return 0;
	}

	find_key->second.erase(nID);
	return 0;
}

TEMPLATE	UINT32		CManagePoBase<_T>::GetPosKeyIDMap(UINT32 nKey, TMapID& tIDMap, UINT32 nPos)
{
	TMapIDMapMapItor find = m_tPosKeyMapMap.find(nPos);
	if(find == m_tPosKeyMapMap.end())
	{
		return 0;
	}

	TMapIDMapItor find_key = find->second.find(nKey);
	if(find_key == find->second.end())
	{
		return 0;
	}

	AppandMapToMap(find_key->second, tIDMap);
	return tIDMap.size();
}

TEMPLATE	UINT32		CManagePoBase<_T>::GetPosKeyIDMap(UINT32 nKey, TListID& tIDList, UINT32 nPos)
{
	TMapIDMapMapItor find = m_tPosKeyMapMap.find(nPos);
	if(find == m_tPosKeyMapMap.end())
	{
		return 0;
	}

	TMapIDMapItor find_key = find->second.find(nKey);
	if(find_key == find->second.end())
	{
		return 0;
	}

	ConvertMapToList(find_key->second, tIDList);
	return tIDList.size();
}

TEMPLATE	UINT32		CManagePoBase<_T>::GetPosKeyIDMap(TListID& tKeyList, UINT32 nPos)
{
	TMapIDMapMapItor find = m_tPosKeyMapMap.find(nPos);
	if(find == m_tPosKeyMapMap.end())
	{
		return 0;
	}

	TMapIDMapItor begin, end;
	begin = find->second.begin();	end = find->second.end();
	for(begin; begin != end; begin++)
	{
		tKeyList.push_back(begin->first);
	}

	return tKeyList.size();
}

TEMPLATE	UINT32		CManagePoBase<_T>::ClearPosKeyIDMap(UINT32 nPos)
{
	TMapIDMapMapItor find = m_tPosKeyMapMap.find(nPos);
	if(find == m_tPosKeyMapMap.end())
	{
		return 0;
	}

	find->second.clear();
	return 0;
}
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

TEMPLATE	UINT32		CManagePoBase<_T>::AddKeySubIDMap(UINT32 nKey, UINT32 nSubKey, UINT32 nID)
{
	TMapIDMapItor find = m_tKeySubIDMap.find(nKey);
	if(find == m_tKeySubIDMap.end())
	{
		TMapID tSubMap;
		m_tKeySubIDMap[nKey] = tSubMap;
		find = m_tKeySubIDMap.find(nKey);
	}

	find->second[nSubKey] = nID;
	return 0;
}

TEMPLATE	UINT32		CManagePoBase<_T>::DelKeySubIDMap(UINT32 nKey)
{
	TMapIDMapItor find = m_tKeySubIDMap.find(nKey);
	if(find != m_tKeySubIDMap.end())
	{
		return 0;
	}

	find->second.clear();
	m_tKeySubIDMap.erase(nKey);
	return 0;
}

TEMPLATE	UINT32		CManagePoBase<_T>::DelKeySubIDMap(UINT32 nKey, UINT32 nSubKey)
{
	TMapIDMapItor find = m_tKeySubIDMap.find(nKey);
	if(find != m_tKeySubIDMap.end())
	{
		return 0;
	}

	find->second.erase(nSubKey);
	return 0;
}

TEMPLATE	UINT32		CManagePoBase<_T>::GetKeySubIDMap(UINT32 nKey, TMapID& tIDMap)
{
	TMapIDMapItor find = m_tKeySubIDMap.find(nKey);
	if(find != m_tKeySubIDMap.end())
	{
		return 0;
	}

	AppandMapToMap(find->second, tIDMap);
	return 0;
}

TEMPLATE	UINT32		CManagePoBase<_T>::ClearKeySubIDMap()
{
	m_tKeySubIDMap.clear();
	return 0;
}
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

TEMPLATE	UINT32		CManagePoBase<_T>::AddPosKeySubIDMap(UINT32 nKey, UINT32 nSubKey, UINT32 nID, UINT32 nPos)
{
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
	return 0;
}

TEMPLATE	UINT32		CManagePoBase<_T>::DelPosKeySubIDMap(UINT32 nKey, UINT32 nPos)
{
	TMapIDMapMapItor find = m_tPosKeySubMapMap.find(nPos);
	if(find == m_tPosKeySubMapMap.end())
	{
		return 0;
	}

	TMapIDMapItor find_key = find->second.find(nKey);
	if(find_key == find->second.end())
	{
		return 0;
	}

	find_key->second.clear();
	find->second.erase(nKey);
	return 0;
}

TEMPLATE	UINT32		CManagePoBase<_T>::DelPosKeySubIDMap(UINT32 nKey, UINT32 nSubKey, UINT32 nPos)
{
	TMapIDMapMapItor find = m_tPosKeySubMapMap.find(nPos);
	if(find == m_tPosKeySubMapMap.end())
	{
		return 0;
	}

	TMapIDMapItor find_key = find->second.find(nKey);
	if(find_key == find->second.end())
	{
		return 0;
	}

	find_key->second.erase(nSubKey);
	return 0;
}

TEMPLATE	UINT32		CManagePoBase<_T>::FindPosKeySubIDMap(UINT32 nKey, UINT32 nSubKey, UINT32 nPos)
{
	TMapIDMapMapItor find = m_tPosKeySubMapMap.find(nPos);
	if(find == m_tPosKeySubMapMap.end())
	{
		return 0;
	}

	TMapIDMapItor find_key = find->second.find(nKey);
	if(find_key == find->second.end())
	{
		return 0;
	}

	TMapIDItor find_key_sub = find_key->second.find(nSubKey);
	if(find_key_sub == find_key->second.end())
	{
		return 0;
	}

	return find_key_sub->second;
}

TEMPLATE	UINT32		CManagePoBase<_T>::GetPosKeySubIDMap(UINT32 nKey, TMapID& tSubKeyMap, UINT32 nPos)
{
	TMapIDMapMapItor find = m_tPosKeySubMapMap.find(nPos);
	if(find == m_tPosKeySubMapMap.end())
	{
		return 0;
	}

	TMapIDMapItor find_key = find->second.find(nKey);
	if(find_key == find->second.end())
	{
		return 0;
	}

	AppandMapToMap(find_key->second, tSubKeyMap);

	return tSubKeyMap.size();
}

TEMPLATE	UINT32		CManagePoBase<_T>::GetPosKeySubIDMap(UINT32 nKey, TListID& tSubKeyList, UINT32 nPos)
{
	TMapIDMapMapItor find = m_tPosKeySubMapMap.find(nPos);
	if(find == m_tPosKeySubMapMap.end())
	{
		return 0;
	}

	TMapIDMapItor find_key = find->second.find(nKey);
	if(find_key == find->second.end())
	{
		return 0;
	}

	ConvertMapToList(find_key->second, tSubKeyList);
	return tSubKeyList.size();
}

TEMPLATE	UINT32		CManagePoBase<_T>::GetPosKeySubIDMap(TMapIDMap& tKeyIDMap, UINT32 nPos)
{
	TMapIDMapMapItor find = m_tPosKeySubMapMap.find(nPos);
	if(find == m_tPosKeySubMapMap.end())
	{
		return 0;
	}

	tKeyIDMap = find->second;
	return tKeyIDMap.size();
}

TEMPLATE	UINT32		CManagePoBase<_T>::ClearPosKeySubIDMap(UINT32 nPos)
{
	TMapIDMapMapItor find = m_tPosKeySubMapMap.find(nPos);
	if(find == m_tPosKeySubMapMap.end())
	{
		return 0;
	}

	find->second.clear();
	return 0;
}

TEMPLATE	UINT32		CManagePoBase<_T>::GetPosKeySubIDMap(UINT32 nKey, UINT32 nSubKey, UINT32 nPos)
{
	UINT32 nRtn = 0;
	TMapIDMapMapItor find = m_tPosKeySubMapMap.find(nPos);
	if(find == m_tPosKeySubMapMap.end())
	{
		return 0;
	}

	TMapIDMapItor find_key = find->second.find(nKey);
	if(find_key == find->second.end())
	{
		return 0;
	}

	TMapIDItor find_subkey = find_key->second.find(nSubKey);
	if(find_subkey == find_key->second.end())
	{
		return 0;
	}

	nRtn = find_subkey->second;

	return nRtn;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

TEMPLATE	INT32		CManagePoBase<_T>::SetEditDataID(UINT32 nID)
{
	m_nEditDataID  = nID;
	ClearEditData();
	return 0;
}

TEMPLATE	INT32		CManagePoBase<_T>::SetEditData(UINT32 nID, UINT32 nMultiPkg)
{
	_T tEmptyData;
	m_tEditData = tEmptyData;

	_T* pData = FindItem(nID);
	if(!pData)	return -1;

	return SetEditData(pData, nMultiPkg);
}

TEMPLATE	 INT32		CManagePoBase<_T>::SetEditData(_T* pData, UINT32 nMultiPkg)
{
	m_tEditData = *pData;
	ClearEditData();

	DB_PO_HEADER tDPH;
	TMapIDItor begin, end;
	begin = pData->tDPH.tSubIDMap.begin();	end = pData->tDPH.tSubIDMap.end();
	for(begin; begin != end; begin++)
	{
		SetEditData(begin->first, begin->second, nMultiPkg);
	}
	return 0;
}

TEMPLATE	INT32		CManagePoBase<_T>::SetEditData(UINT32 nPkgID, UINT32 nUnitID, UINT32 nMultiPkg)
{
	if(nMultiPkg)
	{
		DB_PO_HEADER tDPH;
		UINT32 nKey = tDPH._get_id_to_key(nPkgID);
		UINT32 nSubID = tDPH._get_id_to_subid(nPkgID);

		UINT32 nEditID = ((UINT32)nKey) << 24;
		nEditID += nUnitID;

		m_tEditPkgIDMap[nEditID] = nSubID;
	}
	else
	{
		m_tEditPkgIDMap[nUnitID] = nPkgID;
	}
	return 0;
}

TEMPLATE	INT32		CManagePoBase<_T>::ClearEditData()
{
	m_tEditPkgIDMap.clear();
	m_tEditPkgIDTempMap.clear();
	return 0;
}

TEMPLATE	INT32		CManagePoBase<_T>::ChgEditPkgIDList(TListID tIDList)
{
	TListID tDelLIst;
	{
		TMapIDItor begin, end;
		begin = m_tEditPkgIDMap.begin();	end = m_tEditPkgIDMap.end();
		for(begin; begin != end; begin++)
		{
			if(IsExistsIDFromList(tIDList, begin->first))	continue;

			tDelLIst.push_back(begin->first);
		}
	}

	{
		TListIDItor begin, end;
		begin = tDelLIst.begin();	end = tDelLIst.end();
		for(begin; begin != end; begin++)
		{
			m_tEditPkgIDMap.erase(*begin);
		}
	}

	{
		TListIDItor begin, end;
		begin = tIDList.begin();	end = tIDList.end();
		for(begin; begin != end; begin++)
		{
			if(m_tEditPkgIDMap.find(*begin) != m_tEditPkgIDMap.end())	continue;

			m_tEditPkgIDMap[*begin] = 0;
		}
	}
	return 0;
}

TEMPLATE	INT32		CManagePoBase<_T>::ChgEditPkgIDList(UINT32 nKey, TListID tIDList)
{
	TListID tDelLIst;
	{
		DB_PO_HEADER tDPH;
		TMapIDItor begin, end;
		begin = m_tEditPkgIDMap.begin();	end = m_tEditPkgIDMap.end();
		for(begin; begin != end; begin++)
		{
			UINT8 nChkKey = tDPH._get_id_to_key(begin->first);
			UINT8 nSubID = tDPH._get_id_to_subid(begin->first);

			if(nChkKey != nKey)		continue;

			if(IsExistsIDFromList(tIDList, nSubID))	continue;

			tDelLIst.push_back(begin->first);
		}
	}

	{
		TListIDItor begin, end;
		begin = tDelLIst.begin();	end = tDelLIst.end();
		for(begin; begin != end; begin++)
		{
			m_tEditPkgIDMap.erase(*begin);
		}
	}

	{
		TListIDItor begin, end;
		begin = tIDList.begin();	end = tIDList.end();
		for(begin; begin != end; begin++)
		{
			UINT32 nEditID = ((UINT32)nKey) << 24;
			nEditID += *begin;

			if(m_tEditPkgIDMap.find(nEditID) != m_tEditPkgIDMap.end())	continue;
			m_tEditPkgIDMap[nEditID] = 0;
		}
	}
	return 0;
}

TEMPLATE	_T*			CManagePoBase<_T>::GetEditData()
{
	return &(m_tEditData);
}

TEMPLATE	INT32		CManagePoBase<_T>::GetEditDataID()
{
	return m_nEditDataID;
}

TEMPLATE	INT32		CManagePoBase<_T>::GetEditPkgIDMap(TMapID& tPkgIDMap)
{
	tPkgIDMap = m_tEditPkgIDMap;
	return 0;
}

TEMPLATE	INT32		CManagePoBase<_T>::GetEditPkgIDMap(UINT32 nKey, TMapID& tPkgIDMap)
{
	DB_PO_HEADER tDPH;
	TMapIDItor begin, end;
	begin = m_tEditPkgIDMap.begin();	end = m_tEditPkgIDMap.end();
	for(begin; begin != end; begin++)
	{
		UINT32 nChkKey = tDPH._get_id_to_key(begin->first);
		UINT32 nSubID = tDPH._get_id_to_subid(begin->first);

		if(nChkKey != nKey)	continue;

		tPkgIDMap[nSubID] = begin->second;
	}
	return 0;
}

TEMPLATE	INT32		CManagePoBase<_T>::IsExistEditPkgIDMap(UINT32 nUnitID)
{
	if(m_tEditPkgIDMap.find(nUnitID) == m_tEditPkgIDMap.end())	return 0;
	return 1;
}

TEMPLATE	INT32		CManagePoBase<_T>::AddEditPkgIDTempMap(UINT32 nUnitID)
{
	m_tEditPkgIDTempMap[nUnitID] = 0;
	return 0;
}

TEMPLATE	INT32		CManagePoBase<_T>::DelEditPkgIDTempMap(UINT32 nUnitID)
{
	m_tEditPkgIDTempMap.erase(nUnitID);
	return 0;
}

TEMPLATE	INT32		CManagePoBase<_T>::IsExistEditPkgIDTempMap(UINT32 nUnitID)
{
	if(m_tEditPkgIDTempMap.find(nUnitID) == m_tEditPkgIDTempMap.end())	return 0;
	return 1;
}

TEMPLATE	INT32		CManagePoBase<_T>::CopyEditPkgIDTempMap()
{
	m_tEditPkgIDTempMap = m_tEditPkgIDMap;
	return 0;
}

TEMPLATE	INT32		CManagePoBase<_T>::MergeEditPkgIDTempMap()
{
	TListID tIDList;
	ConvertMapToList(m_tEditPkgIDTempMap, tIDList);
	m_tEditPkgIDTempMap.clear();

	ChgEditPkgIDList(tIDList);
	return 0;
}
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

TEMPLATE	INT32		CManagePoBase<_T>::SetEditDataMap(UINT32 nID)
{
	_T tEditData;
	m_tEditDataMap.clear();
	m_nEditID = 0;

	m_pMapItorBegin = m_tMap.begin();
	m_pMapItorEnd = m_tMap.end();

	for (; m_pMapItorBegin != m_pMapItorEnd; m_pMapItorBegin++)
	{
		if(m_pMapItorBegin->second.tDPH.nPolicyID != nID)
			continue;

		tEditData = m_pMapItorBegin->second;
		tEditData.tDPH.nEditID = ++m_nEditID;
		m_tEditDataMap[tEditData.tDPH.nEditID] = tEditData;
	}
	return m_tEditDataMap.size();
}

TEMPLATE	INT32		CManagePoBase<_T>::AddEditDataMap(_T& data)
{
	data.tDPH.nEditID = ++m_nEditID;
	m_tEditDataMap[data.tDPH.nEditID] = data;
	return m_tEditDataMap.size();
}

TEMPLATE	INT32		CManagePoBase<_T>::EditEditDataMap(_T& data)
{
	m_tEditDataMap[data.tDPH.nEditID] = data;
	return m_tEditDataMap.size();
}

TEMPLATE	INT32		CManagePoBase<_T>::DelEditDataMap(UINT32 nEditID)
{
	m_tEditDataMap.erase(nEditID);
	return m_tEditDataMap.size();
}

TEMPLATE	_T*			CManagePoBase<_T>::FindEditData(UINT32 nEditID)
{
	m_pDataMapItorFind = m_tEditDataMap.find(nEditID);
	if(m_pDataMapItorFind == m_tEditDataMap.end())
		return NULL;

	return &(m_pDataMapItorFind->second);
}

TEMPLATE	INT32		CManagePoBase<_T>::GetEditDataIDList(TListID& tEIDList)
{
	m_pDataMapItorBegin = m_tEditDataMap.begin();
	m_pDataMapItorEnd = m_tEditDataMap.end();

	for (; m_pDataMapItorBegin != m_pDataMapItorEnd; m_pDataMapItorBegin++)
	{
		tEIDList.push_back(m_pDataMapItorBegin->second.tDPH.nEditID);
	}
	return tEIDList.size();
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

TEMPLATE	INT32		CManagePoBase<_T>::ClearEditMMED()
{
	m_tEditMMEDMap.clear();
	m_tEditMMEDTempMap.clear();

	return 0;
}
//-----------------------------------------------------------------------------

TEMPLATE	INT32		CManagePoBase<_T>::SetEditMMED(UINT32 nID)
{
	m_nEditMMEDID = nID;

	_T tEmptyData;
	m_tEditMMED = tEmptyData;

	_T* pData = FindItem(nID);

	if(pData)	SetEditMMED(pData);
	else
	{
		ClearEditMMED();
		MakeEditMMED();
	}

	return 0;
}
//-----------------------------------------------------------------------------

TEMPLATE	INT32		CManagePoBase<_T>::SetEditMMED(_T* pData)
{
	if(pData)
	{
		m_tEditMMED = *pData;
		ClearEditMMED();
		MakeEditMMED();
	}
	return 0;
}
//-----------------------------------------------------------------------------

TEMPLATE	INT32		CManagePoBase<_T>::SetEditMMED(MEM_MB_EDIT_DATA& data)
{
	m_tEditMMEDMap[data.nID] = data;
	m_tEditMMEDTempMap[data.nID] = data;

	return 0;
}
//-----------------------------------------------------------------------------

TEMPLATE	INT32		CManagePoBase<_T>::MakeEditMMED()
{
	return 0;
}
//-----------------------------------------------------------------------------

TEMPLATE	INT32		CManagePoBase<_T>::GetEditMMEDID()
{
	return m_nEditMMEDID;
}
//-----------------------------------------------------------------------------

TEMPLATE	_T*			CManagePoBase<_T>::GetEditMMED()
{
	return &(m_tEditMMED);
}
//-----------------------------------------------------------------------------

TEMPLATE	INT32		CManagePoBase<_T>::GetEditMMEDIDList(TListID& tIDList)
{
	TMapMemMBEditDataItor begin, end;
	begin = m_tEditMMEDMap.begin();		end = m_tEditMMEDMap.end();
	for(begin; begin != end; begin++)
	{
		tIDList.push_back(begin->first);
	}
	return tIDList.size();
}
//-----------------------------------------------------------------------------

TEMPLATE	PMMED		CManagePoBase<_T>::FindEditMMED(UINT32 nID)
{
	TMapMemMBEditDataItor find = m_tEditMMEDMap.find(nID);
	if(find == m_tEditMMEDMap.end())	return NULL;

	return &(find->second);
}
//-----------------------------------------------------------------------------

TEMPLATE	INT32		CManagePoBase<_T>::IsExistEditMMEDTemp(UINT32 nID)
{
	TMapMemMBEditDataItor find = m_tEditMMEDTempMap.find(nID);
	if(find == m_tEditMMEDTempMap.end())	return 0;

	return 1;
}
//-----------------------------------------------------------------------------

TEMPLATE	INT32		CManagePoBase<_T>::AddEditMMEDTemp(MEM_MB_EDIT_DATA& data)
{
	m_tEditMMEDTempMap[data.nID] = data;
	return 0;
}
//-----------------------------------------------------------------------------

TEMPLATE	INT32		CManagePoBase<_T>::EditEditMMEDTemp(MEM_MB_EDIT_DATA& data)
{
	m_tEditMMEDTempMap[data.nID] = data;
	return 0;
}
//-----------------------------------------------------------------------------

TEMPLATE	INT32		CManagePoBase<_T>::DelEditMMEDTemp(UINT32 nID)
{
	m_tEditMMEDTempMap.erase(nID);
	return 0;
}
//-----------------------------------------------------------------------------

TEMPLATE	PMMED		CManagePoBase<_T>::FindEditMMEDTemp(UINT32 nID)
{
	TMapMemMBEditDataItor find = m_tEditMMEDTempMap.find(nID);
	if(find == m_tEditMMEDTempMap.end())	return NULL;

	return &(find->second);
}
//-----------------------------------------------------------------------------

TEMPLATE	INT32		CManagePoBase<_T>::MergeEditMMEDTemp()
{
	TListID tDelList;
	{
		TMapMemMBEditDataItor begin, end;
		begin = m_tEditMMEDMap.begin();	end = m_tEditMMEDMap.end();
		for(begin; begin != end; begin++)
		{
			if(IsExistEditMMEDTemp(begin->first))	continue;

			tDelList.push_back(begin->first);
		}
	}

	{
		TListIDItor begin, end;
		begin = tDelList.begin();	end = tDelList.end();
		for(begin; begin != end; begin++)
		{
			m_tEditMMEDMap.erase(*begin);
		}
	}

	{
		TMapMemMBEditDataItor begin, end;
		begin = m_tEditMMEDTempMap.begin();	end = m_tEditMMEDTempMap.end();
		for(begin; begin != end; begin++)
		{
			PMMED pdata = FindEditMMED(begin->first);
			if(pdata)
			{
				begin->second.nSubID = pdata->nSubID;

				*pdata = begin->second;
			}
			else
			{
				m_tEditMMEDMap[begin->first] = begin->second;
			}
		}
	}
	return 0;
}
//-----------------------------------------------------------------------------

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

TEMPLATE	void		CManagePoBase<_T>::PrintDbgInfo()
{
	return;
}

TEMPLATE	String		CManagePoBase<_T>::GetName(UINT32 nID)
{
	_T* pData = FindItem(nID);
	if(!pData)
		return "";
	return pData->tDPH.strName;
}

TEMPLATE	String		CManagePoBase<_T>::GetHash()
{
	return m_strFullHash;
}

TEMPLATE	PDB_PO_HEADER	CManagePoBase<_T>::GetPoHdr(UINT32 nID)
{
	_T* pData = FindItem(nID);
	if(!pData)
		return NULL;
	return &(pData->tDPH);
}

TEMPLATE	UINT32		CManagePoBase<_T>::GetPoHdrList(TListDBPoHeader& tListDBPoHeader)
{
	TListID tIDList;
	TListIDItor begin, end;
	PDB_PO_HEADER	pDPH = NULL;

	GetItemIDList(tIDList);
	begin = tIDList.begin();	end   = tIDList.end();
	for(; begin != end; begin++)
	{
		pDPH = GetPoHdr(*begin);
		if(!pDPH)
			continue;

		tListDBPoHeader.push_back(*pDPH);
	}

	return 0;
}

TEMPLATE	String		CManagePoBase<_T>::GetHdrHashInfo(_T* pData)
{
	String strHdrHashInfo;

	if(pData == NULL)
	{
		return "";
	}
	strHdrHashInfo = SPrintf("%u,%u,%u,"
							"%s,%s,"
							"%u,%u,%u,"
							"%u,%u,"
							"%u,%u"
							"%u,%u,",
							pData->tDPH.nID, pData->tDPH.nRegDate, pData->tDPH.nSeqNo,
							pData->tDPH.strName.c_str(), pData->tDPH.strDescr.c_str(),
							pData->tDPH.nAdminID, pData->tDPH.nSubAdminLock, pData->tDPH.nTargetLock,
							pData->tDPH.nPolicyID, pData->tDPH.nUnitID,
							pData->tDPH.nNotifyInfoID, pData->tDPH.nExtOption,
							pData->tDPH.nUsedMode, pData->tDPH.tSubIDMap.size());
	return strHdrHashInfo;
}

TEMPLATE	String		CManagePoBase<_T>::GetHdrHashInfoNoLink(_T* pData)
{
	String strHdrHashInfo;
	if(pData == NULL)
	{
		return "";
	}
	strHdrHashInfo = SPrintf("%u,%u,%u,"
		"%s,%s,"
		"%u,%u,%u,"
		"%u,%u,"
		"%u,%u"
		"%u,%u,",
		pData->tDPH.nID, pData->tDPH.nRegDate, pData->tDPH.nSeqNo,
		pData->tDPH.strName.c_str(), pData->tDPH.strDescr.c_str(),
		pData->tDPH.nAdminID, pData->tDPH.nSubAdminLock, pData->tDPH.nTargetLock,
		pData->tDPH.nPolicyID, pData->tDPH.nUnitID,
		pData->tDPH.nNotifyInfoID, pData->tDPH.nExtOption,
		pData->tDPH.nUsedMode, 0);
	return strHdrHashInfo;
}

TEMPLATE	INT32		CManagePoBase<_T>::SetPkt(UINT32 nID, MemToken& SendToken)
{
	return 0;
}

TEMPLATE	INT32		CManagePoBase<_T>::IsMultiUsedUnit(UINT32 nPolicyID, UINT32 nUnitID)
{
	PDB_PO_HEADER pDph = NULL;
	m_pMapItorBegin = m_tMap.begin();
	m_pMapItorEnd = m_tMap.end();
	for(m_pMapItorBegin; m_pMapItorBegin != m_pMapItorEnd; m_pMapItorBegin++)
	{
		pDph = (PDB_PO_HEADER)&(m_pMapItorBegin->second);
		if(pDph->nPolicyID == nPolicyID)
			continue;
		if(pDph->nUnitID == nUnitID)
			return 1;
	}
	return 0;
}
//-----------------------------------------------------------------------------

TEMPLATE	INT32		CManagePoBase<_T>::SetSyncDBMSType(UINT32 nType)
{
	m_nDBSyncChkType = nType;
	return m_nDBSyncChkType;
}
//-----------------------------------------------------------------------------

TEMPLATE	INT32		CManagePoBase<_T>::IsSyncDBMS()
{
	return (m_nDBSyncChkType & m_nDBSyncType);
}
//-----------------------------------------------------------------------------
