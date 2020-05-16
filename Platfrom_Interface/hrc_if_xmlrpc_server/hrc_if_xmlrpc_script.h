#ifndef HRC_IF_XMLRPC_SCRIPT_H
#define HRC_IF_XMLRPC_SCRIPT_H


#include <xmlrpc-c/base.h>
#include <xmlrpc-c/server.h>
#include <xmlrpc-c/server_abyss.h>
#include "xmlrpc-c/config.h"

namespace xmlrpcServer
{

    /* ��ʼ���нű� */
    xmlrpc_value * xmlrpc_StartScript(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo);

    /* ֹͣ���нű� */
    xmlrpc_value * xmlrpc_StopScript(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo);

    /* ��ͣ */
    xmlrpc_value * xmlrpc_PauseScript(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo);

    /* ���� */
    xmlrpc_value * xmlrpc_ContinueScript(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo);

    /* ��һ�� */
    xmlrpc_value * xmlrpc_NextStepScript(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo);

    /* ��һ���ϵ� */
    xmlrpc_value * xmlrpc_NextBreakPoint(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo);

}
#endif





