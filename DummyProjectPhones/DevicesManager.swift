//
//  DevicesManager.swift
//  DummyProjectPhones
//
//  Created by Andrea on 27/07/16.
//  Copyright © 2016 Andrea Ciani. All rights reserved.
//

import Foundation

protocol DeviceAPI {
    
    var eventHandler: DeviceEventHandler? { get set }
    func selectActiveDevice(device: LogicalDevice) -> Bool
    
    /* Properties of selected device */
    var muted  : Bool?   { get set }
    var onHold : Bool?   { get set }
    var offHook: Bool?   { get set }
    var ring   : Bool?   { get set }
    
}

enum DeviceBrand {
    case Jabra
    case Plantronics
}

class LogicalDevice : Equatable {
    
    let brand: DeviceBrand
    var name: String
    let ID: String
    var rawDevice: NSObject?
    
    init(brand: DeviceBrand, name: String, ID: String?) {
        self.ID = ID ?? "\(random().hashValue)" // If not provided create something random
        self.brand = brand
        self.name = name
    }
}

func ==(lhs: LogicalDevice, rhs: LogicalDevice) -> Bool {
    return lhs.ID == rhs.ID && lhs.brand == rhs.brand
}

protocol DeviceEventHandler {
    
    // Device Events
    func deviceDidAttached(source: DeviceAPI, device: LogicalDevice)
    func deviceDidDetached(source: DeviceAPI, device: LogicalDevice)
    
    // Status Events
    func didPressMuteButton(source: DeviceAPI)
    func didMoveOnOffHook(source: DeviceAPI)
    func didChangeSelectedDeviceStatus(source: DeviceAPI)

}

class DevicesManager: DeviceEventHandler {
    
    private let _not = NSNotificationCenter.defaultCenter()
    struct Notifications {
        
        /// Fired when a new device is being attached
        static let deviceAttached = "DevicesManager.deviceAttached"
        /// Fired when a device is being detached
        static let deviceDetached = "DevicesManager.deviceDetached"
        
        /// Fired when the selected device changes.
        static let deviceChanged = "DevicesManager.deviceChanged"
        
        /// Fired when the currentDevice change the mute button status
        static let muteButtonPressed = "DeviceManager.muteButtonPressed"
        
        /// Fired when the selected device receive an event and change one or more of its status.
        static let deviceStatusChanged = "DeviceManager.deviceStatusChanged"
    }
    
    static let defaultManager = DevicesManager()
    
    // APIs managers
    private let _jabra: JabraAPI
    private let _plantronics: PlantronicsManager
    
    private(set) var currentDevice: LogicalDevice? {
        didSet {
            defer { _not.postNotificationName(Notifications.deviceChanged, object: self) }
            guard let cd = currentDevice else { _currentHandler = nil; return}
            switch cd.brand {
            case .Jabra:
                _currentHandler = _jabra
            case .Plantronics:
                _currentHandler = _plantronics
            }
        }
    }
    private(set) var devices: [LogicalDevice] = []
    
    private var _currentHandler: DeviceAPI?
    
    init() {
        _jabra = JabraAPI.sharedInstance
        _plantronics = PlantronicsManager.sharedInstance
            
        _jabra.eventHandler = self
        _plantronics.eventHandler = self
        _plantronics.start()
    }
    
    func selectDevice(device: LogicalDevice) {
        guard let index = devices.indexOf({ $0 == device }) else { return }
        currentDevice = devices[index]
        _currentHandler?.selectActiveDevice(currentDevice!) // `indexOf` did take care of this unwrap.
    }
    
    deinit {
        NSNotificationCenter.defaultCenter().removeObserver(self)
    }
    
}

// MARK - Device handling
extension DevicesManager {
    
    func deviceDidAttached(source: DeviceAPI, device: LogicalDevice) {
        self.devices.append(device)
        _not.postNotificationName(Notifications.deviceAttached, object: self)
    }
    
    func deviceDidDetached(source: DeviceAPI, device: LogicalDevice) {
        guard let index = devices.indexOf(device) else {
            print("A device has been detached but never registerd")
            return
        }
        self.devices.removeAtIndex(index)
        _not.postNotificationName(Notifications.deviceDetached, object: self)
    }
    
    // MARK: - Device API
    
    var mute: Bool? {
        get {
            return _currentHandler?.muted
        }
        set {
            _currentHandler?.muted = newValue
        }
    }
    
    var hold: Bool? {
        get {
            return _currentHandler?.onHold
        }
        set {
            _currentHandler?.onHold = newValue
        }
    }
    
    var offHook: Bool?   {
        get {
            return _currentHandler?.offHook
        }
        set {
            _currentHandler?.offHook = newValue
        }
    }
    
    var ring  : Bool?   {
        get {
            return _currentHandler?.ring
        }
        set {
            _currentHandler?.ring = newValue
        }
    }
    
    //MARK: Event Handler
    
    func didPressMuteButton(source: DeviceAPI) {
        print("DEVICE MANAGER SAYS: <<MUTE BUTTON IS PRESSED!>>")
        _not.postNotificationName(Notifications.muteButtonPressed, object: self)
    }
    
    func didMoveOnOffHook(source: DeviceAPI) {
        print("DEVICE MANAGER SAYS: <<MOVED TO \((source.offHook ?? false ) ? "ON" : "OFF") HOOK!")
        _not.postNotificationName(Notifications.deviceStatusChanged, object: self)
    }
    
    func didChangeSelectedDeviceStatus(source: DeviceAPI) {
        print("DEVICE MANAGER SAYS: <<DEVICE SELECTION CHANGED!>>")
        _not.postNotificationName(Notifications.deviceStatusChanged, object: self)
    }
    
}