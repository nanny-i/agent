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


#ifndef ASI_SDK_SS2_USING_AFC_HEADER_15BE18C4_D543_413E_96F8_61C24AD45985
#define	ASI_SDK_SS2_USING_AFC_HEADER_15BE18C4_D543_413E_96F8_61C24AD45985

//-----------------------------------------------------------------------------------------------

#ifdef ASI_SDK_SS2_USING_AFC_ALL

#define ASI_SDK_SS2_USING_AFC_DLL_NAI

#endif

#ifdef ASI_SDK_SS2_USING_AFC_DDK_ALL

#define ASI_SDK_SS2_USING_AFC_DLL_EPS_APP

#endif

//-----------------------------------------------------------------------------------------------

#ifdef ASI_SDK_SS2_USING_AFC_DLL_NAI

	#include	"ASINAIDLLUtil.h"
	
#endif //ASI_SDK_SS2_USING_AFC_DLL_NAI
//-----------------------------------------------------------------------------------------------

#ifdef ASI_SDK_SS2_USING_AFC_DLL_EPS_APP

#include	"asiepsappdllutil.h"

#endif //ASI_SDK_SS2_USING_AFC_DLL_EPS_APP
//-----------------------------------------------------------------------------------------------

#endif