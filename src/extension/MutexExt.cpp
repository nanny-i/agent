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


#include "stdafx.h"
#include "com_struct.h"
#include "MutexExt.h"


CMutexExt::CMutexExt()
{
	pthread_mutex_init(&m_mutex, NULL);
}


CMutexExt::~CMutexExt()
{
	pthread_mutex_destroy(&m_mutex);
}


int CMutexExt::Lock()
{
	pthread_mutex_lock (&m_mutex);
	return 1;
}


int CMutexExt::UnLock()
{
	pthread_mutex_unlock (&m_mutex);
	return 1;
}

LONG CMutexExt::InterlockedExchangeAdd(volatile LONG *pnAddend, LONG nValue)
{
	LONG nRetVal = 0;
	if(pnAddend != NULL)
	{
		pthread_mutex_lock (&m_mutex);
		*pnAddend += nValue;
		nRetVal = *pnAddend;
		pthread_mutex_unlock (&m_mutex);	
	}
	return nRetVal;
}

LONG CMutexExt::InterlockedExchange(volatile LONG *pnTarget, LONG nValue)
{
	LONG nRetVal = 0;
	if(pnTarget != NULL)
	{
		pthread_mutex_lock (&m_mutex);
		*pnTarget = nValue;
		nRetVal = *pnTarget;
		pthread_mutex_unlock (&m_mutex);	
	}
	return nRetVal;
}

