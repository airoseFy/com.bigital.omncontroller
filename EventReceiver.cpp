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
	m_Started = false;
}

bool EventReceiver::TryBind()
{
	if(NPT_FAILED(m_Socket.Bind(NPT_SocketAddress(NPT_IpAddress::Any, 1189), true)))
	{
		debug("EventReceiver", "EventReceiver TryBind Failed!");
		return false;
	}
	
	m_Socket.SetReadTimeout(1000);
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
			std::unique_lock<std::mutex> lk(m_QueueMutex);
			m_CachedQueue.emplace(0, buffer[0], buffer[1], buffer[2]);
			m_Condition.notify_one();
		}else{
			debug("EventReceiver", "RecvLoop Receive Timeout!");
		}
	}while(m_Started);
}

void EventReceiver::ConsumeLoop()
{
	debug("EventReceiver", "ConsumeLoop");
	int type = 0;
	int code = 0;
	int value= 0;
	
	do{		
		std::unique_lock<std::mutex> lk(m_CondMutex);
		m_Condition.wait(lk);
		
		while(!m_CachedQueue.empty())
		{
			std::unique_lock<std::mutex> lk(m_QueueMutex);
			type = m_CachedQueue.front().type;
			code = m_CachedQueue.front().code;
			value= m_CachedQueue.front().value;
			debug("EventReceiver", "Receive type = %d, code = %d, value = %d", type, code, value);
			m_EventHandler(type, code, value);
			m_CachedQueue.pop();
		}
	}while(m_Started);
}