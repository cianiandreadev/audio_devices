#pragma once
#if !defined INC_DEVICEMANAGER_INTERNAL
#define      INC_DEVICEMANAGER_INTERNAL

#include "DMTypes.h"
#include <cstdint>
#include "IConnectedDevice.h"

#ifdef __cplusplus
extern "C"{
#endif

struct IDeviceManagerInternal {

	/*! Record of data about a device that is not in regular operating mode.
	In most cases, this is a device in DFU mode, after a failed DFU.
	But there are other possible reasons for a device to become non-operational.
	*/
	struct NonOperDevice {
		/*! USB Vendor ID of the device (in this, non-operational state). Some devices
		will have the Plantronics VID, but others will have other VIDs.
		*/
		uint16_t vid;
		/*! USB Product ID of the device (in this, non-operational state). This PID
		is _not_ the PID of the device in the regular device state, and several
		devices may have the same PID in this state.
		*/
		uint16_t pid;
		/*! The USB serial number of the device. Some devices have the serial number
		and for those devices it should be the same as the serial number of the
		device in the regular, operational, state. But, not all devices have
		serial number, and for those, this will be an empty string.
		*/
		wchar_t sernum[64 + 1];
		/*! The system device path of the device. */
		wchar_t path[260 + 1];
		/*! Number of elements in the #possible_regular_pids array */
		uint16_t numRegPids;
		/*! The array of PIDs which this device may have in its regular, operational, state.
		This information is contained in the software, it is not read from the device.
		*/
		uint16_t possible_regular_pids[64];
	};

	/*! Gives the information about non-operational devices. These are, of course, just those
	devices that can be detected programatically. If a device has a serious hardware
	malfunction, it may not be detected.

	\param [in] i_maxNum The dimension of allocated array of device info. At most this many
	elements will be written to the array
	\param [out] o_count The number of elements written to the array. Must not be nullptr.
	\param [out] pBricked An array, allocated by the caller, of device info, where the data
	will be written. If it is nullptr, then the number of elements that would be written
	to it will be written to #o_count (thus enabling the user to find out the number of
	elements needed and allocate array of that size)
	\return indicates the result of operation. It is not an error to have a count of 0 devices.
	*/
	virtual DMResult getNonOperDeviceInfo(int32_t i_maxNum, int32_t *o_count, NonOperDevice *pDevice) NOEXCEPT = 0;

	/*! Gives the version of the device handler for the given PID. The version string is
	allocated by the user, before calling.
	\param [in] productID The product ID (PID) for which to give the handler version
	\param [in] n The size of the version string (in characters)
	\param [out] version The string with the current version of the handler
	\return indicates the result of operation. It is an error if there is no handler
	for the given PID.
	*/
	virtual DMResult GetHandlerVersion(eProductID productID, int32_t n, char *version) NOEXCEPT = 0;

	/*! Unloads a dynamic handler for specified device if all resource that are allocated by it are released.
	If the handler is static, returns success.
	\param productID Product ID (PID) of the device for which to unload handler
	\return indicates the result of operation.
	*/
	virtual DMResult UnloadHandler(eProductID productID) NOEXCEPT = 0;

	/*! Issue an All-Points-Bulletin, which will put any device arrival in custody for a device
	with the specified PID and serial number.
	\param pid The Product ID of the device which APB is issued for
	\param serNo The string of the serial number (may be NULL for devices that have no serial number)
	\return the outcome of the command
	*/
	virtual DMResult issueAPB(int32_t pid, wchar_t const *serNo) NOEXCEPT = 0;

	/*! Cancels a previously issued All-Points-Bulletin. All arrivals that were kept in custody will
	be released.
	\see issueAPB
	\param pid The Product ID of the device which APB is cancelled for
	\param serNo The string of the serial number (may be NULL for devices that have no serial number)
	\return the outcome of the command
	*/
	virtual DMResult cancelAPB(int32_t pid, wchar_t const *serNo) NOEXCEPT = 0;
    
};

/*!
*  Obtain instance of DeviceManagerInternal interface
*  \param ppDevMgr Output parameter which gets filled with pointer to the DeviceMnager
*  \return DM_RESULT_SUCCESS
*/
DMResult DllExport getDeviceManagerInternal(IDeviceManagerInternal** ppDevMgr) NOEXCEPT;

#ifdef __cplusplus
}
#endif

#endif