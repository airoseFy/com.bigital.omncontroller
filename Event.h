//
//  Event.h
//  Bigital
//
//  Created by bigital on 15/9/20.
//
//

#ifndef _EVENT_H
#define _EVENT_H

/*---------------------------------
 |	Includes
 +--------------------------------*/
#include <chrono>
using namespace std::chrono;

class Event{
public:
	 Event() = default;
	~Event() = default;
	 Event(const Event& copy) = default;
public:
	long when;
	int	type;
	int code;
	int value;
};

#endif /*_EVENT_H*/
