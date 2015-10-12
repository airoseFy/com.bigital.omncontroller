//
//  AN_UIDelegate.h
//  Bigital
//
//  Created by bigital on 15/10/8.
//
//

#include "Log.h"
#include "AN_UIDelegate.h"

JNIEnv* AN_UIDelegate::m_Static_EnvPtr = nullptr;

void AN_UIDelegate::SetupJNI(JNIEnv* env)
{
	m_Static_EnvPtr = env;
}

void AN_UIDelegate::OnDeviceDataChanged(const std::vector<IP_Device>& devices)
{
	for(auto it = devices.cbegin(); it != devices.cend(); ++it)
	{
            debug("DeviceManager", "Print DeviceId = %s", (*it).m_Dev.GetDeviceId().c_str());
            debug("DeviceManager", "Print DeviceName= %s", (*it).m_Dev.GetDeviceName().c_str());
            debug("DeviceManager", "Print DeviceDisplayName = %s", (*it).m_Dev.GetDisplayName().c_str());		
	}
}

UIDelegate::UIDelegate()
:m_Delegate(new AN_UIDelegate)
{
	
}