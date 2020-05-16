
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
    /* ���õ������� */
    xmlrpc_value * xmlrpc_SetKinematicCoordinate(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo)
    {
        HRC_NOUSE_2PARAMTER(serInfo,channelInfo);
        DoRobotParameSetJsonConfig(HRC_Status_SetTCP);
    }

    /* �����û����� */
    xmlrpc_value * xmlrpc_SetUserCoordinate(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo)
    {
        HRC_NOUSE_2PARAMTER(serInfo,channelInfo);
        DoRobotParameSetJsonConfig(HRC_Status_SetUCS);
    }
    /* ���û�����װ�Ƕ� */
    xmlrpc_value * xmlrpc_SetBaseMountingAngle(xmlrpc_env* const envP,
         xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo)
    {
        HRC_NOUSE_2PARAMTER(serInfo,channelInfo);
        DoRobotParameSetJsonConfig(HRC_Status_SetBaseMountingAngle);
    }

    /* ���ÿռ������˶���Χ */
    xmlrpc_value * xmlrpc_SetPcsSafeSpaceLimit(xmlrpc_env* const envP,
     xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo)
    {
        HRC_NOUSE_2PARAMTER(serInfo,channelInfo);
        DoRobotParameSetJsonConfig(HRC_Status_SetPcsSafeSpaceLimit);
    }       
     
     /* ���ùؽ������˶���Χ */
    xmlrpc_value * xmlrpc_SetAcsSafeSpaceLimit(xmlrpc_env* const envP,
     xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo)
    {
        HRC_NOUSE_2PARAMTER(serInfo,channelInfo);
        DoRobotParameSetJsonConfig(HRC_Status_SetAcsSafeSpaceLimit);
    }

    /* �������ؽ��˶��ٶ� */
    xmlrpc_value * xmlrpc_SetMoveJointMotionLimits(xmlrpc_env* const envP,
     xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo)
    {
        HRC_NOUSE_2PARAMTER(serInfo,channelInfo);
        DoRobotParameSetJsonConfig(HRC_Status_SetMoveJointMotionLimits);
    }

    /* ��������˶��ٶ� */    
    xmlrpc_value * xmlrpc_SetMovePcsMotionLimits(xmlrpc_env* const envP,
     xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo)
    {
        HRC_NOUSE_2PARAMTER(serInfo,channelInfo);
        DoRobotParameSetJsonConfig(HRC_Status_SetMovePcsMotionLimits);
        
    }

    /* �������ؽ��˶�ֹͣ�ٶ� */        
    xmlrpc_value * xmlrpc_SetStopJointMotionLimits(xmlrpc_env* const envP,
     xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo)
    {
        HRC_NOUSE_2PARAMTER(serInfo,channelInfo);
        DoRobotParameSetJsonConfig(HRC_Status_SetStopJointMotionLimits);
    }
         
    /* ��������˶�ֹͣ�ٶ� */
    xmlrpc_value * xmlrpc_SetStopPcsMotionLimits(xmlrpc_env* const envP,
     xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo)
    {
        HRC_NOUSE_2PARAMTER(serInfo,channelInfo);
        DoRobotParameSetJsonConfig(HRC_Status_SetStopPcsMotionLimits);
    }

    /* ���ø��ز��� */
    xmlrpc_value * xmlrpc_SetPayload(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo)
    {
        HRC_NOUSE_2PARAMTER(serInfo,channelInfo);
        DoRobotParameSetJsonConfig(HRC_Status_SetGravityPayload);
    }    

    /* ���ð�ȫ�ȼ� */
    xmlrpc_value * xmlrpc_SetCollideLevel(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo)
    {
        HRC_NOUSE_2PARAMTER(serInfo,channelInfo);
        DoRobotParameSetJsonConfig(HRC_Status_SetCollideLevel);
    }

    /* ���ð�ȫ��Ļʹ�� */
    xmlrpc_value * xmlrpc_SetSafetyGuardMonitor(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo)
    {
        HRC_NOUSE_2PARAMTER(serInfo,channelInfo);
        DoRobotParameSetJsonConfig(HRC_Status_SetMonitorSafetyStatus);
    }


    /* ���ü�ͣ����IO */
    xmlrpc_value * xmlrpc_SetEmergencyForResetIO(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo)
    {
        HRC_NOUSE_2PARAMTER(serInfo,channelInfo);
        DoRobotParameSetJsonConfig(HRC_Status_SetMonitorErrorStatus);
    }

    /* ����ͨ��IO */
    xmlrpc_value * xmlrpc_SetBoxDIConfig(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo)
    {
        HRC_NOUSE_2PARAMTER(serInfo,channelInfo);
        DoRobotParameSetJsonConfig(HRC_Status_SetDigitalInIO);
    }

    /* ����ͨ��DO */
    xmlrpc_value * xmlrpc_SetBoxDOConfig(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo)
    {
        HRC_NOUSE_2PARAMTER(serInfo,channelInfo);
        DoRobotParameSetJsonConfig(HRC_Status_SetDigitalOutIO);
    }

    /* ����ģ�������� */
    xmlrpc_value * xmlrpc_SetBoxAIConfig(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo)
    {
        HRC_NOUSE_2PARAMTER(serInfo,channelInfo);
        DoRobotParameSetJsonConfig(HRC_Status_SetSerialAnalogInIO);
    }

    /* ����ģ������� */
    xmlrpc_value * xmlrpc_SetBoxAOConfig(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo)
    {
        HRC_NOUSE_2PARAMTER(serInfo,channelInfo);
        DoRobotParameSetJsonConfig(HRC_Status_SetSerialAnalogOutIO);
    }

    /* ���ÿ�����CI */
    xmlrpc_value * xmlrpc_SetBoxCIConfig(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo)
    {
        HRC_NOUSE_2PARAMTER(serInfo,channelInfo);
        DoRobotParameSetJsonConfig(HRC_Status_SetConfigInIO);
    }

    /* ���ÿ�����CO */
    xmlrpc_value * xmlrpc_SetBoxCOConfig(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo)
    {
        HRC_NOUSE_2PARAMTER(serInfo,channelInfo);
        DoRobotParameSetJsonConfig(HRC_Status_SetConfigOutIO);
    }

    /* ����ĩ��IO */
    xmlrpc_value * xmlrpc_SetEndDIConfig(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo)
    {
        HRC_NOUSE_2PARAMTER(serInfo,channelInfo);
        DoRobotParameSetJsonConfig(HRC_Status_SetEndInIO);
    }

    /* ����ĩ��DO */
    xmlrpc_value * xmlrpc_SetEndDOConfig(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo)
    {
        HRC_NOUSE_2PARAMTER(serInfo,channelInfo);
        DoRobotParameSetJsonConfig(HRC_Status_SetEndOutIO);
    }

    /* ����ĩ��AI */
    xmlrpc_value * xmlrpc_SetEndAIConfig(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo)
    {
        HRC_NOUSE_2PARAMTER(serInfo,channelInfo);
        DoRobotParameSetJsonConfig(HRC_Status_SetEndAI);
    }

    /******************  2019.12.16 modbus config --LJH  **************************/
    /* ����豸*/
    xmlrpc_value * xmlrpc_AddModbusClientDevice(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo)
    {
        HRC_NOUSE_2PARAMTER(serInfo,channelInfo);
        DoRobotParameModifiJsonConfig(HRC_Status_AddConfigModbusTcpClient);
    }

    /* ɾ���豸 */
    xmlrpc_value * xmlrpc_DelModbusClientDevice(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo)
    {
        HRC_NOUSE_2PARAMTER(serInfo,channelInfo);
        DoRobotParameModifiJsonConfig(HRC_Status_DeleteConfigModbusTcpClient);
    }

    /* �޸�  �豸���� */
    xmlrpc_value * xmlrpc_SetModbusClientPamar(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo)
    {
        HRC_NOUSE_2PARAMTER(serInfo,channelInfo);
        DoRobotParameModifiJsonConfig(HRC_Status_ModifiConfigModbusTcpClient);
    }

    /******************************************************************************/

    /* ���ؽű���������� */
    xmlrpc_value * xmlrpc_SetRobotConfig(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo)
    {
        HRC_NOUSE_2PARAMTER(serInfo,channelInfo);
        DoRobotParameSetJsonConfig(HRC_Status_ImportScript);
    }

    /* ����Ӳ������ */
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
        char* sJson = nullptr;                      /* ҳ�洫������json�ַ��� */
        char* fileName = nullptr;                   /* ҳ�洫�������ļ��� */
        cJSON *jsonObj = nullptr;                   /* ��ҳ�洫�������ַ���ת����json���� */
        char * strJsonObj = nullptr;                /* ��ת�����json�����ٴ�ת�����ַ��� */
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

        // �Ƚ�json strת����json obj
        // �ڽ�json objת���� json str
        // ת��һ���str�л���'\t' '\n'���ַ�.
        // ��֤json�ļ��Ŀɶ���
        jsonObj = cJSON_Parse(sJson);
        if(jsonObj == nullptr) {
            center_trace(center_log_error, "json format error");
            nRet = REC_JsonFormatErr;
            goto over;
        }
        strJsonObj = cJSON_Print(jsonObj);

        /* ���ļ� */
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
        char* sJson = nullptr;                      /* ҳ�洫������json�ַ��� */
        char* fileName = nullptr;                   /* ҳ�洫�������ļ��� */
        cJSON *jsonObj = nullptr;                   /* ��ҳ�洫�������ַ���ת����json���� */
        char * strJsonObj = nullptr;                /* ��ת�����json�����ٴ�ת�����ַ��� */
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

        // �Ƚ�json strת����json obj
        // �ڽ�json objת���� json str
        // ת��һ���str�л���'\t' '\n'���ַ�.
        // ��֤json�ļ��Ŀɶ���
        jsonObj = cJSON_Parse(sJson);
        if(jsonObj == nullptr) {
            center_trace(center_log_error, "json format error");
            nRet = REC_JsonFormatErr;
            goto over;
        }
        strJsonObj = cJSON_Print(jsonObj);

        /* ���ļ� */
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


    //���ð�ȫƽ��
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

        //xxx ���������ļ�
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
