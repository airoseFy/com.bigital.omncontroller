//
//  EventReceiver.h
//  Bigital
//
//  Created by bigital on 15/9/20.
//
//

#ifndef _EVENT_RECEIVER_H
#define _EVENT_RECEIVER_H

class IEventReceiver{
public:
    virtual ~IEventReceiver() {}
    
    virtual bool Start() = 0;
    virtual void Stop()  = 0;
    virtual void ReceiveEvent() = 0;
    virtual void PollEvent() const = 0;
    virtual void SetEventHandler() = 0;
};

class EventReceiver:public IEventReceiver{
public:
			 EventReceiver() {}
	virtual ~EventReceiver() {}
	
	virtual bool Start() { return false; }
	virtual void Stop() {}
	virtual void ReceiveEvent() {}
	virtual void PollEvent() const{}
	virtual void SetEventHandler() {}
};
#endif /* _EVENT_RECEIVER_H */
