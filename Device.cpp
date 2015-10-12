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
:m_DevType(type)
{
    m_DevId = Hardware::Instance()->GetUDID();
	m_DevName  = Hardware::Instance()->GetDeviceName();
	m_DevDisplayName = m_DevName;

    debug("Device", "m_DeviceId = %s", m_DevId.c_str());
    debug("Device", "m_DeviceName = %s", m_DevName.c_str());
    debug("Device", "m_DisplayName = %s", m_DevDisplayName.c_str());
}

Device::Device(Type type, const string& deviceId, const string& deviceName, const string& displayName)
:m_DevType(type), m_DevId(deviceId), m_DevName(deviceName), m_DevDisplayName(displayName)
{
    
}