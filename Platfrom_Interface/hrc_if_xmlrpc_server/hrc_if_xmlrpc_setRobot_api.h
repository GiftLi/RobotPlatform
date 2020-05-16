#ifndef HRC_IF_XMLRPC_SETROBOT_API_H
#define HRC_IF_XMLRPC_SETROBOT_API_H


#include <xmlrpc-c/base.h>
#include <xmlrpc-c/server.h>
#include <xmlrpc-c/server_abyss.h>
#include "xmlrpc-c/config.h"


namespace xmlrpcServer
{
    
    /* ϵͳ���ϵ�ָ�� */
    xmlrpc_value * xmlrpc_Electrify(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo);

    /* ϵͳ���µ�ָ�� */
    xmlrpc_value * xmlrpc_Blackout(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo);

    /* ������վָ�� */
    xmlrpc_value * xmlrpc_StartMaster(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo);
    
    /* �ر���վָ�� */
    xmlrpc_value * xmlrpc_CloseMaster(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo);

    /* ��������ָ�� */
    xmlrpc_value * xmlrpc_ResetEStop(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo);

    /* ��ȫ��Ļ����ָ�� */
    xmlrpc_value * xmlrpc_ResetSGuard(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo);

    /* ��ͣ�˶�ָ�� */
    xmlrpc_value * xmlrpc_GrpInterrupt(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo);

    /* �����˶�ָ�� */
    xmlrpc_value * xmlrpc_GrpContinue(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo);        

    /* ʹ��ָ�� */    
    xmlrpc_value * xmlrpc_GrpPowerOn(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo);

    /* ȥʹ��ָ�� */   
    xmlrpc_value * xmlrpc_GrpPowerOff(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo);

    /* ����λָ�� */ 
    xmlrpc_value * xmlrpc_GrpReset(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo);

    /* ֹͣ�˶�ָ�� */         
    xmlrpc_value * xmlrpc_GrpStop(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo);

    /* ��������ʾ��ָ�� */ 
    xmlrpc_value * xmlrpc_SetStartAssistiveMode(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo);
    
    /* �ر�����ʾ��ָ�� */    
    xmlrpc_value * xmlrpc_SetCloseAssistiveMode(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo);

    /* ���û������ٶȰٷֱ� */    
    xmlrpc_value * xmlrpc_SetOverride(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo);

    /* ���û����� */
    xmlrpc_value * xmlrpc_SetToolCoordinateMotion(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo);
}
#endif
