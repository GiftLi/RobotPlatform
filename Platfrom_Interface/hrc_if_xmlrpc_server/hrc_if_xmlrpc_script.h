#ifndef HRC_IF_XMLRPC_SCRIPT_H
#define HRC_IF_XMLRPC_SCRIPT_H


#include <xmlrpc-c/base.h>
#include <xmlrpc-c/server.h>
#include <xmlrpc-c/server_abyss.h>
#include "xmlrpc-c/config.h"

namespace xmlrpcServer
{

    /* 开始运行脚本 */
    xmlrpc_value * xmlrpc_StartScript(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo);

    /* 停止运行脚本 */
    xmlrpc_value * xmlrpc_StopScript(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo);

    /* 暂停 */
    xmlrpc_value * xmlrpc_PauseScript(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo);

    /* 继续 */
    xmlrpc_value * xmlrpc_ContinueScript(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo);

    /* 下一步 */
    xmlrpc_value * xmlrpc_NextStepScript(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo);

    /* 下一个断点 */
    xmlrpc_value * xmlrpc_NextBreakPoint(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo);

}
#endif





