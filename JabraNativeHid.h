#ifndef JABRANATIVEHID_H
#define JABRANATIVEHID_H

/* --------------------------------------------------------------------
 * 
 *  GGGGGG  NN    N
 *  G       N N   N
 *  G  GGG  N  N  N - Netcom
 *  G    G  N   N N
 *  GGGGGG  N    NN 
 *
 *  Copyright (c) 2016, GN-Netcom
 * -------------------------------------------------------------------- */

/**
 * @file JabraNativeHid.h
 * @brief Defines the JabraNativeHid interface.
 * Developer information can be found in the JabraNativeHid SDK documentation.
 */

/****************************************************************************/
/*                              INCLUDE FILES                               */
/****************************************************************************/

#include <stdbool.h>


/****************************************************************************/
/*                     EXPORTED TYPES and DEFINITIONS                       */
/****************************************************************************/


#ifdef LIBRARY_GEN
  #if defined _WIN32 || defined __CYGWIN__
    #ifdef LIBRARY_EXPORTS
      #ifdef __GNUC__
        #define LIBRARY_API extern "C" __attribute__ ((dllexport))
      #else
        #define LIBRARY_API extern "C" __declspec(dllexport) // Note: actually gcc seems to also supports this syntax.
      #endif
    #else
      #ifdef __GNUC__
        #define LIBRARY_API extern "C" __attribute__ ((dllimport))
      #else
        #define LIBRARY_API extern "C" __declspec(dllimport) // Note: actually gcc seems to also supports this syntax.
      #endif
    #endif
    #define LOCAL
  #else
    #if __GNUC__ >= 4
      #define LIBRARY_API extern "C" __attribute__ ((visibility ("default")))
      #define LOCAL extern "C" __attribute__ ((visibility ("hidden")))
    #else
      #define LIBRARY_API
      #define LOCAL
    #endif
  #endif
#else
#ifdef __APPLE__
//#define LIBRARY_API extern "C" __attribute__ ((visibility ("default")))
#elif __linux__
#define LIBRARY_API extern "C" __attribute__ ((visibility ("default")))
#else
#define LIBRARY_API
#endif
#endif

// Device description structure
typedef struct Jabra_DeviceInfo
{
  unsigned short deviceID;
  unsigned short productID;
  unsigned short versionNumber;
  char* deviceName;
  char* usbDevicePath;
  char* parentInstanceId;
} Jabra_DeviceInfo_t, Jabra_DeviceInfo;

// Return values enum
typedef enum Jabra_ReturnCode
{
  Return_Ok,
  Device_Unknown,
  Device_Invalid,
  Not_Supported,
  Return_ParameterFail,
  No_Information,
  NetworkRequest_Fail
} Jabra_ReturnCode;

// Predefined inputs enum
typedef enum Jabra_HidInput
{
  Undefined,
  OffHook,
  Mute,
  Flash,
  Redial,
  Key0,
  Key1,
  Key2,
  Key3,
  Key4,
  Key5,
  Key6,
  Key7,
  Key8,
  Key9,
  KeyStar,
  KeyPound,
  KeyClear,
} Jabra_HidInput;

/****************************************************************************/
/*                           EXPORTED FUNCTIONS                             */
/****************************************************************************/

// Get SDK version
// version: Pointer to location where the SDK version is written. Must be allocated by caller.
// count: Max. no of characters to copy to version.
 Jabra_ReturnCode Jabra_GetVersion(
 char* const version,
 int count
);

// Library initialization
// FirstScanForDevicesDoneFunc: Callback method. Called when USB scan is done. Can be NULL if not used.
// DeviceAttachedFunc: Callback method. Called when a device is attached. Can be NULL if not used.
// DeviceRemovedFunc: Callback method. Called when a device is removed. Can be NULL if not used.
// ButtonInDataRawHidFunc: Callback method. Called on new input data. Raw HID. Low-level. Can be NULL if not used.
// ButtonInDataTranslatedFunc: Callback method. Called on new input data. High-level. Can be NULL if not used.
// instance: Optional instance number. Can be 0 if not used
 bool Jabra_Initialize(
  void (*FirstScanForDevicesDoneFunc)(void),
  void (*DeviceAttachedFunc)(Jabra_DeviceInfo deviceInfo),
  void (*DeviceRemovedFunc)(unsigned short deviceID),
  void (*ButtonInDataRawHidFunc)(unsigned short deviceID, unsigned short usagePage, unsigned short usage, bool buttonInData),
  void (*ButtonInDataTranslatedFunc)(unsigned short deviceID, Jabra_HidInput translatedInData, bool buttonInData),
  unsigned int instance
);

// Library uninitialize
 bool Jabra_Uninitialize();

// Check if USB device scan is done. Library initialization must be performed before calling this function.
 bool Jabra_IsFirstScanForDevicesDone();

// Check if a device is attached
// deviceID: Id for a specific device
 bool Jabra_IsDeviceAttached(
  unsigned short deviceID
);

// Fills a provided array with information of attached devcies
// count: Pointer to a int that has the number of Jabra_DeviceInfo structures allocated before calling this function
//        On return this int has the value of how many devices that was added
// deviceInfoList: Pointer to a array of Jabra_DeviceInfo to be populated
 void Jabra_GetAttachedJabraDevices(
  int* count,
  Jabra_DeviceInfo* deviceInfoList
);

// Write a single HID command to the telephony usage page
// deviceID: Id for a specific device
// HID_UsagePage: Usage Page
// HID_Usage: Usage
// value: true or false
 Jabra_ReturnCode Jabra_WriteHIDCommand(
  unsigned short deviceID,
  unsigned short HID_UsagePage,
  unsigned short HID_Usage,
  bool value
);

// Return instance value supplied in the Jabra_Initialize function
 unsigned int Jabra_GetInstance();

// Set OffHook
// deviceID: Id for a specific device
// hook: Off hook/on Hook
 Jabra_ReturnCode Jabra_SetOffHook(
  unsigned short deviceID,
  bool offHook
);

// Set Ringer
// deviceID: Id for a specific device
// ringer: Ringer on/ringer off
 Jabra_ReturnCode Jabra_SetRinger(
  unsigned short deviceID,
  bool ringer
);

// Returns true if ringer is supported for a specific Jabra device.
 bool Jabra_IsRingerSupported(
  unsigned short deviceID
);

// Set Mute
// deviceID: Id for a specific device
// mute: Mute on/mute off
 Jabra_ReturnCode Jabra_SetMute(
  unsigned short deviceID, 
  bool mute
);

// Returns true if mute is supported for a specific Jabra device.
 bool Jabra_IsMuteSupported(
  unsigned short deviceID
);

// Set Hold
// deviceID: Id for a specific device
// hold: Hold on/resume
 Jabra_ReturnCode Jabra_SetHold(
  unsigned short deviceID, 
  bool hold
);

// Returns true if hold is supported for a specific Jabra device.
 bool Jabra_IsHoldSupported(
  unsigned short deviceID
);

// Set Online
// deviceID: Id for a specific device
// online: Online on/online off
// Setting a device online opens radio link between base/dongle and device
 Jabra_ReturnCode Jabra_SetOnline(
  unsigned short deviceID, 
  bool online
);

// Returns true if online mode is supported for a specific Jabra device.
 bool Jabra_IsOnlineSupported(
 unsigned short deviceID
);

// Get battery status, if supported by device.
// deviceID: Id for a specific device
// levelInPercent: Battery level in percent (0 - 100)
// charging: Indicates if battery is being charged
// batteryLow: Indicates if battery level is low
 Jabra_ReturnCode Jabra_GetBatteryStatus(
  unsigned short deviceID,
  int *levelInPercent,
  bool *charging,
  bool *batteryLow
);

// Get serial number. Returns an empty string if the device does not have a
// serial number.
// deviceID: Id for a specific device.
// serialNumber: Pointer to location where the serial number is written. Must be allocated by caller.
// count: Max. no of characters to copy to serialNumber.
 Jabra_ReturnCode Jabra_GetSerialNumber(
  unsigned short deviceID,
  char* const serialNumber,
  int count
);

// Get firmware version
// deviceID: Id for a specific device.
// firmwareVersion: Pointer to location where the firmware version is written. Must be allocated by caller.
// count: Max. no of characters to copy to firmwareVersion.
 Jabra_ReturnCode Jabra_GetFirmwareVersion(
  unsigned short deviceID,
  char* const firmwareVersion,
  int count
);

#endif /* JABRANATIVEHID_H */
