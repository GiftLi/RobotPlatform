#ifndef HRC_IF_XMLRPC_SETROBOT_API_H
#define HRC_IF_XMLRPC_SETROBOT_API_H


#include <xmlrpc-c/base.h>
#include <xmlrpc-c/server.h>
#include <xmlrpc-c/server_abyss.h>
#include "xmlrpc-c/config.h"


namespace xmlrpcServer
{
    
    /* 系统板上电指令 */
    xmlrpc_value * xmlrpc_Electrify(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo);

    /* 系统板下电指令 */
    xmlrpc_value * xmlrpc_Blackout(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo);

    /* 启动主站指令 */
    xmlrpc_value * xmlrpc_StartMaster(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo);
    
    /* 关闭主站指令 */
    xmlrpc_value * xmlrpc_CloseMaster(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo);

    /* 错误重置指令 */
    xmlrpc_value * xmlrpc_ResetEStop(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo);

    /* 安全光幕重置指令 */
    xmlrpc_value * xmlrpc_ResetSGuard(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo);

    /* 暂停运动指令 */
    xmlrpc_value * xmlrpc_GrpInterrupt(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo);

    /* 继续运动指令 */
    xmlrpc_value * xmlrpc_GrpContinue(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo);        

    /* 使能指令 */    
    xmlrpc_value * xmlrpc_GrpPowerOn(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo);

    /* 去使能指令 */   
    xmlrpc_value * xmlrpc_GrpPowerOff(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo);

    /* 错误复位指令 */ 
    xmlrpc_value * xmlrpc_GrpReset(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo);

    /* 停止运动指令 */         
    xmlrpc_value * xmlrpc_GrpStop(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo);

    /* 启动零力示教指令 */ 
    xmlrpc_value * xmlrpc_SetStartAssistiveMode(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo);
    
    /* 关闭零力示教指令 */    
    xmlrpc_value * xmlrpc_SetCloseAssistiveMode(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo);

    /* 设置机器人速度百分比 */    
    xmlrpc_value * xmlrpc_SetOverride(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo);

    /* 设置机器人 */
    xmlrpc_value * xmlrpc_SetToolCoordinateMotion(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo);
}
#endif
