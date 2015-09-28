//
//  EventSender.hpp
//  Bigital
//
//  Created by bigital on 15/9/19.
//
//

#ifndef _EVENT_SENDER_H_
#define _EVENT_SENDER_H_

/*----------------------------------
 |	Includes
 +---------------------------------*/
#include <thread>
#include <mutex>
#include <condition_variable>
#include <deque>
#include "Event.h"
#include "NptSockets.h"

class IEventSender{
public:
    virtual ~IEventSender() {}
    
    virtual bool Start() = 0;
    virtual void Stop()  = 0;
    virtual bool PushEvent() = 0;
    virtual void PollEvent() const = 0;
    virtual void SendEvent() const = 0;
    virtual void SetTarget(NPT_SocketAddress& target) = 0;
};

class EventSender:public IEventSender{
public:
			 EventSender():m_Started(false) {};
	virtual ~EventSender() = default;
	
	virtual bool Start();
	virtual void Stop();
	virtual bool PushEvent() { return false; }
	virtual void PollEvent() const {}
	virtual void SendEvent() const {}
	virtual void SetTarget(NPT_SocketAddress& target) {}
	
protected:
	virtual void ThreadLoop();
	
private:
	bool			  m_Started;
	std::thread		  m_Task;
	std::deque<Event> m_Events;
	
	//for debug
	std::deque<int>	m_IntQueue;
	std::mutex m_Mutex;
	std::condition_variable m_Condition;
};

#endif /* _EVENT_SENDER_H_ */
