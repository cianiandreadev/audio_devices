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
 * @file GNDevice.mm
 * @brief Implements the GNDevice class.
 * GNDevice provides a model to maintain list of attached Jabra devices and their states
 */

/****************************************************************************/
/*                              INCLUDE FILES                               */
/****************************************************************************/

#import "GNDevice.h"
#import <wchar.h>

@implementation GNDevice

@synthesize devHookState,devRingerState,devMuteState,devOnholdState,devOnlineState,deviceInformation;


-(void)initDevice:(Jabra_DeviceInfo)devInfo withHookState:(BOOL)hookState ringerState:(BOOL)rState muteState:(BOOL)mState holdState:(BOOL)hState onlineState:(BOOL)oState{

    deviceInformation = devInfo;
    devHookState = hookState;
    devRingerState = rState;
    devMuteState = mState;
    devOnholdState = hState;
    devOnlineState = oState;
}

- (NSString*) getStringFromWChar:(const wchar_t*) inStr{
    
    char* str = (char*) malloc((wcslen( inStr )) +1);
    wcstombs(str, inStr, wcslen( inStr )+1 );
    NSString* stringValue = [NSString stringWithCString:str encoding:NSUTF8StringEncoding];
    free(str);
    return stringValue;
}

@end
