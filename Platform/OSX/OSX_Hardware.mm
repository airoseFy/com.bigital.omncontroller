//
//  OSX_Hardware.m
//  Platinum
//
//  Created by apple on 15/10/4.
//
//

/*-----------------------------------
 |  Includes
 +---------------------------------*/

#include "Hardware.h"
#include "Log.h"
#include "NptSystem.h"

#import "OSX_OC_Hardware.h"

#ifdef __OBJC__
@class IOS_OC_Hardware;
#else
typedef struct objc_object IOS_OC_Hardware;
#endif

class OSX_Hardware:public IHardware{
public:
     OSX_Hardware() ;
    ~OSX_Hardware() ;
    
    virtual string const& GetUDID(void);
    virtual string const& GetDeviceName();
    
protected:
    OSX_OC_Hardware* m_Impl;
    string           m_UDID;
    string           m_DeviceName;
};

OSX_Hardware::OSX_Hardware()
:m_Impl([[OSX_OC_Hardware alloc] init]), m_UDID([m_Impl GetUDID])
{
    NPT_String _deviceName;
    if(NPT_SUCCEEDED(NPT_GetSystemMachineName(_deviceName)))
    {
        m_DeviceName = _deviceName.GetChars();
    }
}

OSX_Hardware::~OSX_Hardware()
{
    
}

string const&  OSX_Hardware::GetUDID(void)
{
    return m_UDID;
}

string const& OSX_Hardware::GetDeviceName()
{
    return m_DeviceName;
}

//defination Hardware
Hardware::Hardware()
:m_Delegate(new OSX_Hardware)
{
    
}

Hardware* Hardware::m_Instance = nullptr;

mutex Hardware::m_Mutex;

Hardware* Hardware::Instance()
{
    if(nullptr == m_Instance){
        lock_guard<mutex> lk(m_Mutex);
        if(nullptr == m_Instance)
        {
            m_Instance = new Hardware;
        }
    }
    
    return m_Instance;
}
