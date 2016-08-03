//
//  EventSink.h
//  PlantronicsTest
//
//  Created by Andrea Ciani on 26/07/16.
//  Copyright © 2016 Andrea Ciani. All rights reserved.
//

#ifndef EventSink_h
#define EventSink_h

#import "PlantronicsWrapperC.h"

// create sink for receiving session events
class CallEventSink : public ICallEvents
{
private:
    ISession* m_session;
public:
    CallEventSink() {}
    CallEventSink( ISession* session) : m_session( session ) {	m_session->registerCallback( this ); }
    virtual ~CallEventSink()								 {	m_session->unregisterCallback( this ); }
    
    virtual bool OnCallStateChanged(CallStateEventArgs const& pcscArgs)	{ PlantronicsWrapperPrint("OnCallStateChanged Session event"); return true; }
    virtual bool OnCallRequest(CallRequestEventArgs const& pcscArgs)	{ PlantronicsWrapperPrint("OnCallRequest Session event"); return true; }
    void operator delete(void *p) { ::operator delete(p); }
};
// create sink for receiving session manager events
class SessionManagerEventSink : public ISessionManagerEvents
{
private:
    ISessionManager* m_sessionManager;
public:
    SessionManagerEventSink() {}
    SessionManagerEventSink( ISessionManager* sessionManager) : m_sessionManager( sessionManager )	{ m_sessionManager->registerCallback( this ); }
    virtual ~SessionManagerEventSink()																{ m_sessionManager->unregisterCallback( this ); }
    
    virtual bool OnCallStateChanged(CallStateEventArgs const& cseArgs)		{ PlantronicsWrapperPrint("OnCallStateChanged Session Manager event"); return true; }
    virtual bool OnDeviceStateChanged(DeviceStateEventArgs const& devArgs)
    {
        PlantronicsWrapperPrint("OnDeviceStateChanged Session Manager event");
        if (devArgs.deviceState == DEV_STATE_ADDED)
        {
            PlantronicsWrapperAttachDeviceListener();
        }
        else if (devArgs.deviceState == DEV_STATE_REMOVED)
        {
            PlantronicsWrapperRemoveDeviceListener();
        }
        return true;
    }
    void operator delete(void *p) { ::operator delete(p); }
};
// create sink for receiving device listener events
class DeviceListenerEventSink : public IDeviceListenerCallback
{
public:
    DeviceListenerEventSink() { PlantronicsWrapperPrint("DeviceListenerEventSink constructor"); }
    // IDeviceListenerCallback implementations
    virtual void onHeadsetButtonPressed(DeviceListenerEventArgs const &args) { PlantronicsWrapperPrint("onHeadsetButtonPressed Device Listener event"); PlantronicsWrapperHeadsetButtonPressed(args); }
    virtual void onHeadsetStateChanged(DeviceListenerEventArgs const &args) { PlantronicsWrapperPrint("onHeadsetStateChanged Device Listener event"); PlantronicsWrapperHeadsetStateChanged(args); }
    
    virtual void onBaseButtonPressed(DeviceListenerEventArgs const &args) { PlantronicsWrapperPrint("onBaseButtonPressed Device Listener event"); }
    virtual void onBaseStateChanged(DeviceListenerEventArgs const &args) { PlantronicsWrapperPrint("onBaseStateChanged Device Listener event"); }
    virtual void onATDStateChanged(DeviceListenerEventArgs const &args) {PlantronicsWrapperPrint("onATDStateChanged Device Listener event"); }
};

#endif /* EventSink_h */
