/*
    DMTypes.h : All typedefs exposed in Spokes 3G SDK. 
    TODO: Rename file to SpokesTypes.h later
*/

#pragma once
#ifndef DMTYPES
#define DMTYPES

#include "DMEnums.h"

#include "CommonTypes.h"
#include <time.h>
#include <vector>


typedef uint16_t   USAGE;
typedef uint16_t* pUSAGE;

static const uint16_t MAX_LEN = 100;

struct DeviceStateEventArgs
{
    enum {
        MAX_DEVPATH     = 128
    };
    eDeviceState deviceState;
    wchar_t devicePath[MAX_DEVPATH];
};


struct ReportDataEventArgs
{
    enum {
        MAX_REPORT_LEN  =  64,
        MAX_DEVPATH     = 128
    };
    uint32_t reportLen;
    uint8_t report[MAX_REPORT_LEN];
    wchar_t devicePath[MAX_DEVPATH];
};

struct DeviceEventArgs
{
     eHeadsetButton buttonPressed;
     eAudioState audioState;
     bool mute;
};

struct BatteryLevelEventArgs
{
    eBatteryLevel batteryLevel;
};


struct HeadsetStateEventArgs
{
    enum {
        MAX_HEADSET_NAME = 64,
		MAX_SERNO_SIZE   = 16,
		MAX_PATH_SIZE    = 256
    };
    int32_t headsetsInConference;
    char headsetName[MAX_HEADSET_NAME];
    eHeadsetState headsetState;
    eProximity proximity;
    eBTBatteryStatus batteryStatus;
    eBTChargingStatus batteryChargStatus;
    int32_t batteryLife;
	uint8_t serialNumber[MAX_SERNO_SIZE];
	wchar_t devicePath[MAX_PATH_SIZE];
};

struct AALAcousticIncidentReportEventArgs
{
	float gainThreshold;
    uint16_t durationThreshold;
	uint16_t activeLimiters;
    uint32_t incidentDuration;
	float preLimiterSPLEstimate;
	float postLimiterSPLEstimate;
};

struct AALTWAReportEventArgs
{
	uint32_t periodicity;
	uint32_t duration;
	float gainThreshold;
	float preLimiterLongTermSPLEstimate;
	float postLimiterLongTermSPLEstimate;	
};

struct ConversationDynamicsReportEventArgs
{
    uint16_t periodicity;
    uint16_t farTalkDuration;
    uint16_t nearTalkDuration;
    uint16_t doubleTalkDuration;
    float txLevelIn;
	float txLevelOut;
	float rxLevelIn;
	float rxLevelOut;
	float txNoiseIn;
	float txNoiseOut;
	float rxNoiseIn;
	float rxNoiseOut;
	float txPeakIn;
	float txPeakOut;
	float rxPeakIn;
	float rxPeakOut;
	float txVolume;
	float rxVolume;
	float sideToneVolume;
};

struct BaseEventArgs
{
    enum {
        MAX_REPORT_SIZE = 64,
        MAX_PASSWORD_SIZE = 30,
        MAX_SERNO_SIZE = 16,
        MAX_FEATURE_LOCKS = 32
    };
    uint32_t count;
    uint8_t report[MAX_REPORT_SIZE];
    uint8_t password[MAX_PASSWORD_SIZE];
    uint8_t serialNumber[MAX_SERNO_SIZE];
    eBaseEventType baseEvent;
    eFeatureLock featureLock[MAX_FEATURE_LOCKS];
};

struct MobilePresenceEventArgs
{
    enum {
        MAX_CALLER_ID = 64
    };
    char callerID[MAX_CALLER_ID];
    eMobileCallState mobileCallState;
};

enum HIDPipeEventType
{
    HIDPipeEventType_Data = 1,
    HIDPipeEventType_Fragment = 2,
    HIDPipeEventType_Ack = 3
};

struct HIDPipeEventArgs
{
    enum {
        MAX_REPORT_SIZE = 64
    };
    int32_t len;
    uint8_t report[MAX_REPORT_SIZE];
    HIDPipeEventType type;
};

struct MOCEventArgs
{
    bool enabled;
    /// This is a bit-set of values from eMocState
    uint32_t states;
};

enum MOCDisplayInfo
{
    MOCDisplayInfo_Unknown = 0,
    MOCDisplayInfo_CallState = 1,
    MOCDisplayInfo_CallerName = 2,
    MOCDisplayInfo_CallerFriendlyName = 3
};


struct DM_GUID
{
    uint32_t Data1;
    uint16_t Data2;
    uint16_t Data3;
    uint8_t Data4[8];
};


struct DisplayDeviceCallData {
    enum {
        MAX_CALLERID = 128,
        MAX_FRIENDLYNAME = 128
    };

    DM_GUID sessionId;
    int32_t callId;
    DDCallState callState;
    DDSoftphoneID softphoneID;
    wchar_t callerId[MAX_CALLERID];
    wchar_t friendlyName[MAX_FRIENDLYNAME];
};

struct MOCDisplayEventArgs
{
    enum {
        MAX_CALLS = 4
    };
    MOCDisplayInfo type;
    int32_t callCount;
    DisplayDeviceCallData call[MAX_CALLS];
};

struct AudioSenseEventArgs
{
    bool enabled;
    eAudioSenseState state;
};

struct DeviceListenerEventArgs
{
    enum
    {
        MAX_DEVICE_PATH = 256
    };
    eDeviceEventType deviceEventType;
    eHeadsetButton headsetButton;
    eHeadsetStateChange headsetStateChange;
    eBaseButton baseButton;
    int32_t dialedKey;
    eBaseStateChange baseStateChange;
    eATDStateChange ATDStateChange;
    wchar_t devicePath[MAX_DEVICE_PATH];
};

//this wraps the params required for PSKey BTDeviceSettings read/write method calls
struct BTDeviceSettingParams {
	wchar_t keyName[256];				// PS KEY name
	wchar_t keyValStr[256];				// input/output param for PSKEY read allocate buffer, or input param for PSKEY write
	int32_t keyValSize;					// only required for reads, set to 0 for writes
	wchar_t keyAddrStr[256]; 
	wchar_t keyFormat[256]; 
	wchar_t numWordsStr[256]; 
	wchar_t psFoundInKeyTableInHidMode[256];
	wchar_t bitfieldWordIndexStr[256];	// required for bitfield pskey only
	wchar_t bitfieldHiBitStr[256];		// required for bitfield pskey only
	wchar_t bitfieldLoBitStr[256];		// required for bitfield pskey only
};

struct AALReportingThreshold
{
	int16_t gain; //in dB (0-12dB)
	uint16_t time; //in msec (0-1000msec) 
};

struct DeviceWarranty
{
	time_t firstUsed; //First date used
	time_t lastUsed;  //Last date used
	time_t lastConnected; // Last date connected
};

struct SignalStrengthParams
{
	uint8_t id;
	bool enable;
	bool dononly;
	bool trend;
	bool report_rssi_audio;
	bool report_near_far_audio;
	bool report_near_far_base;
	uint8_t sensitiviy;
	uint8_t near_treshold;
	uint16_t max_timeout;
};

struct IndirectEventSimulationParams
{
	HeadsetWearingState wearing_state;
	BatteryStatusMonitor battery_status;
	VoiceRecognition voice_recognition;
	uint8_t proximity_connection_id;
	uint8_t proximity_value_RSSI;
	uint16_t voice_prompt[MAX_LEN];
	uint16_t voice_prompt_length;
	uint16_t led_indication[MAX_LEN];
	uint16_t led_indication_length;
	Charger charger;
};

#endif
