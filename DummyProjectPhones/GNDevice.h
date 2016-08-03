
/* --------------------------------------------------------------------
 *
 *  GGGGGG  NN    N
 *  G       N N   N
 *  G  GGG  N  N  N - Netcom
 *  G    G  N   N N
 *  GGGGGG  N    NN
 *
 *  Copyright (c) 2016, GN-Netcom
 * -------------------------------------------------------------------- */

/**
 * @file GNDevice.h
 * @brief Defines the GNDevice class. GNDevice provides a model to maintain list of attached 
 * Jabra devices and their states
 */
 
/****************************************************************************/
/*                              INCLUDE FILES                               */
/****************************************************************************/

#import <Foundation/Foundation.h>
#import "JabraNativeHid.h"

@interface GNDevice : NSObject{
    
    /*hook switch state for Jabra device*/
    BOOL devHookState;
    /*Ringer state for Jabra device*/
    BOOL devRingerState;
    /*Mute state for Jabra device*/
    BOOL devMuteState;
    /*Hold state for Jabra device*/
    BOOL devOnholdState;
    /*Online state for Jabra device*/
    BOOL devOnlineState;
    /*Jabra_DeviceInfo structure for Jabra device*/
    Jabra_DeviceInfo deviceInformation;
}

@property(nonatomic,assign)BOOL devHookState;
@property(nonatomic,assign)BOOL devRingerState;
@property(nonatomic,assign)BOOL devMuteState;
@property(nonatomic,assign)BOOL devOnholdState;
@property(nonatomic,assign)BOOL devOnlineState;
@property(nonatomic,assign) Jabra_DeviceInfo deviceInformation;

/**
 * Initializer to initialize GNDevice object & its states- Hook off, ringer, mute, hold & online
 * @param[in] Jabra_DeviceInfo structure, bool values for various states
 * @return void
 */
-(void)initDevice:(Jabra_DeviceInfo)devInfo withHookState:(BOOL)hookState ringerState:(BOOL)rState muteState:(BOOL)mState holdState:(BOOL)hState onlineState:(BOOL)oState;

/**
 * Utility method which converts wide character to string
 * @param[in] wchar_t
 * @return NSString
 */
- (NSString*)getStringFromWChar:(const wchar_t*) inStr;

@end
