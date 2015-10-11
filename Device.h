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
    
	static const string& TypeToString(Type type)
	{
		string str;
		switch(type){
			case Type::PHONE:
				str = "PHONE";
				break;
			case Type::TAB:
				str = "TAB";
				break;
			case Type::PC:
				str = "PC";
				break;
			case Type::TV:
			default:
				str = "TV";
				break;
		}
		return std::move(str);
	}
	
	static Type StringToType(const string& typeStr)
	{
		if("PHONE" == typeStr){
			return Type::PHONE;
		}else if("TAB" == typeStr){
			return Type::TAB;
		}else if("PC" == typeStr){
			return Type::PC;
		}else{
			return Type::TV;
		}		
	}
	
    explicit Device(Type type);
	Device(Type type, const string& deviceName, const string& displayName, const string& deviceId);
    virtual ~Device() = default;
    
    //Methods
    inline Type  GetDeviceType() const { return m_DevType; }
    inline const string& GetDeviceName() const { return m_DevName; }
    inline const string& GetDisplayName() const { return m_DevDisplayName; }
    inline const string& GetDeviceId() const { return m_DevId; }
    inline const Resolution& GetResolution() const { return m_Res; }
    
    inline void SetDisplayName(const string& displayName) { m_DevDisplayName = displayName; }
    
    friend class DeviceManager;
    
    //Members
private:
    Type    m_DevType;
    string  m_DevId;
    string  m_DevName;
    string  m_DevDisplayName;
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
            if((*it).dev.m_DevId == device.m_DevId) break;
		}
        
        m_DeviceList.emplace_back(device, addr);
	}
	
	void RemoveDevice(const Device& device) {}
    
	const Device* GetDevice(const string& deviceId) { return NULL; }
    
    //for debug
    void PrintAllDevices(void) const
    {
        for (auto it = m_DeviceList.cbegin(); it != m_DeviceList.cend(); ++it) {
            debug("DeviceManager", "Print DeviceId = %s", (*it).dev.m_DevId.c_str());
            debug("DeviceManager", "Print DeviceId = %s", (*it).dev.m_DevName.c_str());
            debug("DeviceManager", "Print DeviceId = %s", (*it).dev.m_DevDisplayName.c_str());
        }
    }
	
private:
	vector<IP_Device>	m_DeviceList;
};
#endif /* _DEVICE_H_ */
