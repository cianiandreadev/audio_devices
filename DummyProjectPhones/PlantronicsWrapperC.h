//
//  PlantronicsWrapperC.h
//  PlantronicsTest
//
//  Created by Andrea Ciani on 26/07/16.
//  Copyright © 2016 Andrea Ciani. All rights reserved.
//

#ifndef PlantronicsWrapperC_h
#define PlantronicsWrapperC_h

#import <Spokes3GSDK/DeviceManager.h>
#import <Spokes3GSDK/Spokes3G.h>

void PlantronicsWrapperPrint(const char* text);
void PlantronicsWrapperAttachDeviceListener();
void PlantronicsWrapperRemoveDeviceListener();

void PlantronicsWrapperHeadsetButtonPressed(DeviceListenerEventArgs const &args);
void PlantronicsWrapperHeadsetStateChanged(DeviceListenerEventArgs const &args);


#endif /* PlantronicsWrapperC_h */
