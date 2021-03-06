/*
 * Copyright (c) 2007-2009 BLStream Oy.
 *
 * This file is part of OpenVideoHub.
 *
 * OpenVideoHub is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * OpenVideoHub is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with OpenVideoHub; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */

#include "emTubeTimeOutTimer.h"

CEmTubeTimeOutTimer* CEmTubeTimeOutTimer::NewL( MTimeOutObserver& aObserver )
	{
	CEmTubeTimeOutTimer* self = CEmTubeTimeOutTimer::NewLC( aObserver );
	CleanupStack::Pop(self);
	return self;
	}

CEmTubeTimeOutTimer* CEmTubeTimeOutTimer::NewLC( MTimeOutObserver& aObserver )
	{
	CEmTubeTimeOutTimer* self = new (ELeave) CEmTubeTimeOutTimer( aObserver );
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;	
	}

CEmTubeTimeOutTimer::CEmTubeTimeOutTimer( MTimeOutObserver& aObserver ) : CTimer( EPriorityHigh ),
																		  iObserver( aObserver )
	{
	}

void CEmTubeTimeOutTimer::ConstructL()
	{
	CTimer::ConstructL();
	CActiveScheduler::Add( this );
	}
   
void CEmTubeTimeOutTimer::After( TTimeIntervalMicroSeconds32 aInterval, TInt aMode )
	{
	iMode = aMode;
	if( IsActive() )
		Cancel();
	CTimer::After( aInterval );
	}

CEmTubeTimeOutTimer::~CEmTubeTimeOutTimer()
	{
	Cancel();
	}

void CEmTubeTimeOutTimer::RunL()
	{
	iObserver.TimerExpired( iMode );
	}
