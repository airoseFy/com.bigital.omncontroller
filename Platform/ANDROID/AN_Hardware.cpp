//
//  AN_Hardware.cpp
//  Bigital
//
//  Created by bigital on 15/10/8.
//
//

#include "AN_Hardware.h"

Hardware::Hardware()
:m_Delegate(new AN_Hardware)
{
    
}

/*-------------------------------------
 |	Static
 +------------------------------------*/
string AN_Hardware::m_UDID;

void AN_Hardware::Init(JNIEnv* env, jobject context)
{
	jclass ctxCls;
	jclass secureCls;
	jmethodID getContentResMethodID;
	jmethodID getStringMethodID;
	jfieldID ANDROID_ID_Field;
	
	if((ctxCls = env->FindClass("android/content/Context")) == NULL) return ;
	
	if((secureCls = env->FindClass("android/provider/Settings$Secure")) == NULL) return ;
	
	if((getContentResMethodID = env->GetMethodID(ctxCls, "getContentResolver", 
		"()Landroid/content/ContentResolver;")) == NULL) return ;
		
	if((getStringMethodID = env->GetStaticMethodID(secureCls, "getString", 
		"(Landroid/content/ContentResolver;Ljava/lang/String;)Ljava/lang/String;")) == NULL) return ;
		
	if((ANDROID_ID_Field = env->GetStaticFieldID(secureCls, "ANDROID_ID", "Ljava/lang/String;")) == NULL) return ;
	
	jstring key = (jstring)env->GetStaticObjectField(secureCls, ANDROID_ID_Field);
	jobject resolver = env->CallObjectMethod(context, getContentResMethodID);
	jstring udid = (jstring)env->CallStaticObjectMethod(secureCls, getStringMethodID, resolver, key);
	m_UDID = (char*)env->GetStringUTFChars(udid, 0);
}

Hardware* Hardware::m_Instance = nullptr;

mutex Hardware::m_Mutex;

Hardware* Hardware::Instance()
{
    if(nullptr == m_Instance){
        lock_guard<mutex> lk(m_Mutex);
        if(nullptr == m_Instance)
        {
            m_Instance = new Hardware;
        }
    }
    
    return m_Instance;
}