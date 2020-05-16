#ifndef HRC_IF_XMLRPC_READROBOT_API_H
#define HRC_IF_XMLRPC_READROBOT_API_H

#include <xmlrpc-c/base.h>
#include <xmlrpc-c/server.h>
#include <xmlrpc-c/server_abyss.h>
#include "xmlrpc-c/config.h"


namespace xmlrpcServer
{
    /* ��ȡ������ʵʱ��Ϣ*/   
    xmlrpc_value * xmlrpc_ReadRealTimeInfo(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo);

    /* TCP������� */  
    xmlrpc_value * xmlrpc_TCP3PointCalculate(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo);

    /* TCPλ�ü��� */        
    xmlrpc_value * xmlrpc_TCPPositionCalculate(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo);

    /* TCP�������     */
    xmlrpc_value * xmlrpc_TCPOrientationCalculate(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo);

    /* �û���������� */
    xmlrpc_value * xmlrpc_UserPointCoordinateCalculate(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo);

    /* �û���������� */       
    xmlrpc_value * xmlrpc_UserLineCoordinateCalculate(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo);

    /* �û���������� */
    xmlrpc_value * xmlrpc_UserPlaneCoordinateCalculate(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo);

    /* �Ƿ�ģ������� */
    xmlrpc_value * xmlrpc_IsSimulation(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo);

    /* ��ȡ������ID */
    xmlrpc_value * xmlrpc_ReadRobotID(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo);

    /* �������pcs2acs */
    xmlrpc_value * xmlrpc_PCS2ACS(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo);

    /* �������base����תΪUcsTcp */
    xmlrpc_value * xmlrpc_Base2UcsTcp(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo);

    /* �������UcsTcp����תΪbase */
    xmlrpc_value * xmlrpc_UcsTcp2Base(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo);
}
#endif
