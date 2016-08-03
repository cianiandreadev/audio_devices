/*
    Spokes3G.h : All abstract class related to Session, SessionManager and any public interface
*/

#pragma once
#ifndef SPOKES3G
#define SPOKES3G

#include "DeviceManager.h"
#include "SpokesEnums.h"


INTF ICall
{
    virtual int32_t getID()=0;
    virtual void setID(int32_t id)=0;
    virtual int32_t getConferenceID()=0;
    virtual void setConferenceID(int32_t id)=0;
    virtual bool getInConference()=0;
    virtual void setInConference(bool bConference)=0;
private:
    void operator delete(void *);
};
typedef ICall* pCall;

/*! Interface to an object holding the contact data.
*/
INTF IContact
{
    /*! Returns a non-owning pointer to the name of the contact. */
    virtual const wchar_t* getName() const = 0;

    /*! Sets the internal name string to be the same as given pointer.
        \param pName The name to set. If nullptr, name will be set to empty.
    */
    virtual void setName(const wchar_t* pName) = 0;

    /*! Returns a non-owning pointer to the "friendly" name of the contact. */
    virtual const wchar_t* getFriendlyName() const = 0;

    /*! Sets the internal "friendly" name string to be the same as given pointer.
        \param pFName The "friendly" name to set. If nullptr, will be set to empty.
    */
    virtual void setFriendlyName(const wchar_t* pFName) = 0;

    /*! Returns the Id of the contact (which is just some integer value).
    */
    virtual int32_t getID() const = 0;

    /*! Sets the Id of the contact (which is just some integer value).
    */
    virtual void setID(int32_t id) = 0;

    /*! Returns a non-owning pointer to the SIP URL of the contact. */
    virtual const wchar_t* getSipUri() const = 0;

    /*! Sets the internal SIP URL string to be the same as given pointer.
        \param pSip The SIP URL to set. If nullptr, will be set to empty.
    */
    virtual void setSipUri(const wchar_t* pSip) = 0;

    /*! Returns a non-owning pointer to the phone (number as string) of the contact. */
    virtual const wchar_t* getPhone() const = 0;

    /*! Sets the internal phone (number as string) to be the same as given pointer.
        \param pPhone The phone to set. If nullptr, will be set to empty.
    */
    virtual void setPhone(const wchar_t* pPhone) = 0;

    /*! Returns a non-owning pointer to the email address of the contact. */
    virtual const wchar_t* getEmail() const = 0;

    /*! Sets the internal email address string to be the same as given pointer.
        \param pEmail The email address to set. If nullptr, will be set to empty.
    */
    virtual void setEmail(const wchar_t* pEmail) = 0;

    /*! Returns a non-owning pointer to the "work" phone (number as string) of the contact. */
    virtual const wchar_t* getWorkPhone() const = 0;

    /*! Sets the internal "work" phone (number as string) to be the same as given pointer.
        \param pWPhone The "work" phone to set. If nullptr, will be set to empty.
    */
    virtual void setWorkPhone(const wchar_t* pWPhone) = 0;

    /*! Returns a non-owning pointer to the "mobile" phone (number as string) of the contact. */
    virtual const wchar_t* getMobilePhone() const = 0;

    /*! Sets the internal "mobile" phone (number as string) to be the same as given pointer.
        \param pMPhone The "mobile" phone to set. If nullptr, will be set to empty.
    */
    virtual void setMobilePhone(const wchar_t* pMPhone) = 0;

    /*! Returns a non-owning pointer to the "home" phone (number as string) of the contact. */
    virtual const wchar_t* getHomePhone() const = 0;

    /*! Sets the internal "home" phone (number as string) to be the same as given pointer.
        \param pHPhone The "home" phone to set. If nullptr, will be set to empty.
    */
    virtual void setHomePhone(const wchar_t* pHPhone) = 0;

private:
    void operator delete(void *);
};

typedef IContact* pContact;
typedef IContact** ppContact;

struct CallData
{
    int32_t id;
    int32_t conferenceID;
    bool inConference;
    void * callContext;
};

struct ContactData
{
    enum {
        MAX_NAME = 128,
        MAX_URI = 256,
        MAX_PHONE = 64,
        MAX_EMAIL = 64
    };

    wchar_t name[MAX_NAME];
    wchar_t friendlyName[MAX_NAME];
    int32_t id;
    wchar_t sipUri[MAX_URI];
    wchar_t phone[MAX_PHONE];
    wchar_t workPhone[MAX_PHONE];
    wchar_t mobilePhone[MAX_PHONE];
    wchar_t homePhone[MAX_PHONE];   
    wchar_t email[MAX_EMAIL];
};

struct EventArgsOption
{
    enum {
        MAX_OPTION = 64,
        MAX_VALUE = 64,
    };
    char option[MAX_OPTION];
    char value[MAX_VALUE];
};

    
struct CallStateEventArgs
{
    enum {
        MAX_OPTIONS = 32,
        MAX_SOURCE = 128,
        MAX_DEVICE_PATH = 256
    };
    eCallState callState;
    eDeviceEventKind deviceEventkind;
    int numOptions;
    EventArgsOption options[MAX_OPTIONS];
    CallData callId;
    wchar_t callSource[MAX_SOURCE];
	wchar_t callerId[MAX_SOURCE];
    wchar_t devicePath[MAX_DEVICE_PATH];
	double callDuration;
};

struct CallRequestEventArgs
{
    ContactData contact;
};

enum CMResult
{
    CM_RESULT_SUCCESS = 0,
    CM_RESULT_FAIL = 1,
    CM_RESULT_INVALID_ARGUMENT = 2,
    CM_RESULT_INVALID_STATE = 3,
    CM_RESULT_NO_DEVICE = 4,
    CM_RESULT_A2DP_DEVICE = 5,
    CM_RESULT_INVALID_LINETYPE = 6,
	CM_RESULT_NOT_SUPPORTED = 7
};

enum SMResult
{
    SM_RESULT_SUCCESS = 0,
    SM_RESULT_FAIL = 1,
    SM_RESULT_INVALID_ARGUMENT = 2,
    SM_RESULT_ALREADY_REGISTERED = 3,
    SM_RESULT_NOT_FOUND = 4,
    SM_RESULT_NOT_SUPPORTED = 5,
    SM_RESULT_NOT_INITIALIZED = 6
};

typedef CallRequestEventArgs* pCallRequestEventArgs;
  
INTF ICallCommand : public IDisposable
{
    /*! Notify of an incoming call
        *  \param pCall call id for the incoming call
        *  \param pContact contact information for the call
        *  \param tones ring tonecall id for the incoming call
        *  \param route Audio route to Headset or to Speaker
        *  \return CM_RESULT_SUCCESS for success and other codes for failure 
        */
    virtual CMResult incomingCall(pCall callID, pContact contact, eRingTone tones, eAudioRoute route)= 0;

    /*! Notify of an outgoing call
        *  \param pCall call id for the outgoing call
        *  \param pContact contact information for the call
        *  \param route Audio route to Headset or to Speaker
        *  \return CM_RESULT_SUCCESS for success and other codes for failure 
        */
    virtual CMResult outgoingCall(pCall callID, pContact contact, eAudioRoute route)=0;

    /*! Notify that a call has been terminated
        *  \param pCall call id 
        *  \return CM_RESULT_SUCCESS for success and other codes for failure 
        */
    virtual CMResult terminateCall(pCall callID)=0; //Terminated in the GUI

    /*! Notify that a call has been answered (e.g. in the softphone)
        *  \param pCall call id for the answered call
        *  \return CM_RESULT_SUCCESS for success and other codes for failure 
        */
    virtual CMResult answeredCall(pCall callID)=0; // Answered in the GUI

    /*! Notify that a call has been put on hold
        *  \param pCall call id
        *  \return CM_RESULT_SUCCESS for success and other codes for failure 
        */
    virtual CMResult holdCall(pCall callID)=0; // Call held on the GUI

    /*! Notify that a call has been resumed from hold
        *  \param pCall call id 
        *  \return CM_RESULT_SUCCESS for success and other codes for failure 
        */
    virtual CMResult resumeCall(pCall callID)=0; //Call resumed on the GUI

    /*! Use this to notify that an existing call is present,
        *  say, when the softphone starts up
        *  \param pCall call id for the incoming call
        *  \return CM_RESULT_SUCCESS for success and other codes for failure 
        */
    virtual CMResult insertCall(pCall callID, pContact contact)=0; 
        
    /*! Use this to notify that an call is muted in the softphone
        *  \param bMute muted(true) or unmuted(false)
        *  \return CM_RESULT_SUCCESS for success and other codes for failure 
        */
    virtual CMResult muteCall(bool bMute)=0;

    /*! sets the audio route to Speaker or HS
        *  \param pCall call id 
        *  \param route Audio route
        *  \return CM_RESULT_SUCCESS for success and other codes for failure 
        */
    virtual CMResult setAudioRoute(pCall callID, eAudioRoute route)=0;      

    /*! Use this method to make a call tot he given contact using the default softphone
        *  \param pContact contact information for the call
        *  \return CM_RESULT_SUCCESS for success and other codes for failure 
        */
    virtual CMResult makeCall(pContact contact)=0; 

    /*! Use this method to set the conference id of the conference to which
        *  this call belong to, if any
        *  \param callID call id
        *  \return CM_RESULT_SUCCESS for success and other codes for failure 
        */
    virtual CMResult setConferenceId(pCall callID)=0;
private:
    void operator delete(void*);
};

typedef ICallCommand* pCallCommand;
typedef ICallCommand** ppCallCommand;
    
INTF ICallEvents
{
    virtual bool OnCallStateChanged(CallStateEventArgs const& pcscArgs) = 0;
    virtual bool OnCallRequest(CallRequestEventArgs const& pcscArgs) = 0;
private:
    void operator delete(void *);
};
typedef ICallEvents* pCallEvents;
typedef ICallEvents** ppCallEvents;

INTF ISession : public IDisposable
{
    virtual SMResult getSessionId(wchar_t* id, uint32_t len) = 0;
	virtual SMResult getPluginId(int32_t* pluginId) = 0;
    virtual SMResult getPluginName(wchar_t* pName, uint32_t len) = 0;
    virtual SMResult registerCallback(pCallEvents callback) = 0;
    virtual SMResult unregisterCallback(pCallEvents callback) = 0;
    virtual SMResult getCallCommand(ppCallCommand ppCommand) = 0;
    virtual SMResult getCallEvents(ppCallEvents ppEvents) = 0; 		
    virtual SMResult getActiveDevice(ppDevice ppDev)= 0;
    virtual SMResult getActiveDeviceName(wchar_t* pDeviceName, int32_t len) = 0;
    virtual SMResult enableAudio(bool bEnable) = 0;
private:
    void operator delete(void *);
};

typedef ISession* pSession;
typedef ISession** ppSession;

// IUserPreference

INTF IUserPreference
{
    virtual const wchar_t* getMediaPlayerActionIncomingCall() const = 0;
    virtual const wchar_t* mediaPlayerActionCallEnded() const = 0;
    virtual bool getRingPCAndHS() const = 0;
    virtual int32_t getDefaultSoftphone() const = 0;
    virtual int32_t getEscalateToVoiceSoftPhone() = 0;
    virtual bool getKeepLinkUp() const = 0;
    virtual bool getAutoPresence() const = 0;
    virtual const wchar_t* getDonAction() const  = 0;
    virtual const wchar_t* getDoffAction() const = 0;
    virtual bool getSmartLock() const = 0;
	virtual void setMediaPlayerActionIncomingCall(const wchar_t* action) = 0;
	virtual void setMediaPlayerActionCallEnded(const wchar_t* action) = 0;
	virtual void setRingPCAndHS(bool ringBoth) = 0;
	virtual void setDefaultSoftphone(int32_t defaultSP) = 0;
	virtual void setEscalateToVoiceSoftPhone(int32_t etvSP) = 0;
	virtual void setKeepLinkUp(bool keepLink) = 0;
	virtual void setAutoPresence(bool presence) = 0;
	virtual void setDonAction(const wchar_t* action) = 0;
	virtual void setDoffAction(const wchar_t* action) = 0;
    virtual void setSmartLock(bool enable) = 0;
	private:
    void operator delete(void *);
};

#define DON_DOFF_ACTION_DO_NOTHING L"DoNothing"
#define DON_DOFF_ACTION_AVAILABLE L"available"
#define DON_DOFF_ACTION_BUSY L"busy"
#define DON_DOFF_ACTION_DO_NOT_DISTURB L"doNotDisturb"
#define DON_DOFF_ACTION_BE_RIGHT_BACK L"beRightBack"
#define DON_DOFF_ACTION_OFFLINE L"offline"

#define MEDIA_PLAYER_ACTION_DO_NOTHING L"DoNothing"
#define MEDIA_PLAYER_ACTION_PAUSE L"Pause"
#define MEDIA_PLAYER_ACTION_PLAY L"Play"

#define SP_NAME_MAX_LENGTH 512

INTF ICallInfo
{
    virtual int32_t getCallId() = 0;
    virtual bool getSessionId(char * sessionid, int32_t len) = 0;
    virtual bool getSource(wchar_t * source, int32_t len) = 0;
    virtual bool isActive() = 0;
    //TimeSpan Duration { get; }
private:
    void operator delete(void *);
};

// Call Info group used to get information about calls in a group
INTF ICallInfoGroup
{
    /*! Returns a pointer to the call at a given index
    * If there is no call in the group, returns nullptr.
    */
    virtual ICallInfo * getCall(uint32_t index) = 0;

    /*! Returns the number of calls in the group.
        */
    virtual uint32_t numCalls() = 0;

private:
    void operator delete(void *);
};

// CallManager State
INTF ICallManagerState : public IDisposable
{
    virtual bool HasActiveCall() = 0;
    virtual int32_t numberOfCallsOnHold() = 0;
    virtual bool getCalls(ICallInfoGroup** group) = 0;
};
  

INTF ISessionManagerEvents
{
    /*! Notifies on call state changes, returns success status
        */
    virtual bool OnCallStateChanged(CallStateEventArgs const& cseArgs) = 0;

    /*! Notifies on device state changes like device arrival and removal, returns success status
        */
    virtual bool OnDeviceStateChanged(DeviceStateEventArgs const& devArgs) = 0;

private:
    void operator delete(void *);
};

typedef ISessionManagerEvents* pSessionManagerEvents;
typedef ISessionManagerEvents** ppSessionManagerEvents;
    
INTF ISessionManager
{
    /*! Registers and returns a session object for a given plug-in name 
    *  \param pPluginname Name of the plug-in
    *  \return SM_RESULT_SUCCESS for success and other codes for failure
    */
    virtual SMResult registerSession(const wchar_t* pPluginName, ppSession ppSess) NOEXCEPT = 0;
        
    /*! Unregisters a session 
    *  \param pSess denotes the session to unregister
    *  \return SM_RESULT_SUCCESS for success and other codes for failure
    */
    virtual SMResult unregisterSession(pSession pSess) NOEXCEPT = 0;
        
    /*! Sets the plugin status
    *  \param pluginId Id of the plug-in
    *  \param pluginState state of the plug-in
    *  \return SM_RESULT_SUCCESS for success and other codes for failure
    */
    virtual SMResult setPluginStatus(int32_t pluginId, ePluginState pluginState) NOEXCEPT = 0;

/*! Gets the plugin active status.
    *  \param pluginId Plug-in id
    *  \param bActive output parameter that gets the active state of the plug-in
    *  \return SM_RESULT_SUCCESS for success and other codes for failure
    */
    virtual SMResult getActive(int32_t pluginId, bool& bActive) NOEXCEPT = 0;

    /*! Sets an option to a given value
    *  \param eDOption Name of the session manager option in eSessionMgrOption
    *  \param lValue  value of the option
    *  \return SM_RESULT_SUCCESS for success and other codes for failure
    */
    virtual SMResult setOption(eSessionMgrOption eDOption, int32_t lValue) NOEXCEPT = 0;

    /*! 
    *  NOT SUPPORTED: Gets the value for a given option
    */
    virtual SMResult getOption(eSessionMgrOption eDOption, int32_t* plValue, int16_t iMaxLength, int16_t* piLength) NOEXCEPT = 0;  

    /*! Registers a call back for CallStateChanged and DeviceStateChanged notifications
    *  \param callback  Session manager events callback
    *  \return SM_RESULT_SUCCESS for success and other codes for failure
    */
    virtual SMResult registerCallback(pSessionManagerEvents callback) NOEXCEPT = 0;

    /*! UnRegisters a call back
    *  \param callback  Session manager events callback
    *  \return SM_RESULT_SUCCESS for success and other codes for failure
    */
    virtual SMResult unregisterCallback(pSessionManagerEvents callback) NOEXCEPT = 0;

    /*! Gets the user preference.
    *  \param userPref output pointer to receive IUserPreference
    *  \return SM_RESULT_SUCCESS for success and other codes for failure
    */
    virtual SMResult getUserPreference(IUserPreference** userPref) NOEXCEPT = 0;

    /*! Gets the current call manager state.
    *  \param callManagerState output pointer to receive callManagerState
    *  \return SM_RESULT_SUCCESS for success and other codes for failure
    */
    virtual SMResult getCallManagerState(ICallManagerState ** callManagerState) NOEXCEPT = 0;

    /*! Gets the current active device.
    *  \param ppDev output pointer to receive active device
    *  \return SM_RESULT_SUCCESS for success and other codes for failure
    */
    virtual SMResult getActiveDevice(ppDevice ppDev) NOEXCEPT = 0;

	/*! Gets the device given its path.
	*  \param devicePath is the path to the device
	*  \param ppDev output pointer to receive device for the path provided
	*  \return SM_RESULT_SUCCESS for success and other codes for failure
	*/
	virtual SMResult getDeviceForPath(const wchar_t* devicePath, ppDevice ppDev) NOEXCEPT = 0;

private:
    void operator delete(void *);
};

typedef ISessionManager* pSessionManager;
typedef ISessionManager** ppSessionManager;


//SessionManager interface
     
struct PluginProperties
{
    enum 
    {
        MAX_NAME = 64,
        MAX_TYPE = 32,
    };

	int32_t pluginId;
    wchar_t pluginName[MAX_NAME];
    wchar_t className[MAX_NAME];
    wchar_t pluginType[MAX_TYPE];
    wchar_t pluginFeatureType[MAX_TYPE];
    wchar_t processName[MAX_NAME];
    bool enabled;
    bool active;
	bool canBeDefault;
	bool canEscalateToVoice;
};


extern "C" {
    /*!  
    *  Obtain instance of SessionManager interface
    *  \param ppSessionMgr Output parameter which gets filled with pointer to the SessionManager
    *  \return 0 for success or error code for failure
    */
    SMResult DllExport getSessionManager(ppSessionManager ppSessionMgr);

    /*!
        Initializes the Spokes Runtime environment. Should be called before any other function of the
        Spokes Interface. Should be called only once during the exectution of the program (process).
    */
    int DllExport InitSpokesRuntime(void);

    /*!
        Shuts down (deinitializes) the Spokes Runtime environment. Should be called at the end of
        the execution of the program (process). No other function of the Spokes interface should be
        called after calling this function.
    */
    void DllExport ShutDownSpokesRuntime(void);

}


#endif  
