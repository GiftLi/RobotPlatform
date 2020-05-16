#include "hrc_if_xmlrpc_api.h"

#include "HRC_StatusMachine/hrc_status_api.h"
#include "../public_files/global_error/hrc_public_gerrorcode.h"
#include "HRC_Public/hrc_public_factory/hrc_public_factory.h"

namespace xmlrpcServer
{
    /* 开始运行脚本 */
    xmlrpc_value * xmlrpc_StartScript(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo)
    {
        xmlrpc_int nRbtID = 0;
        xmlrpc_int nClientType = 0;
        char* strJsonScript = nullptr; 
        xmlrpc_int nRet = 0;
        cJSON *cJson = nullptr;
        
        HRC_NOUSE_2PARAMTER(serInfo,channelInfo);

        center_trace(center_log_debug, "recv xmlrpc_StartScript");
        xmlrpc_decompose_value(envP, paramArray, "(iis)", 
                    &nRbtID, &nClientType, &strJsonScript);

        if (envP->fault_occurred)
        {
            center_trace(center_log_error, "xmlrpc call error %d %s",
                envP->fault_code,envP->fault_string);
            return nullptr;
        }

        if(strJsonScript == nullptr)
        {
            center_trace(center_log_error,"json error");
            nRet = REC_JsonFormatErr;
            goto over;
        }
        //printf("%s",strJsonScript);

        if((cJson = cJSON_Parse(strJsonScript))== nullptr)
        {
            center_trace(center_log_error, "error json str");
            nRet = REC_JsonFormatErr;
            goto over;
        }
        
        nRet = HRC_GET_SCRIPT()->writeDefaultJsonInFile(cJson);
        if(nRet != REC_Successed)
        {
            goto over;
        }       

        nRet = HMRC_Status_StartScript(nRbtID,nClientType);

over:
        if(nRet != REC_Successed)
        {
            printf("\nstart script error %d!!!!!!!!!!!!!!!!!!\n",nRet);
        }
        if(strJsonScript) free(strJsonScript);
        if(cJson) cJSON_Delete(cJson);
        return xmlrpc_build_value(envP, "i", nRet);
    }
    
    /* 停止运行脚本 */
    xmlrpc_value * xmlrpc_StopScript(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo)
    {
        HRC_NOUSE_2PARAMTER(serInfo,channelInfo);
        DoRobotScriptParame(HMRC_Status_StopScript);
    }
    
    /* 暂停 */
    xmlrpc_value * xmlrpc_PauseScript(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo)
    {
        HRC_NOUSE_2PARAMTER(serInfo,channelInfo);
        DoRobotScriptParame(HMRC_Status_ScriptHold);
    }

    
    /* 继续 */
    xmlrpc_value * xmlrpc_ContinueScript(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo)
    {
        HRC_NOUSE_2PARAMTER(serInfo,channelInfo);
        DoRobotScriptParame(HMRC_Status_ScriptContinue);
    }    

    /* 下一步 */
    xmlrpc_value * xmlrpc_NextStepScript(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo)
    {
        HRC_NOUSE_2PARAMTER(serInfo,channelInfo);
        DoRobotScriptParame(HMRC_Status_ScriptStepNext);
    }

    /* 下一个断点 */
    xmlrpc_value * xmlrpc_NextBreakPoint(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo)
    {
        HRC_NOUSE_2PARAMTER(serInfo,channelInfo);
        DoRobotScriptParame(HMRC_Status_ScriptNextBreakPoint);
    }


}





