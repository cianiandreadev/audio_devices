/*!
 * \author  	Plantronics, Inc.
 * \version	    1.0
 *
 * \copyright 
 *              Copyright � 2012 Plantronics, Inc. All rights reserved.
 *              This code is confidential and proprietary information belonging to 
 *              Plantronics, Inc. and may not be copied, modified or distributed
 *              without the express written consent of Plantronics, Inc.
 *
 * \brief       This file contains interfaces of the IDeviceEvents hierarchy (for subscribing
 *              to notifications) and the corresponding IDeviceEventCallbacks interfaces for receiving
 *              the notifications.
 * 
 */

#pragma once
#if !defined INC_IDEVICEEVENTS
#define      INC_IDEVICEEVENTS


#include "DMTypes.h"


INTF IDeviceEventsQuery;

/*! 
 *  \brief DeviceEventsCallback interface  
 *  To receive Device Events inherit this class, and then register via IDeviceEvents
 */
INTF IDeviceEventsCallback
{
    /** Called when a talk button press is detected */
    virtual void onTalkButtonPressed(DeviceEventArgs const& args) = 0;
    /** Called when a button press is detected */
    virtual void onButtonPressed(DeviceEventArgs const& args) = 0;
    /** Called when device mute state change is detected */
    virtual void onMuteStateChanged(DeviceEventArgs const& args) = 0;
    /** Called when a audio state change is detected */
    virtual void onAudioStateChanged(DeviceEventArgs const& args) = 0;
    /** Called when flash on a button is detected */
    virtual void onFlashButtonPressed(DeviceEventArgs const& args) = 0;
    /** Called when a "smart" button press is detected. 
        This in general means a "long" button pressed.
        */
    virtual void onSmartButtonPressed(DeviceEventArgs const& args) = 0;

private:
    void operator delete(void *);
};
typedef IDeviceEventsCallback* pDeviceEventsCallback;
typedef IDeviceEventsCallback** ppDeviceEventsCallback;

/** Provides functions to register for notifications via IDeviceEventsCallback
    and the function to receive and parse/handle the report received from the device.
*/
INTF IDeviceEvents
{
    /** Returns the query pointer */
    virtual IDeviceEventsQuery *getQuery() NOEXCEPT = 0;

    /** Registers device events receiver */
    virtual DMResult regCbDeviceEvents(IDeviceEventsCallback*) NOEXCEPT = 0;

    /** Unregisters device events receiver */
    virtual DMResult unregCbDeviceEvents(IDeviceEventsCallback*) NOEXCEPT = 0;

    /*!  Parses input report received from the device
     *   \param reportBuffer report byte array
     *   \param length report buffer length
     *   \return DM_RESULT_SUCCESS on success, DM_RESULT_FAIL otherwise.
     */
    virtual DMResult setInputReport(uint8_t const * reportBuffer, int32_t length) NOEXCEPT = 0;

private:
    void operator delete(void *);
};
typedef IDeviceEvents* pDeviceEvents;
typedef IDeviceEvents** ppDeviceEvents;


/** To receive Device Events "Ext" inherit this class, and then register via IDeviceEventsExt */
INTF IDeviceEventsExtCallback
{
    /** Called when the status of the battery on the device changes */
    virtual void onBatteryLevelChanged(BatteryLevelEventArgs const& args) = 0;
    /** Called when the state of the headset changes */
    virtual void onHeadsetStateChanged(HeadsetStateEventArgs const& args) = 0;

private:
    void operator delete(void *);
};

/** Provides functions to register for notifications via IDeviceEventsExtCallback. */
INTF IDeviceEventsExt
{
    /** Registers device events "ext" receiver */
    virtual DMResult regCbDeviceEventsExt(IDeviceEventsExtCallback*) NOEXCEPT = 0;
    /** Unregisters device events "ext" receiver */
    virtual DMResult unregCbDeviceEventsExt(IDeviceEventsExtCallback*) NOEXCEPT = 0;

private:
    void operator delete(void *);
};


/** To receive Base Events inherit this class, and then register via IBaseEvents */
INTF IBaseEventsCallback
{
    /** Called when a base event is detected */
    virtual void onBaseEventReceived(BaseEventArgs const& args) = 0;

private:
    void operator delete(void *);
};

/** Provides functions to register for notifications via IBaseEventsCallback. */
INTF IBaseEvents
{
    /** Registers base events receiver */
    virtual DMResult regCbBaseEvents(IBaseEventsCallback*) NOEXCEPT = 0;
    /** Unregisters base events receiver */
    virtual DMResult unregCbBaseEvents(IBaseEventsCallback*) NOEXCEPT = 0;

private:
    void operator delete(void *);
};


/** To receive HID Pipe Events inherit this class, and then register via IHIDPipeEvents */
INTF IHIDPipeEventsCallback
{
    /** Called when a HID Pipe Event (message) is detected (received) */
    virtual void onHIDPipeEventReceived(HIDPipeEventArgs const& args) = 0;

private:
    void operator delete(void *);
};

/** Provides functions to register for notifications via IHIDPipeEventsCallback. */
INTF IHIDPipeEvents
{
    /** Registers HID pipe events receiver */
    virtual DMResult regCbHIDPipeEvents(IHIDPipeEventsCallback*) NOEXCEPT = 0;
    /** Unregisters HID pipe events receiver */
    virtual DMResult unregCbHIDPipeEvents(IHIDPipeEventsCallback*) NOEXCEPT = 0;

private:
    void operator delete(void *);
};


/** To receive Mobile presence Events inherit this class, and then register via IMobilePresenceEvents */
INTF IMobilePresenceEventsCallback
{
    virtual void onPresenceChanged(MobilePresenceEventArgs const& args) = 0;

private:
    void operator delete(void *);
};

/** Provides functions to register for notifications via IHIDPipeEventsCallback. */
INTF IMobilePresenceEvents
{
    /** Registers Mobile presence events receiver */
    virtual DMResult regCbMobilePresenceEvents(IMobilePresenceEventsCallback*) NOEXCEPT = 0;
    /** Unregisters Mobile presence events receiver */
    virtual DMResult unregCbMobilePresenceEvents(IMobilePresenceEventsCallback*) NOEXCEPT = 0;

private:
    void operator delete(void *);
};


/** To receive MOC Events inherit this class, and then register via IMOCEvents */
INTF IMOCEventsCallback
{
    /** Called when MOC state change is detected */
    virtual void onMOCStateChanged(MOCEventArgs const& args) = 0;
    /** Called when MOC hook change is detected */
    virtual void onMOCHookChanged(MOCEventArgs const& args) = 0;
    /** Called when MOC report (message) is detected */
    virtual void onMOCReportReceived(MOCEventArgs const& args) = 0;

private:
    void operator delete(void *);
};

/** Provides functions to register for notifications via IMOCEventsCallback. */
INTF IMOCEvents
{
    /** Registers MOC events receiver */
    virtual DMResult regCbMOCEvents(IMOCEventsCallback* callback) NOEXCEPT = 0;
    /** Unregisters MOC events receiver */
    virtual DMResult unregCbMOCEvents(IMOCEventsCallback* callback) NOEXCEPT = 0;

private:
    void operator delete(void *);
};


/** To receive MOC Events "ext" (display data) inherit this class, and then register 
    via IMOCEventsExt
    */
INTF IMOCEventsExtCallback
{
    /** Called when MOC display data is received */
    virtual void onMOCDisplayDataReceived(MOCDisplayEventArgs const& args) = 0;

private:
    void operator delete(void *);
};

/** Provides functions to register for notifications via IMOCEventsExtCallback. */
INTF IMOCEventsExt
{
    /** Registers MOC events "ext" (display data) receiver */
    virtual DMResult regCbMOCEventsExt(IMOCEventsExtCallback* callback) NOEXCEPT = 0;
    /** Unregisters MOC events "ext" (display data) receiver */
    virtual DMResult unregCbMOCEventsExt(IMOCEventsExtCallback* callback) NOEXCEPT = 0;

private:
    void operator delete(void *);
};


/** To receive Audio sense Events inherit this class, and then register via IAudioSenseEvents */
INTF IAudioSenseEventsCallback
{
    /** Called when audio sense change is detected */
    virtual void onAudioSenseChanged(AudioSenseEventArgs const& args) = 0;

private:
    void operator delete(void *);
};

/** Provides functions to register for notifications via IAudioSenseCallback. */
INTF IAudioSenseEvents
{
    /** Registers Audio sense events receiver */
    virtual DMResult regCbAudioSenseEvents(IAudioSenseEventsCallback* callback) NOEXCEPT = 0;
    /** Unregisters Audio sense events receiver */
    virtual DMResult unregCbAudioSenseEvents(IAudioSenseEventsCallback* callback) NOEXCEPT = 0;

private:
    void operator delete(void *);
};


/** To receive CI reports */
INTF IAudioIntelligenceEventsCallback
{
    /** Called when the AAL Acoustic Incident Report Recieved */
    virtual void onAALAcousticIncidentReportRecieved(AALAcousticIncidentReportEventArgs const& args) = 0;
    /** Called when the AAL Acoustic Incident Report Recieved */
    virtual void onAALTWAReportRecieved(AALTWAReportEventArgs const& args) = 0;
    /** Called when the Conversation Dynamics Report Recieved */
    virtual void onConversationDynamicsReportRecieved(ConversationDynamicsReportEventArgs const& args) = 0;
    
private:
    void operator delete(void *);
};

/** Provides functions to register for notifications via IAudioIntelligenceEventsCallback. */
INTF IAudioIntelligenceEvents
{
    /** Registers audio intelligence events receiver */
    virtual DMResult regCbAudioIntelligenceEvents(IAudioIntelligenceEventsCallback*) NOEXCEPT = 0;
    /** Unregisters audio intelligence events receiver */
    virtual DMResult unregCbAudioIntelligenceEvents(IAudioIntelligenceEventsCallback*) NOEXCEPT = 0;
    
private:
    void operator delete(void *);
};

/** This interface is used to obtain an interface from IDeviceEvents hierarchy.
    It is used because dynamic_cast<> doesn't work across DLL (.so) boundaries.
*/
INTF IDeviceEventsQuery
{
    virtual bool query(IDeviceEvents **p) NOEXCEPT = 0;
    virtual bool query(IDeviceEventsExt **p) NOEXCEPT = 0;
    virtual bool query(IBaseEvents **p) NOEXCEPT = 0;
    virtual bool query(IHIDPipeEvents **p) NOEXCEPT = 0;
    virtual bool query(IMobilePresenceEvents **p) NOEXCEPT = 0;
    virtual bool query(IMOCEventsCallback **p) NOEXCEPT = 0;
    virtual bool query(IMOCEvents **p) NOEXCEPT = 0;
    virtual bool query(IMOCEventsExtCallback **p) NOEXCEPT = 0;
    virtual bool query(IMOCEventsExt **p) NOEXCEPT = 0;
    virtual bool query(IAudioSenseEventsCallback **p) NOEXCEPT = 0;
    virtual bool query(IAudioSenseEvents **p) NOEXCEPT = 0;
    virtual bool query(IAudioIntelligenceEventsCallback **p) NOEXCEPT = 0;
    virtual bool query(IAudioIntelligenceEvents **p) NOEXCEPT = 0;

private:
    void operator delete(void *);
};

#endif // !defined INC_IDEVICEEVENTS
