# audio_devices

Using Jabra and Plantronics SDKs in my work I found out that can be a little bit tricky to import and use them in a modern MacOS project written in Swift.
Then I decided to create this Dummy Project building wrappers for their SDKs **as example on how to use that SDKs in a modern project**. 

Of course I release the project as it is and the ownership of Jabra and Plantronics SDKs belong to the respectives companies.

It is written in **Swift 2.2** with XCode *7.3.1* and tested on _MacOs ElCapitan_.

##How to use it

Mainly the project is build in 3 parts:

* **The Jabra SDK and Wrappers.**
* **The Plantronics SDK and Wrappers.**
* **The Manager** (`DeviceManager.swift`), useful as example to handle both the SDKs simultaneously.

I provide the Jabra and Planotronics SDKs in the application.

The original SDK sources are:

* [Jabra Developers Website](https://developer.jabra.com/sdks)
* [Plantronics Developers Website](developer.plantronics.com)


Currently the manager supports the following features:

* *Hook*(up/down) notifications.
* *Mute/unmute*
* *Hold/unhold*
* *Ring*

If you want to extend the features you need to add the properties to the `DeviceAPI` protocol and implement every getter and setter in the Jabra and Plantronics wrappers.

If you want to add another brand you can just add the name to the `DeviceBrand` enum and create a wrapper/handler conform to the `DeviceAPI` protocol.

The `DeviceHandler` protocols is a delegate protocol between the brand API wrapper and the manager and it's used to handle the events from/to the wrappers. You usually do not need to modify anything here execpt the case you're adding a new brand or new *DeviceAPI properties*.


##Notes:

###Jabra:

In my case, when multiple Jabra devices are connected, I had an issue about the state of the on/off hook of the phone.
In particular, if the user picks the phone up (*hook off state activated*), switches the selection to a second phone, and hook up the first phone, the state of the first one is no longer set to *hook on*.

To fix this issue (I had the same issue also in the Jabra Demo app) I assume that every time the user switch the phone, he hook on the other one, and I set the hook on before switching to the new phone (This is done internally and no notifications are fired in the manager).

Currently (02/08/2016) there is no better handling about that done by Jabra.

###Plantronics:

Even if the Wrappers and the main Manager (`DeviceManager.swift`) are able to handle multiple attached devices, Planotronics SDK seems that does not support this feature (this is what I get from the got but I can be wrong). Then, I assign to the device a fixed ID and **only one Plantronics device can be handled at a time**.

- - - -

# Release Notes

## 0.1
First community release.
###Known bugs:

1. Plantronics can handle just one device at a time
2. Jabra SDK may goes on an inconsistent state if the phone is hooked up while another source is being selected. Fixed by setting hook off state every time I switch to a new device.
