//
//  TestWrapper.swift
//  DummyProjectPhones
//
//  Created by Andrea on 18/07/16.
//  Copyright © 2016 Andrea Ciani. All rights reserved.
//

class JabraAPI {
    
    private(set) var deviceArray: [GNDevice] = []
    private(set) var selectedDevice: GNDevice? = nil {
        willSet {
            guard let device = selectedDevice where newValue != selectedDevice else { return }
            /* Before change to a new device remove the hook state of the old one.
             This avoid the old device to have an inconsistent state where it's hook off
             but hooked on while not active.
             The code is similar to the `self.hook(true)` but doesn't call the handler that
             should not receive notifications for this bahavior.
             */
            _isButtonPressed = true
            device.devHookState = false
            Jabra_SetOffHook(selectedDeviceID!, false) // force ok. Cannot be nil if device exists.
            _isButtonPressed = false
            
        }
        didSet {
            
            // ----
            
            var count = DEVICE_INITIAL_CNT
            
            let deviceInfoList = UnsafeMutablePointer<Jabra_DeviceInfo>.alloc(10)
            
            /*Get all the attached device information from library*/
            Jabra_GetAttachedJabraDevices(&count, deviceInfoList)
            
            for _ in 0 ..< Int(count) {
                let a = deviceInfoList.advancedBy(0).memory
                print(a)
            }
            
            
            // -----
            
            _refreshInternalState()
            
        }
    }
    private(set) var sdkVersion: String = "" // gather in `_libraryInit`
    
    private var selectedDeviceID: UInt16? {
        get {
            return selectedDevice?.deviceInformation.deviceID
        }
    }
    
    var eventHandler: DeviceEventHandler?
    
    static let sharedInstance = JabraAPI()

    init() {
        _libraryInitialize()
    }
    
    private func _libraryInitialize() {
        /*Function pointers declaration*/
        
        /* Swift C function pointers */
        
        let firstScanForDevicesDonePtr  : @convention(c) (Void) -> Void = {  JabraAPI.sharedInstance.firstScanForDevicesDoneEvent() }
        let deviceAttachedPtr           : @convention(c) (deviceInfo: Jabra_DeviceInfo) -> Void = { deviceInfo in JabraAPI.sharedInstance.deviceAttachedEvent(deviceInfo) }
        let deviceRemovedPtr            : @convention(c) (deviceID: CUnsignedShort) -> Void = { deviceID in JabraAPI.sharedInstance.deviceRemovedEvent(deviceID) }
        let btnInDataRawHIDFuncPtr      : @convention(c) (deviceID: CUnsignedShort, usagePage: CUnsignedShort, usage: CUnsignedShort, buttonInData: CBool) -> Void = { (deviceID: CUnsignedShort, usagePage: CUnsignedShort, usage: CUnsignedShort, buttonInData: CBool) -> Void in
            JabraAPI.sharedInstance.buttonInDataRawHIDFuncEvent(deviceID, usagePage: usagePage, usage: usage, buttonInData: buttonInData)
        }
        let btnInDataTransaledFuncPtr   : @convention(c) (deviceID: CUnsignedShort, translatedInData :Jabra_HidInput, buttonInData: CBool) -> Void = { (deviceID: CUnsignedShort, t_data: Jabra_HidInput, buttonInData: CBool) -> Void in
            JabraAPI.sharedInstance.buttonInDataTranslatedFuncEvent(deviceID, translatedInData: t_data, buttonInData: buttonInData)
        }
        let instance: CUnsignedInt = 0
        
        /*Set the SDK version information*/
        
        let buffer = UnsafeMutablePointer<CChar>.alloc(Int(TXT_BUFF_SIZE))
        if (Return_Ok == Jabra_GetVersion(buffer, TXT_BUFF_SIZE)) {
            sdkVersion = "\(TXT_BUFF_SIZE)\(buffer)"
        }
        
        /*Call the initialize interface by passing the function pointers*/
        Jabra_Initialize(firstScanForDevicesDonePtr, deviceAttachedPtr, deviceRemovedPtr, btnInDataRawHIDFuncPtr, btnInDataTransaledFuncPtr, instance)
    }
    
    // Just an helper method
    private func _post(not: String) {
        NSNotificationCenter.defaultCenter().postNotificationName(not, object: self, userInfo: nil)
    }
    
    // MARK: - C Wrappers
    // MARK: C Callbacks
    
    private func firstScanForDevicesDoneEvent() -> Void {
        var count = DEVICE_INITIAL_CNT
        
        let deviceInfoList = UnsafeMutablePointer<Jabra_DeviceInfo>.alloc(10)
        
        /*Get all the attached device information from library*/
        Jabra_GetAttachedJabraDevices(&count, deviceInfoList)
       
        /*Pass dummy device info, and dummy device ID along with device count*/
        let devInfo = Jabra_DeviceInfo()
        deviceCallback(devInfo, devID: 0, devCount: count, val: DEVICE_SCAN_DONE)
    }
    
    /**
     * Callback for Jabra attach event
     * @param[in] Jabra_DeviceInfo structure
     * @return void
     */
    private func deviceAttachedEvent(deviceInfo: Jabra_DeviceInfo) {
        deviceCallback(deviceInfo, devID: 0, devCount: 0, val: DEVICE_ATTACH)
    }

    /**
     * Callback for Jabra detach event
     * @param[in] deviceID
     * @return void
     */
    private func deviceRemovedEvent(deviceID: CUnsignedShort) {
        let deviceInfo = Jabra_DeviceInfo()
        deviceCallback(deviceInfo, devID: deviceID, devCount: 0, val: DEVICE_DETACH)
    }

    /**
     * Callback for buttonInDataRawHidFuncEvent
     * @param[in] deviceID
     * @return void
     */
    private func buttonInDataRawHIDFuncEvent(deviceID: CUnsignedShort, usagePage: CUnsignedShort, usage: CUnsignedShort, buttonInData: CBool) {
        self.updateHIDInformation(deviceID, usagePage: usagePage, usage: usage, translatedInput: Undefined, buttonState: buttonInData, val: UPDATE_RAW_HID)
    }

    /**
     * Callback for buttonInDataTranslatedFuncEvent
     * @param[in] deviceID
     * @return void
     */
    private func buttonInDataTranslatedFuncEvent(deviceID: CUnsignedShort, translatedInData t_data:Jabra_HidInput, buttonInData b_data: CBool) {
        self.updateHIDInformation(deviceID, usagePage: 0, usage: 0, translatedInput: t_data, buttonState: b_data, val: UPDATE_TRANSLATED_HID)
    }

    //MARK: - Blocks implemenation
    /**
     * Handle C callbacks to manage objective C objects
     * @param[in] void
     * @return void
     */
    private func deviceCallback(deviceInfo: Jabra_DeviceInfo, devID: CUnsignedShort, devCount: CInt, val: JabraLib_CallbackStates) {
        switch val {
        case DEVICE_ATTACH:
            initializeDeviceObj(deviceInfo)
        case DEVICE_DETACH:
            deviceDetached(devID)
        case DEVICE_SCAN_DONE:
            updateFirstScanDoneInformation(devCount)
        default: break
        }
    }
    
    private func updateFirstScanDoneInformation(devCount: CInt) {
//        let count = Int32(devCount)
//        NSNotificationCenter.postNotification(<#T##NSNotificationCenter#>) /// TODO
    }
    
    private func updateHIDInformation(devID: CUnsignedShort, usagePage: CUnsignedShort, usage: CUnsignedShort, translatedInput input: Jabra_HidInput, buttonState: CBool, val: JabraLib_CallbackStates) {
        switch val {
        case UPDATE_RAW_HID:
            let string = ("\(devID) , \(usagePage) , \(usage), \(buttonState)")
//            let string = [NSString stringWithFormat:"0x%02X: 0x%04X, 0x%04X, 0x%04X\n",devID,usagePage,usage,bButtonState]
            if devID == selectedDeviceID {
                updateRawHIDInfo(string)
            }
        case UPDATE_TRANSLATED_HID:
            // Update UI with translated HID data only if device ID matches
            if devID == selectedDeviceID {
                updateTranslatedHIDInfo(devID, translatedInput: input, buttonState: buttonState)
            }
        default:
            print(#function + "Default case!! Check out this! Is that normal?!?")
        }
    }

    /**
     * Initialize GNDevice object once attach callback is received from library
     * @param[in] Jabra_DeviceInfo structure
     * @return void
     */
    private func initializeDeviceObj(devInfo: Jabra_DeviceInfo) {
        let device = GNDevice()
        device.initDevice(devInfo, withHookState: false, ringerState: false, muteState: false, holdState: false, onlineState: false)
        deviceArray.append(device)
        print("Initialized new device:\(device.deviceInformation.deviceName)")
        let ld = logicalDeviceFromGNDevice(device)
        eventHandler?.deviceDidAttached(self, device: ld)
    }
    
    /**
     * GNDevice detached from system
     * @param[in] unsigned short device ID
     * @return void
     */
    func deviceDetached(deviceID: CUnsignedShort) {
        for device in deviceArray {
            if device.deviceInformation.deviceID == deviceID {
                let ld = logicalDeviceFromGNDevice(device)
                eventHandler?.deviceDidDetached(self, device: ld)
                deviceArray.removeAtIndex(deviceArray.indexOf(device)!)
            }
            if selectedDeviceID == deviceID {
                selectedDevice = nil
            }
        }
        print("Detached device:\(deviceID)")
    }

    /**
     * Display the scan count information on UI
     * @param[in] int device count
     * @return void
     */
    private func updateScanCount(devCount: Int) {
        for i in 0 ..< deviceArray.count {
            let device = deviceArray[i]
            let ID = device.deviceInformation.deviceID
            Jabra_SetOffHook(ID, false)
            Jabra_SetRinger(ID, false)
            Jabra_SetMute(ID, false)
            Jabra_SetHold(ID, false)
            Jabra_SetOnline(ID, false)
        }
    }
    
    /**
     * Receive the Raw HID Information
     * @param[in] NSString* message - The Raw HID information to be displayed.
     * @return void
     */
    
    private func updateRawHIDInfo(message: String) {
        print("Device raw info: \(message)")
    }

    /**
     * Receive the Translated HID Information
     * @param[in] unsigned short deviceID - Id of the device, whose translated HID Information is sent.
     * @param[in] Jabra_HidInput translatedInput - Translated HID information recieved from the device.
     * @param[in] bool bButtonState - State of the button
     * @return void
     */
    private func updateTranslatedHIDInfo(deviceID: CUnsignedShort, translatedInput: Jabra_HidInput, buttonState: CBool) {
        let eVal = translatedInput
        
        dispatch_async(dispatch_get_main_queue(),{
            self.updateTranslatedDataUI(deviceID, data: eVal.rawValue, buttonState: buttonState, eVal: eVal)
        })
    }
    

    /**
     * Update UI with the translated HID information recieves as a dictionary
     * @param[in] NSDictionary* data - The Raw HID information to be displayed.
     * @return void
     */
    private func updateTranslatedDataUI(deviceID: CUnsignedShort, data: CUnsignedInt, buttonState: CBool, eVal: Jabra_HidInput) {
        
        guard let id = selectedDeviceID, let device = selectedDevice else {
            print ("Error on selected device: \(selectedDevice)")
            return
        }
        
        if _isButtonPressed { return }
        
        defer {
            _refreshInternalState()
        }
        
        switch eVal {
        case OffHook :
            device.devHookState = buttonState
            Jabra_SetOffHook(id, buttonState)
            // TODO: handler.setOffHook
        case Mute:
            device.devMuteState = !device.devMuteState
            Jabra_SetMute(id, !device.devMuteState)
            eventHandler?.didPressMuteButton(self)
        case Flash: // When on hold flash the lights
            
            if device.devOnholdState == true {
                device.devOnholdState = false
                device.devHookState = true
                
                Jabra_SetOffHook(id, device.devHookState)
                Jabra_SetHold(id, device.devOnholdState)
            } else {
                device.devOnholdState = true
                device.devHookState = false
                
                Jabra_SetHold(id, device.devOnholdState) // maybe the order is important?
                Jabra_SetOffHook(id, device.devHookState)
            }
        default:
            print("Unhandled device event: \(eVal)")
        }
    }
    
    deinit {
        Jabra_Uninitialize()
    }

    /**
     * Update button state for different API testing scenerios like hookoff, mute, hold etc
     * @param[in] void
     * @return void
     */
    private var _isButtonPressed: Bool = false
    
    private func _refreshInternalState() {
        _isButtonPressed = false
    }
}

//MARK: - Jabra sequences implementation (implemented following docs sequences)
extension JabraAPI {

    private func logicalDeviceFromGNDevice(device: GNDevice) -> LogicalDevice {
        let name = String(UTF8String: device.deviceInformation.deviceName) ?? "Unknown"
        let ID = String(device.deviceInformation.deviceID)
        let ld = LogicalDevice(brand: .Jabra, name: name, ID: ID)
        ld.rawDevice = device
        return ld
    }
    
    //MARK: 👨 User Initiated
    // Procedures that comes from the User, i.e., the Swyx app

    func mute(mute: Bool) -> Bool {
        guard let ID = selectedDeviceID, let device = selectedDevice else { return false }
        _isButtonPressed = true
        device.devMuteState = mute
        Jabra_SetMute(ID, mute)
        _refreshInternalState()
        eventHandler?.didPressMuteButton(self)
        return true
    }
    
    func offHook(offHook: Bool) -> Bool {
        guard let ID = selectedDeviceID, let device = selectedDevice else { return false }
        _isButtonPressed = true
        device.devHookState = offHook
        Jabra_SetOffHook(ID, offHook)
        _refreshInternalState()
        eventHandler?.didMoveOnOffHook(self)
        return true
    }
    
    func ring(ring: Bool) -> Bool {
        
        guard let ID = selectedDeviceID, let device = selectedDevice where Jabra_IsRingerSupported(ID) else { return false }
        
        var returnValue: Jabra_ReturnCode?
        returnValue = Jabra_SetRinger(ID, ring)
        
        guard let _ = returnValue else {
            device.devRingerState = ring
            _refreshInternalState()
            eventHandler?.didChangeSelectedDeviceStatus(self)
        }
        return true
    }
    
    func onHold(onHold: Bool) -> Bool {
        guard let ID = selectedDeviceID, let device = selectedDevice else { return false }
        _isButtonPressed = true
        if onHold {
            device.devOnholdState = true
            device.devHookState = false
            
            Jabra_SetHold(ID, device.devOnholdState)
            Jabra_SetOffHook(ID, device.devHookState)
        } else {
            device.devOnholdState = false
            device.devHookState = true
            
            Jabra_SetOffHook(ID, device.devHookState)
            Jabra_SetHold(ID, device.devOnholdState)
        }
        eventHandler?.didChangeSelectedDeviceStatus(self)
        _refreshInternalState()
        return true
    }
}


// MARK: - DeviceAPI protocol conformance
extension JabraAPI: DeviceAPI {
    
    func selectActiveDevice(device: LogicalDevice) -> Bool {
        selectedDevice = device.rawDevice as? GNDevice
        return selectedDevice != nil
    }
    
    // (not supported by swift) var eventHanlder: DeviceEventHandler? -> Defined in the main class
    
    var muted: Bool? {
        get {
            return selectedDevice?.devMuteState
        }
        set {
            guard let m = newValue else { return }
            self.mute(m)
        }
    }
    
    var onHold: Bool? {
        get {
           return selectedDevice?.devOnholdState
        }
        set {
            guard let h = newValue else { return }
            self.onHold(h)
        }
    }
    
    var offHook: Bool? {
        get {
            return selectedDevice?.devHookState
        }
        set {
            guard let h = newValue else { return }
            self.offHook(h)
        }
    }
    
    var ring: Bool? {
        get {
            return selectedDevice?.devRingerState
        }
        set {
            guard let r = newValue else { return }
            self.ring(r)
        }
    }
    
}
