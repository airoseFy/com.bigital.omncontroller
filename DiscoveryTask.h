//
//  DiscoveryTask.h
//  Bigital
//
//  Created by bigital on 15/9/20.
//
//

#ifndef _DISCOVERY_TASK_H_
#define _DISCOVERY_TASK_H_

/*-----------------------------
 |  Includes
 +----------------------------*/
#include <string>
#include "NptSockets.h"
#include "Device.h"
#include "UIDelegate.h"

/*-------------------------------------------------
|	Constants
--------------------------------------------------*/
#define		MULTICAST_IP		"225.0.0.24"
#define 	MULTICAST_PORT		13724

enum class DiscoveryCommand{
    JOIN  = 0,
    LEAVE = 1,
	SEARCH = 2,
    DISCRIBE = 3,
	NONE = 4,
};

class IDiscovery{
public:
	virtual ~IDiscovery() {}
	
	virtual bool Start() = 0;
	virtual void Stop()  = 0;
	virtual DiscoveryCommand ReceiveCommand(NPT_SocketAddress& target) = 0;
	virtual void SendSearchCommand() = 0;
	virtual void SendJoinCommand() = 0;
	virtual void SendJoinCommand(NPT_SocketAddress& target) = 0;
	virtual void SendLeaveCommand() = 0;
	virtual void SendDescribeCommand() = 0;
	virtual void SendDescribeCommand(NPT_SocketAddress& target) = 0;
	virtual void OnSearchCommandReceived(const NPT_SocketAddress& target, const std::string& extra) = 0;
	virtual void OnJoinCommandReceived(const NPT_SocketAddress& target, const std::string& extra) = 0;
	virtual void OnLeaveCommandReceived(const NPT_SocketAddress& target, const std::string& extra) = 0;
	virtual void OnDescribeCommandReceived(const NPT_SocketAddress& target, const std::string& extra) = 0;
};

class Discovery{
public:
	explicit Discovery(const Device& device);
	virtual ~Discovery() = default;
	
	virtual bool Start();
	virtual void Stop();
	virtual DiscoveryCommand ReceiveCommand(NPT_SocketAddress& target, std::string& extra);
	virtual void SendSearchCommand();
	virtual void SendJoinCommand();
	virtual void SendJoinCommand(NPT_SocketAddress& target);
	virtual void SendLeaveCommand();
	virtual void SendDescribeCommand();
	virtual void SendDescribeCommand(NPT_SocketAddress& target);
	virtual void OnSearchCommandReceived(const NPT_SocketAddress& target, const std::string& extra);
	virtual void OnJoinCommandReceived(const NPT_SocketAddress& target, const std::string& extra);
	virtual void OnLeaveCommandReceived(const NPT_SocketAddress& target, const std::string& extra);
	virtual void OnDescribeCommandReceived(const NPT_SocketAddress& target, const std::string& extra);
	
protected:
	void SendCommand(DiscoveryCommand command, const std::string& extra);
	
private:
          DeviceManager m_DevManager;
		  UIDelegate m_UIDelegate;
	const Device m_Device;
		  NPT_UdpMulticastSocket m_Socket;
		  NPT_IpAddress	m_MuticastIpAddr;
		  bool	m_Binded;
		  
};

class IDiscoveryTask{
public:
    virtual ~IDiscoveryTask() {}
    
    virtual bool Start() = 0;
    virtual void Stop()  = 0;
	virtual void OnRun() = 0;
};

class DiscoveryTask:public IDiscoveryTask{
public:
	explicit DiscoveryTask(const Device& device);
	virtual ~DiscoveryTask();
	
	//Methods
	virtual bool Start();
	virtual void Stop();
	
	//Task Run Routine
	virtual void OnRun();
	
private:
	Discovery 	m_Discovery;
    bool		m_Started {false};
};

#endif /* _DISCOVERY_TASK_H_ */
