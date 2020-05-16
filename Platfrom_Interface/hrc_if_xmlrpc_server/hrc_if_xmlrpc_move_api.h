#ifndef HRC_IF_XMLRPC_MOVE_API_H
#define HRC_IF_XMLRPC_MOVE_API_H


#include <xmlrpc-c/base.h>
#include <xmlrpc-c/server.h>
#include <xmlrpc-c/server_abyss.h>
#include "xmlrpc-c/config.h"

namespace xmlrpcServer
{
    /* �ؽڶ̵㶯 */
    xmlrpc_value * xmlrpc_ShortJogJ(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo);

    /* �ռ�̵㶯 */
    xmlrpc_value * xmlrpc_ShortJogL(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo);

    /* �ؽڳ��㶯 */    
    xmlrpc_value * xmlrpc_LongJogJ(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo);

    /* �ռ䳤�㶯 */  
    xmlrpc_value * xmlrpc_LongJogL(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo);

    /* �ؽ�����˶� */ 
    xmlrpc_value * xmlrpc_MoveRelJ(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo);

    /* �ռ�����˶� */ 
    xmlrpc_value * xmlrpc_MoveRelL(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo);

    /* �ؽ��˶� */     
    xmlrpc_value * xmlrpc_MoveJ(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo);

    /* �ռ��˶� */ 
    xmlrpc_value * xmlrpc_MoveL(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo);

    /* �ؽ��˶����� */
    xmlrpc_value * xmlrpc_MoveToACS(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo);

    /* �ռ��˶����� */
    xmlrpc_value * xmlrpc_MoveToPCS(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo);

    /* �ռ��˶����� */
    xmlrpc_value * xmlrpc_MoveToSS(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo);

    /* Long move event */
    xmlrpc_value * xmlrpc_LongMoveEvent(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo);

    /* Բ���˶� 
    xmlrpc_value * xmlrpc_MoveC(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo);*/ 

    /* ��ʼ�·�blending��λ */
    xmlrpc_value * xmlrpc_StartPushBlending(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo);

    /* �·�blending��λ */
    xmlrpc_value *xmlrpc_PushBlendingPoint(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo);

    /* ��ʼblending�˶�*/        
    xmlrpc_value *xmlrpc_StartBlendingMotion(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo);


}
#endif
