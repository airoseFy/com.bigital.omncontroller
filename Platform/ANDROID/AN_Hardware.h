//
//  AN_Hardware.h
//  Bigital
//
//  Created by bigital on 15/10/8.
//
//

#ifndef _AN_HARDWARE_H_
#define _AN_HARDWARE_H_

#include "Hardware.h"
#include <jni.h>

class AN_Hardware:public IHardware{
public:
	 AN_Hardware()
	 {
		 
	 }
	~AN_Hardware() = default;
	
public:
	string const& GetUDID(void) final
    {
        return m_UDID;
    }

	string const& GetDeviceName(void) final
	{
		return m_DeviceName;
	}
	
public:
	static void Init(JNIEnv* env, jobject context);
private:
	static string m_UDID;
	static string m_DeviceName;
};

#endif /*_AN_HARDWARE_H_*/