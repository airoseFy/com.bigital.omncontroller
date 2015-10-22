//
//  EventSender.cpp
//  Bigital
//
//  Created by bigital on 15/9/19.
//
//

#include "Log.h"
#include "EventSender.h"

/*---------------------------------------
 |	Setup Logger
 +--------------------------------------*/
#define TAG "EventSender"
 
bool EventSender::PushEvent(int type, int code, int value)
{
	std::unique_lock<std::mutex> lk(m_QueueMutex);
	m_CachedQueue.emplace(0, type, code, value);
	m_Condition.notify_one();
	return false;
}

bool EventSender::PushEvent(const Event& event)
{
	std::unique_lock<std::mutex> lk(m_QueueMutex);
	m_CachedQueue.push(event);
	m_Condition.notify_one();
	return false;
}

bool EventSender::PushEvent(Event&& event)
{
	std::unique_lock<std::mutex> lk(m_QueueMutex);
	m_CachedQueue.push(std::forward<Event>(event));
	m_Condition.notify_one();
	return false;
}

bool EventSender::Start()
{
	if(m_Started == false)
	{
		m_Socket.SetWriteTimeout(200);
		m_Started = true;
		//m_PollingTask = std::thread(std::bind(&EventSender::PollingLoop, this));
		//m_PollingTask.detach();		
		
		m_SendingTask = std::thread(std::bind(&EventSender::SendingLoop, this));
		m_SendingTask.detach();

		return true;
	}
	
	return false;
}

void EventSender::Stop()
{
	m_Started = false;
}

void EventSender::PollingLoop()
{
	debug(TAG, "ThreadLoop....");
	do{
		{
			std::unique_lock<std::mutex> lk(m_QueueMutex);
			if(m_InputQueue.size() > 0)
			{
				for(int i = 0; i < m_InputQueue.size(); ++i)
				{
					m_CachedQueue.push(std::move(m_InputQueue.front()));
					m_InputQueue.pop();				
				}
				m_Condition.notify_one();
			}
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}while(m_Started);	
}

void EventSender::SendingLoop()
{
	NPT_Byte buffer[3] = {0, 0, 0};
	
	do{
		//debug("SendingLoop", "lock");
		std::unique_lock<std::mutex> lk(m_CondMutex);
		//debug("SendingLoop", "wait");
		m_Condition.wait(lk);
		while(!m_CachedQueue.empty()){
			buffer[0] = m_CachedQueue.front().type;
			buffer[1] = m_CachedQueue.front().code;
			buffer[2] = m_CachedQueue.front().value;
			debug(TAG, "Event type = %d, code = %d, value = %d", 
				buffer[0],
				buffer[1],
				buffer[2]);
			NPT_DataBuffer packet(buffer, 3);
			m_Socket.Send(packet, &m_Target);
			
			//pop the consume event
			std::unique_lock<std::mutex> lk(m_QueueMutex);
			m_CachedQueue.pop();
		}
	}while(m_Started);
}