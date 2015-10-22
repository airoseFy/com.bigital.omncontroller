//
//  DiscoveryTask.cpp
//  Bigital
//
//  Created by bigital on 15/9/20.
//
//

//std::thread
#include <thread>
#include <unordered_map>
#include "Common.h"
#include "Log.h"
#include "Utils.h"
#include "DiscoveryTask.h"

/*---------------------------------------
 |	Setup Logger
 +--------------------------------------*/
#define TAG "DiscoveryTask"
 
/*---------------------------------------
 |	DiscoveryTask
 +--------------------------------------*/
DiscoveryTask::DiscoveryTask(const Device& device)
:m_Discovery(device), m_Started(false)
{
	debug(TAG, "constructor");
}

DiscoveryTask::~DiscoveryTask()
{
	debug(TAG, "destructor");
}

bool DiscoveryTask::Start()
{
	if(m_Started == false)
	{
		m_Started = true;
		std::thread task(std::bind(&DiscoveryTask::OnRun, this));
		task.detach();	
		return true;
	}

	return false;
}

void DiscoveryTask::Stop()
{
	m_Started = false;
	std::this_thread::sleep_for(std::chrono::milliseconds(500));
}

void DiscoveryTask::OnRun()
{
	bool bSetup = false;
	NPT_SocketAddress target;
	std::string extra;
	do{
		if(!bSetup)
		{
			if(!(bSetup = m_Discovery.Start()))
			{
				debug(TAG, "Discovery Start Failed!");
				std::this_thread::sleep_for(std::chrono::milliseconds(300));
				continue;
			}
		}
				
		DiscoveryCommand command = m_Discovery.ReceiveCommand(target, extra);
//        debug(TAG, "onRun extra = %s", extra.c_str());
		switch(command){
			case DiscoveryCommand::JOIN:
				m_Discovery.OnJoinCommandReceived(target, extra);
				break;
			case DiscoveryCommand::LEAVE:
				m_Discovery.OnLeaveCommandReceived(target, extra);
				break;
			case DiscoveryCommand::SEARCH:
				m_Discovery.OnSearchCommandReceived(target, extra);
				break;
			case DiscoveryCommand::DISCRIBE:
				m_Discovery.OnDescribeCommandReceived(target, extra);
				break;		
			default:
				std::this_thread::sleep_for(std::chrono::milliseconds(300));
				break;
		}		
	}while(m_Started);
	
	m_Discovery.Stop();
}

/*---------------------------------------
 |	Discovery
 +--------------------------------------*/
Discovery::Discovery(const Device& device)
:m_Device(device), m_Socket(true), m_MuticastIpAddr(NPT_IpAddress()), m_Binded(false)
{
	m_MuticastIpAddr.Parse(MULTICAST_IP);
}

bool Discovery::Start()
{
	if( !m_Binded )
	{
		if(NPT_FAILED(m_Socket.Bind(NPT_SocketAddress(NPT_IpAddress::Any, MULTICAST_PORT), true)))
		{
			debug(TAG, "Discovery Start Bind Failed!");
			return false;
		}else{
			m_Binded = true;
		}	
	}

	
	if(NPT_FAILED(m_Socket.JoinGroup(m_MuticastIpAddr)))
	{
		debug(TAG, "Discovery Start JoinGroup Failed!");
		return false;
	}else{
        m_Socket.SetWriteTimeout(300);
		m_Socket.SetReadTimeout(300);
		if(m_Device.GetDeviceType() == Device::Type::TV || m_Device.GetDeviceType() == Device::Type::PC){
			this->SendJoinCommand();
		}else{
			this->SendSearchCommand();
		}
	}		
	
	return true;
}

void Discovery::Stop()
{
	if(m_Device.GetDeviceType() == Device::Type::TV || m_Device.GetDeviceType() == Device::Type::PC){
		this->SendLeaveCommand();
	}
	
	m_Socket.LeaveGroup(m_MuticastIpAddr);
	m_Socket.Cancel();
	m_Binded = false;
}

DiscoveryCommand Discovery::ReceiveCommand(NPT_SocketAddress& target, std::string& extra)
{
	DiscoveryCommand command = DiscoveryCommand::NONE;

    const NPT_Size bufferSize = 2048;
	NPT_DataBuffer bufferPacket(bufferSize);
	if(NPT_SUCCEEDED(m_Socket.Receive(bufferPacket, &target)))
	{
			  NPT_String ip 	= target.GetIpAddress().ToString();
			  NPT_Size   size 	= bufferPacket.GetDataSize();
		const NPT_Byte*  buffer = bufferPacket.GetData();

		/****************************************************************
		*		parse command
		****************************************************************/
        debug(TAG, "ReceiveCommand packetSize = %d", size);
		if(size >= 4 /*Min Size*/ && buffer[0] == 0xEA /*Magic Code*/ && buffer[3] <= 4)
		{
			command = (DiscoveryCommand) buffer[3];
            int extraSize = 0;
            memcpy(&extraSize, &buffer[4], sizeof(int));
            debug(TAG, "ReceiveCommand extraSize = %d", extraSize);
            if(extraSize > 0)
            {
                char* _extra = (char*)malloc(extraSize);
                memcpy(_extra, &buffer[4+sizeof(int)], extraSize);
                extra = _extra;
                free(_extra);
            }
		}
	}
		
	return command;
}

void Discovery::SendCommand(DiscoveryCommand command, const std::string& extra)
{
    int  extraSize  = extra.size();
	NPT_Size  bufferSize = extraSize + 4+sizeof(extraSize);
	NPT_Byte* buffer     =(NPT_Byte*)malloc(bufferSize);
	
    NPT_Byte* pos = buffer;
	pos[0] = PROTOCOL_MAGIC;
	pos[1] = MAJOR_VERSION;
	pos[2] = MINOR_VERSION;
	pos[3] =(NPT_Byte)command;
    
    pos = pos + 4;
    memcpy(pos, &extraSize, sizeof(int));
    pos += sizeof(int);
	memcpy(pos, (void*)extra.c_str(), extraSize);
	
	NPT_DataBuffer packet(buffer, bufferSize);
	NPT_SocketAddress socketAddr(m_MuticastIpAddr, MULTICAST_PORT);
	m_Socket.Send(packet, &socketAddr);
	
	free(buffer);	
}

void Discovery::SendSearchCommand()
{
	debug(TAG, "SendSearchCommand");
	this->SendCommand(DiscoveryCommand::SEARCH, string());
}

void Discovery::SendJoinCommand()
{
	debug(TAG, "SendJoinCommand");
    const string space = " ";
    string type;
    string id = m_Device.GetDeviceId();
    string name = m_Device.GetDeviceName();
    string display_name = m_Device.GetDisplayName();
	string extra;
    
	switch(m_Device.GetDeviceType()){
		case Device::Type::PHONE:
			type = "PHONE";
			break;
		case Device::Type::TAB:
			type = "TAB";
			break;
		case Device::Type::PC:
			type = "PC";
			break;
		case Device::Type::TV:
		default:
			type = "TV";
			break;
    }
    
    extra = "device_type=" + ReplaceAll(type, ' ', '%') + space +
            "device_id=" + ReplaceAll(id, ' ', '%') + space +
            "device_name=" + ReplaceAll(name, ' ', '%') + space +
            "device_display_name=" + ReplaceAll(display_name, ' ', '%');
	this->SendCommand(DiscoveryCommand::JOIN, extra);
    debug(TAG, "extra = %s", extra.c_str());
}

void Discovery::SendJoinCommand(NPT_SocketAddress& target)
{
	debug(TAG, "SendJoinCommand");
}

void Discovery::SendLeaveCommand()
{
	debug(TAG, "SendLeaveCommand");
	this->SendCommand(DiscoveryCommand::LEAVE, std::string());
}

void Discovery::SendDescribeCommand()
{
	debug(TAG, "SendDescribeCommand");
	this->SendCommand(DiscoveryCommand::DISCRIBE, std::string());
}

void Discovery::SendDescribeCommand(NPT_SocketAddress& target)
{
	debug(TAG, "SendDescribeCommand");
}

void Discovery::OnSearchCommandReceived(const NPT_SocketAddress& target, const std::string& extra)
{
	debug(TAG, "OnSearchCommandReceived = %s", target.GetIpAddress().ToString().GetChars());
	if(m_Device.GetDeviceType() == Device::Type::TV || m_Device.GetDeviceType() == Device::Type::PC){
		this->SendJoinCommand();
	}
}

void Discovery::OnJoinCommandReceived(const NPT_SocketAddress& target, const std::string& extra)
{
	if(m_Device.GetDeviceType() == Device::Type::PHONE || m_Device.GetDeviceType() == Device::Type::TAB){
		string device_type;
		string device_id;
		string device_name;
		string device_display_name;
		
		unordered_map<string, string> devInfos;
		for(auto prv = extra.cbegin(), cur = extra.cbegin(); cur <= extra.cend(); ++cur)
		{			
			if(cur == extra.cend() || *cur == ' '){
				string info(prv, cur);
				prv = cur + 1;
				
				int pos = info.find_first_of('=');
				if(pos != string::npos)
				{
					devInfos[info.substr(0, pos)] = info.substr(pos+1);
				}
				debug(TAG, "info = %s", info.c_str());	
			}
		}
		
		for(auto it = devInfos.cbegin(); it != devInfos.cend(); ++it)
		{
			debug(TAG, "devInfos = %s", (*it).second.c_str());
		}
		
		Device device(Device::StringToType(devInfos["device_type"]), devInfos["device_id"], 
			devInfos["device_name"], devInfos["device_display_name"]);
			
		DeviceManager::GetInstance()->AddDevice(device, target);
		m_UIDelegate.OnDeviceDataChanged(DeviceManager::GetInstance()->GetAllDevices());
	}
}

void Discovery::OnLeaveCommandReceived(const NPT_SocketAddress& target, const std::string& extra)
{
	debug(TAG, "OnLeaveCommandReceived = %s", target.GetIpAddress().ToString().GetChars());
}

void Discovery::OnDescribeCommandReceived(const NPT_SocketAddress& target, const std::string& extra)
{
	debug(TAG, "OnDescribeCommandReceived = %s", target.GetIpAddress().ToString().GetChars());
}
