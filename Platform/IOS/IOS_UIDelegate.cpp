//
//  IOS_UIDelegate.cpp
//  Bigital
//
//  Created by bigital on 15/10/2.
//
//

/*-------------------------------
 |  Includes
 +------------------------------*/
#include "UIDelegate.h"

class IOS_UIDelegate:public UIDelegate{
public:
     IOS_UIDelegate() = default;
    ~IOS_UIDelegate() = default;
    
    virtual void Init(void* context);
    virtual void OnDeviceDataChanged(std::vector<Device> devices);
};

UIDelegate::UIDelegate()
:m_Delegate(new IOS_UIDelegate)
{
    
}

void IOS_UIDelegate::Init(void *context)
{
    
}

void IOS_UIDelegate::OnDeviceDataChanged(std::vector<Device> devices)
{
    
}
