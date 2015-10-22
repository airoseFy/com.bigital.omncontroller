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
	 Event(long w, int t, int c, int v)
	 :when(w), type(t), code(c), value(v)
	 {
		 
	 }
	~Event() = default;
	 Event(const Event& copy) = default;
	 
	 Event(Event&& r)
	 :when(std::forward<long>(r.when)), type(std::forward<int>(r.type)), 
	 code(std::forward<int>(r.code)), value(std::forward<int>(r.value))
	 {
		 
	 }
	 
	 Event& operator=(const Event& copy)
	 {
		this->when = copy.when;
		this->type = copy.type;
		this->code = copy.code;
		this->value= copy.value;
		return *this;
	 }
	 
	 Event& operator=(Event&& r)
	 {
		this->when = std::forward<long>(r.when);
		this->type = std::forward<int>(r.type);
		this->code = std::forward<int>(r.code);
		this->value= std::forward<int>(r.value);
		return *this;
	 }
public:
	long when;
	int	type;
	int code;
	int value;
};

#endif /*_EVENT_H*/
