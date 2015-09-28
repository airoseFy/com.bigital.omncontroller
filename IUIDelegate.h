//
//  UIDelegate.h
//  Bigital
//
//  Created by bigital on 15/9/20.
//
//

#ifndef _IUIDELEGATE_H_
#define _IUIDELEGATE_H_

/*----------------------------------------
 |	Includes
 +---------------------------------------*/
#include <vector>
#include "Device.h"

class UIDelegate{
public:
	virtual ~UIDelegate() {}
	
	virtual void Init(void* context) = 0;
	virtual void OnDeviceDataChanged(std::vector<Device> devices) = 0;
};

#endif /*_IUIDELEGATE_H_*/