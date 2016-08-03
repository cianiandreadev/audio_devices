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
 * \brief       This file contains interfaces of the IDeviceListener hierarchy.
 * 
 */

#pragma once
#if !defined INC_IDEVICELISTENER
#define      INC_IDEVICELISTENER


#include "DMTypes.h"


/*!
    \brief IDeviceListenerCallback interface
    The receiver of DeviceListener notifications should implement this interface,
    and register with IDeviceListener::registerCallback, in order to receive
    the notifications.
    */
INTF IDeviceListenerCallback
{
    /** Called on headset button pressed detection */
    virtual void onHeadsetButtonPressed(DeviceListenerEventArgs const&) = 0;
    /** Called on headset state changed detection */
    virtual void onHeadsetStateChanged(DeviceListenerEventArgs const&) = 0;
    /** Called on base button pressed detection */
    virtual void onBaseButtonPressed(DeviceListenerEventArgs const&) = 0;
    /** Called on base state changed detection */
    virtual void onBaseStateChanged(DeviceListenerEventArgs const&) = 0;
    /** Called on ATD state changed detection */
    virtual void onATDStateChanged(DeviceListenerEventArgs const&) = 0;
};


INTF IDeviceListenerQuery;

/*! 
 *  \brief IDeviceListener interface  
 *  The IDeviceListener interface provides a consistent interface across all Plantronics devices so applications
 *  need not handle device-specific events and commands. Some Plantronics devices support multiple (VOIP,
 *  PTSN, and mobile ) interfaces
 */
INTF IDeviceListener
{
    /** Returns the interface query pointer */
    virtual IDeviceListenerQuery *getQuery() NOEXCEPT = 0;

    /*! Rings the device
     *  \param enable Tells device to enable or disable ringing
     */
    virtual DMResult ring(bool enable) NOEXCEPT = 0;

    /*! Gets the current audio state of the device
     * \param state The current state will be written to this reference
     * \return indicates the result of the operation
     */
    virtual DMResult getAudioState(eAudioState &state) const NOEXCEPT = 0;
    
    /*! Sets the current audio state of the device
     *  \param value Audio state to be set
     * \return indicates the result of the operation
     */
    virtual DMResult setAudioState(eAudioState value) NOEXCEPT = 0;
    
    /*! Gets mute state of device
     *  \param muteTo this reference will assigned: true if device is in mute state, false otherwise
     * \return indicates the result of the operation
     */
    virtual DMResult getMute(bool &mute) const NOEXCEPT = 0;
    
    /*! Sets mute state of device
     *  \param value Mute state which will be set
     */
    virtual DMResult setMute(bool value) NOEXCEPT = 0;
    
    /*! Gets auto answer functionality state
     *  \param enabled A boolean 'Auto answer functionality enabled' will be assigned to this reference
     *  \return indicates the result of the operation
     */
    virtual DMResult getIntellistand(bool &enabled) const NOEXCEPT = 0;
    
    /*! Sets auto answer functionality state
     *  \param value State of auto answer functionality which will be set
     */
    virtual DMResult setIntellistand(bool value) NOEXCEPT = 0;
    
    /*! On a device that supports multiple interfaces, gets the current audio mixer state
     *  \param state A bitwise combination of eMuteState flags which reflect audio mixer state on device will be assigned to this reference.
     *  \return indicates the result of the operation
     */
    virtual DMResult getAudioMixerState(int32_t &state) const NOEXCEPT = 0;
    
    /*! On a device that supports multiple interfaces, sets the current audio mixer state
     *  \param value A bitwise combination of eMuteState flags that define an audio mixer state which will be set
     *  \return DM_RESULT_SUCCESS on success
     */
    virtual DMResult setAudioMixerState(int32_t value) NOEXCEPT = 0;

    /*! On a device that supports multiple interfaces, gets the default interface
     *  \param line The default interface will be written to this reference
     *  \return indicates result of operation
     */
    virtual DMResult getDefaultLine(eLineType &line) const NOEXCEPT = 0; 
    
    /*! On a device that supports multiple interfaces, sets the default interface
     *  \param value Default interface which will be set
     *  \return DM_RESULT_SUCCESS on success
     */
    virtual DMResult setDefaultLine(eLineType value) NOEXCEPT = 0;

    /*! When a call is active, indicates that the device is handling a call
     *  \param bOn The host application can use inCall(true) to notify a connected Plantronics device that it is handling a VOIP call. inCal (false) lets the device know that the VOIP call is ended.
     */
    virtual DMResult inCall(bool bOn) NOEXCEPT = 0;    
        
    /*! On a device that supports multiple interfaces, allows you to set the specified interface as active
     *  \param lineType Interface (PSTN, VOIP, or Mobile)
     *  \param bActive bActive (true) will set the interface active and bring up the radio link for the specified LineType. bActive (false) will drop the radio link for the specific LineType
     *  \return result of operation.
     */
    virtual DMResult setActiveLink(eLineType lineType, bool bActive) NOEXCEPT = 0;
    
    /*! On a device that supports multiple interfaces, allows you to check whether the specified interface is active
     *  \param lineTpe Interface for which to check if line is active. Possible values for lineType are (PSTN, VOIP, or Mobile)
     *  \param active Boole will be assigned to this referecne - true if line is active, false otherwise
     *  \return indicates result of operation
     */
    virtual DMResult isLineActive(eLineType lineType, bool &active) const NOEXCEPT = 0;
    
    /*! On a device that supports multiple interfaces, puts the specified on hold or off (resume)
     *  \param lineType Interface (PSTN, VOIP, or Mobile)
     *  \param bHold true puts interface on hold, false puts interface off hold
     *  \return result of operation
     */
    virtual DMResult hold(eLineType lineType, bool bHold) NOEXCEPT = 0;
    
    /*! On a device that supports multiple interfaces, gets the current hold state for the specified interface
     *  \param lineType Interface (PSTN, VOIP, or Mobile)
     *  \param hold Current hold state for the specified interface will be assigned to this reference
     *  \return indicates result of operation
     */
    virtual DMResult getHoldState(eLineType lineType, bool &hold) NOEXCEPT = 0;
    
    /*! Gets the current audio link state
     *  \param state Current audio link state will be written to this reference
     *  \return indicates result of operation
     */
    virtual DMResult getAudioLinkState(eAudioLinkState &state) const NOEXCEPT = 0;
 
    /*! On a mobile device, specifies the audio location (AG or headset)
     *  \param location Location (headset or handset) will be written to this reference
     *  \return indicates result of operation
     */
    virtual DMResult getAudioLocation(eAudioLocation &location) const NOEXCEPT = 0;
    
    /*! Register callback interface for receiving notifications */
    virtual DMResult registerCallback(IDeviceListenerCallback*) NOEXCEPT = 0;

    /*! UnRegister (a previously registered) callback interface, to stop receiving notifications. */
    virtual DMResult unregisterCallback(IDeviceListenerCallback*) NOEXCEPT = 0;

private:
    void operator delete(void *p);
};
typedef IDeviceListener* pDeviceListener;
typedef IDeviceListener** ppDeviceListener;


/*! \brief IDisplayDeviceCall
    Interface for getting and setting call parameters for calls on Display devices.
    */
INTF IDisplayDeviceCall : public IDisposable
{
    /*! Returns the session ID assigned to the call */
    virtual DM_GUID getSessionId() const = 0;

    /*! Sets the session ID assigned to the call */
    virtual DMResult setSessionId(DM_GUID guid) = 0;

    /*! Returns the call ID assigned to the call */
    virtual int32_t getCallId() const = 0;

    /*! Sets the call ID assigned to the call */
    virtual DMResult setCallId(int32_t callId) = 0;

    /*! Returns the call state */
    virtual DDCallState getCallState() const = 0;

    /*! Sets the call state */
    virtual DMResult setCallState(DDCallState callState) = 0;

    /*! Returns the ID of the softphone of the call */
    virtual DDSoftphoneID getSoftphoneID() const = 0;

    /*! Sets the ID of the softphone of the call */
    virtual DMResult setSoftphoneID(DDSoftphoneID spID) = 0;

    /*! Returns the caller ID string of the call */
    virtual wchar_t const *getCallerId() const = 0;

    /*! Sets the caller ID string of the call */
    virtual DMResult setCallerId(wchar_t const *callerId) = 0;

    /*! Returns the friendly name string of the call */
    virtual wchar_t const *getFriendlyName() const = 0;

    /*! Sets the friendly name string of the call */
    virtual DMResult setFriendlyName(wchar_t const *name) = 0;

private:
    void operator delete(void *p);
};


/// Cross-platform date and time
struct DM_DateTime {
    /// The full year A.D. number
    uint16_t year; 
    /// The number of the month in a year, 1-12
    uint8_t month;
    /// The number of day in a month, 1-31
    uint8_t day;
    /// The number of hour in a day, 0-23
    uint8_t hour;
    /// The number of minute in a hour, 0-59
    uint8_t minute;
    /// The number of seconds in a minute, 0-59 in general, can be more due to leap seconds
    uint8_t secs;
};


/*! \brief IDisplayDeviceListener
    The interface for Display device handling of Device Listener
*/
INTF IDisplayDeviceListener
{
    /** Sets the current locale ID on the device */
    virtual DMResult setLocale(uint32_t lcid) = 0;

    /** Sets the presence (and softphone) indicator on the device */
    virtual DMResult setPresence(DDSoftphoneID spID, DDPresence presence) = 0;

    /** Sets the default softphone the device. The status of the default softphone/call is 
        displayed on the device and kept in sync with the softphone.
        */
    virtual DMResult setDefaultSoftphone(DDSoftphoneID spID) = 0;

    /** Sets the date and time for the device. It will be displayed on the device
        according to time/date format.
        */
    virtual DMResult setDateTime(DM_DateTime const& dt) = 0;

    /** Sets the date and time format for the device. The actual format is read from the
        system settings for the given locale.
        */
    virtual DMResult setDateTimeFormat(uint32_t lcid) = 0;

    /** Sets the softphone name for the device */
    virtual DMResult setSoftphoneName(DDSoftphoneID spID, wchar_t const *spName) = 0;

    /** Sets the state of (all active) calls for the device. These will be displayed on
        the device.
    */
    virtual DMResult setMultiCallState(int32_t nCount, IDisplayDeviceCall **ddCall) = 0;

    /** Returns the softphone ID of the current call for the device */
    virtual DDSoftphoneID getSoftphoneID() = 0;

    /** Retursne the string of the name with which to make a call */
    virtual wchar_t const *getMakeCallName() = 0;

private:
    void operator delete(void *p);
};

INTF IDoubloonListener
{
    virtual void simulateMuteEvent(bool bFlag) NOEXCEPT = 0;
    virtual void simulateMakeBreakEvent(bool bFlag) NOEXCEPT = 0;

private:
    void operator delete(void *p);
};

/** This interface is used to obtain an interface from IDeviceListener hierarchy.
    It is used because dynamic_cast<> doesn't work across DLL (.so) boundaries.
*/
INTF IDeviceListenerQuery
{
    virtual bool query(IDeviceListener **p) = 0;
    virtual bool query(IDisplayDeviceListener **p) = 0;
    virtual bool query(IDoubloonListener **p) = 0;

private:
    void operator delete(void *p);
};


#endif // !defined INC_IDEVICELISTENER
