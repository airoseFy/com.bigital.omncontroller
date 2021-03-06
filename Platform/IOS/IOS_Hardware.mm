//
//  IOS_Hardware.cpp
//  Bigital
//
//  Created by bigital on 15/10/2.
//
//

/*-----------------------------------
 |  Includes
 +---------------------------------*/

#include "Hardware.h"
#include "Log.h"

#import "IOS_OC_Hardware.h"

#ifdef __OBJC__
@class IOS_OC_Hardware;
#else
typedef struct objc_object IOS_OC_Hardware;
#endif

class IOS_Hardware:public IHardware{
public:
     IOS_Hardware() ;
    ~IOS_Hardware() ;
    
    virtual string const& GetUDID(void);
    virtual string const& GetDeviceName();

protected:
    IOS_OC_Hardware* m_Impl;
    string           m_UDID;
    string           m_DeviceName;
};

IOS_Hardware::IOS_Hardware()
:m_Impl([[IOS_OC_Hardware alloc] init]), m_UDID([m_Impl GetUDID]), m_DeviceName([m_Impl GetDeviceName])
{
    
}

IOS_Hardware::~IOS_Hardware()
{
    
}

string const&  IOS_Hardware::GetUDID(void)
{
    return m_UDID;
}

string const& IOS_Hardware::GetDeviceName()
{
    return m_DeviceName;
}

//defination Hardware
Hardware::Hardware()
:m_Delegate(new IOS_Hardware)
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



