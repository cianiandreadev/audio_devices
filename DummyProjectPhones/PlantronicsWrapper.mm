//
//  PlantronicsWrapper.m
//  PlantronicsTest
//
//  Created by Andrea Ciani on 26/07/16.
//  Copyright © 2016 Andrea Ciani. All rights reserved.
//

#import "PlantronicsWrapper.h"
#import "PlantronicsWrapperC.h"

#import "EventSink.h"

#import <iostream>
#import <Spokes3GSDK/cpp/query_cast.h>

#import "IDeviceWrapper+IDeviceC.h"

#define NOT_SUPPORTED(NAME) [NSString stringWithFormat:@"%s not supported on Plantronics devices",NAME]

@interface PlantronicsWrapper() {
    pSessionManager sessionManager;
    pSession session;
    IDevice* activeDevice;
    DeviceListenerEventSink* deviceListenerCallback;
    CallEventSink* callEvents;
    SessionManagerEventSink* sessionManagerEvents;
    ICallCommand* callCommand;
}
@end


@implementation PlantronicsWrapper

+ (instancetype)sharedInstance
{
    static PlantronicsWrapper *sharedInstance = nil;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        sharedInstance = [[PlantronicsWrapper alloc] init];
        // Do any other initialisation stuff here
    });
    return sharedInstance;
}



void PlantronicsWrapperPrint(const char* text) {
    NSString *s = [NSString stringWithCString:text encoding:NSUTF8StringEncoding];
    [PlantronicsWrapper print:s];
}

+ (void)print:(NSString*)text {
    NSLog(@"%@", text);
}

- (void)startSpokes {
    
    InitSpokesRuntime();
    
    // create session manager
    if( SM_RESULT_SUCCESS == getSessionManager(&sessionManager) )
    {
        // create session
        if( SM_RESULT_SUCCESS == sessionManager->registerSession( L"Sample client", &session ) )
        {
            IUserPreference* userPreference = nullptr;
            if( SM_RESULT_SUCCESS == sessionManager->getUserPreference( &userPreference) )
            {
                // set this session as default one for receiving CallRequest events
                int32_t pluginId;
                session->getPluginId(&pluginId);
                userPreference->setDefaultSoftphone( pluginId );
            }
            
            // get call command
            if( SM_RESULT_SUCCESS == session->getCallCommand( &callCommand ) )
            {
                // sink to all call events
                callEvents = new CallEventSink(session);
                sessionManagerEvents = new SessionManagerEventSink( sessionManager );
                
                // Attach device listener (if device is attached to PC)
                [self AttachDeviceListener];
            }
        }
    }
    
}

- (void)stopSpokes {
    
    [self RemoveDeviceListener];
    sessionManager->unregisterSession( session );
    session->Release();
    callCommand = nullptr;
    ShutDownSpokesRuntime();
}

void PlantronicsWrapperAttachDeviceListener() {
    [[PlantronicsWrapper sharedInstance] AttachDeviceListener];
}

- (void)AttachDeviceListener
{
    if( SM_RESULT_SUCCESS != session->getActiveDevice( &activeDevice ) )
    {
        NSLog(@"there is no active devices, please attach one then run the app again");
        activeDevice = nullptr;
    }
    else
    {
        // Get device listener
        pDeviceListener dev_listener = nullptr;
        
        auto dm_result = activeDevice->getDeviceListener(&dev_listener);
        
        if(dm_result != DM_RESULT_SUCCESS)
        {
            NSLog(@"failed to get device listener interface");
        }
        else
        {
            // Register device listener callbacks
            deviceListenerCallback = new DeviceListenerEventSink();
            dm_result = dev_listener->registerCallback(deviceListenerCallback);
            
            if(dm_result != DM_RESULT_SUCCESS)
            {
                NSLog(@"failed to register device listener callback");
            }
            
            [self printDevice:activeDevice];
            activeDevice->attach();
            
            if (activeDevice != nullptr) {
                IDeviceWrapper *wrapper = [[IDeviceWrapper alloc] initWithDevice:activeDevice];
                NSString* name = [wrapper productName];
//                NSString* ID = [NSString stringWithFormat:@"%i",wrapper.productID];
#warning We should have different IDs but for now we support only one Plantronics device
                NSString *ID = @"FIXED_DEVICE_ID";
                [self.delegate deviceAttached:wrapper withName:name ID:ID];
            }
        }
    }
}

void PlantronicsWrapperRemoveDeviceListener() {
    [[PlantronicsWrapper sharedInstance] RemoveDeviceListener];
}

- (void)RemoveDeviceListener
{
    // Cleanup
    if (activeDevice != nullptr)
    {
        pDeviceListener dev_listener = nullptr;
        auto dm_result = activeDevice->getDeviceListener(&dev_listener);
        if (dm_result == DM_RESULT_SUCCESS && deviceListenerCallback != nullptr)
        {
            dev_listener->unregisterCallback(deviceListenerCallback);
            delete deviceListenerCallback;
        }
        
        if (activeDevice != nullptr) {
            IDeviceWrapper *wrapper = [[IDeviceWrapper alloc] initWithDevice:activeDevice];
#warning We should have different IDs but for now we support only one Plantronics device
//            NSString* ID = [NSString stringWithFormat:@"%i",wrapper.productID];
            NSString* ID = @"FIXED_DEVICE_ID";
            [self.delegate deviceDetached:wrapper withID:ID];
        }
            
        activeDevice->Release();
        
        activeDevice = nullptr;
    }
}

/**
 *  @brief Helper function that attempt to execute a function on the device handling eventual errors.
 *
 *  @param command Command to execute in the Plantronics device.
 *
 *  @return True if the command is being executed, false otherwise.
 */
- (BOOL)executeHostCommand:(void (^_Nullable)(IHostCommandExt *hostCommandExt)) command {
    
    IHostCommand* hostCommand = nullptr;
    if( DM_RESULT_SUCCESS != activeDevice->getHostCommand( &hostCommand ) || hostCommand == nullptr)
    {
        NSLog(@"there is no active devices, please attach one");
        return false;
    }
    
    IHostCommandExt* hostCommandExt = query_cast<IHostCommandExt>(hostCommand);
    if (hostCommandExt != nullptr) {
        command(hostCommandExt);
    }
    return false;
}

#pragma mark - Delegate 🔥

- (void)DidPressTalk {
    [self.delegate didPressTalk];
}

- (void)DidPressReject {
    [self.delegate didPressReject];
}

- (void)DidPressOnHook {
    [self.delegate didPressOnHook];
}

- (void)DidPressOffHook {
    [self.delegate didPressOffHook];
}

- (void)DidPressMute {
    [self.delegate didPressMute];
}

// Only for states! Not for events!!
void PlantronicsWrapperHeadsetStateChanged(DeviceListenerEventArgs const &args) {
    
    switch (args.headsetStateChange) {
        case HS_STATE_CHANGE_MUTE_OFF:
            [[PlantronicsWrapper sharedInstance] DidChangeMute:NO];
            break;
        case HS_STATE_CHANGE_MUTE_ON:
            [[PlantronicsWrapper sharedInstance] DidChangeMute:YES];
            break;
        default:
            break;
    }
}

// Only for events! Not for states!!
void PlantronicsWrapperHeadsetButtonPressed(DeviceListenerEventArgs const &args) {
    
    switch (args.headsetButton) {
        case HS_STATE_CHANGE_MUTE_ON:
            [[PlantronicsWrapper sharedInstance] DidPressMute];
            break;
        case HEADSET_BUTTON_TALK:
            [[PlantronicsWrapper sharedInstance] DidPressTalk];
            break;
        case HEADSET_BUTTON_REJECT:
            [[PlantronicsWrapper sharedInstance] DidPressReject];
            break;
        case HEADSET_BUTTON_ON_HOOK:
            [[PlantronicsWrapper sharedInstance] DidPressOnHook];
            break;
        case HEADSET_BUTTON_OFF_HOOK:
            [[PlantronicsWrapper sharedInstance] DidPressOffHook];
            break;
            
        default:
            break;
    }
    
}

- (void)DidChangeMute:(BOOL)muted {
    [self.delegate didChangeMute:muted];
}

- (BOOL)setMute:(BOOL)mute {
    
    bool __block result = false;
    
    [self executeHostCommand:^(IHostCommandExt *hostCommandExt) {
        result = hostCommandExt -> setHeadsetMute(mute);
    }];
    
    return result;
}

- (BOOL)setOnHold:(BOOL)hold {
    DMResult __block result = DM_RESULT_FAIL;
    
    [self executeHostCommand:^(IHostCommandExt *hostCommandExt) {
        result = hostCommandExt -> hold(LINE_TYPE_VOIP, hold); // VoIP. Is that righ?
    }];
    
    return result == DM_RESULT_SUCCESS;
}

- (BOOL)setOffHook:(BOOL)offHook {
    NSLog(@"%@",NOT_SUPPORTED(__FUNCTION__));
    return false;
}

- (BOOL)setRing:(BOOL)ring {
    NSLog(@"%@",NOT_SUPPORTED(__FUNCTION__));
    
    return false;
}

- (NSString*)printDevice:(IDevice*)device
{
    wchar_t buffer[1024];
    device->getProductName( buffer, 1024 );
    NSString* name = [[NSString alloc] initWithBytes:buffer length:wcslen(buffer)*sizeof(*buffer) encoding:NSUTF32LittleEndianStringEncoding];
    NSLog(@"Device: %@", name);
    return name;
}




@end
