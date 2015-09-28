//
//  UIDelegate.h
//  Bigital
//
//  Created by bigital on 15/9/20.
//
//

#ifndef _UIDELEGATE_H_
#define _UIDELEGATE_H_

/*----------------------------------------
 |	Includes
 +---------------------------------------*/
#include "IUIDelegate.h"

#ifdef __ANDROID__
#include "AndroidUIDelegate.h"
#endif

#include <mutex>

std::mutex instance_mutex;
UIDelegate* uiDelegate = nullptr;

UIDelegate* getUIDelegate()
{
	if(nullptr == uiDelegate)
	{
		std::unique_lock<std::mutex> lk(instance_mutex);
		if(nullptr == uiDelegate)
		{
			#ifdef __ANDROID__
				uiDelegate = static_cast<UIDelegate*>(new AndroidUIDelegate);
			#endif
		}
	}
	
	return uiDelegate;
}
#endif /*_UIDELEGATE_H_*/