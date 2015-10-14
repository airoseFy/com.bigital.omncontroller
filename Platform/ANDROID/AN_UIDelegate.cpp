//
//  AN_UIDelegate.h
//  Bigital
//
//  Created by bigital on 15/10/8.
//
//

#include "Log.h"
#include "AN_UIDelegate.h"

JavaVM* AN_UIDelegate::m_Static_JVMPtr = nullptr;
jobject AN_UIDelegate::m_Static_Clazz;

void AN_UIDelegate::Init(JavaVM* jvm, jobject viewDelegate)
{
	m_Static_JVMPtr = jvm;
	m_Static_Clazz  = viewDelegate;
}

void AN_UIDelegate::OnDeviceDataChanged(const std::vector<IP_Device>& devices)
{
	JNIEnv* env;
	if(m_Static_JVMPtr == NULL)
	{
		debug("AN_UIDelegate", "vm is null");
		return ;
	}
	
	if(m_Static_JVMPtr->AttachCurrentThread(&env, NULL) == JNI_OK)
	{
		jclass viewDelegateCls;
		jmethodID methodGetInstance;
		jmethodID methodUpdateView;
		
		do{
			viewDelegateCls = env->GetObjectClass(m_Static_Clazz);
			
			if((methodGetInstance = env->GetStaticMethodID(viewDelegateCls, "getInstance", "()Lcom/bigital/omncontrol/controller/ViewDelegate;")) == NULL)
			{
				debug("AN_UIDelegate", "getInstance method not found!");
				break;
			}
			
			if((methodUpdateView = env->GetMethodID(viewDelegateCls, "updateDeviceList", "([Ljava/lang/String;)V")) == NULL)
			{
				debug("AN_UIDelegate", "updateDeviceList method not found!");
				break;	
			}
			
			jobject viewDelegate = env->CallObjectMethod(viewDelegateCls, methodGetInstance);
			
			int size = devices.size();
			jobjectArray deviceInfos = env->NewObjectArray(size, env->FindClass("java/lang/String"), env->NewStringUTF(""));
			for(int i = 0; i < size; ++i)
			{
				env->SetObjectArrayElement(deviceInfos, i, env->NewStringUTF(devices[i].m_Dev.GetDeviceId().c_str()));
			}
			
			for(auto it = devices.cbegin(); it != devices.cend(); ++it)
			{
				debug("DeviceManager", "Print DeviceId = %s", (*it).m_Dev.GetDeviceId().c_str());
				debug("DeviceManager", "Print DeviceName= %s", (*it).m_Dev.GetDeviceName().c_str());
				debug("DeviceManager", "Print DeviceDisplayName = %s", (*it).m_Dev.GetDisplayName().c_str());		
			}
			
			env->CallVoidMethod(viewDelegate, methodUpdateView, deviceInfos);
		}while(0);
		
		m_Static_JVMPtr->DetachCurrentThread();
	}	
}

UIDelegate::UIDelegate()
:m_Delegate(new AN_UIDelegate)
{
	
}