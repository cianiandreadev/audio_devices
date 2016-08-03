//
//  IDeviceWrapper.h
//  DummyProjectPhones
//
//  Created by Andrea on 29/07/16.
//  Copyright © 2016 Andrea Ciani. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface IDeviceWrapper : NSObject

/*! Gets USB Product ID assigned to the device by Plantronics, Inc.
 *  \return USB Product ID
 */
@property (atomic, readonly) int productID;

/*! Gets USB Vendor ID for Plantronics, Inc., (0x47F).
 *  \return Vendor ID (0x47F)
 */
@property (atomic, readonly) int vendorID;

/*! Gets USB firmware version assigned to the device by Plantronics, Inc.
 *  \return USB firmware version number
 */
@property (atomic, readonly) int versionNumber;

/*! Human interface device (HID) path of the device. This is the path the Device Manager uses to read/write to the device.
 *  \param path Pointer to the buffer which will be filled with the device path
 *  \param len Size of buffer
 *  \return DM_RESULT_SUCCESS on success, DM_RESULT_BUFFER_TOO_SMALL if buffer is too small
 */
@property (atomic, readonly) NSString* _Nullable devicePath;

/*! Method which gets internal device name
 *  \param name Pointer to the buffer which will be filled with internal name
 *  \param len Size of buffer
 *  \return DM_RESULT_SUCCESS on success, DM_RESULT_BUFFER_TOO_SMALL if buffer is too small
 */
@property (atomic, readonly) NSString* _Nullable internalName;

/*! Gets name under which the device is marketed.
 *  \param name Pointer to the buffer which will be filled with product name
 *  \param len Size of buffer
 *  \return DM_RESULT_SUCCESS on success, DM_RESULT_BUFFER_TOO_SMALL if buffer is too small
 */
@property (atomic, readonly) NSString* _Nullable productName;

/*! Gets manufacturer name (Plantronics Inc.)
 *  \param name Pointer to the buffer which will be filled with manufacturer name
 *  \param len Size of buffer
 *  \return DM_RESULT_SUCCESS on success, DM_RESULT_BUFFER_TOO_SMALL if buffer is too small
 */
@property (atomic, readonly) NSString* _Nullable manufacturerName;

/*! Gets serial number assigned to the USB port.
 *  \param path Pointer to the buffer which will be filled with serial number
 *  \param len Size of buffer
 *  \return DM_RESULT_SUCCESS on success, DM_RESULT_BUFFER_TOO_SMALL if buffer is too small
 */
@property (atomic, readonly) NSString* _Nullable serialNumber;
    
@property (atomic, readonly) BOOL attached;

/*! Connects to the device and starts listening for input reports from the device.
 *  \return Boolean true on successful attach, false otherwise.
 */
-(BOOL)attach;

/*! Disconnects from the device and stops listening for input reports from the device.
 *  \return Boolean true on successful detach, false otherwise.
 */
-(BOOL)detach;

/*! Determines whether an attached device supports the specified usage.
 *  \return Boolean true if device supports the specific usage, false otherwise
 */
-(BOOL)isSupported:(uint16) usage;
    
/*******
 
                                MISSING WRAPPING
    
 *******/


    /*! Gets an IDeviceAttributes object, which provides metadata about device.
     *  \param ppAttributes Pointer which will be set to an instance of IDeviceAttributes interface
     *  \return DM_RESULT_SUCCESS on success, DM_RESULT_ILLEGAL_ARGUMENT if ppAttributes argument is nullptr
     */
//    virtual DMResult getDeviceAttributes(IDeviceAttributes **ppAttributes) const NOEXCEPT = 0;
    
    /*! Gets an IHostCommand object, which provides methods and properties that can be used to send specific requests to the device from the host application.
     *  \param ppCommand Pointer which will be set to an instance of IHostCommand interface
     *  \return DM_RESULT_SUCCESS on success, DM_RESULT_ILLEGAL_ARGUMENT if ppCommand argument is nullptr
     */
//    virtual DMResult getHostCommand(ppHostCommand ppCommand) const NOEXCEPT = 0;
    
    /*! Gets and IDeviceEvents object, which provides a way to register and unregister for device events.
     *  \param ppEvents Pointer which will be set to an instance of IDeviceEvents interface
     *  \return DM_RESULT_SUCCESS on success, DM_RESULT_ILLEGAL_ARGUMENT if ppEvents argument is nullptr
     */
//    virtual DMResult getDeviceEvents(ppDeviceEvents ppEvents) const NOEXCEPT = 0;

    /*! Gets and IDeviceListener object, which provides unified interface for accessing device.
     *  \param ppListener Pointer which will be set to an instance of IDeviceListener interface
     *  \return DM_RESULT_SUCCESS on success, DM_RESULT_ILLEGAL_ARGUMENT if ppListener argument is nullptr
     */
//    virtual DMResult getDeviceListener(ppDeviceListener ppListener) const NOEXCEPT = 0;

    /*! Set options for device level properties */
//    virtual DMResult setOption(eDeviceOption eDOption, int32_t lValue) NOEXCEPT = 0;

    /*! Get options for device level properties */
//    virtual DMResult getOption(eDeviceOption eDOption, int32_t* plValue, int16_t iMaxLength, int16_t* piLength) NOEXCEPT = 0;

    /*! Register to receive callbacks on device arrival/removal */
//    virtual DMResult registerCallback(pDeviceCallback pDevCallbacks) NOEXCEPT = 0;

    /*! Unregister to receive callbacks on device arrival/removal */
//    virtual DMResult unregisterCallback(pDeviceCallback pDevCallbacks) NOEXCEPT = 0;




@end
