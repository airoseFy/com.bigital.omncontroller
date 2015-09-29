//
//  Device.cpp
//  Platinum
//
//  Created by apple on 15/9/20.
//
//

#include "Device.h"

#define TAG "Device"

Device::Device(Type type)
:m_Type(type)
{
	NPT_List<NPT_NetworkInterface*> interfaces;
    NPT_Result result = NPT_NetworkInterface::GetNetworkInterfaces(interfaces);
    if (NPT_FAILED(result)) {
        debug(TAG, "GetNetworkInterfaces() failed");
    }else if(interfaces.GetItemCount() > 0){
		//NPT_NetworkInterface* netInterface = *interfaces.GetFirstItem();
		//debug(TAG, "NPT_NetworkInterface MacAddress = %s", netInterface->GetMacAddress().ToString().GetChars());
		    NPT_List<NPT_NetworkInterface*>::Iterator iface = interfaces.GetFirstItem();
		while (iface) {
			debug(TAG, "  name  = %s", (*iface)->GetName().GetChars());
			debug(TAG, "  flags = %x [ ", (*iface)->GetFlags());
			debug(TAG, "  mac   = %s (type=%d)", (*iface)->GetMacAddress().ToString().GetChars(), (*iface)->GetMacAddress().GetType());
			++iface;
		}
	}
}