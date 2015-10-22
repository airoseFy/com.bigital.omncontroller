//
//  EventReceiver.cpp
//  Bigital
//
//  Created by bigital on 15/9/20.
//
//

#include "Log.h"
#include "EventReceiver.h"

bool EventReceiver::Start()
{
	if(!m_Started){
		m_Started = true;
		m_RecvTask = std::thread(std::bind(&EventReceiver::RecvLoop, this));
		m_RecvTask.detach();		
		
		m_ConsumeTask = std::thread(std::bind(&EventReceiver::ConsumeLoop, this));
		m_ConsumeTask.detach();	
		
		return true;
	}
	return false;
}

void EventReceiver::Stop()
{
	
}

bool EventReceiver::TryBind()
{
	if(NPT_FAILED(m_Socket.Bind(NPT_SocketAddress(NPT_IpAddress::Any, 1189), true)))
	{
		debug("EventReceiver", "EventReceiver TryBind Failed!");
		return false;
	}
	
	m_Socket.SetReadTimeout(200);
	return true;	
}

void EventReceiver::RecvLoop()
{
	debug("EventReceiver", "RecvLoop");
	bool  ret = false;
	const NPT_Size size = 3;
		  NPT_DataBuffer packet(size);
		  NPT_SocketAddress target;
	
	do{
		if(!ret)
		{
			if(!(ret = this->TryBind()))
			{
				std::this_thread::sleep_for(std::chrono::milliseconds(300));
				continue;
			}
		}
		
		if(NPT_SUCCEEDED(m_Socket.Receive(packet, &target)) && packet.GetDataSize() == size)
		{
			const NPT_Byte*  buffer = packet.GetData();
			debug("EventReceiver", "Receive type = %d, code = %d, value = %d", buffer[0], buffer[1], buffer[2]);
		}else{
			debug("EventReceiver", "RecvLoop Receive Timeout!");
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	}while(m_Started);
}

void EventReceiver::ConsumeLoop()
{
	debug("EventReceiver", "ConsumeLoop");
	do{		
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	}while(m_Started);
}