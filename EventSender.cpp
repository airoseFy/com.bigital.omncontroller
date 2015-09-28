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
		m_Task = std::thread(std::bind(&EventSender::ThreadLoop, this));
		m_Task.detach();
		m_Started = true;
		
		std::this_thread::sleep_for(std::chrono::milliseconds(5000));
		m_Condition.notify_one();
		return true;
	}
	
	return false;
}

void EventSender::Stop()
{
	m_Started = false;
}

void EventSender::ThreadLoop()
{
	std::unique_lock<std::mutex> lk(m_Mutex);
	m_Condition.wait(lk);
	debug(TAG, "ThreadLoop.....");
}