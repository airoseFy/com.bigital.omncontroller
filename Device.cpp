//
//  Device.cpp
//  Bigital
//
//  Created by bigital on 15/9/20.
//
//

#include "Device.h"
#include "Hardware.h"

#define TAG "Device"

Device::Device(Type type)
:m_Type(type)
{
	m_DeviceName  = Hardware::Instance()->GetDeviceName();
	m_DisplayName = m_DeviceName;
    m_DeviceId = Hardware::Instance()->GetUDID();
    debug("Device", "m_DeviceName = %s", m_DeviceName.c_str());
    debug("Device", "m_DisplayName = %s", m_DisplayName.c_str());
    debug("Device", "m_DeviceId = %s", m_DeviceId.c_str());
}
