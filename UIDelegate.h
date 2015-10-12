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
#include <vector>
#include "Device.h"

class IUIDelegate{
public:
    virtual ~IUIDelegate() {}
    virtual void OnDeviceDataChanged(const std::vector<IP_Device>& devices) = 0;
};

class UIDelegate:public IUIDelegate{
public:
    explicit UIDelegate();
    ~UIDelegate()
    {
        if(m_Delegate != nullptr) delete m_Delegate;
    }   
    
    inline virtual void OnDeviceDataChanged(const std::vector<IP_Device>& devices)
    {
        if(m_Delegate != nullptr)
			m_Delegate->OnDeviceDataChanged(devices);
    }
	
protected:
    IUIDelegate*    m_Delegate;
};

#endif /*_UIDELEGATE_H_*/
