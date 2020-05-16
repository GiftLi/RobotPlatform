
#include <fstream>
#include <streambuf>
#include <unistd.h>


#include "hrc_if_xmlrpc_api.h"
#include "HRC_StatusMachine/hrc_status_config_api.h"
#include "../public_files/global_error/hrc_public_gerrorcode.h"
#include "HRC_Public/hrc_public_factory/hrc_public_factory.h"
#include "HRC_Public/hrc_public_func.h"


namespace xmlrpcServer
{
    /* 设置刀具坐标 */
    xmlrpc_value * xmlrpc_SetKinematicCoordinate(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo)
    {
        HRC_NOUSE_2PARAMTER(serInfo,channelInfo);
        DoRobotParameSetJsonConfig(HRC_Status_SetTCP);
    }

    /* 设置用户坐标 */
    xmlrpc_value * xmlrpc_SetUserCoordinate(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo)
    {
        HRC_NOUSE_2PARAMTER(serInfo,channelInfo);
        DoRobotParameSetJsonConfig(HRC_Status_SetUCS);
    }
    /* 设置基座安装角度 */
    xmlrpc_value * xmlrpc_SetBaseMountingAngle(xmlrpc_env* const envP,
         xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo)
    {
        HRC_NOUSE_2PARAMTER(serInfo,channelInfo);
        DoRobotParameSetJsonConfig(HRC_Status_SetBaseMountingAngle);
    }

    /* 设置空间坐标运动范围 */
    xmlrpc_value * xmlrpc_SetPcsSafeSpaceLimit(xmlrpc_env* const envP,
     xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo)
    {
        HRC_NOUSE_2PARAMTER(serInfo,channelInfo);
        DoRobotParameSetJsonConfig(HRC_Status_SetPcsSafeSpaceLimit);
    }       
     
     /* 设置关节坐标运动范围 */
    xmlrpc_value * xmlrpc_SetAcsSafeSpaceLimit(xmlrpc_env* const envP,
     xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo)
    {
        HRC_NOUSE_2PARAMTER(serInfo,channelInfo);
        DoRobotParameSetJsonConfig(HRC_Status_SetAcsSafeSpaceLimit);
    }

    /* 设置最大关节运动速度 */
    xmlrpc_value * xmlrpc_SetMoveJointMotionLimits(xmlrpc_env* const envP,
     xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo)
    {
        HRC_NOUSE_2PARAMTER(serInfo,channelInfo);
        DoRobotParameSetJsonConfig(HRC_Status_SetMoveJointMotionLimits);
    }

    /* 设置最大运动速度 */    
    xmlrpc_value * xmlrpc_SetMovePcsMotionLimits(xmlrpc_env* const envP,
     xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo)
    {
        HRC_NOUSE_2PARAMTER(serInfo,channelInfo);
        DoRobotParameSetJsonConfig(HRC_Status_SetMovePcsMotionLimits);
        
    }

    /* 设置最大关节运动停止速度 */        
    xmlrpc_value * xmlrpc_SetStopJointMotionLimits(xmlrpc_env* const envP,
     xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo)
    {
        HRC_NOUSE_2PARAMTER(serInfo,channelInfo);
        DoRobotParameSetJsonConfig(HRC_Status_SetStopJointMotionLimits);
    }
         
    /* 设置最大运动停止速度 */
    xmlrpc_value * xmlrpc_SetStopPcsMotionLimits(xmlrpc_env* const envP,
     xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo)
    {
        HRC_NOUSE_2PARAMTER(serInfo,channelInfo);
        DoRobotParameSetJsonConfig(HRC_Status_SetStopPcsMotionLimits);
    }

    /* 设置负载参数 */
    xmlrpc_value * xmlrpc_SetPayload(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo)
    {
        HRC_NOUSE_2PARAMTER(serInfo,channelInfo);
        DoRobotParameSetJsonConfig(HRC_Status_SetGravityPayload);
    }    

    /* 设置安全等级 */
    xmlrpc_value * xmlrpc_SetCollideLevel(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo)
    {
        HRC_NOUSE_2PARAMTER(serInfo,channelInfo);
        DoRobotParameSetJsonConfig(HRC_Status_SetCollideLevel);
    }

    /* 设置安全光幕使能 */
    xmlrpc_value * xmlrpc_SetSafetyGuardMonitor(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo)
    {
        HRC_NOUSE_2PARAMTER(serInfo,channelInfo);
        DoRobotParameSetJsonConfig(HRC_Status_SetMonitorSafetyStatus);
    }


    /* 配置急停重置IO */
    xmlrpc_value * xmlrpc_SetEmergencyForResetIO(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo)
    {
        HRC_NOUSE_2PARAMTER(serInfo,channelInfo);
        DoRobotParameSetJsonConfig(HRC_Status_SetMonitorErrorStatus);
    }

    /* 配置通用IO */
    xmlrpc_value * xmlrpc_SetBoxDIConfig(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo)
    {
        HRC_NOUSE_2PARAMTER(serInfo,channelInfo);
        DoRobotParameSetJsonConfig(HRC_Status_SetDigitalInIO);
    }

    /* 配置通用DO */
    xmlrpc_value * xmlrpc_SetBoxDOConfig(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo)
    {
        HRC_NOUSE_2PARAMTER(serInfo,channelInfo);
        DoRobotParameSetJsonConfig(HRC_Status_SetDigitalOutIO);
    }

    /* 配置模拟量输入 */
    xmlrpc_value * xmlrpc_SetBoxAIConfig(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo)
    {
        HRC_NOUSE_2PARAMTER(serInfo,channelInfo);
        DoRobotParameSetJsonConfig(HRC_Status_SetSerialAnalogInIO);
    }

    /* 配置模拟量输出 */
    xmlrpc_value * xmlrpc_SetBoxAOConfig(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo)
    {
        HRC_NOUSE_2PARAMTER(serInfo,channelInfo);
        DoRobotParameSetJsonConfig(HRC_Status_SetSerialAnalogOutIO);
    }

    /* 配置可配置CI */
    xmlrpc_value * xmlrpc_SetBoxCIConfig(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo)
    {
        HRC_NOUSE_2PARAMTER(serInfo,channelInfo);
        DoRobotParameSetJsonConfig(HRC_Status_SetConfigInIO);
    }

    /* 配置可配置CO */
    xmlrpc_value * xmlrpc_SetBoxCOConfig(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo)
    {
        HRC_NOUSE_2PARAMTER(serInfo,channelInfo);
        DoRobotParameSetJsonConfig(HRC_Status_SetConfigOutIO);
    }

    /* 配置末端IO */
    xmlrpc_value * xmlrpc_SetEndDIConfig(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo)
    {
        HRC_NOUSE_2PARAMTER(serInfo,channelInfo);
        DoRobotParameSetJsonConfig(HRC_Status_SetEndInIO);
    }

    /* 配置末端DO */
    xmlrpc_value * xmlrpc_SetEndDOConfig(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo)
    {
        HRC_NOUSE_2PARAMTER(serInfo,channelInfo);
        DoRobotParameSetJsonConfig(HRC_Status_SetEndOutIO);
    }

    /* 配置末端AI */
    xmlrpc_value * xmlrpc_SetEndAIConfig(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo)
    {
        HRC_NOUSE_2PARAMTER(serInfo,channelInfo);
        DoRobotParameSetJsonConfig(HRC_Status_SetEndAI);
    }

    /******************  2019.12.16 modbus config --LJH  **************************/
    /* 添加设备*/
    xmlrpc_value * xmlrpc_AddModbusClientDevice(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo)
    {
        HRC_NOUSE_2PARAMTER(serInfo,channelInfo);
        DoRobotParameModifiJsonConfig(HRC_Status_AddConfigModbusTcpClient);
    }

    /* 删除设备 */
    xmlrpc_value * xmlrpc_DelModbusClientDevice(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo)
    {
        HRC_NOUSE_2PARAMTER(serInfo,channelInfo);
        DoRobotParameModifiJsonConfig(HRC_Status_DeleteConfigModbusTcpClient);
    }

    /* 修改  设备参数 */
    xmlrpc_value * xmlrpc_SetModbusClientPamar(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo)
    {
        HRC_NOUSE_2PARAMTER(serInfo,channelInfo);
        DoRobotParameModifiJsonConfig(HRC_Status_ModifiConfigModbusTcpClient);
    }

    /******************************************************************************/

    /* 加载脚本及软件配置 */
    xmlrpc_value * xmlrpc_SetRobotConfig(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo)
    {
        HRC_NOUSE_2PARAMTER(serInfo,channelInfo);
        DoRobotParameSetJsonConfig(HRC_Status_ImportScript);
    }

    /* 加载硬件配置 */
    xmlrpc_value * xmlrpc_SetRobotHardConfig(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo)
    {
        HRC_NOUSE_2PARAMTER(serInfo,channelInfo);
        DoRobotParameSetJsonConfig(HRC_Status_ImportHard);
    }

    /*  */
    xmlrpc_value * xmlrpc_SaveScriptFile(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo)
    {
        xmlrpc_int nRbtID = 0;
        xmlrpc_int nClientID = 0;
        char* sJson = nullptr;                      /* 页面传过来的json字符串 */
        char* fileName = nullptr;                   /* 页面传过来的文件名 */
        cJSON *jsonObj = nullptr;                   /* 将页面传过来的字符串转化成json对象 */
        char * strJsonObj = nullptr;                /* 将转换后的json对象再次转换成字符串 */
        xmlrpc_int nRet = REC_Successed;
        FILE *fp = nullptr;
        string filePath = "";

        HRC_NOUSE_2PARAMTER(serInfo,channelInfo);
        xmlrpc_decompose_value(envP, paramArray, "(iiss)", &nRbtID, &nClientID, &fileName, &sJson);
        if (envP->fault_occurred)
        {
            center_trace(center_log_error, "xmlrpc call error %d %s",envP->fault_code,envP->fault_string);
            return nullptr;
        }

		if (0 != access(CENTER_SCRIPT_PATH, 0))
		{
            mkdir(CENTER_SCRIPT_PATH, 0777);
		}

        if(sJson == nullptr || fileName == nullptr) 
        {
            center_trace(center_log_error, "json or filename empty");
            nRet = REC_ParamError;
            goto over;
        }

        // 先将json str转化成json obj
        // 在将json obj转化成 json str
        // 转化一遍后str中会有'\t' '\n'等字符.
        // 保证json文件的可读性
        jsonObj = cJSON_Parse(sJson);
        if(jsonObj == nullptr) {
            center_trace(center_log_error, "json format error");
            nRet = REC_JsonFormatErr;
            goto over;
        }
        strJsonObj = cJSON_Print(jsonObj);

        /* 存文件 */
        filePath = string(CENTER_SCRIPT_PATH) + "/" + fileName;
        fp = fopen( filePath.c_str(), "w");
        if (nullptr == fp)
		{
            center_trace(center_log_error, "json format error");
            nRet = REC_SaveCfgFileFaile;
            goto over;
		}
        fwrite(strJsonObj,1,strlen(strJsonObj),fp);

        /* auto goto over */
over:
        if(fileName != nullptr) free(fileName);
        if(sJson != nullptr) free(sJson);
        if(jsonObj != nullptr) cJSON_Delete(jsonObj);
        if(fp != nullptr) fclose(fp);
        if(strJsonObj != nullptr) free(strJsonObj);
        
        return xmlrpc_build_value(envP, "i", nRet);
        
    }

        
    /* */
    xmlrpc_value * xmlrpc_SaveRobotHardFile(xmlrpc_env* const envP,
       xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo)
    {
        xmlrpc_int nRbtID = 0;
        xmlrpc_int nClientID = 0;
        char* sJson = nullptr;                      /* 页面传过来的json字符串 */
        char* fileName = nullptr;                   /* 页面传过来的文件名 */
        cJSON *jsonObj = nullptr;                   /* 将页面传过来的字符串转化成json对象 */
        char * strJsonObj = nullptr;                /* 将转换后的json对象再次转换成字符串 */
        xmlrpc_int nRet = REC_Successed;
        FILE *fp = nullptr;
        string filePath = "";
        
        HRC_NOUSE_2PARAMTER(serInfo,channelInfo);
        xmlrpc_decompose_value(envP, paramArray, "(iiss)", &nRbtID, &nClientID, &fileName, &sJson);
        if (envP->fault_occurred)
        {
            center_trace(center_log_error, "xmlrpc call error %d %s",envP->fault_code,envP->fault_string);
            return nullptr;
        }

        if (0 != access(CENTER_SCRIPT_PATH, 0))
        {
            mkdir(CENTER_SCRIPT_PATH, 0777);
        }

        if(sJson == nullptr || fileName == nullptr) 
        {
            center_trace(center_log_error, "json or filename empty");
            nRet = REC_ParamError;
            goto over;
        }

        // 先将json str转化成json obj
        // 在将json obj转化成 json str
        // 转化一遍后str中会有'\t' '\n'等字符.
        // 保证json文件的可读性
        jsonObj = cJSON_Parse(sJson);
        if(jsonObj == nullptr) {
            center_trace(center_log_error, "json format error");
            nRet = REC_JsonFormatErr;
            goto over;
        }
        strJsonObj = cJSON_Print(jsonObj);

        /* 存文件 */
        filePath = string(CENTER_SCRIPT_PATH) + "/" + fileName;
        fp = fopen( filePath.c_str(), "w");
        if (nullptr == fp)
        {
            center_trace(center_log_error, "json format error");
            nRet = REC_SaveCfgFileFaile;
            goto over;
        }
        fwrite(strJsonObj,1,strlen(strJsonObj),fp);

        /* auto goto over */
over:
        if(fileName != nullptr) free(fileName);
        if(sJson != nullptr) free(sJson);
        if(jsonObj != nullptr) cJSON_Delete(jsonObj);
        if(fp != nullptr) fclose(fp);
        if(strJsonObj != nullptr) free(strJsonObj);
        
        return xmlrpc_build_value(envP, "i", nRet);


    }


    //设置安全平面
    xmlrpc_value * xmlrpc_SetSafetyPanel(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo)
    {
        HRC_NOUSE_3PARAMTER(paramArray,serInfo,channelInfo);
        return xmlrpc_build_value(envP, "i", 0);
    }


/*    xmlrpc_value * xmlrpc_SetStartFeedforwardMode(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo)
    {
        xmlrpc_int nRbtID = 0;
        xmlrpc_decompose_value(envP, paramArray, "(i)", &nRbtID);
        xmlrpc_int nRet = HMRC_Robot_Set_StartFeedforwardMode(nRbtID);
        return xmlrpc_build_value(envP, "i", nRet);
    }
    xmlrpc_value * xmlrpc_SetEmergencyForResetIOState(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo)
    {
        DoRobotParameSetConfig(HMRC_Status_Set_EmergencyForResetIOState);
    }

    xmlrpc_value * xmlrpc_SetCloseFeedforwardMode(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo)
    {
        xmlrpc_int nRbtID = 0;
        xmlrpc_decompose_value(envP, paramArray, "(i)", &nRbtID);
        xmlrpc_int nRet = HMRC_Robot_Set_CloseFeedforwardMode(nRbtID);
        return xmlrpc_build_value(envP, "i", nRet);
    }

    xmlrpc_value * xmlrpc_SetFeedforwardVelocityMode(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo)
    {
        xmlrpc_int nRbtID = 0;
        xmlrpc_int nFeedforwardVelocityMode = 0;
        xmlrpc_decompose_value(envP, paramArray, "(ii)", &nRbtID, &nFeedforwardVelocityMode);
        xmlrpc_int nRet = HMRC_Robot_Set_FeedForwardVelocityMode(nRbtID, nFeedforwardVelocityMode);
        return xmlrpc_build_value(envP, "i", nRet);
    }


    xmlrpc_value * xmlrpc_SetToolCoordinateMotion(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo)
    {
        xmlrpc_int nRbtID = 0;
        xmlrpc_int nState = 0;
        xmlrpc_decompose_value(envP, paramArray, "(ii)", &nRbtID, &nState);
        xmlrpc_int nRet = HMRC_Robot_Set_ToolCoordinateMotion(nRbtID, nState);
        return xmlrpc_build_value(envP, "i", nRet);
    }

    xmlrpc_value * xmlrpc_SetHomePosition(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo)
    {
        xmlrpc_int nRbtID = 0;
        xmlrpc_int nClientID = 0;
        ST_MultiEndatPos pHomePos;
        xmlrpc_decompose_value(envP, paramArray, "(iidddddd)", &nRbtID, &nClientID,
            &(pHomePos.multiEndatPos[0]),
            &(pHomePos.multiEndatPos[1]),
            &(pHomePos.multiEndatPos[2]),
            &(pHomePos.multiEndatPos[3]),
            &(pHomePos.multiEndatPos[4]),
            &(pHomePos.multiEndatPos[5]));
        if (envP->fault_occurred)
        {
            center_trace(center_log_error, "xmlrpc call error %d %s",
                envP->fault_code,envP->fault_string);
            return nullptr;
        }

        //xxx 保存配置文件
        xmlrpc_int nRet = HMRC_Robot_Set_HomePosition(nRbtID, pHomePos);
        return xmlrpc_build_value(envP, "i", nRet);
    }
    
    xmlrpc_value * xmlrpc_SetSafetyGuardHold(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo)
    {
        DoRobotParameSetConfig(HMRC_Status_Set_SafetyGuardHold);
    } 

    */


}
