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
* \brief       This file contains interfaces for exposing BT Connected devices in DM.
*
* \author      T.Ramesh, A. Gopal
*/

#pragma once
#if !defined INC_ICONNECTEDDEVICE
#define      INC_ICONNECTEDDEVICE

#include "DMTypes.h"
#include "DeviceManager.h"
#include "SpokesEnums.h"
#include "IDeviceAttributes.h"
#include "IHostCommand.h"
#include "IDeviceEvents.h"
#include "IDeviceListener.h"

INTF IDevice;

#ifdef __cplusplus
extern "C"{
#endif

	//ADDED for CONNECTED DEVICE Support 
	struct ConnectedDeviceSettingsChangedEventArgs
	{
		wchar_t devicePath[256];
	};

	// Address for a connected Device. 
	INTF IConnectedDeviceAddress : public IDisposable
	{
		virtual bool isEqual(IConnectedDeviceAddress* address) = 0;
		virtual bool contains(IConnectedDeviceAddress* subaddress) = 0;
		virtual IConnectedDeviceAddress* clone() = 0;
		virtual bool fromEnumeration() = 0;
		virtual IDevice * getOriginDevice() = 0;
	private:
		void operator delete(void *p);
	};
	typedef IConnectedDeviceAddress* pConnectedDeviceAddress;	

	INTF IConnectedDeviceCallback
	{
		virtual void onConnected(pConnectedDeviceAddress const &address) = 0;
		virtual void onDisconnected(pConnectedDeviceAddress const &address) = 0;
		/** Called when the state of the headset changes */
		virtual void onHeadsetStateChanged(HeadsetStateEventArgs const& args) = 0;
		virtual void onBaseEventReceived(BaseEventArgs const& args) = 0;
        virtual void onBatteryLevelChanged(BatteryLevelEventArgs const& args) = 0;
		virtual void onConnectedDeviceSettingsChanged(ConnectedDeviceSettingsChangedEventArgs const& ){}
		//TODO: Add other callbacks for Audio diag, CI data e.t.c

	private:
		void operator delete(void *p);
	};
	typedef IConnectedDeviceCallback* pConnectedDeviceCallback;

	//Connected device specific settings
	INTF IConnectedDeviceSettings : public IDisposable
	{
		//Query if a feature is supported by the connected device
		virtual bool isSupported(eFeatureType feature) const NOEXCEPT = 0;

		//TODO: Add device settings that are supported by a connected device
		//Instead of implementing IDeviceSettings, IDeviceSettingsExt and reporing NOT SUPPORTED for most of the calls
		//it is better to have API's exposed in IConnectedDeviceSettings and as new connected devices are developed extend this interface.

		virtual DMResult getWearingSensorEnabled(bool& enabled) NOEXCEPT = 0;
		virtual DMResult setWearingSensorEnabled(bool enabled) NOEXCEPT = 0;
		virtual DMResult getAnswerOnDon(bool& bEnable) const NOEXCEPT = 0;
		virtual DMResult setAnswerOnDon(bool value) NOEXCEPT = 0;
		virtual DMResult getAutoPause(eSensorControl& value) const NOEXCEPT = 0;
		virtual DMResult setAutoPause(eSensorControl value) NOEXCEPT = 0;
		virtual DMResult getLockHookswitch(eSensorControl& value) const NOEXCEPT = 0;
		virtual DMResult setLockHookswitch(eSensorControl value) NOEXCEPT = 0;
		virtual DMResult getMuteOffVoicePrompt(bool & on) NOEXCEPT = 0;
		virtual DMResult setMuteOffVoicePrompt(bool on) NOEXCEPT = 0;
		virtual DMResult getMutePromptInterval(uint16_t & interval) NOEXCEPT = 0;
		virtual DMResult setMutePromptInterval(uint16_t interval) NOEXCEPT = 0;
		virtual DMResult getCallerNameAnnouncement(bool & on) NOEXCEPT = 0;
		virtual DMResult setCallerNameAnnouncement(bool on) NOEXCEPT = 0;
		virtual DMResult getA2DPEnabled(bool& value) const NOEXCEPT = 0;
		virtual DMResult setA2DPEnabled(bool value) NOEXCEPT = 0;
		virtual DMResult getPSTNBandwidth(eAudioBandwidth& audio) const NOEXCEPT = 0;
		virtual DMResult setPSTNBandwidth(eAudioBandwidth value) NOEXCEPT = 0;
		virtual DMResult getMobileBandwidth(eAudioBandwidth &audio) const NOEXCEPT = 0;
		virtual DMResult setMobileBandwidth(eAudioBandwidth value) NOEXCEPT = 0;
		virtual DMResult getVOIPBandwidth(eAudioBandwidth &audio) const NOEXCEPT = 0;
		virtual DMResult setVOIPBandwidth(eAudioBandwidth value) NOEXCEPT = 0;
		virtual DMResult getVOIPRing(eDeviceRingTone &tone) const NOEXCEPT = 0;
		virtual DMResult setVOIPRing(eDeviceRingTone value) NOEXCEPT = 0;
		virtual DMResult getVOIPRingVolume(eVolumeLevel &level) const NOEXCEPT = 0;
		virtual DMResult setVOIPRingVolume(eVolumeLevel value) NOEXCEPT = 0;
		virtual DMResult getMobileRing(eDeviceRingTone &tone) const NOEXCEPT = 0;
		virtual DMResult setMobileRing(eDeviceRingTone value) NOEXCEPT = 0;
		virtual DMResult getMobileRingVolume(eVolumeLevel &level) const NOEXCEPT = 0;
		virtual DMResult setMobileRingVolume(eVolumeLevel value) NOEXCEPT = 0;
		virtual DMResult getPSTNRing(eDeviceRingTone& value) const NOEXCEPT = 0;
		virtual DMResult setPSTNRing(eDeviceRingTone value) NOEXCEPT = 0;
		virtual DMResult getPSTNRingVolume(eVolumeLevel& value) const NOEXCEPT = 0;
		virtual DMResult setPSTNRingVolume(eVolumeLevel value) NOEXCEPT = 0;
		virtual DMResult getActiveCallRing(eActiveCallRing &ring) const NOEXCEPT = 0;
		virtual DMResult setActiveCallRing(eActiveCallRing value) NOEXCEPT = 0;
		virtual DMResult getDialTone(bool& value) const NOEXCEPT = 0;
		virtual DMResult setDialTone(bool value) NOEXCEPT = 0;
		virtual DMResult getData(eCustomData dataType) NOEXCEPT = 0;
		virtual DMResult setData(eCustomData dataType, uint8_t const* buffer, int32_t bufferLength) NOEXCEPT = 0;
        virtual DMResult getMuteToneVolume(eVolumeLevel &level) const NOEXCEPT = 0;
        virtual DMResult setMuteToneVolume(eVolumeLevel level) NOEXCEPT = 0;
		virtual DMResult getTattooSerialNumber(uint8_t* serialNumber, int32_t& size) const NOEXCEPT = 0;
		virtual DMResult getTattooBuildCode(uint8_t* code, int32_t& size) const NOEXCEPT = 0;
		virtual DMResult getProximity() NOEXCEPT = 0;
		virtual DMResult enableProximity(bool bEnable) NOEXCEPT = 0;

		// **************************  NOTE THERE are more settings please look at Madone SFS Spec
		// ***********************
		virtual DMResult getLanguage(uint16_t & lang) NOEXCEPT = 0;
		virtual DMResult setLanguage(uint16_t lang) NOEXCEPT = 0;
		virtual DMResult getSupportedLanguages(uint16_t *lngList, unsigned int & capacity) NOEXCEPT = 0;
		virtual DMResult setAutoMuteCall(bool enabled) NOEXCEPT = 0;
		virtual DMResult getAutoMuteCall(bool& enabled) const NOEXCEPT = 0;
		virtual DMResult setMuteAlert(eMuteAlertValues value) NOEXCEPT = 0;
		virtual DMResult getMuteAlert(eMuteAlertValues &value) const NOEXCEPT = 0;
		virtual DMResult setOLIEnable(bool value) NOEXCEPT = 0;
		virtual DMResult getOLIEnable(bool& value) const NOEXCEPT = 0;
		virtual DMResult getAudioLimit(eAudioLimit& value) const NOEXCEPT = 0;
		virtual DMResult setAudioLimit(eAudioLimit value) NOEXCEPT = 0;
		virtual DMResult getTWAPeriod(eTWAPeriod &period) const NOEXCEPT = 0;
		virtual DMResult setTWAPeriod(eTWAPeriod value) NOEXCEPT = 0;
		virtual DMResult getG616Enabled(bool& value) const NOEXCEPT = 0;
		virtual DMResult setG616Enabled(bool value) NOEXCEPT = 0;
		virtual DMResult getExtendedRangeModeEnabled(bool& value) const NOEXCEPT = 0;
		virtual DMResult setExtendedRangeModeEnabled(bool value) NOEXCEPT = 0;
		virtual DMResult restoreDefaultSettings() NOEXCEPT = 0;
        virtual DMResult getHeadsetState(eHeadsetState &state) const NOEXCEPT = 0;

		virtual DMResult getBatteryInfo(eBTBatteryStatus * status, int32_t * minutesOfTalkTime, eBTChargingStatus * chargingStatus, eBatteryLevel * level) NOEXCEPT = 0;
		virtual DMResult getBatteryInfo(eBTBatteryStatus * status, int32_t * minutesOfTalkTime, eBTChargingStatus * chargingStatus) NOEXCEPT = 0;
        virtual DMResult getBatteryLevel(eBatteryLevel &level) const NOEXCEPT = 0;
		virtual DMResult getHeadsetCallStatus() const NOEXCEPT = 0;

		// Additional settings for Crystal
		virtual DMResult getVoicePrompt(eSensorControl& value) const NOEXCEPT = 0;
		virtual DMResult setVoicePrompt(eSensorControl value) NOEXCEPT = 0;
		virtual	DMResult getSCOTone(bool & tone) NOEXCEPT = 0;
		virtual DMResult setSCOTone(bool tone) NOEXCEPT = 0;
		virtual DMResult getAutoTransfer(eSensorControl& value) const NOEXCEPT = 0;
		virtual DMResult setAutoTransfer(eSensorControl value) NOEXCEPT = 0;
		virtual DMResult getMuteTone(eMuteTone &mode) const NOEXCEPT = 0;
		virtual DMResult setMuteTone(eMuteTone mode) NOEXCEPT = 0;

        // For OTA DFU
        virtual DMResult getPartitionInfo(uint16_t & partition, uint16_t & position, uint16_t & version, uint16_t & number) NOEXCEPT = 0;
        virtual DMResult removePartition(const uint16_t & partitionId) NOEXCEPT = 0;
        virtual DMResult setTargetPartition(const uint16_t & partition) NOEXCEPT = 0;
        virtual DMResult mountPartition(const uint16_t & partition, const uint16_t & language, const uint16_t & version) = 0;
        virtual DMResult ResetFileSystem() NOEXCEPT = 0;
        virtual DMResult OpenFileForWrite(char* filename, unsigned int offset, unsigned int len, unsigned int & fileHandle) = 0;
        virtual DMResult WriteNextBlock(unsigned int handle, unsigned int offset, uint8_t * bytes, unsigned int size) = 0;
        virtual DMResult WriteNextBlockNoAck(unsigned int handle, unsigned int offset, uint8_t * bytes, unsigned int size) = 0;
        virtual DMResult ChecksumFile(unsigned int handle, unsigned int & checksum) = 0;
        virtual DMResult CloseFile(unsigned int fileHandle) = 0;
        virtual DMResult CloseFileWithCRC(unsigned int handle, unsigned int crc) = 0;

        virtual DMResult getDevicePowerState(const uint8_t &, uint16_t &) = 0;
        virtual DMResult setDevicePowerState(const uint8_t &) = 0;
        virtual DMResult getStackVersion(uint8_t &, uint16_t &, uint16_t &) = 0;
        virtual DMResult setSingleRemoteLock(const bool & lck) = 0;

	private:
		void operator delete(void *p);
	};
	typedef IConnectedDeviceSettings* pCDSettings;
	typedef IConnectedDeviceSettings** ppCDSettings;


	INTF IConnectedDevice : public IDisposable
	{
		//Connected Device info
		virtual int32_t getProductID() const NOEXCEPT = 0;
		virtual int32_t getVendorID() const NOEXCEPT = 0;
		virtual DMResult getProductName(wchar_t* name, int32_t len) const NOEXCEPT = 0;
		virtual DMResult getSerialNumber(uint8_t* serialNumber, int32_t len) const NOEXCEPT = 0;
		virtual DMResult getVersion(eVersionType version, wchar_t* buffer, uint32_t bufferLength) const NOEXCEPT = 0;
		virtual DMResult getManufacturerName(wchar_t* name, int32_t len) const NOEXCEPT = 0;
		virtual DMResult getModelID(uint16_t& modelID) const NOEXCEPT = 0;

		//Connected Device settings
		virtual DMResult getDeviceSettings(ppCDSettings ppSettings) const NOEXCEPT = 0;

		//Callbacks registration
		virtual DMResult registerCallback(pConnectedDeviceCallback pCDCallbacks) NOEXCEPT = 0;
		virtual DMResult unregisterCallback(pConnectedDeviceCallback pCDCallbacks) NOEXCEPT = 0;
		virtual bool IsConnected() const NOEXCEPT = 0;
		virtual bool IsMobilePhone() const NOEXCEPT = 0;
		virtual bool IsHeadset() const NOEXCEPT = 0;
		virtual pConnectedDeviceAddress getAddress() NOEXCEPT = 0;

	private:
		void operator delete(void *p);
	};

	/*!
	* \brief Group of connected devices interface
	* Provides access to IConnectedDevice in a group of Connected devices.
	*/
	INTF IConnectedDeviceGroup : public IDisposable
	{
		/*! Returns an owning pointer to the first device from the group and
		* removes it from the group.
		* If there is no device in the group (the group is empty), returns nullptr.
		*/
		virtual IConnectedDevice *getConnectedDevice() NOEXCEPT = 0;

		/*! Returns the number of connected devices in the group.
		* Each successful call to getConnectedDevice() will decrement this number.
		*/
		virtual uint32_t numDevices() NOEXCEPT = 0;

	private:
		void operator delete(void *p);
	};


	INTF IDeviceExt : IDeviceBaseExt
	{
		virtual DMResult getConnectedDevices(IConnectedDeviceGroup** devices) NOEXCEPT = 0;
		virtual DMResult getConnectedDevice(pConnectedDeviceAddress address, IConnectedDevice **connectedDevice) NOEXCEPT = 0;
		//Callbacks registration
		virtual DMResult registerCallback(pConnectedDeviceCallback pCDCallbacks) NOEXCEPT = 0;
		virtual DMResult unregisterCallback(pConnectedDeviceCallback pCDCallbacks) NOEXCEPT = 0;

	private:
		void operator delete(void *p);
	};

	//ADDED for CONNECTED DEVICE Support

#ifdef __cplusplus
}
#endif

#endif // !defined INC_ICONNECTEDEVICE