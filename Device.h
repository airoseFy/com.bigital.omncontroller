//
//  Device.h
//  Bigital
//
//  Created by bigital on 15/9/20.
//
//

#ifndef _DEVICE_H_
#define _DEVICE_H_

/*------------------------------
 |  Includes
 -----------------------------*/
#include <string>
#include <vector>
#include "NptSockets.h"
#include "Log.h"

using namespace std;

//Screen Resolution
struct Resolution{
    Resolution() = default;
    Resolution(const Resolution& copy) = default;
    float w;    //dimension = px
    float h;    //dimension = px
};

class DeviceManager;

class Device{
public:
    enum class Type{
        TV = 0,
        PC = 1,
        PHONE = 2,
        TAB = 3,
    };
    
    explicit Device(Type type);
    virtual ~Device() = default;
    
    //Methods
    inline Type  GetDeviceType() const { return m_Type; }
    inline const string& GetDeviceName() const { return m_DeviceName; }
    inline const string& GetDisplayName() const { return m_DisplayName; }
    inline const string& GetDeviceId() const { return m_DeviceId; }
    inline const Resolution& GetResolution() const { return m_Res; }
    
    inline void SetDisplayName(const string& displayName) { m_DisplayName = displayName; }
    
    friend class DeviceManager;
    
    //Members
private:
    Type    m_Type;
    string  m_DeviceName;
    string  m_DisplayName;
    string  m_DeviceId;
    Resolution  m_Res;
};

struct IP_Device{
    IP_Device(const Device& device, const NPT_SocketAddress& addr)
    :dev(device), sockAddr(addr)
    {
        
    }
    Device dev;
    NPT_SocketAddress sockAddr;
};

class DeviceManager{
public:
     DeviceManager() = default;
    ~DeviceManager() = default;
	
	inline void AddDevice(const Device& device, const NPT_SocketAddress& addr)
	{
		for(auto it = m_DeviceList.cbegin();
            it != m_DeviceList.cend(); ++it)
		{
            if((*it).dev.m_DeviceId == device.m_DeviceId) break;
		}
        
        m_DeviceList.emplace_back(device, addr);
	}
	
	void RemoveDevice(const Device& device) {}
    
	const Device* GetDevice(const string& deviceId) { return NULL; }
    
    //for debug
    void PrintAllDevices(void) const
    {
        for (auto it = m_DeviceList.cbegin(); it != m_DeviceList.cend(); ++it) {
            debug("DeviceManager", "Print DeviceId = %s", (*it).dev.m_DeviceId.c_str());
        }
    }
	
private:
	vector<IP_Device>	m_DeviceList;
};
#endif /* _DEVICE_H_ */
