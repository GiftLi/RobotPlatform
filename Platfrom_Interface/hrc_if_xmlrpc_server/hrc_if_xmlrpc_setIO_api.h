#ifndef HRC_IF_XMLRPC_SETIO_API_H
#define HRC_IF_XMLRPC_SETIO_API_H

#include <xmlrpc-c/base.h>
#include <xmlrpc-c/server.h>
#include <xmlrpc-c/server_abyss.h>
#include "xmlrpc-c/config.h"

namespace xmlrpcServer
{
    /* 设置通用IO */
    xmlrpc_value * xmlrpc_SetBoxDO(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo);

    /* 设置可配置IO */
    xmlrpc_value * xmlrpc_SetBoxCO(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo);  

    /* 设置模拟量模式 */
    xmlrpc_value * xmlrpc_SetBoxAOMode(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo);

    /* 设置模拟量值 */
    xmlrpc_value * xmlrpc_SetBoxAO(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo);

    /* 设置末端IO */
    xmlrpc_value * xmlrpc_SetEndDO(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo);

    /* set Shutdown time*/
    xmlrpc_value * xmlrpc_SetShutdownTime(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo);
}
#endif
