#ifndef HRC_IF_XMLRPC_SETIO_API_H
#define HRC_IF_XMLRPC_SETIO_API_H

#include <xmlrpc-c/base.h>
#include <xmlrpc-c/server.h>
#include <xmlrpc-c/server_abyss.h>
#include "xmlrpc-c/config.h"

namespace xmlrpcServer
{
    /* ����ͨ��IO */
    xmlrpc_value * xmlrpc_SetBoxDO(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo);

    /* ���ÿ�����IO */
    xmlrpc_value * xmlrpc_SetBoxCO(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo);  

    /* ����ģ����ģʽ */
    xmlrpc_value * xmlrpc_SetBoxAOMode(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo);

    /* ����ģ����ֵ */
    xmlrpc_value * xmlrpc_SetBoxAO(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo);

    /* ����ĩ��IO */
    xmlrpc_value * xmlrpc_SetEndDO(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo);

    /* set Shutdown time*/
    xmlrpc_value * xmlrpc_SetShutdownTime(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo);
}
#endif
