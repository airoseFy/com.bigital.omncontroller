//
//  OC_ControllerDevice.m
//  Platinum
//
//  Created by apple on 15/10/3.
//
//

#import "OC_ControllerDevice.h"
#include "Application.h"

@interface OC_ControllerDevice(){
    ICtrlApplication ctrlApp;
}
@end

@implementation OC_ControllerDevice

- (void) onCreate
{
    ctrlApp.OnCreate();
}

- (void) onDestroy
{
    ctrlApp.OnDestroy();
}

@end
