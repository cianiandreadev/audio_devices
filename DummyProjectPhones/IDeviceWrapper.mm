//
//  IDeviceWrapper.m
//  DummyProjectPhones
//
//  Created by Andrea on 29/07/16.
//  Copyright © 2016 Andrea Ciani. All rights reserved.
//

#import "IDeviceWrapper.h"

#import "PlantronicsWrapperC.h"

#import "EventSink.h"

#import <iostream>
#import <Spokes3GSDK/cpp/query_cast.h>
#import <Spokes3gSDK/DeviceManager.h>

#define CHAR_BUFFER_SIZE 1024

@interface IDeviceWrapper() {
    
    IDevice* rawDevice;
    
}

@end

@implementation IDeviceWrapper

@synthesize
attached = _attached;

-(instancetype _Nonnull)initWithDevice:(IDevice* _Nonnull)device {
    if (self = [super init]) {
        rawDevice = device;
    }
    return self;
}

-(int)productID {
    return rawDevice -> getProductID();
}

-(int)vendorID {
    return rawDevice -> getVendorID();
}

-(int)versionNumber {
    return rawDevice -> getVersionNumber();
}

-(NSString* _Nullable) devicePath {
    wchar_t buffer[CHAR_BUFFER_SIZE];
    rawDevice->getProductName( buffer, CHAR_BUFFER_SIZE );
    return [self getStringFromCChar:buffer];
}

-(NSString* _Nullable) internalName {
    wchar_t buffer[CHAR_BUFFER_SIZE];
    rawDevice->getInternalName(buffer, CHAR_BUFFER_SIZE);
    return [self getStringFromCChar:buffer];
}

-(NSString* _Nullable) productName {
    wchar_t buffer[CHAR_BUFFER_SIZE];
    rawDevice->getProductName(buffer, CHAR_BUFFER_SIZE);
    return [self getStringFromCChar:buffer];
}

-(NSString* _Nullable) manufacturerName {
    wchar_t buffer[CHAR_BUFFER_SIZE];
    rawDevice->getManufacturerName(buffer, CHAR_BUFFER_SIZE);
    return [self getStringFromCChar:buffer];
}

-(NSString* _Nullable) serialNumber {
    wchar_t buffer[CHAR_BUFFER_SIZE];
    rawDevice->getSerialNumber(buffer, CHAR_BUFFER_SIZE);
    return [self getStringFromCChar:buffer];
}

-(BOOL)attach {
    return rawDevice->attach();
}

-(BOOL)detach {
    return rawDevice->detach();
}

-(BOOL)isSupported:(uint16) usage {
    return rawDevice->isSupported(usage);
}

#pragma mark - Helpers

-(NSString* _Nullable)getStringFromCChar:(wchar_t*)buffer {
    NSString *value = [[NSString alloc]initWithBytes:buffer length:wcslen(buffer)*sizeof(*buffer) encoding:NSUTF32LittleEndianStringEncoding];
    return value;
    
}

@end
