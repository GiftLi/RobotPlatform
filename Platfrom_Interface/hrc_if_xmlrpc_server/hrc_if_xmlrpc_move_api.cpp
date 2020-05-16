#include "hrc_if_xmlrpc_api.h"
#include "HRC_StatusMachine/hrc_status_api.h"
#include "HRC_Public/hrc_public_factory/hrc_public_factory.h"
#include "../public_files/global_error/hrc_public_gerrorcode.h"


namespace xmlrpcServer
{
    /* 关节短点动 */
    xmlrpc_value * xmlrpc_ShortJogJ(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo)	
    {
        HRC_NOUSE_2PARAMTER(serInfo,channelInfo);
        DoRobotParameShortMove(HMRC_Status_ShortJogAcs);
    }

    /* 空间短点动 */
    xmlrpc_value * xmlrpc_ShortJogL(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo)	
    {
        HRC_NOUSE_2PARAMTER(serInfo,channelInfo);
        DoRobotParameShortMove(HMRC_Status_ShortJogPcs);
    }

    /* 关节长点动 */  
    xmlrpc_value * xmlrpc_LongJogJ(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo)	
    {
        HRC_NOUSE_2PARAMTER(serInfo,channelInfo);
        DoRobotParameLongMove(HMRC_Status_LongJogAcs); 
    }

    /* 空间长点动 */  
    xmlrpc_value * xmlrpc_LongJogL(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo)	
    {
        HRC_NOUSE_2PARAMTER(serInfo,channelInfo);
        DoRobotParameLongMove(HMRC_Status_LongJogPcs);
    }

    /* 关节相对运动 */ 
    xmlrpc_value * xmlrpc_MoveRelJ(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo)	
    {
        HRC_NOUSE_2PARAMTER(serInfo,channelInfo);
        DoRobotParameRealMove(HMRC_Status_MoveRelJ);
    }

    /* 空间相对运动 */ 
    xmlrpc_value * xmlrpc_MoveRelL(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo)	
    {
        HRC_NOUSE_2PARAMTER(serInfo,channelInfo);
        DoRobotParameRealMove(HMRC_Status_MoveRelL);
    }

    /* 关节运动 */
    xmlrpc_value * xmlrpc_MoveJ(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo)	
    {
        HRC_NOUSE_2PARAMTER(serInfo,channelInfo);
        DoRobotParameMove(HMRC_Status_MoveJ);
    }

    /* 空间运动 */ 
    xmlrpc_value * xmlrpc_MoveL(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo)	
    {
        HRC_NOUSE_2PARAMTER(serInfo,channelInfo);
        DoRobotParameMove(HMRC_Status_MoveL);
    }

    /* 关节运动到点 */
    xmlrpc_value * xmlrpc_MoveToACS(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo)   
    {
        HRC_NOUSE_2PARAMTER(serInfo,channelInfo);
        DoRobotParameMove(HMRC_Status_MoveToACS);
    }

    /* 空间运动到点 */
    xmlrpc_value * xmlrpc_MoveToPCS(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo)	
    {
        HRC_NOUSE_2PARAMTER(serInfo,channelInfo);
        DoRobotParameMoveLTo(HMRC_Status_MoveToPCS);
    }

    /* 运动到安全空间 */
    xmlrpc_value * xmlrpc_MoveToSS(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo)
    {
        HRC_NOUSE_2PARAMTER(serInfo,channelInfo);
        DoRobotParameMoveToSS(HMRC_Status_MoveToSS);
    }

    /* long Move Event */
    xmlrpc_value * xmlrpc_LongMoveEvent(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo)
    {
        HRC_NOUSE_2PARAMTER(serInfo,channelInfo);
        DoRobotParameLongMoveEvent(HMRC_Status_LongMoveEvent);
    }
    /* 圆周运动 */
   /* xmlrpc_value * xmlrpc_MoveC(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo)	
    {
        xmlrpc_int nRbtID = 0;
        xmlrpc_int nClientType = 0;
        PointCoord ViaCoord;
        PointCoord GoalCoord;
        xmlrpc_int nMoveCFixedPosure = 0;
        xmlrpc_decompose_value(envP, paramArray, "(iiddddddddddddi)", &nRbtID, &nClientType,
            &(ViaCoord.Axis[0]), &(ViaCoord.Axis[1]), &(ViaCoord.Axis[2]),
            &(ViaCoord.Axis[3]), &(ViaCoord.Axis[4]), &(ViaCoord.Axis[5]),
            &(GoalCoord.Axis[0]), &(GoalCoord.Axis[1]), &(GoalCoord.Axis[2]),
            &(GoalCoord.Axis[3]), &(GoalCoord.Axis[4]), &(GoalCoord.Axis[5]), &nMoveCFixedPosure);
        if (envP->fault_occurred)
        {
            center_trace(center_log_error, "xmlrpc call error %d %s",
                envP->fault_code,envP->fault_string);
            return nullptr;
        }
        xmlrpc_int nRet = HMRC_Status_MoveC(nRbtID, ViaCoord, GoalCoord, nMoveCFixedPosure, NOT_SCRIPT);
        return xmlrpc_build_value(envP, "i", nRet);
    }*/

    /* 开始下发blending点位 */
    xmlrpc_value * xmlrpc_StartPushBlending(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo)
    {
        HRC_NOUSE_2PARAMTER(serInfo,channelInfo);
        DoRobotParame(HMRC_Status_StartPushBlending);
    }

    /* 下发blending点位 */
    xmlrpc_value *xmlrpc_PushBlendingPoint(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo)
    {
        xmlrpc_int nRbtID = 0;
        xmlrpc_int nClientType = 0;
        PointCoord ViaCoord;
        double dVel = 0;
        double dAcc = 0;
        double dRadius = 0;
        int nType = 0;
        int nPointGuid = 0;

        HRC_NOUSE_2PARAMTER(serInfo,channelInfo);

        xmlrpc_decompose_value(envP, paramArray, "(iidddddddddii)", &nRbtID, &nClientType,
            &(ViaCoord.Axis[0]), &(ViaCoord.Axis[1]), &(ViaCoord.Axis[2]),
            &(ViaCoord.Axis[3]), &(ViaCoord.Axis[4]), &(ViaCoord.Axis[5]),
            &dVel, &dAcc, &dRadius, &nType,&nPointGuid);
        
        if (envP->fault_occurred)
        {
            center_trace(center_log_error, "xmlrpc call error %d %s",
                envP->fault_code,envP->fault_string);
            return nullptr;
        } 
        xmlrpc_int nRet = HMRC_Status_PushBlendingPoint(nRbtID,nClientType,
                                                        ViaCoord.Axis,dVel,dAcc,dRadius,
                                                        nType,nPointGuid);
                                                        
        return xmlrpc_build_value(envP, "i", nRet);
    }


    /* 开始blending运动*/
    xmlrpc_value *xmlrpc_StartBlendingMotion(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo)
    {
        HRC_NOUSE_2PARAMTER(serInfo,channelInfo);
        DoRobotParame(HMRC_Status_StartBlendingMotion);
    }

}
