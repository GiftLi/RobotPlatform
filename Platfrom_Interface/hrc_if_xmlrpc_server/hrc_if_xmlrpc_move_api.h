#ifndef HRC_IF_XMLRPC_MOVE_API_H
#define HRC_IF_XMLRPC_MOVE_API_H


#include <xmlrpc-c/base.h>
#include <xmlrpc-c/server.h>
#include <xmlrpc-c/server_abyss.h>
#include "xmlrpc-c/config.h"

namespace xmlrpcServer
{
    /* 关节短点动 */
    xmlrpc_value * xmlrpc_ShortJogJ(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo);

    /* 空间短点动 */
    xmlrpc_value * xmlrpc_ShortJogL(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo);

    /* 关节长点动 */    
    xmlrpc_value * xmlrpc_LongJogJ(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo);

    /* 空间长点动 */  
    xmlrpc_value * xmlrpc_LongJogL(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo);

    /* 关节相对运动 */ 
    xmlrpc_value * xmlrpc_MoveRelJ(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo);

    /* 空间相对运动 */ 
    xmlrpc_value * xmlrpc_MoveRelL(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo);

    /* 关节运动 */     
    xmlrpc_value * xmlrpc_MoveJ(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo);

    /* 空间运动 */ 
    xmlrpc_value * xmlrpc_MoveL(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo);

    /* 关节运动到点 */
    xmlrpc_value * xmlrpc_MoveToACS(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo);

    /* 空间运动到点 */
    xmlrpc_value * xmlrpc_MoveToPCS(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo);

    /* 空间运动到点 */
    xmlrpc_value * xmlrpc_MoveToSS(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo);

    /* Long move event */
    xmlrpc_value * xmlrpc_LongMoveEvent(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo);

    /* 圆周运动 
    xmlrpc_value * xmlrpc_MoveC(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo);*/ 

    /* 开始下发blending点位 */
    xmlrpc_value * xmlrpc_StartPushBlending(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo);

    /* 下发blending点位 */
    xmlrpc_value *xmlrpc_PushBlendingPoint(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo);

    /* 开始blending运动*/        
    xmlrpc_value *xmlrpc_StartBlendingMotion(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo);


}
#endif
