//
//  EventReceiver.h
//  Bigital
//
//  Created by bigital on 15/9/20.
//
//

#ifndef _EVENT_RECEIVER_H
#define _EVENT_RECEIVER_H

/*----------------------------------
 |	Includes
 +---------------------------------*/
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include "Event.h"
#include "NptSockets.h"

typedef std::function<bool(int, int, int)> EventHandler;

class IEventReceiver{
public:
    virtual ~IEventReceiver() {}
    
    virtual bool Start() = 0;
    virtual void Stop()  = 0;
    virtual void ReceiveEvent() = 0;
    virtual void PollEvent() const = 0;
    virtual void SetEventHandler(EventHandler event_handler) = 0;
};

class EventReceiver:public IEventReceiver{
public:
			 EventReceiver():m_Started(false), m_Socket(true) {}
	virtual ~EventReceiver() {}
	
	virtual bool Start();
	virtual void Stop();
	virtual void ReceiveEvent() {}
	virtual void PollEvent() const{}
	virtual void SetEventHandler(EventHandler event_handler) { m_EventHandler = event_handler; }
	
protected:
	virtual bool TryBind();
	virtual void RecvLoop();
	virtual void ConsumeLoop();
	
private:
	bool			  	m_Started;
	EventHandler		m_EventHandler;
	NPT_UdpSocket	  	m_Socket;	
	std::thread			m_RecvTask;
	std::thread			m_ConsumeTask;
	std::queue<Event> 	m_CachedQueue;
	std::mutex m_QueueMutex;
	std::mutex m_CondMutex;
	std::condition_variable m_Condition;
};
#endif /* _EVENT_RECEIVER_H */
