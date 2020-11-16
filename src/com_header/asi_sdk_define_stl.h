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



#ifndef     ASI_GLOBAL_STL_DEFINE_H_938EF200_F60B_452A_BD30_A10E8507EDCC
#define     ASI_GLOBAL_STL_DEFINE_H_938EF200_F60B_452A_BD30_A10E8507EDCC

#define		STL_USING_ALL

//------------------------------------------------------------------------------

//////////////////////////////////////////////////////////////////////
// handy define to include all stuff
//////////////////////////////////////////////////////////////////////

#ifdef STL_USING_ALL

#define STL_USING_MAP
#define STL_USING_VECTOR
#define STL_USING_LIST
#define STL_USING_STRING
#define STL_USING_STREAM
#define STL_USING_MEMORY
#define STL_USING_STACK

#endif


//////////////////////////////////////////////////////////////////////
// STL neccessary declaration for map
//////////////////////////////////////////////////////////////////////

#ifdef STL_USING_MAP

#include <set>

#include <map>

#endif


//////////////////////////////////////////////////////////////////////
// STL neccessary declaration for vector
//////////////////////////////////////////////////////////////////////

#ifdef STL_USING_VECTOR

#include <vector>

#endif


//////////////////////////////////////////////////////////////////////
// STL neccessary declaration for list
//////////////////////////////////////////////////////////////////////

#ifdef STL_USING_LIST

#include <list>

#endif


//////////////////////////////////////////////////////////////////////
// STL neccessary declaration for string
//////////////////////////////////////////////////////////////////////

#ifdef STL_USING_STRING

#include <string>

#endif


//////////////////////////////////////////////////////////////////////
// STL neccessary declaration for streams
//////////////////////////////////////////////////////////////////////

#ifdef STL_USING_STREAM

#include <sstream>
#include <fstream>

#endif


//////////////////////////////////////////////////////////////////////
// STL neccessary declaration for memory
//////////////////////////////////////////////////////////////////////

#ifdef STL_USING_MEMORY

#include <memory>

#endif


//////////////////////////////////////////////////////////////////////
// STL neccessary declaration for stack
//////////////////////////////////////////////////////////////////////

#ifdef STL_USING_STACK

#include <stack>

#endif


//////////////////////////////////////////////////////////////////////
// verify proper use of macros
//////////////////////////////////////////////////////////////////////

#if defined STL_USING_MAP || defined STL_USING_VECTOR || defined STL_USING_LIST || defined STL_USING_STRING || defined STL_USING_STREAM || defined STL_USING_ASSERT || defined STL_USING_MEMORY || defined STL_USING_STACK
using namespace std;
#else
#pragma message( "Warning: You included <STL.H> without using any STL features!" )
#endif

//------------------------------------------------------------------------------

typedef pair<UINT32, UINT32>			T64Key;

typedef list<UINT32>            		TListID;
typedef TListID::iterator       		TListIDItor;
typedef TListID::reverse_iterator  		TListIDRItor;

typedef list<UINT64>            		TListID64;
typedef TListID64::iterator       		TListID64Itor;
typedef TListID64::reverse_iterator		TListID64RItor;

typedef list<String>            		TListStr;
typedef TListStr::iterator      		TListStrItor;
typedef list<TListStr>					TListListStr;
typedef TListListStr::iterator			TListListStrItor;
typedef list<TListID>					TListListID;
typedef TListListID::iterator			TListListIDItor;
typedef vector<UINT32>					TVectID;
typedef TVectID::iterator				TVectIDItor;
typedef set<INT32>						TSetID;
typedef set<INT32>::iterator			TSetIDItor;
typedef map<UINT32, UINT32>     		TMapID;
typedef TMapID::iterator        		TMapIDItor;
typedef TMapID::reverse_iterator        TMapIDRItor;
typedef TMapID							*PTMapID;
typedef map<string, string>     		TMapSTR;
typedef TMapSTR::iterator       		TMapSTRItor;
typedef map<String, String>     		TMapStr;
typedef TMapStr::iterator       		TMapStrItor;
typedef map<String, UINT32>    		TMapStrID;
typedef TMapStrID::iterator     		TMapStrIDItor;
typedef map<UINT32, String>			TMapIDStr;
typedef TMapIDStr::iterator				TMapIDStrItor;
typedef map<String, UINT32>			TMapSortName;
typedef TMapSortName::iterator			TMapSortNameItor;
typedef map<UINT32, TListID>			TMapIDList;
typedef TMapIDList::iterator			TMapIDListItor;
typedef map<UINT32, TListStr>			TMapIDListStr;
typedef TMapIDListStr::iterator			TMapIDListStrItor;
typedef map<UINT32, TMapID>				TMapIDMap;
typedef TMapIDMap::iterator				TMapIDMapItor;
typedef TMapIDMap::reverse_iterator		TMapIDMapRIter;
typedef map<UINT32, TMapIDMap>			TMapIDMapMap;
typedef TMapIDMapMap::iterator			TMapIDMapMapItor;   
typedef map<UINT32, TMapStrID>			TMapIDMapStrID;
typedef TMapIDMapStrID::iterator		TMapIDMapStrIDItor;
typedef map<UINT32, TMapStr>			TMapIDMapStr;
typedef TMapIDMapStr::iterator			TMapIDMapStrItor;
typedef map<String, TListID>			TMapStrList;
typedef TMapStrList::iterator			TMapStrListItor;
typedef map<String, TListStr>			TMapStrListStr;
typedef TMapStrListStr::iterator		TMapStrListStrItor;
typedef map<String, TMapID>			TMapStrMapID;
typedef TMapStrMapID::iterator			TMapStrMapIDItor;
typedef map<UINT32, TMapStrMapID>		TMapIDMapStrMapID;
typedef TMapIDMapStrMapID::iterator		TMapIDMapStrMapIDItor;   

typedef struct _TMapStrMapStrMapID
{
	map<String, TMapStrMapID>				tMap;
}stlMapStrMapStrMapID;
typedef map<String, TMapStrMapID>::iterator	TMapStrMapStrMapIDItor;

typedef struct _TMapIDMapStrMapStrMapID
{
	map<UINT32, stlMapStrMapStrMapID>		tMap;
}stlMapIDMapStrMapStrMapID;
typedef map<UINT32, stlMapStrMapStrMapID>::iterator	TMapIDMapStrMapStrMapIDItor;   

typedef map<UINT32, TVectID>			TMapIDVect;
typedef TMapIDVect::iterator			TMapIDVectItor;

typedef list<StringW>					TListStrW;
typedef TListStrW::iterator    		 	TListStrWItor;
typedef map<String, UINT32>    			TMapStrID;
typedef TMapStrID::iterator     		TMapStrIDItor;

typedef map<UINT64, UINT64>	     		TMapID64;
typedef TMapID64::iterator        		TMapID64Itor;
typedef TMapID64::reverse_iterator 		TMapID64RItor;
typedef map<String, UINT64>	   		TMapStrID64;
typedef TMapStrID64::iterator        	TMapStrID64Itor;
typedef TMapStrID64::reverse_iterator 	TMapStrID64RItor;
typedef map<INT64, String>		  		TMapID64Str;
typedef TMapID64Str::iterator        	TMapID64StrItor;
typedef TMapID64Str::reverse_iterator 	TMapID64StrRItor;

typedef multimap<INT64, String>			TMultiMapID64Str;
typedef TMultiMapID64Str::iterator			TMultiMapID64StrItor;
typedef TMultiMapID64Str::reverse_iterator 	TMultiMapID64StrRItor;

typedef map<T64Key, TListID>			TMapID64List;
typedef TMapID64List::iterator			TMapID64ListItor;
typedef map<UINT64, TListStr>			TMapID64ListStr;
typedef TMapID64ListStr::iterator		TMapID64ListStrItor;
typedef map<UINT64, TMapStr>			TMapID64MapStr;
typedef TMapID64MapStr::iterator		TMapID64MapStrItor;
typedef map<UINT64, TMapStrID>			TMapID64MapStrID;
typedef TMapID64MapStrID::iterator		TMapID64MapStrIDItor;
typedef map<UINT64, TMapStrID>			TMapID64MapStrID;
typedef TMapID64MapStrID::iterator		TMapID64MapStrIDItor;
typedef map<UINT64, TMapStrID64>		TMapID64MapStrID64;
typedef TMapID64MapStrID64::iterator	TMapID64MapStrID64Itor;
typedef map<UINT64, TMapID64>	   		TMapID64MapID64;
typedef TMapID64MapID64::iterator       TMapID64MapID64Itor;
	

typedef map<T64Key, UINT32>				TMapKey64ID;
typedef TMapKey64ID::iterator			TMapKey64IDItor;
typedef map<T64Key, TListID>			TMapKey64IDList;
typedef TMapKey64IDList::iterator		TMapKey64IDListItor;

typedef map<T64Key, String>			TMapKey64Str;
typedef TMapKey64Str::iterator			TMapKey64StrItor;

typedef list<T64Key>					TListKey64;
typedef TListKey64::iterator			TListKey64Itor;

typedef pair<String, UINT32>			TStrIDKey;
typedef map<TStrIDKey, UINT32>			TMapKeyStrID;
typedef TMapKeyStrID::iterator			TMapKeyStrIDItor;
typedef TMapKeyStrID::reverse_iterator	TMapKeyStrIDRItor;


typedef map<UINT32, UINT64>				TMapDBFKey;
typedef TMapDBFKey::iterator			TMapDBFKeyItor;
typedef TMapDBFKey::reverse_iterator	TMapDBFKeyRItor;

typedef list<PVOID>            			TListPVOID;
typedef TListPVOID::iterator     		TListPVOIDItor;
typedef TListPVOID::reverse_iterator    TListPVOIDRItor;

typedef map<UINT32, PVOID>	    		TMapPVOID;
typedef TMapPVOID::iterator      		TMapPVOIDItor;
typedef TMapPVOID::reverse_iterator		TMapPVOIDRItor;

typedef map<PVOID, UINT32>	    		TMapPVOIDID;
typedef TMapPVOIDID::iterator      		TMapPVOIDIDItor;
typedef TMapPVOIDID::reverse_iterator	TMapPVOIDIDRItor;

typedef map<T64Key, PVOID>	    			TMap64KeyPVOID;
typedef TMap64KeyPVOID::iterator      		TMap64KeyPVOIDItor;
typedef TMap64KeyPVOID::reverse_iterator	TMap64KeyPVOIDRItor;

typedef map<PVOID, TListPVOID>	   				TMapPVOIDListPVOID;
typedef TMapPVOIDListPVOID::iterator			TMapPVOIDListPVOIDItor;
typedef TMapPVOIDListPVOID::reverse_iterator	TMapPVOIDListPVOIDRItor;

typedef map<PVOID, TMapPVOID>	   				TMapPVOIDMapPVOID;
typedef TMapPVOIDMapPVOID::iterator				TMapPVOIDMapPVOIDItor;
typedef TMapPVOIDMapPVOID::reverse_iterator		TMapPVOIDMapPVOIDRItor;

typedef map<PVOID, TMapPVOIDID>	   				TMapPVOIDMapPVOIDID;
typedef TMapPVOIDMapPVOIDID::iterator			TMapPVOIDMapPVOIDIDItor;
typedef TMapPVOIDMapPVOIDID::reverse_iterator	TMapPVOIDMapPVOIDIDRItor;

typedef map<UINT32, TMapKey64ID>	   		TMapIDMapKey64;
typedef TMapIDMapKey64::iterator			TMapIDMapKey64Itor;
typedef TMapIDMapKey64::reverse_iterator	TMapIDMapKey64RItor;

typedef map<String, PVOID>					TMapStrKeyPVOID;
typedef TMapStrKeyPVOID::iterator			TMapStrKeyPVOIDItor;
typedef TMapStrKeyPVOID::reverse_iterator	TMapStrKeyPVOIDRItor;

typedef union _int32_union
{
	struct
	{
		UINT8 type, type_value, hour, min;
	}cell;
	UINT32 all;
}INT32_UNION;
//------------------------------------------------------------------------------

typedef union _u64_schedule
{
	_u64_schedule()
	{
		all = 0;
	}
	struct
	{
		UINT8 type, value, hour, min;
		UINT8 ext_type, ext_value, ext_hour, ext_min;
	}U8;

	struct
	{
		UINT16 type_16, value_16, hour_16, min_16;
	}U16;

	struct
	{
		UINT32 all_low;
		UINT32 all_high;
	}U32;

	UINT64  all;
	
}U64_SCHEDULE, *PU64_SCHEDULE;
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

typedef struct _id_value
{
	_id_value()
	{
		nID		= 0;
		nValue	= 0;
	} 
	_id_value(const UINT32 a, UINT32 b)
	{
		nID		= a;
		nValue 	= b;
		return;
	}

	UINT32	nID;
	UINT32	nValue;
}ID_VALUE, *PID_VALUE;

typedef vector<ID_VALUE>				TVectIDValue;
typedef TVectIDValue::iterator			TVectIDValueItor;
typedef TVectIDValue::reverse_iterator	TVectIDValueRItor;

typedef list<ID_VALUE>					TListIDValue;
typedef TListIDValue::iterator			TListIDValueItor;
typedef TListIDValue::reverse_iterator	TListIDValueRItor;

typedef map<UINT32, ID_VALUE>			TMapIDValue;
typedef TMapIDValue::iterator			TMapIDValueItor;
typedef TMapIDValue::reverse_iterator	TMapIDValueRItor;
//------------------------------------------------------------------------------

typedef struct _id_name
{
	_id_name()
	{
		nID		= 0;
		strName	= "";
	} 
	_id_name(const UINT32 a, String b)
	{
		nID			= a;
		strName 	= b;
		return;
	}

	UINT32	nID;
	String	strName;
}ID_NAME, *PID_NAME;

typedef vector<ID_NAME>					TVectIDName;
typedef TVectIDName::iterator			TVectIDNameItor;
typedef TVectIDName::reverse_iterator	TVectIDNameRItor;

typedef list<ID_NAME>					TListIDName;
typedef TListIDName::iterator			TListIDNameItor;
typedef TListIDName::reverse_iterator	TListIDNameRItor;

typedef map<UINT32, ID_NAME>			TMapIDName;
typedef TMapIDName::iterator			TMapIDNameItor;
typedef TMapIDName::reverse_iterator	TMapIDNameRItor;
//------------------------------------------------------------------------------

typedef struct _name_value
{
	_name_value()
	{
		nValue	= 0;
	}
	_name_value(String a, UINT32 b)
	{
		strName = a;
		nValue	= b;
	}
	String	strName;
	UINT32	nValue;
}NAME_VALUE, *PNAME_VALUE;

typedef vector<NAME_VALUE>				 	TVectNameValue;
typedef TVectNameValue::iterator			TVectNameValueItor;
typedef TVectNameValue::reverse_iterator	TVectNameValueRItor;
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//sort function

class com_sort_id_value{
public:
	bool    operator()(ID_VALUE a, ID_VALUE b) const
	{
		if( (a.nValue) > (b.nValue))	return true;
		return false;
	}
};
//------------------------------------------------------------------------------

class com_sort_name_value{
public:
	bool    operator()(NAME_VALUE a, NAME_VALUE b) const
	{
		if( (a.nValue) > (b.nValue))	return true;
		return false;
	}
};
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------


#endif      //ASI_GLOBAL_STL_DEFINE_H_938EF200_F60B_452A_BD30_A10E8507EDCC
