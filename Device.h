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

class Device{
public:
    enum class Type{
        TV = 0,
        PC = 1,
        PHONE = 2,
        TAB = 3,
    };
    
    Device(Type type);
    virtual ~Device() {}
    
    //Methods
    inline Type  GetDeviceType() const { return m_Type; }
    inline const string& GetDeviceName() const { return m_DeviceName; }
    inline const string& GetDisplayName() const { return m_DisplayName; }
    inline const string& GetDeviceId() const { return m_DeviceId; }
    inline const Resolution& GetResolution() const { return m_Res; }
    
    inline void SetDeviceName(const string& name) { m_DeviceName = name; }
    inline void SetDisplayName(const string& displayName) { m_DisplayName = displayName; }
    inline void SetDeviceId(const string& id) { m_DeviceId = id; }
    inline void SetResolution(const Resolution& resolution) { m_Res = resolution; }
    
    //Members
private:
    Type    m_Type;
    string  m_DeviceName;
    string  m_DisplayName;
    string  m_DeviceId;
    Resolution  m_Res;
};

typedef pair<Device, NPT_SocketAddress> device_ip_pair;

class DeviceManager{
public:
	virtual ~DeviceManager() = default;
	
	inline void AddDevice(const Device& device, const NPT_SocketAddress& addr)
	{
		for(vector<device_ip_pair>::const_iterator it = m_DeviceList.cbegin(); it != m_DeviceList.cend(); ++it)
		{
			
		}
	}
	
	void RemoveDevice(const Device& device) {}
	const Device* GetDevice(const string& deviceId) { return NULL; }

	//for debug
	inline void AddDevice(const NPT_SocketAddress& addr)
	{
		for(auto it = m_IpList.cbegin(); it != m_IpList.cend(); ++it)
		{
			if(*it == addr) return ;
		}
		
		m_IpList.push_back(addr);
	}
	
	inline void RemoveDevice(const NPT_SocketAddress& addr)
	{
		for(auto it = m_IpList.begin(); it != m_IpList.end(); ++it)
		{
			if(*it == addr) m_IpList.erase(it) ;
		}
	}
	
	inline const vector<NPT_SocketAddress>& GetDeviceList(void)
	{
		return m_IpList;
	}
	
private:
	vector<device_ip_pair>	m_DeviceList;
	
	//for debug
	vector<NPT_SocketAddress> m_IpList;
};
#endif /* _DEVICE_H_ */
