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
 
bool EventSender::Start()
{
	if(m_Started == false)
	{
		m_Started = true;
		m_PollingTask = std::thread(std::bind(&EventSender::PollingLoop, this));
		m_PollingTask.detach();		
		
		m_SendingTask = std::thread(std::bind(&EventSender::SendingLoop, this));
		m_SendingTask.detach();

		/*for(; ;){
			for(int i = 0; i < 20; ++i)
			{
				m_InputQueue.push(i);
			}
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
		}*/
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
	debug(TAG, "SendingLoop....");
	do{
		std::unique_lock<std::mutex> lk(m_Mutex);
		m_Condition.wait(lk);
		while(!m_CachedQueue.empty()){
			debug(TAG, "m_CachedQueue = %d", m_CachedQueue.front());
			m_CachedQueue.pop();
		}
	}while(m_Started);
}