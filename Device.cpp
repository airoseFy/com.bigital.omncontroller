//
//  Device.cpp
//  Bigital
//
//  Created by bigital on 15/9/20.
//
//

#include "Device.h"
#include "Hardware.h"
#include "NptSystem.h"

#define TAG "Device"

static const char* GetMachineName(void)
{
    const char* machineName = NULL;
    NPT_String _machineName ;
    if(NPT_SUCCEEDED(NPT_GetSystemMachineName(_machineName)))
    {
        debug("Device", "_machineName = %s", _machineName.GetChars());
        machineName = _machineName.GetChars();
    }
    return machineName;
}

Device::Device(Type type)
:m_Type(type)
{
	debug("Device", "Constructor");
    //get machine name
    NPT_String machineName;
    if(NPT_SUCCEEDED(NPT_GetSystemMachineName(machineName)))
    {
        m_DeviceName = machineName.GetChars();
        m_DisplayName = m_DeviceName;
    }
    
	debug("Device", "GetUDID Begin");
    m_DeviceId = Hardware::Instance()->GetUDID();
	debug("Device", "GetUDID End");
    debug("Device", "m_DeviceName = %s", m_DeviceName.c_str());
    debug("Device", "m_DisplayName = %s", m_DisplayName.c_str());
    debug("Device", "m_DeviceId = %s", m_DeviceId.c_str());
}
