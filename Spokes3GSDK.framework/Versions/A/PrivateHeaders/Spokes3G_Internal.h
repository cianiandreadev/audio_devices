/*
    Spokes3G_Internal.h : Spokes3G internal entities exposed to PLT-manufactured plugins
*/

#pragma once
#ifndef SPOKES3G_INTERNAL
#define SPOKES3G_INTERNAL

#include "Spokes3G.h"
#include "SpokesEnums.h"
#include "LogWriterProxyType.h"
#include "cpp/CppUtility.h"
#include <string>

#include "ProcWatchTypes.h"
#include "IConnectedDevice.h"

#ifdef __APPLE__
    #define SPOKES_APP_ID       "8161beca-7ece-4b26-9e20-1b415e3b9991"
    #define SPOKES_APP_SECRET   "6936f8b6-e307-41ad-bf9f-371bef2a5107"
#else
    #define SPOKES_APP_ID       "f81d4fae-7dec-11d0-a765-00a0c91e6bf6"
    #define SPOKES_APP_SECRET   "6b51995b-70c0-4e8d-9eb3-78ecf9d4dd05"
#endif

#define SPOKES_APP_NAME "Plantronics Hub"
#define SPOKES_PROP_FILE "Spokes.prop"
#define PLT_VENDOR_ID "PLT"
#define SPOKES_VERSION "3.4"
#define WMI_PROVIDER_ID "eddfb9ba-47be-41b9-8071-92d46c1a5bb7"

enum eSessionManagerState
{
	SESSION_MANAGER_STATE_INITIALIZED,
	SESSION_MANAGER_STATE_UNINITIALIZED
};

typedef enum SpokesLogLevel
{
	UNDEFINED,
	OFF,
	LOW,
	MEDIUM,
	HIGH,
	VERBOSE
} eSpokesLogLevel;

// TODO: update enum to better reflect needs
typedef enum PluginStateExt
{
	PLUGIN_STATE_UNKNOWN		= 0, 
	PLUGIN_STATE_RUNNING		= PLUGIN_RUNNING,			// Soft Phone process is running
	PLUGIN_STATE_ACTIVE			= PLUGIN_ACTIVE,			// Plugin is attached to SP API
	PLUGIN_STATE_USER_SIGNIN	= PLUGIN_USER_SIGNIN,		// User is signed in to SP
	PLUGIN_STATE_USER_SIGNOUT	= PLUGIN_USER_SIGNOUT,		// User is signed out from SP
	PLUGIN_STATE_NOT_ACTIVE		= PLUGIN_NOT_ACTIVE,		// Plugin is detached from SP API
	// internal enums
	PLUGIN_STATE_LOADED = 6,								// Plugin is loaded in memory
	PLUGIN_STATE_INITIALIZED = 7,							// Plugin is initialized
	PLUGIN_STATE_EXIT = 8,									// Plugin is de-initialized
	PLUGIN_STATE_UNLOADED = 9								// Plugin is unloaded from memory
} ePluginStateExt;

enum class ePluginAction
{
	PLUGIN_ATTACH,
	PLUGIN_DETACH
};

/*structure contains  information regarding plugin state change */
struct PluginEventArgs
{
    int32_t pluginId;
	ePluginStateExt state;
};

struct PluginActionArgs
{
	int32_t pluginId;
	ePluginAction action;
};

struct PluginMetadata
{
	enum {
        MAX_VERSION_SIZE = 24,
		MAX_PLUGIN_TYPE = 24,
		MAX_FILE_PATH = 254
    };
	char pluginVersion[MAX_VERSION_SIZE];
	char libraryPath[MAX_FILE_PATH];
	char pluginType[MAX_PLUGIN_TYPE];
	ePluginStateExt state;
	bool inCall;
	bool installed;
	bool active;
	std::wstring softphoneVersion;
	bool canBeDefault;
	bool canEscalateToVoice;

	int32_t pluginID;
};

namespace PluginId
{
	static const int32_t UNKNOWN = 0;
	static const int32_t AVAYA_ONE_X_COMMUNICATOR = 1000;
	static const int32_t AVAYA_ONE_X_AGENT = 1100;
	static const int32_t AVAYA_IP_SOFTPHONE = 1200;
	static const int32_t AVAYA_IP_AGENT = 1300;
	static const int32_t CIPC = 1400;
	static const int32_t CSF = 1500;
	static const int32_t NEC = 1700;
	static const int32_t CISCO_WEBEX = 1800;
	static const int32_t SHORTEL_COMMUNICATOR = 2000;
	static const int32_t LYNC2010 = 2100;
	static const int32_t SKYPE = 2200;
	static const int32_t WMP = 2300; 
	static const int32_t WINAMP = 2400;
	static const int32_t ITUNES = 2500;
	static const int32_t COM_SERVER = 2600;
	static const int32_t REST = 2700;
	static const int32_t LYNC2013 = 2800;
	static const int32_t SWYX = 2900;
    static const int32_t AVAYA_AURA_AGENT_DESKTOP = 3000;
	static const int32_t CISCO_JABBER = 3100;    
	static const int32_t AVAYA_COMMUNICATOR = 3200;
    static const int32_t COMMON_PLUGIN = 3300;
	static const int32_t AVAYA_ACA = 3400;
	static const int32_t BROADSOFT_UC_ONE = 3500;

	// Ideally, this should be responsibility of Session Manager
	// who is always aware of max plugin id value
	static int32_t generateId()
	{
		// Should be updated with highest new ids when added 
        static int32_t currentVal = BROADSOFT_UC_ONE + 5000;

		currentVal += 100;
		return currentVal;
	}
}

namespace PluginName
{
	static const std::wstring Undefined = L"";
	static const std::wstring AvayaIPAgent = L"Avaya IP Agent";
	static const std::wstring AvayaIPSoftphone = L"Avaya IP Softphone";
	static const std::wstring AvayaOneXAgent = L"Avaya one-X Agent";
	static const std::wstring AvayaOneXCommunicator = L"Avaya one-X Communicator";
	static const std::wstring CiscoIPCommunicator = L"Cisco IP Communicator";
	static const std::wstring CiscoUCClientsCSF = L"Cisco UC Clients (CSF)";
	static const std::wstring MicrosoftOfficeCommunicator = L"Microsoft OC/Lync";
	static const std::wstring NECSP350 = L"NEC SP350";
	static const std::wstring Rest = L"Rest";
	static const std::wstring COM_SERVER = L"COM Server";
	static const std::wstring ShoreTelCommunicator = L"ShoreTel Communicator";
	static const std::wstring Skype = L"Skype";
	static const std::wstring MicrosoftLync2013 = L"Microsoft Lync 2013";
	static const std::wstring Webex = L"Cisco WebEx Connect";
	static const std::wstring ITunes = L"iTunes";
	static const std::wstring Wmp = L"Windows Media Player";
	static const std::wstring Winamp = L"Winamp";
	static const std::wstring Swyx = L"SwyxIt! Softphone";
    static const std::wstring AvayaAuraAgentDesktop = L"Avaya Aura Agent Desktop";
	static const std::wstring CiscoJabber = L"Cisco Jabber";
    static const std::wstring CommonPlugin = L"Common Features";
	static const std::wstring AvayaCommunicator = L"Avaya Communicator";
	static const std::wstring AvayaACA = L"Avaya Communicator for Microsoft Lync";
	static const std::wstring BroadsoftUCOne = L"BroadSoft UC-One";
}

namespace PluginExecutable
{
#ifdef __APPLE__
	static const std::wstring AvayaIPAgent = L"ipagent";
	static const std::wstring AvayaIPSoftphone = L"ipsoftphone";
	static const std::wstring AvayaOneXAgent = L"onexagentui";
	static const std::wstring AvayaOneXCommunicator = L"Avaya one-X Communicator";
	static const std::wstring CiscoIPCommunicator = L"communicatork9";
	static const std::wstring CiscoUCClientsCSF = L"cucsf";
	static const std::wstring MicrosoftOfficeCommunicator = L"communicator";
	static const std::wstring NECSP350 = L"clientphone32";
	static const std::wstring ShoreTelCallManager = L"pcm";
	static const std::wstring ShoreTelCommunicator = L"shoretel";
	static const std::wstring Skype = L"Skype";
	static const std::wstring MicrosoftLync2013 = L"Microsoft Lync";
	static const std::wstring Webex = L"connect";
	static const std::wstring ITunes = L"iTunes";
	static const std::wstring Wmp = L"wmplayer";
	static const std::wstring Winamp = L"winamp";
	static const std::wstring Swyx = L"clmgr";
	static const std::wstring AvayaAuraAgentDesktop = L"CCAD";
	static const std::wstring CiscoJabber = L"Jabber";
	static const std::wstring CUCILync = L"CUCILync";
	static const std::wstring AvayaACA = L"LyncAddin";
	static const std::wstring AvayaACA2013 = L"Lync2013Addin";
	static const std::wstring CommunicatorForLync2010 = L"CommunicatorForLync2010";
	static const std::wstring CommunicatorForLync2013 = L"CommunicatorForLync2013";
	static const std::wstring BroadsoftUCOne = L"Communicator";
#else
	static const std::wstring AvayaIPAgent = L"IpAgent";
	static const std::wstring AvayaIPSoftphone = L"ipsoftphone";
	static const std::wstring AvayaOneXAgent = L"OneXAgentUI";
	static const std::wstring AvayaOneXCommunicator = L"onexcui";
	static const std::wstring CiscoIPCommunicator = L"communicatork9";
	static const std::wstring CiscoUCClientsCSF = L"cucsf";
	static const std::wstring MicrosoftOfficeCommunicator = L"communicator";
	static const std::wstring NECSP350 = L"ClientPhone32";
	static const std::wstring ShoreTelCommunicator = L"ShoreTel";
	static const std::wstring Skype = L"Skype";
	static const std::wstring MicrosoftLync2013 = L"lync";
	static const std::wstring Webex = L"connect";
	static const std::wstring ITunes = L"iTunes";
	static const std::wstring Wmp = L"wmplayer";
	static const std::wstring Winamp = L"winamp";
	static const std::wstring Swyx = L"CLMgr";
    static const std::wstring AvayaAuraAgentDesktop = L"CCAD";
	static const std::wstring CiscoJabber = L"CiscoJabber";
	static const std::wstring CUCILync = L"CUCILync";
	static const std::wstring AvayaCommunicator = L"AvayaCommunicator";
	static const std::wstring AvayaACA = L"LyncAddin";
	static const std::wstring AvayaACA2013 = L"Lync2013Addin";
	static const std::wstring CommunicatorForLync2010 = L"CommunicatorForLync2010";
	static const std::wstring CommunicatorForLync2013 = L"CommunicatorForLync2013";
	static const std::wstring BroadsoftUCOne = L"Communicator";

#endif
}

namespace PluginType
{
	static const std::wstring Softphone = L"Softphone";
	static const std::wstring Media = L"Media";
	static const std::wstring Service = L"Service";
}

/*Interface that user need to extend if he wants to receive Plugin state changed events*/
INTF ISessionManagerEventsExt
{
	/*event fired whenever plugin state is changed*/
	virtual void onPluginStateChanged( PluginEventArgs const& args) = 0;
	/*event fired whenever call control is changed*/
	virtual void onCallControlChanged( bool const& enabled ) = 0;
};

INTF ISessionManagerPluginActionEvents
{
	/*event fired whenever there is an action for a plugin */
	virtual void onPluginAction(PluginActionArgs const &args) = 0;
};

/** Interface for receiving notifications on device arrival and removal. */
INTF ISessionManagerIntDevEvents
{
    /** This method will be called on device arrival (plug-in). The path of the
        device may be used to get an IDevice interface to it.
        @param path The system path of the device
        */
    virtual void onDeviceArrival(wchar_t const * const& path) = 0;

    /** This method will be called on device removal (plug-out). The path of the
        device may be used to identify the device and link to the arrival of that
        same device.
        @param path The system path of the device
        */
    virtual void onDeviceRemoval(wchar_t const * const& path) = 0;
};

/*! 
 *  \brief Internal Session Manager interface
 *  Exposes internal session manager functionality
 */
INTF ISessionManagerInt 
{
	/*!	
	 * Register PLT manufactured plugin
	 * \param pluginName Plugin name
	 * \param pluginId Plugin id
	 * \param ppSession Output pointer to newly created session
	 * \return SM_RESULT_SUCCESS for success and other codes for failure
	 */
	virtual SMResult registerSession(const wchar_t* pluginName, int32_t pluginId, ppSession ppSession) NOEXCEPT = 0;

	/*!	
	 *	Register for plugin and session manager state events
	 *  \param callback object that needs to be subscribed on events
	 *  \return operation result code
	 */
	virtual SMResult regCbPluginEvents(ISessionManagerEventsExt* callback) NOEXCEPT = 0 ;

	/*!
	 *  Unregister from receiving plugin and session manager state events
	 *  \param callback object that needs to be unsubscribed from events
	 *  \return operation result code
	 */
    virtual SMResult unregCbPluginEvents(ISessionManagerEventsExt* callback) NOEXCEPT = 0 ;

	virtual SMResult regPluginActionEvents(ISessionManagerPluginActionEvents *callback) NOEXCEPT = 0;
	virtual SMResult unregPluginActionEvents(ISessionManagerPluginActionEvents *callback) NOEXCEPT = 0;

	/*!
	 *  Get plugin properties 
	 *	\param pluginId Id of plugin for which we are querying for Properties
	 *  \param prop returns Plugin Properties 
	 *	\return operation result code
	 */
	virtual SMResult GetPluginProperties(int32_t pluginId, PluginMetadata& prop) NOEXCEPT = 0;

	/*!
	 *  Loads plugin into memory (if previously unloaded) and call Init 
	 *	\param pluginId Id of plugin that needs to be loaded
	 *	\return operation result code
	 */
	virtual SMResult LoadPlugin( int32_t pluginId ) NOEXCEPT = 0;

	/*!
	 *  Loads plugin library into memory (if previously unloaded) and call Init on every plugin 
	 *	\param path path to 
	 *	\return operation result code
	 */
	virtual SMResult LoadLibfile( const std::string& path) NOEXCEPT = 0;

	/*!
	*   Sets plugin paths
	*   \param plugin_paths Collection of plugin paths
	*/
	virtual void SetPluginPaths(std::vector<std::wstring> const &plugin_paths) NOEXCEPT = 0;

	/*!
	*   Gets plugin paths
	*	\return Collection of plugin paths
	*/
	virtual std::vector<std::wstring> const &GetPluginPaths() NOEXCEPT = 0;

	/*!
	 *  Call Exit on plugin, and unload from memory if this was last plugin which was disabled in library
	 *	\param pluginId Id of plugin that needs to be unloaded
	 *	\return operation result code
	 */
	virtual SMResult UnloadPlugin( int32_t pluginId ) NOEXCEPT = 0;

	/*!
	 *  Fire OnCallRequest event on Session that is registered by plugin with "softphone" name
	 *	\param softphone Id of plugin for which session we want to make call
	 *	\param contact Contact that initiated call
	 *	\return operation result code
	 */
	virtual SMResult MakeCall(int32_t softphone, const pContact contact ) NOEXCEPT = 0;

	/*!
	 *  Returns list of all devices that are currently connected
	 *	\param devices returns list of devices that are currently connected on machine. User owns interface and must release it by calling Release
	 *	\return operation result code
	 */
	virtual SMResult getDevices(IDeviceGroup** devices) NOEXCEPT = 0;

	/*! Gets first device that matches specified device path
     *  \param devicePath HID device path
     *  \param ppDev Pointer to the IDevice which will be filled with device if found, or nullptr if device is not found
     *  \return DM_RESULT_SUCCESS if device is found, DM_RESULT_NOT_FOUND if device was not found, DM_RESULT_ILLEGAL_ARGUMENT if ppDev or devicePath are nullptr
     */
	 virtual SMResult getDevice(const wchar_t* devicePath, ppDevice ppDev) NOEXCEPT = 0;


	/*!
	 *  Returns list of HID devices that are currently connected that has a specific HID page as a top level collection
	 *	\param devices returns list of devices that are currently connected on machine. User owns interface and must release it by calling Release
	 *	\return operation result code
	 */
	virtual SMResult getHIDDevices(uint16_t i_usagePage, IDeviceGroup** devices) NOEXCEPT = 0;

	/*!
	 *  Change current log level
	 *	\param logLevel Possible values "low", "medium" and "high"
	 *	\return operation result code
	 */
	virtual SMResult SetLogLevel(eSpokesLogLevel logLevel) NOEXCEPT = 0;

	/*!
	 *  Set Spokes call control
	 *	\param enable If "false" unload all plugins and detach from all devices, if "true" attach to first PLT device.
	 *	\return operation result code
	 */
	virtual SMResult SetCallControl(bool enable) NOEXCEPT = 0;

	/*!
	*  Set Active device that is used for call control
	*	\param pid device product id
	*	\return operation result code
	*/
	virtual SMResult SetActiveDevice(int32_t pid) NOEXCEPT = 0;

	/*!
	 *  Set Active device that is used for call control
	 *	\param devicePath Path to uniquely identify device which will become active one
	 *	\return operation result code
	 */
	virtual SMResult SetActiveDevice(const std::wstring& devicePath) NOEXCEPT = 0;
	/*!
	 *  Returns ID of plugin based on plugin name
	 *	\param pluginID Unique identifier of plugin
	 *	\param pluginName Name of plugin
	 *	\return operation result code
	 */
	virtual SMResult GetPluginId( int32_t& pluginID, const std::wstring& pluginName)  NOEXCEPT = 0;

	/*!
	 *   Returns plugin name based on plugin ID
	 *	\param pluginID Unique identifier of plugin
	 *	\param pluginName - wide char buffer that is ready to receive plugin name
	 *	\param maxLen - buffer length
	 *	\return operation result code
	 */
	virtual SMResult GetPluginNameExternal( int32_t pluginId, wchar_t* pluginName, int32_t maxLen) NOEXCEPT = 0;
	/*!
	 *   Returns plugin name based on plugin ID
	 *	\param pluginID Unique identifier of plugin
	 *	\param pluginName Name of plugin
	 *	\return operation result code
	 */
	virtual SMResult GetPluginName( int32_t pluginID, std::wstring& pluginName) NOEXCEPT = 0;

    /** Register a receiver of notifications of device arrival and removal.
        @param p Pointer to interface of the object that will receive notifications. Must not be nullptr.
        @return indicates the result of operation
        */
    virtual SMResult regCbDevEvents(ISessionManagerIntDevEvents *p) NOEXCEPT = 0;

    /** Unregister a receiver of notifications of device arrival and removal.
        @param p Pointer to interface of the object that won't receive notifications any more.
        @return indicates the result of operation
        */
    virtual SMResult unregCbDevEvents(ISessionManagerIntDevEvents *p) NOEXCEPT = 0;

	/** */
	virtual SMResult firePluginAction(PluginActionArgs const &args) NOEXCEPT = 0;

    /*! Returns a proxy LogWriter for plugins to use.

        \return The pointer to the function which will act as a proxy to the LogWriter module
    */
    virtual LogWriter_ProxyPF GetLoggerProxy() = 0;

    virtual int AddProcWatch(wchar_t const *procName, ProcWatch_CallBack cb) = 0;
    virtual int RemoveProcWatch(wchar_t const *procName, ProcWatch_CallBack cb) = 0;
};

enum RTResult
{
	RT_RESULT_SUCCESS = 0,
	RT_RESULT_FAIL = 1,
	RT_RESULT_INVALID_ARGUMENT = 2,
	RT_RESULT_BUFFER_TOO_SMALL = 3,
	RT_RESULT_NOT_SUPPORTED = 4,
	RT_RESULT_NO_DATA = 5
};

// Class used to represent post data for a web request.
INTF ISpokesPostData
{
public:
	// Returns the number of existing post data elements.
	virtual size_t GetElementCount() const = 0;

	// Retrieve the post data element at index position.
	virtual bool GetElement(size_t index, size_t & size, void * bytes) const = 0;
private:
	void operator delete(void *p);
};

INTF ISpokesRestAPI
{
	virtual RTResult Execute(const wchar_t* command, ISpokesPostData * postData, wchar_t* result, int32_t resultSize) = 0;
};


// IPlugin Interface. Each plugin has to implement this interface
INTF IPlugin
{
    /*! Initializes a plugin.
    *  \return 0 for success or < 0 for failure
    */
    virtual int32_t init(ISessionManager *pSM, ISessionManagerInt *pSMint) = 0;

    /*! Exits a plugin.
    *  \return 0 for success or < 0 for failure
    */
    virtual int32_t exit() = 0;

    /*! Gets the name of the plug-in
    *  \return 0 for success or < 0 for failure
    */
    virtual int32_t getPluginName(wchar_t* pName, int32_t len) = 0;

private:
    void operator delete(void *);
};

typedef IPlugin* pPlugin;
typedef IPlugin** ppPlugin;



/*!
  \brief Resource interface
  Exposes Resources interface.
*/
struct resourceData
{
	enum {
		MAX_FILEPATH = 256,
		MAX_MIMETYPE = 32
	};
	char filePath[MAX_FILEPATH];
	int id;
	char mime_type[MAX_MIMETYPE];
};

INTF IClientResources
{
	/*!
	Get resources list.
	\param resNum Number of resources hosted.
	\param resData New resource data array. Expected nullptr.
	*/
	virtual bool GetResourcesList(size_t &resNum, resourceData const * &resData) NOEXCEPT = 0;

	/*! Retrieve a resource by ID.
	\param binaryId Id of a resource to fetch.
	\param dwSize Output size.
	\param pBytes Output content.
	*/
	virtual bool LoadBinaryResource(int binaryId, size_t &dwSize, unsigned char * &pBytes) NOEXCEPT = 0;

};
/*!
\brief Generic internal interface that should contain different engine API's
*/
struct BatteryWatcherData
{
	eBTBatteryStatus btBatteryStatus;
	eBTChargingStatus btChargingStatus;
	int32_t btLife;
	bool btFromInfo;
	bool isCharging;
	eBatteryLevel btLevel;

	uint32_t batteryLevel;
	uint32_t batteryPercent;
	uint32_t talkTimeH;
	uint32_t talkTimeMin;
};

enum eBatteryWatcherStatus
{
	BTW_STATUS_UNKNOWN = 0,
	BTW_STATUS_OK = 1,
	BTW_STATUS_ENOBATTERY = 2,
	BTW_STATUS_EMAPPED = 3,
	BTW_STATUS_ENOTFOUND = 4

};

INTF IBatteryWatcherListener
{
	virtual void OnBatteryEvent() = 0;
};

typedef IBatteryWatcherListener* pBatteryWatcherListener;

INTF IBatteryWatcher
{
    virtual eBatteryWatcherStatus GetDeviceWatcherData(const wchar_t* sPath, BatteryWatcherData& bData, IConnectedDeviceAddress* address = nullptr) = 0;
	virtual void RegisterListener(pBatteryWatcherListener listener) = 0;
	virtual void UnregisterListener(pBatteryWatcherListener listener) = 0;
	virtual void RaiseEvent() = 0;
};

INTF IUpdateNotifier;

INTF IPlantronicsHubAPI
{
    /*! Returns whether there is a DFU in progress at this moment */
    virtual bool IsAnyDFUOngoing() = 0;

	// BatteryWatcher support
	virtual IBatteryWatcher* getBatteryWatcher() = 0;

	/*! Returns UpdateNotifier pointer */
	virtual IUpdateNotifier* getUpdateNotifier() = 0;
};

INTF IConnectedDeviceProviderListener
{
	virtual void ConnectedDeviceArrived(int32_t const& pid) = 0;
};

INTF IConnectedDeviceProvider
{
	INTF IConnectedDeviceData
	{
		std::shared_ptr<IConnectedDevice> connDevice;
		std::unique_ptr<IConnectedDeviceSettings, IDisposableDeleter> connDeviceSettings;
	};

	virtual  std::shared_ptr<IConnectedDeviceData> getConnectedDeviceFromPid(int32_t pid) = 0;
	virtual std::vector<int32_t> getListOfConnectedDevices(int32_t parentPid) = 0;

	virtual void registerConnectedDeviceProviderListener(IConnectedDeviceProviderListener* listener) = 0;
	virtual void unregisterConnectedDeviceProviderListener(IConnectedDeviceProviderListener* listener) = 0;
};



/*! Retrieve instance of ISessionManagerInt interface
 *  \param Output parameter which gets filled with pointer to the SessionManagerInt
 *  \return SM_RESULT_SUCCESS for success or error code for failure
 */
#ifdef __cplusplus
extern "C"{
#endif

	void DllExport SetHubRunningMode();

	void DllExport SetMetricsRunningMode();

	void DllExport InitSpokesSupportModules(void);

	/** Provides a pointer to an implementation of the Session Manager "Internal" interface */
	SMResult DllExport getSessionManagerInt(ISessionManagerInt** sessionManagerInt);

	/** Returns the pointer to the implementation of the Spokes REST API (for HTML UI) */
	ISpokesRestAPI *getSpokesRestAPI(void);

	/** Returns the pointer to the implementation of the Spokes Client Resources */
	IClientResources * getClientResources(void);

	/** Returns the pointer to implementation of internal API object that provided different Spokes services*/
	IPlantronicsHubAPI * getPlantronicsHubAPI(void);

	class IConfigurationManager;
	int DllExport getConfigManager(IConfigurationManager** cm);

	class EnterpriseConnector;
	int DllExport getEnterpriseConnector(EnterpriseConnector** ec);

	INTF IUpdateHandler;
	int DllExport getUpdateCoordinator(IUpdateHandler** uh);

	INTF INotificationManagerInt;
	int DllExport getNotificationManager(INotificationManagerInt** nm);

	class IPluginManager;
	SMResult DllExport getPluginManager(IPluginManager** pm);

#ifdef __cplusplus
}
#endif


#endif
