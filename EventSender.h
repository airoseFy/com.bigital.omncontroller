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
#include <queue>
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
    explicit EventSender():m_Started(false) {};
	virtual ~EventSender() = default;
	
	virtual bool Start();
	virtual void Stop();
	virtual bool PushEvent() { return false; }
	virtual void PollEvent() const {}
	virtual void SendEvent() const {}
	virtual void SetTarget(NPT_SocketAddress& target) {}
	
protected:
	virtual void PollingLoop();
	virtual void SendingLoop();
	
private:
	bool			  m_Started;
	std::thread		  m_PollingTask;
	std::thread		  m_SendingTask;
	std::queue<Event> m_Events;
	
	//for debug
	std::queue<int>	m_InputQueue;
	std::queue<int> m_CachedQueue;
	std::mutex m_Mutex;
	std::condition_variable m_Condition;
};

#endif /* _EVENT_SENDER_H_ */
