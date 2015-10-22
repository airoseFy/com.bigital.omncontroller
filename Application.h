//
//  Application.h
//  Bigital
//
//  Created by bigital on 15/9/20.
//
//

#ifndef _APPLICATION_H_
#define _APPLICATION_H_

/*----------------------------------------
 |	Includes
 +---------------------------------------*/
#include "Device.h"
#include "DiscoveryTask.h"
#include "EventReceiver.h"
#include "EventSender.h"

class IApplication{
public:
	virtual ~IApplication() {}
	
	virtual void OnCreate() = 0;
	virtual void OnResume() = 0;
	virtual void OnPause()  = 0;
	virtual void OnDestroy() = 0;
};

class IHostApplication:public IApplication{
public:
	IHostApplication()
	:m_Device(Device::Type::TV), m_DiscoveryTask(m_Device)
	{
		
	}
	
	virtual ~IHostApplication() {}
	
	virtual void OnCreate() 
	{
		m_DiscoveryTask.Start();
		m_EventReceiver.Start();
	}
	
	virtual void OnDestroy()
	{
		m_DiscoveryTask.Stop();
		m_EventReceiver.Stop();
	}
	
	virtual void OnResume() {}
	virtual void OnPause() {}
	
private:
	Device	m_Device;
	DiscoveryTask m_DiscoveryTask;
	EventReceiver m_EventReceiver;
};

class ICtrlApplication:public IApplication{
public:
	ICtrlApplication()
	:m_Device(Device::Type::PHONE), m_DiscoveryTask(m_Device)
	{
	}
	virtual ~ICtrlApplication() {}
	
	void SetTarget(const char* udid)
	{
		std::string _udid(udid);
		const IP_Device* ipDevice = DeviceManager::GetInstance()->GetDevice(_udid);
		if(ipDevice != nullptr)
		{
			m_EventSender.SetTarget(ipDevice->m_SockAddr);
		}
	}
	
	void InputEvent(int type, int code, int value)
	{
		m_EventSender.PushEvent(type, code, value);
	}
	
	virtual void OnCreate() 
	{
		m_DiscoveryTask.Start();
		m_EventSender.Start();
	}
	
	virtual void OnDestroy()
	{
		m_DiscoveryTask.Stop();
		m_EventSender.Stop();
	}
	
	virtual void OnResume() {}
	virtual void OnPause() {}
	
private:
	Device	m_Device;
	DiscoveryTask m_DiscoveryTask;
	EventSender m_EventSender;
};

#endif /*_APPLICATION_H_*/
