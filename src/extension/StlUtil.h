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


#ifndef _AS_STL_H__
#define	_AS_STL_H__

extern INT32	IsExistsIDFromMap(TMapID& tIDMap, UINT32 nID);
extern INT32	IsExistsIDFromList(TListID& tIDList, UINT32 nID);

extern VOID	ConvertListToMap(TListID& tIDList, TMapID& tIDMap);
extern VOID	ConvertMapToList(TMapID& tIDMap, TListID& tIDList);
extern VOID	ChangeMapKeyValue(TMapID& tOrIDMap, TMapID& tChgIDMap);
extern VOID	AppandMapToMap(TMapID& tFromIDMap, TMapID& tToIDMap);
extern VOID	AppandListToList(TListID& tFromIDList, TListID& tToIDList);
extern VOID	AppandListToMap(TListID& tFromIDList, TMapID& tToIDMap);
extern VOID	AppandMapToList(TMapID& tFromIDMap, TListID& tToIDList);
extern INT32	RemoveListID(TListID& tIDList, UINT32 nID);
extern INT32	CompareMapID(TMapID& tAMap, TMapID& tBMap);
extern INT32	CompareMapID64(TMapID64& tAMap, TMapID64& tBMap);
extern INT32	CompareList(TListID& tAList, TListID& tBList);
extern INT32	CompareListChgMap(TListID& tAList, TListID& tBList);



#endif //_AS_STL_H__