//
//  PlantronicsManager.swift
//  PlantronicsTest
//
//  Created by Andrea Ciani on 26/07/16.
//  Copyright © 2016 Andrea Ciani. All rights reserved.
//

import Foundation

class PlantronicsManager: PlantronicsHandler {
    
    static let sharedInstance = PlantronicsManager()
    
    private let wrapper = PlantronicsWrapper.sharedInstance()
    
    private var devices: [IDeviceWrapper] = []
    private var currentDevice: IDeviceWrapper?
    
    var eventHandler: DeviceEventHandler?
    
    private init() {
        wrapper.delegate = self
    }
    
    func start() {
        wrapper.startSpokes()
    }
    
    func stop() {
        wrapper.stopSpokes()
    }
    
    // These should be stored in the device obj
    private var _hold = false       // assume not on hold at start
    private var _muted = false      // assume muted on start
    private var _offHook = false    // assume false at start
    private var _ring = false       // assume false at start
    
    //MARK: PlantronicsHandler
    
    @objc func deviceAttached(device: NSObject, withName name: String, ID: String) {
        
        let logical = LogicalDevice(brand: .Plantronics, name: name, ID: ID)
        logical.rawDevice = device
        
        devices.append(device as! IDeviceWrapper)
        
        eventHandler?.deviceDidAttached(self, device: logical)
    }
    
    @objc func deviceDetached(device: NSObject, withID ID: String) {
        
        // Dummy device. Will be checked ID and Brand
        let logical = LogicalDevice(brand: .Plantronics, name: "Unknwon", ID: ID)
        logical.rawDevice = device
        
        eventHandler?.deviceDidDetached(self, device: logical)
        
    }
    
    @objc func didPressMute() {
        NSLog("Mute button pressed")
        eventHandler?.didPressMuteButton(self)
    }
    
    @objc func didPressTalk() {
        NSLog("Did Press Talk")
    }
    
    @objc func didPressOnHook() {
        print("Did Press On Hook")
        _offHook = false;
        eventHandler?.didMoveOnOffHook(self)
    }
    
    @objc func didPressReject() {
        print("Did Press Reject")
    }
    
    @objc func didPressOffHook() {
        print("Did Press Off Hook")
        _offHook = true;
        eventHandler?.didMoveOnOffHook(self)
    }
    
    @objc func didChangeMute(muted: Bool) {
        _muted = muted
        NSLog("Headset change muted to \(muted)")
    }
    
    deinit {
        wrapper.stopSpokes()
    }
}

//MARK: - Device API

extension PlantronicsManager: DeviceAPI {
    
    // (not supported by swift) var eventHanlder: DeviceEventHandler? -> Defined in the main class
    
    func selectActiveDevice(device: LogicalDevice) -> Bool {
        
        if  let raw = device.rawDevice as? IDeviceWrapper,
            let i = devices.indexOf(raw) {
                let device = devices[i] // safe for indexOf
                currentDevice = device
                return true
        }
        return false
    }
    
    /* Properties of selected device */
    
    var muted: Bool? {
        get {
            return _muted
        }
        set {
            guard let m = newValue else { return }
            wrapper.setMute(m)
            _muted = m
        }
    }
    var onHold: Bool?   {
        get {
            return _hold
        }
        set {
            guard let h = newValue else { return }
            wrapper.setOnHold(h)
            _hold = h
        }
    }
    
    var offHook: Bool? {
        get {
           return _offHook
        }
        set {
            guard let v = newValue else { return }
            wrapper.setOffHook(v)
        }
    }
    
    var ring: Bool? {
        get {
           return _ring
        }
        set {
            guard let v = newValue else { return }
            wrapper.setRing(v)
        }
    }
    
}

