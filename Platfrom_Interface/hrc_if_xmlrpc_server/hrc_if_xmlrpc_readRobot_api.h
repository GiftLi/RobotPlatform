#ifndef HRC_IF_XMLRPC_READROBOT_API_H
#define HRC_IF_XMLRPC_READROBOT_API_H

#include <xmlrpc-c/base.h>
#include <xmlrpc-c/server.h>
#include <xmlrpc-c/server_abyss.h>
#include "xmlrpc-c/config.h"


namespace xmlrpcServer
{
    /* 读取机器人实时信息*/   
    xmlrpc_value * xmlrpc_ReadRealTimeInfo(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo);

    /* TCP三点计算 */  
    xmlrpc_value * xmlrpc_TCP3PointCalculate(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo);

    /* TCP位置计算 */        
    xmlrpc_value * xmlrpc_TCPPositionCalculate(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo);

    /* TCP方向计算     */
    xmlrpc_value * xmlrpc_TCPOrientationCalculate(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo);

    /* 用户点坐标计算 */
    xmlrpc_value * xmlrpc_UserPointCoordinateCalculate(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo);

    /* 用户线坐标计算 */       
    xmlrpc_value * xmlrpc_UserLineCoordinateCalculate(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo);

    /* 用户面坐标计算 */
    xmlrpc_value * xmlrpc_UserPlaneCoordinateCalculate(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo);

    /* 是否模拟机器人 */
    xmlrpc_value * xmlrpc_IsSimulation(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo);

    /* 读取机器人ID */
    xmlrpc_value * xmlrpc_ReadRobotID(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo);

    /* 坐标计算pcs2acs */
    xmlrpc_value * xmlrpc_PCS2ACS(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo);

    /* 坐标计算base坐标转为UcsTcp */
    xmlrpc_value * xmlrpc_Base2UcsTcp(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo);

    /* 坐标计算UcsTcp坐标转为base */
    xmlrpc_value * xmlrpc_UcsTcp2Base(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo);
}
#endif
