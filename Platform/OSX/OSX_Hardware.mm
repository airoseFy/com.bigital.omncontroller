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
    
protected:
    OSX_OC_Hardware* m_Impl;
    string           m_UDID;
};

OSX_Hardware::OSX_Hardware()
:m_Impl([[OSX_OC_Hardware alloc] init]), m_UDID([m_Impl GetUDID])
{
    
}

OSX_Hardware::~OSX_Hardware()
{
    
}

string const&  OSX_Hardware::GetUDID(void)
{
    return m_UDID;
}

//defination Hardware
Hardware::Hardware()
:m_Delegate(new OSX_Hardware)
{
    
}

Hardware* Hardware::m_Instance = nullptr;

//mutex Hardware::m_Mutex;

Hardware* Hardware::Instance()
{
    if(nullptr == m_Instance){
//        lock_guard<mutex> lk(m_Mutex);
        if(nullptr == m_Instance)
        {
            m_Instance = new Hardware;
        }
    }
    
    return m_Instance;
}
