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
 * \brief       This file contains interfaces to the DeviceManager classes.
 * 
 * \author      Ramesh T.
 * \author      Nikola M.
 */

#pragma once
#if !defined INC_DEVICEMANAGER
#define      INC_DEVICEMANAGER

// bsheehan - Spokes 3.0 does not support HID 2.0 devices.
#undef HID_2_0_SUPPORT_ENABLED


#include "DMTypes.h"
#include "SpokesEnums.h"
#include "IDeviceAttributes.h"
#include "IHostCommand.h"
#include "IDeviceEvents.h"
#include "IDeviceListener.h"


#ifdef __cplusplus
extern "C"{
#endif


/*! 
 *  \brief DeviceCallback interface  
 *  To register for Device event inherit this class
 */
INTF IDeviceCallback
{
    /*! Called by ReportReader when data is received from device
     *  \param args Data from device
     */
    virtual void onDataReceived(ReportDataEventArgs const& args) = 0;	
};
typedef IDeviceCallback* pDeviceCallback;

INTF IDeviceBaseExt 
{
	//virtual for dynamic_cast to work
	virtual DMResult getAllConnectedDevices() NOEXCEPT = 0;

};

INTF IDeviceManager;

/*! 
 *  \brief Device interface  
 *  Controlling and monitoring devices is performed through IDevice interface
 */
INTF IDevice : public IDisposable
{
    /*! Gets USB Product ID assigned to the device by Plantronics, Inc.
     *  \return USB Product ID
     */
    virtual int32_t getProductID() const NOEXCEPT = 0;

    /*! Gets USB Vendor ID for Plantronics, Inc., (0x47F).
     *  \return Vendor ID (0x47F)
     */
    virtual int32_t getVendorID() const NOEXCEPT = 0;

    /*! Gets USB firmware version assigned to the device by Plantronics, Inc.
     *  \return USB firmware version number
     */
    virtual int32_t getVersionNumber() const NOEXCEPT = 0;

    /*! Human interface device (HID) path of the device. This is the path the Device Manager uses to read/write to the device.
     *  \param path Pointer to the buffer which will be filled with the device path
     *  \param len Size of buffer
     *  \return DM_RESULT_SUCCESS on success, DM_RESULT_BUFFER_TOO_SMALL if buffer is too small
     */
    virtual DMResult getDevicePath(wchar_t* path, int32_t len) const NOEXCEPT = 0;

    /*! Method which gets internal device name
     *  \param name Pointer to the buffer which will be filled with internal name
     *  \param len Size of buffer
     *  \return DM_RESULT_SUCCESS on success, DM_RESULT_BUFFER_TOO_SMALL if buffer is too small
     */
    virtual DMResult getInternalName(wchar_t* name, int32_t len) const NOEXCEPT = 0;

    /*! Gets name under which the device is marketed.
     *  \param name Pointer to the buffer which will be filled with product name
     *  \param len Size of buffer
     *  \return DM_RESULT_SUCCESS on success, DM_RESULT_BUFFER_TOO_SMALL if buffer is too small
     */
    virtual DMResult getProductName(wchar_t* name, int32_t len) const NOEXCEPT = 0;

    /*! Gets manufacturer name (Plantronics Inc.)
     *  \param name Pointer to the buffer which will be filled with manufacturer name
     *  \param len Size of buffer
     *  \return DM_RESULT_SUCCESS on success, DM_RESULT_BUFFER_TOO_SMALL if buffer is too small
     */
    virtual DMResult getManufacturerName(wchar_t* name, int32_t len) const NOEXCEPT = 0;

    /*! Gets serial number assigned to the USB port.
     *  \param path Pointer to the buffer which will be filled with serial number
     *  \param len Size of buffer
     *  \return DM_RESULT_SUCCESS on success, DM_RESULT_BUFFER_TOO_SMALL if buffer is too small
     */
    virtual DMResult getSerialNumber(wchar_t* serialNumber, int32_t len) const NOEXCEPT = 0;

    /*! Indicates whether this IDevice object is currently attached.
     *  \return Boolean true if this IDevice object is currently attached, false otherwise.
     */
    virtual bool isAttached() const NOEXCEPT = 0;

    /*! Connects to the device and starts listening for input reports from the device.
     *  \return Boolean true on successful attach, false otherwise.
     */
    virtual bool attach() NOEXCEPT = 0;

    /*! Disconnects from the device and stops listening for input reports from the device.
     *  \return Boolean true on successful detach, false otherwise.
     */
    virtual bool detach() NOEXCEPT = 0;

    /*! Determines whether an attached device supports the specified usage.
     *  \return Boolean true if device supports the specific usage, false otherwise
     */
    virtual bool isSupported(uint16_t usage) const NOEXCEPT = 0;    

    /*! Gets an IDeviceAttributes object, which provides metadata about device.
     *  \param ppAttributes Pointer which will be set to an instance of IDeviceAttributes interface
     *  \return DM_RESULT_SUCCESS on success, DM_RESULT_ILLEGAL_ARGUMENT if ppAttributes argument is nullptr
     */
    virtual DMResult getDeviceAttributes(IDeviceAttributes **ppAttributes) const NOEXCEPT = 0;

    /*! Gets an IHostCommand object, which provides methods and properties that can be used to send specific requests to the device from the host application.
     *  \param ppCommand Pointer which will be set to an instance of IHostCommand interface
     *  \return DM_RESULT_SUCCESS on success, DM_RESULT_ILLEGAL_ARGUMENT if ppCommand argument is nullptr
     */
    virtual DMResult getHostCommand(ppHostCommand ppCommand) const NOEXCEPT = 0;

    /*! Gets and IDeviceEvents object, which provides a way to register and unregister for device events.
     *  \param ppEvents Pointer which will be set to an instance of IDeviceEvents interface
     *  \return DM_RESULT_SUCCESS on success, DM_RESULT_ILLEGAL_ARGUMENT if ppEvents argument is nullptr
     */
    virtual DMResult getDeviceEvents(ppDeviceEvents ppEvents) const NOEXCEPT = 0; 
    
    /*! Gets and IDeviceListener object, which provides unified interface for accessing device.
     *  \param ppListener Pointer which will be set to an instance of IDeviceListener interface
     *  \return DM_RESULT_SUCCESS on success, DM_RESULT_ILLEGAL_ARGUMENT if ppListener argument is nullptr
     */
    virtual DMResult getDeviceListener(ppDeviceListener ppListener) const NOEXCEPT = 0;

    /*! Set options for device level properties */
    virtual DMResult setOption(eDeviceOption eDOption, int32_t lValue) NOEXCEPT = 0;

    /*! Get options for device level properties */
    virtual DMResult getOption(eDeviceOption eDOption, int32_t* plValue, int16_t iMaxLength, int16_t* piLength) NOEXCEPT = 0;
   
    /*! Register to receive callbacks on device arrival/removal */
    virtual DMResult registerCallback(pDeviceCallback pDevCallbacks) NOEXCEPT = 0;

    /*! Unregister to receive callbacks on device arrival/removal */
    virtual DMResult unregisterCallback(pDeviceCallback pDevCallbacks) NOEXCEPT = 0;

    /*! Device type. This is a classification of devices, based on their functionallity.
        A device can be of more than one type.
    */
    enum DeviceType {
        /*! Device which carries sound over Bluetooth */
        dtBluetooth,
        /*! Device which carries sound over DECT */
        dtDECT,
        /*! Device which carries sound over wire-USB */
        dtWireline
    };

    /** Returns the type(s) for the given device.

        While most devices are of only one type, some complex devices (eg. Savi 7xx)
        have more than one type.

        @param io_cntRec On input, the size of the array #o_pType (allocated by the caller),
        on output, the number of entries written to the #o_pType array
        @param o_pType The array of device types to be filled
        @return The result of the operation
    */
    virtual DMResult getDeviceType(uint32_t *io_cntType, DeviceType *o_pType) NOEXCEPT = 0;

    /** Returns the (pointer to the) Device Manager that created the device object this
        interface is to.

        This should be a valid pointer, as all device objects are created by Device Manager,
        as long as the device object is valid. If device objects becomes invalid, then you
        may expect an error (null pointer).

        @return The (pointer to the) Device Manager that created the Device object. Null
            pointer on error.
    */
    virtual IDeviceManager *getDeviceManager() NOEXCEPT = 0;

private:
    void operator delete(void *p);
};
typedef IDevice* pDevice;
typedef IDevice** ppDevice;

/*!
 * \brief Group of devices interface
 * Provides access to devices in a group of devices.
 */
INTF IDeviceGroup : public IDisposable {
    /*! Returns an owning pointer to the first device from the group and 
    * removes it from the group.
    * If there is no device in the group (the group is empty), returns nullptr.
    */
    virtual IDevice *getDevice() NOEXCEPT = 0;

    /*! Returns the number of devices in the group.
    * Each successful call to getDevice() will decrement this number.
    */
    virtual uint32_t numDevices() NOEXCEPT = 0;

private:
    void operator delete(void *p);
};

/*! 
 *  \brief DeviceManagerCallback interface  
 *  To receive DeviceManager callbacks, inherit this interface, and use it with #IDeviceManager::registerCallback.
 *  When done, use #IDeviceManager::unregisterCallback.
 */
INTF IDeviceManagerCallback
{
     /*! Will be called when a device is added 
     *  \param pDev Pointer to the IDevice interface of the device instance created for the added device
     *  \param path The device path to the added device
     */
    virtual void onDeviceAdded(IDevice *pDev, wchar_t const *path) = 0;

     /*! Will be called when a device is removed
     *  \param path The device path to the removed device
     */
    virtual void onDeviceRemoved(wchar_t const *path) = 0;

    /*! Will be called before system goes to sleep
     */
    virtual void onSystemSuspending() = 0;
    
    /*! Will be called after system returns from sleep
     */
    virtual void onSystemResuming() = 0;

private:
    void operator delete(void *p);
};

/*!
*  \brief DeviceManagerCallback interface
*  To receive DeviceManager callbacks, inherit this interface, and use it with #IDeviceManager::registerCallback.
*  When done, use #IDeviceManager::unregisterCallback.
*/
INTF IGenericDeviceCallback
{
	/*! Will be called when a device is added
	*  \param pDev Pointer to the IDevice interface of the device instance created for the added device
	*  \param path The device path to the added device
	*/
	virtual void onGenericDeviceAdded(IDevice *pDev, wchar_t const *path) = 0;

	/*! Will be called when a device is removed
	*  \param path The device path to the removed device
	*/
	virtual void onGenericDeviceRemoved(wchar_t const *path) = 0;

	/*! Will be called before system goes to sleep
	*/
	virtual void onGenericSystemSuspending() = 0;

	/*! Will be called after system returns from sleep
	*/
	virtual void onGenericSystemResuming() = 0;

	/*! Called when non-plt HID device is added
	 */
	virtual void onNonPltDeviceAdded() = 0;

private:
	void operator delete(void *p);
};

typedef IDeviceManagerCallback* pDeviceManagerCallback;

/*! 
 *  \brief DeviceManager interface
 *  The Device Manager API provides the host-to-device interface layer for all Plantronics devices
 */
INTF IDeviceManager : public IDisposable
{
    /*! Gets first device that matches specified Vendor ID and Product ID
     *  \param vendorID Vendor of the HID device (for example, 0x047F for Plantronics)
     *  \param productID Product ID of the HID device
     *  \param ppDev Pointer to the IDevice which will be filled with device if found, or nullptr if device is not found
     *  \return DM_RESULT_SUCCESS if device is found, DM_RESULT_NOT_FOUND if device was not found, DM_RESULT_ILLEGAL_ARGUMENT if ppDev is nullptr
     */
    virtual DMResult getDevice(eVendorID vendorID, eProductID productID, ppDevice ppDev) NOEXCEPT = 0;

    /*! Gets first device that matches specified Vendor ID
     *  \param vendorID Vendor of the HID device (for example, 0x047F for Plantronics)
     *  \param ppDev Pointer to the IDevice which will be filled with device if found, or nullptr if device is not found
     *  \return DM_RESULT_SUCCESS if device is found, DM_RESULT_NOT_FOUND if device was not found, DM_RESULT_ILLEGAL_ARGUMENT if ppDev is nullptr
     */
    virtual DMResult getDevice(eVendorID vendorID, ppDevice ppDev) NOEXCEPT = 0;

    /*! Gets first device that matches specified device path
     *  \param devicePath HID device path
     *  \param ppDev Pointer to the IDevice which will be filled with device if found, or nullptr if device is not found
     *  \return DM_RESULT_SUCCESS if device is found, DM_RESULT_NOT_FOUND if device was not found, DM_RESULT_ILLEGAL_ARGUMENT if ppDev or devicePath are nullptr
     */
    virtual DMResult getDevice(const wchar_t* devicePath, ppDevice ppDev) NOEXCEPT = 0;


    virtual DMResult getDevices(IDeviceGroup** devices) NOEXCEPT = 0;
	
    virtual DMResult getHIDDevices(uint16_t i_usagePage, IDeviceGroup** devices) NOEXCEPT = 0;

    virtual DMResult getDevices(eVendorID vendorID, IDeviceGroup** devices) NOEXCEPT = 0;

    virtual DMResult getDevices(eVendorID vendorID, eProductID productID, IDeviceGroup** devices) NOEXCEPT = 0;

    //Set/Get options for device manager level properties
    virtual DMResult setOption(eDMOption eDOption, int32_t lValue) NOEXCEPT = 0;

    virtual DMResult getOption(eDMOption eDOption, int32_t* plValue, int16_t iMaxLength, int16_t* piLength) NOEXCEPT = 0;  
     
    //Callbacks registration
    virtual DMResult registerCallback(pDeviceManagerCallback pDMCallbacks) NOEXCEPT = 0;
    virtual DMResult unregisterCallback(pDeviceManagerCallback pDMCallbacks) NOEXCEPT = 0;
	virtual DMResult registerCallback(IGenericDeviceCallback *pDMCallbacks) NOEXCEPT = 0;
	virtual DMResult unregisterCallback(IGenericDeviceCallback *pDMCallbacks) NOEXCEPT = 0;
    virtual DMResult setDeviceFilterEnabled(bool) NOEXCEPT = 0;
    virtual bool getDeviceFilterEnabled() NOEXCEPT = 0;
	virtual IDeviceBaseExt * getDeviceExtension(IDevice* pDev) NOEXCEPT = 0;

private:
    void operator delete(void *p);
};
typedef IDeviceManager* pDeviceManager;
typedef IDeviceManager** ppDeviceManager;

/*!  
 *  Obtain instance of DeviceManager interface
 *  \param ppDevMgr Output parameter which gets filled with pointer to the DeviceMnager
 *  \return DM_RESULT_SUCCESS
 */
DMResult DllExport getDeviceManager(ppDeviceManager ppDevMgr) NOEXCEPT;

#ifdef __cplusplus
}
#endif


#endif // !defined INC_DEVICEMANAGER
