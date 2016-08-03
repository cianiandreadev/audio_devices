#pragma once
/*!
* \author	Plantronics, Inc.
* \version	1.0
*
* \copyright
*				Copyright (c) 2012 Plantronics, Inc. All rights reserved.
*				This code is confidential and proprietary information belonging to
*				Plantronics, Inc. and may not be copied, modified or distributed
*				without the express written consent of Plantronics, Inc.
*
* \brief		This file contains interfaces of the IUpdateNotifier and
*				IUpdateNotifierListener.
*				Its purpose is to enable clients to subscribe and get update notifications.
*/


#include "CommonTypes.h"

INTF IUpdateNotifierListener
{
	/** Notification event
	*/
	virtual void ReceiveNotification(const wchar_t* const& msg) = 0;
};


INTF IUpdateNotifier
{
	/** Register for notifications
	*/
	virtual void Subscribe(IUpdateNotifierListener *p) = 0;

	/** UnRegister notifications listener
	*/
	virtual void CancelSubscription(IUpdateNotifierListener *p) = 0;

	/**	Set notificationInterval.
	*/
	virtual void SetNotifyInterval(const char *updID, uint64_t notificationInterval) = 0;

};