#include "hrc_if_xmlrpc_api.h"
#include "HRC_StatusMachine/hrc_status_api.h"
#include "../public_files/global_error/hrc_public_gerrorcode.h"
#include "HRC_Public/hrc_public_factory/hrc_public_factory.h"

namespace xmlrpcServer
{
    xmlrpc_value * xmlrpc_Electrify(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo)	
    {
        center_trace(center_log_debug, "recv xmlrpc_Electrify");
        HRC_NOUSE_2PARAMTER(serInfo,channelInfo);
        DoRobotParame(HMRC_Status_Electrify);
    }
 
    xmlrpc_value * xmlrpc_Blackout(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo)	
    {
        center_trace(center_log_debug, "recv xmlrpc_Blackout");
        HRC_NOUSE_2PARAMTER(serInfo,channelInfo);
        DoRobotParame(HMRC_Status_Blackout);
    }

    xmlrpc_value * xmlrpc_StartMaster(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo)
    {
        center_trace(center_log_debug, "recv xmlrpc_StartMaster");
        HRC_NOUSE_2PARAMTER(serInfo,channelInfo);
        DoRobotParame(HMRC_Status_StartMaster);
    }
   
    xmlrpc_value * xmlrpc_CloseMaster(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo)
    {
        center_trace(center_log_debug, "recv xmlrpc_CloseMaster");
        HRC_NOUSE_2PARAMTER(serInfo,channelInfo);
        DoRobotParame(HMRC_Status_CloseMaster);
    }
    
    xmlrpc_value * xmlrpc_ResetEStop(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo)
    {
        center_trace(center_log_debug, "recv xmlrpc_ResetEStop");
        HRC_NOUSE_2PARAMTER(serInfo,channelInfo);
        DoRobotParame(HMRC_Status_ResetEStop);
    }
    
    xmlrpc_value * xmlrpc_ResetSGuard(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo)
    {
        center_trace(center_log_debug, "recv xmlrpc_ResetSGuard");
        HRC_NOUSE_2PARAMTER(serInfo,channelInfo);
        DoRobotParame(HMRC_Status_ResetSGuard);
    }

    xmlrpc_value * xmlrpc_GrpContinue(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo)	
    {
        center_trace(center_log_debug, "recv xmlrpc_GrpContinue");
        HRC_NOUSE_2PARAMTER(serInfo,channelInfo);
        DoRobotParame(HMRC_Status_GrpContinue);
    }

    xmlrpc_value * xmlrpc_GrpInterrupt(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo)	
    {
        center_trace(center_log_debug, "recv xmlrpc_GrpInterrupt");
        HRC_NOUSE_2PARAMTER(serInfo,channelInfo);
        DoRobotParame(HMRC_Status_GrpInterrupt);
    }
    xmlrpc_value * xmlrpc_GrpPowerOn(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo)	
    {
        center_trace(center_log_debug, "recv xmlrpc_GrpPowerOn");
        HRC_NOUSE_2PARAMTER(serInfo,channelInfo);
        DoRobotParame(HMRC_Status_PowerOn);
    }
    xmlrpc_value * xmlrpc_GrpPowerOff(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo)	
    {
        center_trace(center_log_debug, "recv xmlrpc_GrpPowerOff");
        HRC_NOUSE_2PARAMTER(serInfo,channelInfo);
        DoRobotParame(HMRC_Status_PowerOff);
    }
    xmlrpc_value * xmlrpc_GrpReset(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo)	
    {
        center_trace(center_log_debug, "recv xmlrpc_GrpReset");
        HRC_NOUSE_2PARAMTER(serInfo,channelInfo);
        DoRobotParame(HMRC_Status_Reset);
    }
    xmlrpc_value * xmlrpc_GrpStop(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo)	
    {
        center_trace(center_log_debug, "recv xmlrpc_GrpStop");
        HRC_NOUSE_2PARAMTER(serInfo,channelInfo);
        DoRobotParame(HMRC_Status_Stop);
    }

    xmlrpc_value * xmlrpc_SetStartAssistiveMode(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo)
    {
        center_trace(center_log_debug, "recv xmlrpc_SetStartAssistiveMode");
        HRC_NOUSE_2PARAMTER(serInfo,channelInfo);
        DoRobotParame(HMRC_Status_StartAssistiveMode);
    }
    
    xmlrpc_value * xmlrpc_SetCloseAssistiveMode(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo)
    {
        center_trace(center_log_debug, "recv xmlrpc_SetCloseAssistiveMode");
        HRC_NOUSE_2PARAMTER(serInfo,channelInfo);
        DoRobotParame(HMRC_Status_CloseAssistiveMode);
    }

    xmlrpc_value * xmlrpc_SetOverride(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo)
    {
        center_trace(center_log_debug, "recv xmlrpc_SetOverride");
        HRC_NOUSE_2PARAMTER(serInfo,channelInfo);
        xmlrpc_int nRbtID = 0;
        xmlrpc_int nClientType = 0;
        char* strOverRide = nullptr;
        string strOverRide2 = "";
        xmlrpc_decompose_value(envP, paramArray, "(iis)", &nRbtID, &nClientType, &strOverRide);
        if (envP->fault_occurred)
        {
            center_trace(center_log_error, "xmlrpc call error %d %s",
                                envP->fault_code,envP->fault_string);
            return nullptr;
        }
        if(strOverRide != nullptr)
        {
            strOverRide2 = string(strOverRide);
            free(strOverRide);
        }
        
        xmlrpc_int nRet = HMRC_Status_SetOverride(nRbtID, stod(strOverRide2), nClientType);
        return xmlrpc_build_value(envP, "i", nRet);
    }
    /* ÉèÖÃTool×ø±ê */
   xmlrpc_value * xmlrpc_SetToolCoordinateMotion(xmlrpc_env* const envP,
       xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo)
   {
       center_trace(center_log_debug, "recv xmlrpc_SetToolCoordinateMotion");
       HRC_NOUSE_2PARAMTER(serInfo,channelInfo);
       xmlrpc_int nRbtID = 0;
       xmlrpc_int nClientType = 0;
       xmlrpc_int nState = 0;
       string strOverRide2 = "";
       xmlrpc_decompose_value(envP, paramArray, "(iii)", &nRbtID, &nClientType, &nState);
       if (envP->fault_occurred)
       {
           center_trace(center_log_error, "xmlrpc call error %d %s",
                               envP->fault_code,envP->fault_string);
           return nullptr;
       }

       xmlrpc_int nRet = HMRC_Status_Set_ToolCoordinateMotion(nRbtID, nState, nClientType);
       return xmlrpc_build_value(envP, "i", nRet);
   }
}
