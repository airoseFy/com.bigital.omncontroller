//
//  Hardware.hpp
//  Bigital
//
//  Created by bigital on 15/10/2.
//
//

#ifndef _HARDWARE_H_
#define _HARDWARE_H_

/*--------------------------------
 |  Includes
 +-------------------------------*/
#include <string>
#include <mutex>

using namespace std;
class IHardware{
public:
    virtual ~IHardware() = default;
    
    virtual string const& GetUDID(void) = 0;
	virtual string const& GetDeviceName(void) = 0;
};

class Hardware:public IHardware{
protected:
    Hardware();
    Hardware(const Hardware&) = delete ;
    Hardware& operator = (const Hardware&) = delete ;

public:
    ~Hardware()
    {
        if(m_Delegate != nullptr) delete m_Delegate;
    }
    
    virtual string const& GetUDID(void)
    {
        return m_Delegate->GetUDID();
    }
    
	virtual string const& GetDeviceName(void)
	{
		return m_Delegate->GetDeviceName();
	}
	
    static Hardware*  Instance(void);
    
protected:
    IHardware*   m_Delegate;
    
private:
    static Hardware* m_Instance;
    static mutex     m_Mutex;
};

#endif /* _HARDWARE_H_ */
