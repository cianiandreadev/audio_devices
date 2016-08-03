//
//  ViewController.swift
//  DummyProjectPhones
//
//  Created by Andrea on 18/07/16.
//  Copyright © 2016 Andrea Ciani. All rights reserved.
//

import Cocoa


class ViewController: NSViewController {

    @IBOutlet var deviceList: NSPopUpButton!
    
    let manager = DevicesManager.defaultManager
    
    override func viewDidLoad() {
        super.viewDidLoad()
        registerForNotifications()
    }
    
    let not = NSNotificationCenter.defaultCenter()
    private func registerForNotifications() {
        
        not.addObserver(self, selector: #selector(refreshDeviceList), name: DevicesManager.Notifications.deviceAttached, object: nil)
        not.addObserver(self, selector: #selector(refreshDeviceList), name: DevicesManager.Notifications.deviceDetached, object: nil)
        
        // just for test
        
        not.addObserver(self, selector: #selector(testNotification_deviceChanged), name: DevicesManager.Notifications.deviceChanged, object: nil)
        not.addObserver(self, selector: #selector(testNotification_muteButtonPressed), name: DevicesManager.Notifications.muteButtonPressed, object: nil)
        not.addObserver(self, selector: #selector(testNotification_deviceStatusChanged), name: DevicesManager.Notifications.deviceStatusChanged, object: nil)
        
    }
    
    override func viewDidAppear() {
        super.viewDidAppear()
        refreshDeviceList()
    }

    var i = 0
    @IBAction func muteButtonPressed(sender: NSButton) {
        switch i {
        case 0:
            sender.title = "Next: Mute on"
        case 1:
            manager.mute = true
            sender.title = "Next: Mute Off"
        case 2:
            manager.mute = false
            sender.title = "Next: Hold on"
        case 3:
            manager.hold = true
            sender.title = "Next: Hold Off"
        case 4:
            manager.hold = false
            sender.title = "Next: Restart"
        default:
            sender.title = "Push me please 😫"
            i = -1
        }
        i = i+1
    }
    
    // MARK: Callbacks
    
    func refreshDeviceList() {
        deviceList.removeAllItems()
        
        for device in manager.devices {
            deviceList.addItemWithTitle(device.name + "(\(device.ID))")
        }
    }
    
    @IBAction func selectedDeviceChanged(sender: NSPopUpButton) {
        let i = sender.indexOfSelectedItem
        manager.selectDevice(manager.devices[i])
    }
    
    //MARK: Notifications test
    
    func testNotification_deviceChanged() {
        print(#function)
    }
    
    func testNotification_muteButtonPressed () {
        print(#function)
    }
    
    func testNotification_deviceStatusChanged() {
        print(#function)
    }
    
}

