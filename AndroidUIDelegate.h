#ifndef _ANDROID_UIDELEGATE_H_
#define _ANDROID_UIDELEGATE_H_

#include "Log.h"
 
class AndroidUIDelegate:public UIDelegate{
public:
	AndroidUIDelegate() {}
	virtual ~AndroidUIDelegate() = default;
	
	virtual void Init(void* context)
	{
		debug("AndroidUIDelegate", "Init");
	}
	
	virtual void OnDeviceDataChanged(std::vector<Device> devices)
	{
		debug("AndroidUIDelegate", "OnDeviceDataChanged");
	}
};

#endif /*_ANDROID_UIDELEGATE_H_*/