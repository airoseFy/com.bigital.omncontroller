//
//  IOS_OC_Hardware.m
//  Platinum
//
//  Created by apple on 15/10/2.
//
//

#import <UIKit/UIKit.h>
#import "IOS_OC_Hardware.h"

@implementation IOS_OC_Hardware

-(const char*) GetUDID
{
    NSString* udid = [[[UIDevice currentDevice] identifierForVendor] UUIDString];

    return [udid UTF8String];
}

- (const char*) GetDeviceName
{
    NSString* deviceName = [[UIDevice currentDevice] name];
    
    return [deviceName UTF8String];
}

@end
