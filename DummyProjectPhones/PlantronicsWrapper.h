//
//  PlantronicsWrapper.h
//  PlantronicsTest
//
//  Created by Andrea Ciani on 26/07/16.
//  Copyright © 2016 Andrea Ciani. All rights reserved.
//

#import <Foundation/Foundation.h>

@protocol PlantronicsHandler

- (void)deviceAttached:(NSObject* _Nonnull)device withName:(NSString* _Nonnull)name ID:(NSString* _Nonnull)ID;
- (void)deviceDetached:(NSObject* _Nonnull)device withID:(NSString* _Nonnull)ID;

- (void)didPressMute;
- (void)didChangeMute:(BOOL)muted;
- (void)didPressTalk;
- (void)didPressReject;
- (void)didPressOnHook;
- (void)didPressOffHook;

@end

@interface PlantronicsWrapper : NSObject

+ (instancetype _Nonnull)sharedInstance;

@property id<PlantronicsHandler> _Nullable delegate;

- (void)startSpokes;
- (void)stopSpokes;

/**
 *  @brief Set the device on mute.
 *
 *  @param mute True to enable, false to disable
 *
 *  @return True if the status is begin set without issue, false is not set.
 */
- (BOOL)setMute:(BOOL)mute;
/**
 *  @brief Set the device on hold
 *
 *  @param hold True to enable, false to disable
 *
 *  @return True if the status is begin set without issue, false is not set.
 */
- (BOOL)setOnHold:(BOOL)hold;

/**
 *  @brief Set the status on the selected device
 *
 *  @param offHook True to set on OffHook, false to set on OnHook
 *
 *  @return True if the status is begin set without issue, false is not set.
 */
- (BOOL)setOffHook:(BOOL)offHook;

/**
 *  @brief Set the status on the selected device
 *
 *  @param ring True is the device should show that is ringing (in the device that handle that)
 *
 *  @return True if the status is begin set without issue, false is not set.
 */
- (BOOL)setRing:(BOOL)ring;
    
@end
