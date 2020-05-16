#ifndef HRC_IF_XMLRPC_READ_CONFIG_API_H
#define HRC_IF_XMLRPC_READ_CONFIG_API_H

#include <xmlrpc-c/base.h>
#include <xmlrpc-c/server.h>
#include <xmlrpc-c/server_abyss.h>
#include "xmlrpc-c/config.h"



namespace xmlrpcServer
{

    /* 读取硬件配置 */
    xmlrpc_value * xmlrpc_ReadRobotsHardConfig(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo);

    /* 读取软件配置 */
    xmlrpc_value * xmlrpc_ReadRobotsConfig(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo);

    /* 读取安全配置 */
    xmlrpc_value * xmlrpc_ReadSafeLevel(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo);



    /*
    xmlrpc_value * xmlrpc_ReadEmergencyMonitor(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo);

	xmlrpc_value * xmlrpc_ReadEmergencyForResetIO(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo);


	xmlrpc_value * xmlrpc_ReadEmergencyForResetIOState(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo);

	xmlrpc_value * xmlrpc_ReadSafetyGuardMonitor(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo);

	xmlrpc_value * xmlrpc_ReadSafetyGuardHold(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo);

	xmlrpc_value * xmlrpc_ReadSwitchOnMonitor(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo);

	//////////////////////////////////////////////////////////////////////////
	xmlrpc_value * xmlrpc_ReadConveyorConfig(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo);
        
        xmlrpc_value * xmlrpc_ReadConveyorValue(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo);

    //读取安全平面
    xmlrpc_value * xmlrpc_ReadSafetyPanel(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo);
    */

    
    /*
    *读取安全限制范围

    xmlrpc_value * xmlrpc_ReadSafetyScope(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo);
*/


}
#endif
