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

#ifndef MEM_VULN_RST_H_4D39CDDB_CTL_E289_4d56_9F98_FE42776F4467
#define MEM_VULN_RST_H_4D39CDDB_CTL_E289_4d56_9F98_FE42776F4467

typedef struct _mem_vuln_patch
{
	_mem_vuln_patch()
	{
		nID				= 0;
	}

	void _set_int(UINT32 nKey, UINT32 nValue)
	{
		tIntMap[nKey] = nValue;
	}

	INT32 _get_int(UINT32 nKey)
	{
		TMapIDItor find = tIntMap.find(nKey);
		if(find == tIntMap.end())	return -1;

		return find->second;
	}

	void _set_str(UINT32 nKey, String strValue)
	{
		tStrMap[nKey] = strValue;
	}

	String _get_str(UINT32 nKey)
	{
		TMapIDStrItor find = tStrMap.find(nKey);
		if(find == tStrMap.end())	return "";

		return find->second;
	}

	UINT32		nID;
	TMapID		tIntMap;
	TMapIDStr	tStrMap;

}MEM_VULN_RST, *PMEM_VULN_RST;

typedef list<MEM_VULN_RST>				TListMemVulnRst;
typedef TListMemVulnRst::iterator		TListMemVulnRstItor;

typedef map<UINT32, MEM_VULN_RST>		TMapMemVulnRst;
typedef TMapMemVulnRst::iterator		TMapMemVulnRstItor;

#endif //MEM_VULN_RST_H_4D39CDDB_CTL_E289_4d56_9F98_FE42776F4467



