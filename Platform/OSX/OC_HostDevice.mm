//
//  OC_HostDevice.m
//  Platinum
//
//  Created by apple on 15/10/3.
//
//

#import "OC_HostDevice.h"
#include "Application.h"

@interface OC_HostDevice(){
    IHostApplication hostApp;
}
@end

@implementation OC_HostDevice

- (void) onCreate
{
    hostApp.OnCreate();
}

- (void) onDestroy
{
    hostApp.OnDestroy();
}

@end
