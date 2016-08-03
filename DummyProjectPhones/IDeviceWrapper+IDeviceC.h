//
//  IDeviceWrapperC.h
//  DummyProjectPhones
//
//  Created by Andrea on 29/07/16.
//  Copyright © 2016 Andrea Ciani. All rights reserved.
//

#ifndef IDeviceWrapperC_h
#define IDeviceWrapperC_h

#import <Spokes3GSDK/DeviceManager.h>
#import <Spokes3GSDK/Spokes3G.h>
#import "IDeviceWrapper.h"

@interface IDeviceWrapper (IDeviceC)

-(instancetype _Nonnull)initWithDevice:(IDevice* _Nonnull)device;

@end

#endif /* IDeviceWrapperC_h */
