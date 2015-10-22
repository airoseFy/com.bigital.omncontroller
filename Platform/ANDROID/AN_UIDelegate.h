//
//  AN_UIDelegate.h
//  Bigital
//
//  Created by bigital on 15/10/8.
//
//

#ifndef _AN_UI_DELEGATE_H_
#define _AN_UI_DELEGATE_H_

#include <jni.h>
#include "UIDelegate.h"

class AN_UIDelegate:public IUIDelegate{
public:
	 AN_UIDelegate() = default;
	~AN_UIDelegate() = default;
	virtual void OnDeviceDataChanged(const std::vector<IP_Device>& devices);

public:
	static void Init(JNIEnv* env, jobject viewDelegate);
	static void Release(JNIEnv* env);
private:
	static JavaVM* m_Static_JVMPtr;
	static jobject m_Static_Clazz;
};

#endif