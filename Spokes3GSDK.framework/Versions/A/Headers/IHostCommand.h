/*!
 * \author  	Plantronics, Inc.
 * \version	    1.0
 *
 * \copyright 
 *              Copyright ï¿½ 2012 Plantronics, Inc. All rights reserved.
 *              This code is confidential and proprietary information belonging to 
 *              Plantronics, Inc. and may not be copied, modified or distributed
 *              without the express written consent of Plantronics, Inc.
 *
 * \brief       This file contains interfaces of the IHostCommand hierarchy.
 * 
 */

#pragma once
#if !defined INC_IHOSTCOMMAND
#define      INC_IHOSTCOMMAND


#include "DMTypes.h"

INTF IHostCommandQuery;

/*! 
 *  \brief HostCommand interface  
 *
 *  The IHostCommand interface provides methods and properties that
 *  can be used to send specific requests to the attached device from
 *  the host application. This is the root of the HostCommand
 *  interface hierarchy.  All other interfaces are optional.
 */
INTF IHostCommand
{
    /** Returns the query pointer */
    virtual IHostCommandQuery *getQuery() NOEXCEPT = 0 ;

    /*!  Puts the device in ring state. On some devices, there is no audiable "ringer", so no audio changes
     *  will happen. But even for those devices, this will succeed, if the command is successfully sent to
     *  the device.
     *   \param bEnable (true) sends a command to the device to start the ringer. On devices that do
     *          not have a ringer, this call will be a NOP. bEnable (false) sends a command to the
     *          device to stop the ringer.
     *   \return indicates the result of the operation (success may happen even if there are no audio changes to hear)
     */
    virtual DMResult setRing(bool bEnable) NOEXCEPT = 0;

    /*!  Gets the audio stream state to the attached device.
     *   \return Constant value from eAudioState enum which represents current audio state
     */
    virtual DMResult getAudioState(eAudioState &state) const NOEXCEPT = 0;

    /*!  Enables or disables the audio stream to the attached device. For a wireless device, this property also controls
     *   the audio link.
     *   \param audioType The link is up when audio is enabled by setting the AudioState to AUDIO_TYPE_MONO_ON.
     *                    The link is down when the audio is disabled by setting the AudioState to AUDIO_TYPE_MONO_OFF.
     *   \return indicates the result of the operation
     */
    virtual DMResult setAudioState(eAudioState audioType) NOEXCEPT = 0;

    /*!  Gets the mute state of the microphone in the device.
     *   \param To this reference will be assigned: true if muted, or false if not muted.
     *   \return indicates the result of the operation
     */
    virtual DMResult getMute(bool &mute) const NOEXCEPT = 0;

    /*!  Signs a host application in or out. Signing in lets the device know that the host application is running.
     *   \param sign Constant value from eRegistrationType enum.
     */
    virtual DMResult registerCommand(eRegistrationType sign) NOEXCEPT = 0;

    /*!  Gets the USB, base, or headset firmware version.
     *   \param version Type of firmware: USB, Base, or remote.
     *   \param buffer Buffer which will be filled with version string, or will be empty if specified version is not applicable for current device
     *   \param bufferLength Length of provided buffer.
     *   \return DM_RESULT_SUCCESS on success, DM_RESULT_BUFFER_TOO_SMALL if buffer is too small and DM_RESULT_FAIL on fail
     */
    virtual DMResult getVersion(eVersionType version, wchar_t* buffer, uint32_t bufferLength) const NOEXCEPT = 0;

    /*!  Determines whether the attached device supports the specified feature.
     *   \param feature Feature to test for.
     *   \return Boolean true if feature is supported, or false otherwise.
     */
    virtual bool isSupported(eFeatureType feature) const NOEXCEPT = 0;

private:
    void operator delete(void *);
};
typedef IHostCommand* pHostCommand;
typedef IHostCommand** ppHostCommand;

/*! \brief IExtendedVersion
    Interface with additional data to be read from (for) the device
*/
INTF IExtendedVersion
{
    /*! Returns the product ID (PID) of the device */
    virtual int32_t getProductId() NOEXCEPT = 0;
    /*! Returns the version number of the device */
    virtual int32_t getVersionNumber() NOEXCEPT = 0;

private:
    void operator delete(void *);
};

/*! \brief IDisplayDeviceCommand
    Interface with commands for display devices
*/
INTF IDisplayDeviceCommand
{
    /*! Sets the HID pipe mode for the device */
    virtual DMResult setHIDPipeMode(HIDPipeMode mode) NOEXCEPT = 0;

    /*! Sets the "enable HID pipe ack(nowledge)" option for the device */
    virtual DMResult setEnableHIDPipeAck(bool ack) NOEXCEPT = 0;

    /*! Reads the "enable HID pipe ack(nowledge)" option for the device */
    virtual DMResult getEnableHIDPipeAck(bool &enabled) const NOEXCEPT = 0;

    /*! Sets the "enable display " option for the device. When display is disabled
        it doesn't display any of our useful information.
    */
    virtual DMResult setEnableDisplay(bool enable) NOEXCEPT = 0;

    /*! Reads the "enable display " option for the device. */
    virtual DMResult getEnableDisplay(bool &enabled) const NOEXCEPT = 0;

private:
    void operator delete(void *);
};

INTF IHostCommandExt
{
    /*!  Gets the battery level of the device.
     *   \param level A value from eBatteryLevel enum will be written to this reference
     *   \return indicates the result of operation
     */
    virtual DMResult getBatteryLevel(eBatteryLevel &level) const NOEXCEPT = 0;

    /*!  Gets number of headsets currently in conference.
     *   \param count A count of headsets in conference will be written to this reference
     *   \return indicates the result of operation
     */
    virtual DMResult getHeadsetsInConference(uint32_t &count) const NOEXCEPT = 0;

    /*!  Sets mute state of headset.
     *   \param bMute (true) sets headset mute state to mute, bMute (false) unmutes the headset.
     *   \return indicates the result of operation
     */
    virtual DMResult setHeadsetMute(bool bMute) NOEXCEPT = 0;

    /*!  Gets the headset type.
     *   \param  hs A value from eHeadsetType enum will be written to this reference
     *   \return indicates the result of operation
     */
    virtual DMResult getHeadsetType(eHeadsetType &hs) const NOEXCEPT = 0;

    /*!  Sends the GetVersion command (request) to the device.
     *   Device will give the version in a new report sent back to host.
     *   \return indicates the result of operation
     */
    virtual DMResult sendVersionRequest() NOEXCEPT = 0;

    /*!  Sets the currently active link.
     *   \param lineType Line to change active state (VOIP, PSTN or Mobile).
     *   \param bActive (true) activates the specified line type, bActive (false) deactivates specified line type.
     *   \return DM_RESULT_SUCCESS on success, DM_RESULT_FAIL otherwise.
     */
    virtual DMResult setActiveLink(eLineType lineType, bool bActive) NOEXCEPT = 0;

    /*!  Checks if specified line is active.
     *   \param i_lineType Line to check active state (VOIP, PSTN or Mobile).
     *   \param o_active A Boolean will be written to this reference - true if specified line type is active, false otherwise.
     *   \return indicates the result of operation
     */
    virtual DMResult isLineActive(eLineType i_lineType, bool &o_active) const NOEXCEPT = 0;

	/*!  Checks if specified line is connected.
	*   \param i_lineType Line to check active state (VOIP, PSTN or Mobile).
	*   \param o_active A Boolean will be written to this reference - true if specified line type is active, false otherwise.
	*   \return indicates the result of operation
	*/
	virtual DMResult isLineConnected(eLineType i_lineType, bool &o_active) const NOEXCEPT = 0;

    /*!  Puts line on hold.
     *   \param lineType Line to hold (VOIP, PSTN or Mobile).
     *   \param bHold (true) holds specified line, bHold (false) unholds specific line.
     *   \return DM_RESULT_SUCCESS on success, DM_RESULT_FAIL otherwise.
     */
    virtual DMResult hold(eLineType lineType, bool bHold) NOEXCEPT = 0;

    /*!  Gets hold state for the line
     *   \param i_lineType Line (VOIP, PSTN or Mobile) to check for hold.
     *   \param o_hold A Boolean will be written to this reference true if specified line type is on hold, false otherwise.
     *   \return indicates the result of operation
     */
    virtual DMResult getHoldState(eLineType i_lineType, bool &o_hold) NOEXCEPT = 0;

    /*!  Gets the audio link state.
     *   \param state Value from eAudioLinkState enum will be written to this reference
     *   \return indicates the result of operation
     */
    virtual DMResult getAudioLinkState(eAudioLinkState &state) const NOEXCEPT = 0;

    /*!  Checks if headset is docked.
     *   \param isHsDocked, return value, true if HS is docked
     *   \return DMResult, DM_RESULT_SUCCESS if operation succedded.
     */
    virtual DMResult isHeadsetDocked(bool& isHsDocked) const NOEXCEPT = 0;

    /*!  Get headset product name. This function will block for 300ms waiting for headset product name to be returned.
     *   \param buffer Buffer which will be filled with headset product name.
     *   \return result of operation. In some cases headset product name is not received in 300ms timeframe, then DM_RESULT_DATA_NOT_AVAILABLE will be returned.
     */
    virtual DMResult getHeadsetProductName(wchar_t* buffer, int32_t length) NOEXCEPT = 0;
    
    /*!  Gets audio location.
     *   \param localtin Value from eAudioLocation enum will be written to this reference
     *   \return indicates the result of operation
     */
    virtual DMResult getAudioLocation(eAudioLocation &location) const NOEXCEPT = 0;
    
    /*!  Gets battery info from device. This function will block for 300ms waiting for battery information to be returned.
     *   \param btBatteryStatus Pointer to a value which will be set to a value from eBTBatteryStatus enum.
     *   \param life Battery life.
     *   \param btChargingStatus Pointer to a value which will be set to a value from eBTChargingStatus enum.
     *   \return indicates the result of operation. In some cases battery information is not received in 300ms timeframe, then DM_RESULT_DATA_NOT_AVAILABLE will be returned.
     */
    virtual DMResult getBatteryInfo(eBTBatteryStatus* btBatteryStatus, int32_t* life, eBTChargingStatus* btChargingStatus) NOEXCEPT = 0;
    
    /*!  Sends the serial number request for the device part type to the device.
     *   \param devType For which device part type to send get serial number command / request.
     *   \return result of operation.
     */
    virtual DMResult sendSerialNumberReq(eDevice_Type devType) NOEXCEPT = 0;

    /*!  Try to retrieve persisted device type (base or headset) serial number. Serial number is a GUID (or alike) number.
     *   \param devType For which device type to send get serial number command.
     *   \param serialNumber pointer to serial number buffer
     *   \param serial number buffer size (should be exactly 16)
     *   \return DM_RESULT_SUCCESS if successful, DM_RESULT_DATA_NOT_AVAILABLE if data not available (not requested probably).
     *           or DM_RESULT_BUFFER_TOO_SMALL if buffer sent is too small
     */
    virtual DMResult getSerialNumber(eDevice_Type devType, uint8_t* serialNumber, int32_t serialNumberBufferSize) const NOEXCEPT = 0;

    /*!  Check if specified usage is constant.
     *   \param usage Usage to check.
     *   \return Boolean true if specified usage is constant, false otherwise.
     */
    virtual bool isConstant(uint16_t usage) const NOEXCEPT = 0;

    /*!  Sends request for proximity to device. Value will be returned as HeadsetStateChanged event.
     *   \return indicates the result of operation.
     */
    virtual DMResult getProximity() NOEXCEPT = 0;

    /*!  Sets proximity state.
     *   \param bEnable (true) enables proximity, (false) disables proximity
     */
    virtual DMResult enableProximity(bool bEnable) NOEXCEPT = 0;

    /*!  Gets headset state from device.
     *   \param state A value from eHeadset state enum will be written to this reference
     *   \return indicates the result of operation.
     */
    virtual DMResult getHeadsetState(eHeadsetState &state) const NOEXCEPT = 0;

    /*! Turns headset pairing mode on/off
     *  \return result of setting the mode (DM_RESULT_NOT_SUPPORTED if device does not support pairing)
     */
    virtual DMResult HeadsetPairing(bool on) NOEXCEPT = 0;

private:
    void operator delete(void *);
};

/*! \brief IDeviceSettings 
    The interface with commands to set and get various device option settings.
*/
INTF IDeviceSettings 
{
    /*! Get VOIP ring tone from device */
    virtual DMResult getVOIPRing(eDeviceRingTone &tone) const NOEXCEPT = 0;
    /*! Set VOIP ring tone on device */
    virtual DMResult setVOIPRing(eDeviceRingTone value) NOEXCEPT = 0;
    /*! Get VOIP auidio bandwith from device */
    virtual DMResult getVOIPBandwidth(eAudioBandwidth &audio) const NOEXCEPT = 0;
    /*! Set VOIP audio bandwith on device */
    virtual DMResult setVOIPBandwidth(eAudioBandwidth value) NOEXCEPT = 0;
    /*! Get VOIP ring volume level from device */
    virtual DMResult getVOIPRingVolume(eVolumeLevel &level) const NOEXCEPT = 0;
    /*! Set VOIP ring volume level on device */
    virtual DMResult setVOIPRingVolume(eVolumeLevel value) NOEXCEPT = 0;
    /*! Get VOIP tone level from device */
    virtual DMResult getVOIPToneControl(eToneLevel &level) const NOEXCEPT = 0;
    /*! Set VOIP tone level on device */
    virtual DMResult setVOIPToneControl(eToneLevel value) NOEXCEPT = 0;

    /*! Get PSTN ring tone from device */
    virtual DMResult getPSTNRing(eDeviceRingTone& value) const NOEXCEPT = 0;
    /*! Set PSTN ring tone on device */
    virtual DMResult setPSTNRing(eDeviceRingTone value) NOEXCEPT = 0;
    /*! Get PSTN auidio bandwith from device */
    virtual DMResult getPSTNBandwidth(eAudioBandwidth& value) const NOEXCEPT = 0;
    /*! Set PSTN audio bandwith on device */
    virtual DMResult setPSTNBandwidth(eAudioBandwidth value) NOEXCEPT = 0;
    /*! Get PSTN ring volume level from device */
    virtual DMResult getPSTNRingVolume(eVolumeLevel& value) const NOEXCEPT = 0;
    /*! Set PSTN ring volume level on device */
    virtual DMResult setPSTNRingVolume(eVolumeLevel value) NOEXCEPT = 0;
    /*! Get PSTN tone level from device */
    virtual DMResult getPSTNToneControl(eToneLevel &level) const NOEXCEPT = 0;
    /*! Set PSTN tone level on device */
    virtual DMResult setPSTNToneControl(eToneLevel value) NOEXCEPT = 0;

    /*! Get mobile ring tone from device */
    virtual DMResult getMobileRing(eDeviceRingTone &tone) const NOEXCEPT = 0;
    /*! Set mobile ring tone on device */
    virtual DMResult setMobileRing(eDeviceRingTone value) NOEXCEPT = 0;
    /*! Get mobile auidio bandwith from device */
    virtual DMResult getMobileBandwidth(eAudioBandwidth &audio) const NOEXCEPT = 0;
    /*! Set mobile audio bandwith on device */
    virtual DMResult setMobileBandwidth(eAudioBandwidth value) NOEXCEPT = 0;
    /*! Get mobile ring volume level from device */
    virtual DMResult getMobileRingVolume(eVolumeLevel &level) const NOEXCEPT = 0;
    /*! Set mobile ring volume level on device */
    virtual DMResult setMobileRingVolume(eVolumeLevel value) NOEXCEPT = 0;

    /*! Get mute tone from device */
    virtual DMResult getMuteTone(eDeviceRingTone &tone) const NOEXCEPT = 0;
    /*! Set mute tone on device */
    virtual DMResult setMuteTone(eDeviceRingTone value) NOEXCEPT = 0;

    /*! Get tone volume level from device */
    virtual DMResult getToneVolume(eVolumeLevel &level) const NOEXCEPT = 0;
    /*! Set tone volume level on device */
    virtual DMResult setToneVolume(eVolumeLevel value) NOEXCEPT = 0;
    /*! Get mute tone volume level from device */
    virtual DMResult getMuteToneVolume(eVolumeLevel &level) const NOEXCEPT = 0;
    /*! Set mute tone volume level on device */
    virtual DMResult setMuteToneVolume(eVolumeLevel value) NOEXCEPT = 0;
    /*! Get active ring tone volume level from device */
    virtual DMResult getActiveCallRing(eActiveCallRing &ring) const NOEXCEPT = 0;
    /*! Set active ring tone volume level on device */
    virtual DMResult setActiveCallRing(eActiveCallRing value) NOEXCEPT = 0;

    virtual DMResult getAntiStartleEnabled(bool& value) const NOEXCEPT = 0;
    virtual DMResult setAntiStartleEnabled(bool value) NOEXCEPT = 0;
    virtual DMResult getAudioLimit(eAudioLimit& value) const NOEXCEPT = 0;
    virtual DMResult setAudioLimit(eAudioLimit value) NOEXCEPT = 0;
    virtual DMResult getG616Enabled(bool& value) const NOEXCEPT = 0;
    virtual DMResult setG616Enabled(bool value) NOEXCEPT = 0;

    virtual DMResult getOTAEnabled(bool &enabled) const NOEXCEPT = 0;
    virtual DMResult setOTAEnabled(bool value) NOEXCEPT = 0;
    virtual DMResult getIntellistandEnabled(bool &enabled) const NOEXCEPT = 0;
    virtual DMResult setIntellistandEnabled(bool value) NOEXCEPT = 0;
    virtual DMResult getPowerMode(ePowerLevel &level) const NOEXCEPT = 0;
    virtual DMResult setPowerMode(ePowerLevel value) NOEXCEPT = 0;

    virtual DMResult getData(eCustomData dataType) NOEXCEPT = 0;
    virtual DMResult setData(eCustomData dataType, uint8_t const* buffer, int32_t bufferLength) NOEXCEPT = 0;       
    virtual DMResult isPasswordProtected(bool &protec) const NOEXCEPT = 0;
    virtual DMResult getDECTMode(bool &mode) const NOEXCEPT = 0;
    virtual DMResult getTWAPeriod(eTWAPeriod &period) const NOEXCEPT = 0;
    virtual DMResult setTWAPeriod(eTWAPeriod value) NOEXCEPT = 0;
    virtual DMResult getPhoneLine(eLineType &type) const NOEXCEPT = 0;
    virtual DMResult setPhoneLine(eLineType value) NOEXCEPT = 0;
    virtual DMResult getBTInterfaceEnabled(bool &enabled) const NOEXCEPT = 0;
    virtual DMResult setBTInterfaceEnabled(bool value) NOEXCEPT = 0;
    virtual DMResult getBTAutoConnectEnabled(bool &enabled) const NOEXCEPT = 0;
    virtual DMResult setBTAutoConnectEnabled(bool value) NOEXCEPT = 0;
    virtual DMResult restoreDefaultSettings() NOEXCEPT = 0;
    virtual DMResult getACLPollingEnabled(bool &enabled) const NOEXCEPT = 0;
    virtual DMResult setACLPollingEnabled(bool value) NOEXCEPT = 0;
    virtual DMResult getBTVoiceCommandEnabled(bool &enabled) const NOEXCEPT = 0;
    virtual DMResult setBTVoiceCommandEnabled(bool value) NOEXCEPT = 0;

	virtual DMResult getVolumeControlOrientation(eVolumeControlOrientation& value) const NOEXCEPT = 0;
    virtual DMResult setVolumeControlOrientation(eVolumeControlOrientation value) NOEXCEPT = 0;
    virtual DMResult getA2DPEnabled(bool& value) const NOEXCEPT = 0;
    virtual DMResult setA2DPEnabled(bool value) NOEXCEPT = 0;

private:
    void operator delete(void *);
};

/*! \brief IAdvanceSettings
    The interface with commands to set and get various "advanced" (less common) 
    device option settings.
*/
INTF IAdvanceSettings
{
    virtual DMResult getDialTone(bool& value) const NOEXCEPT = 0;
    virtual DMResult setDialTone(bool value) NOEXCEPT = 0;
    virtual DMResult getAudioSensing(bool& value) const NOEXCEPT = 0;
    virtual DMResult setAudioSensing(bool value) NOEXCEPT = 0;
    virtual DMResult getDialToneActive(bool& value) const NOEXCEPT = 0;
    virtual DMResult getAnswerOnDon(bool& bEnable) const NOEXCEPT = 0;
    virtual DMResult setAnswerOnDon(bool value) NOEXCEPT = 0;

    virtual DMResult getAutoTransfer(eSensorControl& value) const NOEXCEPT = 0;
    virtual DMResult setAutoTransfer(eSensorControl value) NOEXCEPT = 0;
    virtual DMResult getAutoDisconnect(eSensorControl& value) const NOEXCEPT = 0;
    virtual DMResult setAutoDisconnect(eSensorControl value) NOEXCEPT = 0;
    virtual DMResult getAutoReject(eSensorControl& value) const NOEXCEPT = 0;
    virtual DMResult setAutoReject(eSensorControl value) NOEXCEPT = 0;
    virtual DMResult getLockHookswitch(eSensorControl& value) const NOEXCEPT = 0;
    virtual DMResult setLockHookswitch(eSensorControl value) NOEXCEPT = 0;
    virtual DMResult getAutoPause(eSensorControl& value) const NOEXCEPT = 0;
    virtual DMResult setAutoPause(eSensorControl value) NOEXCEPT = 0;
    virtual DMResult getVoicePrompt(eSensorControl& value) const NOEXCEPT = 0;
    virtual DMResult setVoicePrompt(eSensorControl value) NOEXCEPT = 0;

private:
    void operator delete(void *);
};


/*! \brief IDeviceSettingsExt
Interface to capture all HID 2.0 device settings that are not already exposed
via IDeviceSettings and IAdvanceSettings*/
INTF IDeviceSettingsExt
{
	//Get and set Acoustics Reporting for AAL Acoustics incident and TWA reporting and Conversation dynamics reporting
	virtual DMResult getAcousticsReporting(eAcousticsReportType type, bool& value) const NOEXCEPT = 0;
	virtual DMResult setAcousticsReporting(eAcousticsReportType type, bool value) NOEXCEPT = 0;
	
	//Get and set AAL Acoustics incident Threshold
	virtual DMResult getAALReportingThreshold(AALReportingThreshold& value) const NOEXCEPT = 0;
	virtual DMResult setAALReportingThreshold(AALReportingThreshold value) NOEXCEPT = 0;	

	//Get and set AAL TWA reporting time period
	virtual DMResult getTWAReportingPeriod(uint32_t& value) const NOEXCEPT = 0;
	virtual DMResult setTWAReportingPeriod(uint32_t value) NOEXCEPT = 0;

	//Get and set AAL Conversation dynamics reporting time period
	virtual DMResult getConversationDynamicsPeriod(uint16_t& value) const NOEXCEPT = 0;
	virtual DMResult setConversationDynamicsPeriod(uint16_t value) NOEXCEPT = 0;

	virtual DMResult getPartitionInfo(uint16_t & partition, uint16_t & position, uint16_t & version, uint16_t & number) = 0;
	virtual DMResult removePartition(const uint16_t&) = 0;
	virtual DMResult setLanguage(uint16_t lang) = 0;
	virtual DMResult getLanguage(uint16_t & lang) = 0;
	virtual DMResult getAnswerIgnoreVoiceCommand(bool & on) = 0;
	virtual DMResult setAnswerIgnoreVoiceCommand(bool on) = 0;
	virtual DMResult getCallerNameAnnouncement(bool & on) = 0;
	virtual DMResult setCallerNameAnnouncement(bool on) = 0;
	virtual DMResult getMuteOffVoicePrompt(bool & on) = 0;
	virtual DMResult setMuteOffVoicePrompt(bool on) = 0;
	virtual DMResult getMutePromptInterval(uint16_t & interval) = 0;
	virtual DMResult setMutePromptInterval(uint16_t interval) = 0;
	virtual DMResult getCallButtonLock(bool & on) = 0;
	virtual DMResult setCallButtonLock(bool on) = 0;
	virtual DMResult getSupportedLanguages(uint16_t *, unsigned int & capacity) = 0;	
	virtual DMResult setSignalStrengthEvents(SignalStrengthParams param) = 0;
	virtual DMResult getCurrentSignalStrengthEvents(uint8_t id, uint8_t& conId, uint8_t& strength, SignalStrengthType& type) = 0;
	virtual DMResult setPairingMode(bool enable) = 0;
	virtual DMResult getPairingMode(bool& enable) = 0;	
	virtual DMResult getConnectionStatus(std::vector<uint8_t>& downPort, std::vector<uint8_t>& connectedPort, uint8_t& origPort) = 0;
	virtual DMResult getSignalStrengthConfiguration(uint8_t connId, SignalStrengthParams& param) = 0;
	virtual DMResult getAudioStatus(uint8_t& codec, uint8_t& port, uint8_t& speakerGain, uint8_t& micGain) = 0;
	virtual	DMResult getSCOTone(bool & tone) = 0;
	virtual DMResult setSCOTone(bool tone) = 0;
	virtual DMResult setFindHeadsetLEDAlert(bool enable) = 0;
	virtual DMResult getFindHeadsetLEDAlert(bool& enabled) = 0;
	virtual DMResult setAudioTransmitGain(uint8_t gain) = 0;
	virtual DMResult setSpeakerVolume(bool action, uint16_t volume) = 0;	
	virtual DMResult getWearingSensorEnabled(bool& enabled) = 0;
	virtual DMResult setWearingSensorEnabled(bool enabled) = 0;
	virtual DMResult setVRCallRejectAnswer(bool enable) = 0;
	virtual DMResult getVRCallRejectAnswer(bool& enabled) = 0;
	virtual DMResult getHeadsetConnectedState(bool& enabled) const NOEXCEPT = 0;
	virtual DMResult getHTopSelector(eHTopSelectorType& value) const NOEXCEPT = 0;
	virtual DMResult setHTopSelector(eHTopSelectorType value) NOEXCEPT = 0;
	virtual DMResult setAutoMuteCall(bool enabled) NOEXCEPT = 0;
	virtual DMResult getAutoMuteCall(bool& enabled) const NOEXCEPT = 0;
	virtual DMResult setMuteAlert(eMuteAlertValues value) NOEXCEPT = 0;
	virtual DMResult getMuteAlert(eMuteAlertValues &value) const NOEXCEPT = 0;
	virtual DMResult getVoiceSilenceDetectionMode(eVoiceSilenceDetectionMode& mode) const NOEXCEPT = 0;
    virtual DMResult setOLIFeature(bool enabled) NOEXCEPT = 0;
	virtual DMResult getOLIFeature(bool& enabled) const NOEXCEPT = 0;
	virtual DMResult getExtendedRangeModeEnabled(bool &enabled) const NOEXCEPT = 0;
	virtual DMResult setExtendedRangeModeEnabled(bool value) NOEXCEPT = 0;
	
private:
	void operator delete(void *);
};

/*! \brief IDeviceExtendedInfo
Interface for HID 2.0 devices extended info.
*/
INTF IDeviceExtendedInfo
{
	//Get and set Tattoo Serial Number
    virtual DMResult getProductSerialNumber(eDevice_Type  devType, uint8_t* serialNumber, int32_t& size) const NOEXCEPT = 0;
    virtual DMResult setProductSerialNumber(eDevice_Type  devType, uint8_t const* serialNumber, int32_t size) NOEXCEPT = 0;

    //Get and set Tattoo Build Code
    virtual DMResult getProductBuildCode(eDevice_Type  devType, uint8_t* code, int32_t& size) const NOEXCEPT = 0;
    virtual DMResult setProductBuildCode(eDevice_Type  devType, uint8_t const* code, int32_t size) NOEXCEPT = 0;

	//Get Model ID
	virtual DMResult getModelID(eDevice_Type devType, int32_t& modelID) const NOEXCEPT = 0;

private:
    void operator delete(void *);
};


/*! \brief IHostCommandOption
Interface for setting properties in hostcommand for HID 2.0
*/
INTF IHostCommandOption
{
	/*! Set options for hostcommand level properties */
	virtual DMResult setOption(eCommandOption eCOption, int32_t lValue) NOEXCEPT = 0;

	/*! Get options for hostcommand level properties */
	virtual DMResult getOption(eCommandOption eCOption, int32_t* plValue, int16_t iMaxLength, int16_t* piLength) NOEXCEPT = 0;
};

/*! \brief IMOCCommand
    The interface with commands for MOC handling.
*/
INTF IMOCCommand
{
    virtual DMResult Hook(bool value) NOEXCEPT = 0;
    virtual DMResult Flash() NOEXCEPT = 0;
    virtual DMResult SetHeadsetMute(bool bMute) NOEXCEPT = 0;

    virtual bool getMOCHook() const NOEXCEPT = 0;
    virtual DMResult setMOCHook(bool value) NOEXCEPT = 0;
    virtual bool getMOCMute() const NOEXCEPT = 0;
    virtual DMResult setMOCMute(bool value) NOEXCEPT = 0;
    virtual bool getMOCRing() const NOEXCEPT = 0;
    virtual DMResult setMOCRing(bool value) NOEXCEPT = 0;
    virtual bool getMOCSpeaker() const NOEXCEPT = 0;
    virtual DMResult setMOCSpeaker(bool value) NOEXCEPT = 0;
    virtual bool getMOCOnLine() const NOEXCEPT = 0;
    virtual DMResult setMOCOnLine(bool value) NOEXCEPT = 0;

    //These are specific to Hydra. Leaving it here for now.
    virtual bool getMOCHookDropped() const NOEXCEPT = 0;
    virtual DMResult setMOCHookDropped(bool value) NOEXCEPT = 0;
    virtual bool getMOCHookPending() const NOEXCEPT = 0;
    virtual DMResult setMOCHookPending(bool value) NOEXCEPT = 0;

    //Added for MOC Conferencing
    virtual DMResult ForceHook(bool value) NOEXCEPT = 0;

    //Added for sending DTMF digits to MOC
    virtual DMResult SendDTMFKey(int key) NOEXCEPT = 0;

    //Added for Reject support
    virtual DMResult Reject() NOEXCEPT = 0;

	//Added for Redial support
	virtual DMResult CallRedial() NOEXCEPT = 0;

private:
    void operator delete(void *);
};

/*! \brief IMOCCommandExt
    The interface with commands for Microsoft Lync handling.
*/
INTF IMOCCommandExt
{
    /*! Returns whether Microsoft Lync is currently running */
    virtual bool isLyncRunning() const NOEXCEPT = 0;
    virtual bool getMOCHold() const NOEXCEPT = 0;
    virtual DMResult setMOCHold(bool value) NOEXCEPT = 0;
    virtual bool getISONull() const NOEXCEPT = 0;
    virtual bool getISOData() const NOEXCEPT = 0;
    virtual bool getISORumble() const NOEXCEPT = 0;        

private:
    void operator delete(void *);
};

/*! \brief IDelphiCommand
    The interface with commands for Delphi (mobile) devices
*/
INTF IDelphiCommand 
{
    virtual DMResult Alert(bool on) NOEXCEPT = 0;
    virtual eBTPowerLevel getBTPowerLevel() const NOEXCEPT = 0;
    virtual DMResult setBTPowerMode(eBTPowerLevel value) NOEXCEPT = 0;
    virtual DMResult GetProducts() NOEXCEPT = 0;
    virtual DMResult GetDeviceInterface() NOEXCEPT = 0;
    virtual int32_t getVolumeStepLevel() const NOEXCEPT = 0;
    virtual DMResult setVolumeStepLevel(int32_t level) NOEXCEPT = 0;
    virtual DMResult setHIDPipeMode(HIDPipeMode mode ) NOEXCEPT = 0;
    virtual DMResult SetData(uint8_t* buffer, int32_t bufferLength ) NOEXCEPT = 0;
    virtual DMResult getATDMute(bool& mute) const NOEXCEPT = 0;
    virtual DMResult setATDMute( bool mute ) NOEXCEPT = 0;
    virtual bool getHeadsetMute() const NOEXCEPT = 0;
    virtual DMResult setHeadsetMute(bool mute ) NOEXCEPT = 0;
    virtual int32_t getATDVolumeLevel() const NOEXCEPT = 0;
    virtual DMResult setATDVolumeLevel(int32_t level ) NOEXCEPT = 0;
    virtual DMResult ATDRejectCall( bool flag ) NOEXCEPT = 0;
    virtual DMResult CallHandOff(bool on, int32_t timeout ) NOEXCEPT = 0;
    
private:
    void operator delete(void *);
};

/*! \brief IATDCommand
    The interface with ATD commands
*/
INTF IATDCommand
{
    virtual DMResult AnswerMobileCall() NOEXCEPT = 0;
    virtual DMResult EndMobileCall() NOEXCEPT = 0;
    virtual DMResult Redial() NOEXCEPT = 0;
    virtual DMResult MakeMobileCall(wchar_t const *callerId, int32_t length) NOEXCEPT = 0;
    virtual DMResult GetMobileCallStatus() NOEXCEPT = 0;
    virtual wchar_t const *getCallerId() NOEXCEPT = 0; //TODO: change to accept buffer as param and copy callerId
    virtual DMResult MuteMobileCall(bool mute) NOEXCEPT = 0;
    //virtual DMResult HoldMobileCall(bool hold) NOEXCEPT = 0;

private:
    void operator delete(void *);
};


/*! \brief IDeviceCookie
    The interface with Device Cookie commands
*/
INTF IDeviceCookie
{
	  //Cookie name will always be ASCII so no need for wchar_t
      virtual DMResult Add(char const *name, uint8_t* buffer, int32_t bufferLength ) NOEXCEPT = 0;
	  virtual DMResult Remove(char const *name ) NOEXCEPT = 0;
	  virtual DMResult Get(char const *name ) NOEXCEPT = 0;

private:
    void operator delete(void *);
};

/*! \brief IVOIPCall
    The interface with the command to set the VOIP call active option (flag) 
    for the device.
*/
INTF IVOIPCall
{
    /*! Sets the VOID call active option (flag) for the device to the
     *  given state */
    virtual DMResult setVOIPCallActive(bool value) NOEXCEPT = 0;

private:
    void operator delete(void *);
};

/*! \brief IAudioSense
    The interface with the commands for audio-sensing.
*/
INTF IAudioSense
{
    virtual bool getWindowsMicrophone() NOEXCEPT = 0;
    virtual bool getWindowsSpeaker() NOEXCEPT = 0;

private:
    void operator delete(void *);
};


/*! \brief IAdvanceSettingsExt
Added to support Civic HID 1.0 device specific settings
*/
INTF IAdvanceSettingsExt
{
	virtual DMResult getMuteTone(eMuteTone& value) const NOEXCEPT = 0;
	virtual DMResult setMuteTone(eMuteTone value) NOEXCEPT = 0;
	virtual DMResult getVolumeTone(eVolumeTone& value) const NOEXCEPT = 0;
	virtual DMResult setVolumeTone(eVolumeTone value) NOEXCEPT = 0;
	virtual DMResult getMuteReminder(eMuteReminder& value) const NOEXCEPT = 0;
	virtual DMResult setMuteReminder(eMuteReminder value) NOEXCEPT = 0;
	virtual DMResult getVoiceMuteReminder(eVoiceMuteReminder& value) const NOEXCEPT = 0;
	virtual DMResult setVoiceMuteReminder(eVoiceMuteReminder value) NOEXCEPT = 0;
	virtual DMResult getMuteReminderInterval(uint16_t& interval) const NOEXCEPT = 0;
	virtual DMResult setMuteReminderInterval(uint16_t interval) NOEXCEPT = 0;

private:
	void operator delete(void *);
};

/* This interface is used to gain direct access to BR settings on HID2 device */
class BRDeviceSettings;
INTF IBRCommandInternal
{
    virtual BRDeviceSettings & getBRSettings() = 0;
};


/** This interface is used to obtain an interface from IHostCommand hierarchy.
    It is used because dynamic_cast<> doesn't work across DLL (.so) boundaries.
*/
INTF IHostCommandQuery
{
    virtual bool query(IHostCommand **p) NOEXCEPT = 0;
    virtual bool query(IExtendedVersion **p) NOEXCEPT = 0;
    virtual bool query(IDisplayDeviceCommand **p) NOEXCEPT = 0;
    virtual bool query(IHostCommandExt **p) NOEXCEPT = 0;
    virtual bool query(IDeviceSettings  **p) NOEXCEPT = 0;
    virtual bool query(IAdvanceSettings **p) NOEXCEPT = 0;
    virtual bool query(IMOCCommand **p) NOEXCEPT = 0;
    virtual bool query(IMOCCommandExt **p) NOEXCEPT = 0;
    virtual bool query(IDelphiCommand  **p) NOEXCEPT = 0;
    virtual bool query(IATDCommand **p) NOEXCEPT = 0;
    virtual bool query(IVOIPCall **p) NOEXCEPT = 0;
    virtual bool query(IAudioSense **p) NOEXCEPT = 0;
    virtual bool query(IDeviceSettingsExt **p) NOEXCEPT = 0;
    virtual bool query(IDeviceExtendedInfo **p) NOEXCEPT = 0;
	virtual bool query(IHostCommandOption **p) NOEXCEPT = 0;
	virtual bool query(IAdvanceSettingsExt **p) NOEXCEPT = 0;
    virtual bool query(IBRCommandInternal **p) NOEXCEPT = 0;
   

private:
    void operator delete(void *);
};


#endif // !defined INC_IHOSTCOMMAND
