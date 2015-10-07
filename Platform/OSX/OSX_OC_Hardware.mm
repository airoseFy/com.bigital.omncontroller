//
//  OSX_OC_Hardware.m
//  Platinum
//
//  Created by apple on 15/10/4.
//
//

#import "OSX_OC_Hardware.h"

@implementation OSX_OC_Hardware

-(const char*) GetUDID
{
    const char* uuid = NULL;
    NSString* _uuid = nil;
    
    io_service_t platformExpert;
    platformExpert = IOServiceGetMatchingService(kIOMasterPortDefault, IOServiceMatching("IOPlatformExpertDevice"));
    
    if(platformExpert){
        CFTypeRef uuidAsCFString;
        uuidAsCFString = IORegistryEntryCreateCFProperty(platformExpert, CFSTR("IOPlatformUUID"), kCFAllocatorDefault, 0);
        if(uuidAsCFString){
            _uuid = [(__bridge NSString*)(CFStringRef)uuidAsCFString copy];
            CFRelease(uuidAsCFString);uuidAsCFString = NULL;
            uuid = [_uuid UTF8String];
        }
        IOObjectRelease(platformExpert);platformExpert = 0;
    }
    
    return uuid;
}

@end
