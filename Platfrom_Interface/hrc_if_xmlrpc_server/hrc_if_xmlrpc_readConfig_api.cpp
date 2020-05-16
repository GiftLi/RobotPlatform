
#include "hrc_if_xmlrpc_api.h"
#include "HRC_StatusMachine/hrc_status_config_api.h"
#include "HRC_Public/hrc_public_factory/hrc_public_factory.h"


namespace xmlrpcServer
{
    /* 读取硬件配置 */
    xmlrpc_value * xmlrpc_ReadRobotsHardConfig(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo)
    {
        string strRespone;
        xmlrpc_int nClientType = 0;
        xmlrpc_int nRbtID = 0;

        HRC_NOUSE_2PARAMTER(serInfo,channelInfo);

        xmlrpc_decompose_value(envP, paramArray, "(ii)", &nRbtID,&nClientType);
        if (envP->fault_occurred)
        {
            center_trace(center_log_error, "xmlrpc call error %d %s",
                envP->fault_code,envP->fault_string);
            return nullptr;
        }

        HRC_Status_ReadHardCfg(strRespone);

        return xmlrpc_build_value(envP, "s", strRespone.c_str());
    }

    /* 读取软件配置 */
    xmlrpc_value * xmlrpc_ReadRobotsConfig(xmlrpc_env* const envP,
            xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo)
    {
        string strRespone;
        xmlrpc_int nClientType = 0;
        xmlrpc_int nRbtID = 0;

        HRC_NOUSE_2PARAMTER(serInfo,channelInfo);

        xmlrpc_decompose_value(envP, paramArray, "(ii)", &nRbtID,&nClientType);
        if (envP->fault_occurred)
        {
            center_trace(center_log_error, "xmlrpc call error %d %s",
                envP->fault_code,envP->fault_string);
            return nullptr;
        }
        HRC_Status_ReadUserCfg(strRespone);

        return xmlrpc_build_value(envP, "s", strRespone.c_str());
    }

    
    /* 读取安全配置 */
    xmlrpc_value * xmlrpc_ReadSafeLevel(xmlrpc_env* const envP,
         xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo)
    {
        string strRespone;
        xmlrpc_int nClientType = 0;
        xmlrpc_int nRbtID = 0;

        HRC_NOUSE_2PARAMTER(serInfo,channelInfo);

        xmlrpc_decompose_value(envP, paramArray, "(ii)", &nRbtID,&nClientType);
        if (envP->fault_occurred)
        {
            center_trace(center_log_error, "xmlrpc call error %d %s",
                            envP->fault_code,envP->fault_string);
            return nullptr;
        }

        HRC_Status_ReadSafeLevelCfg(strRespone);
        return xmlrpc_build_value(envP, "s", strRespone.c_str());
        
    }

    /*
	//////////////////////////////////////////////////////////////////////////
	xmlrpc_value * xmlrpc_ReadEmergencyMonitor(xmlrpc_env* const envP,
		xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo)
	{
         xmlrpc_int nVal = HMRC_Board_IsEmergencyStopEnable() ? 1 : 0;
         return xmlrpc_build_value(envP, "i", nVal);
	}

    //////////////////////////////////////////////////////////////////////////
	xmlrpc_value * xmlrpc_ReadEmergencyForResetIO(xmlrpc_env* const envP,
		xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo)
	{
        xmlrpc_int nVal = HMRC_Board_IsEmergencyStopForResetIO() ? 1 : 0;
        return xmlrpc_build_value(envP, "i", nVal);
	}

	//////////////////////////////////////////////////////////////////////////
	xmlrpc_value * xmlrpc_ReadEmergencyForResetIOState(xmlrpc_env* const envP,
		xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo)
	{
		int nState = 0;
        HMRC_Board_ReadEmergencyStopForResetIOState(nState);
		xmlrpc_int nVal = nState;
		return xmlrpc_build_value(envP, "i", nVal);
	}

	//////////////////////////////////////////////////////////////////////////
	xmlrpc_value * xmlrpc_ReadSafetyGuardMonitor(xmlrpc_env* const envP,
		xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo)
	{
         xmlrpc_int nVal = HMRC_Board_IsSaftyGuradEnable() ? 1 : 0;
         return xmlrpc_build_value(envP, "i", nVal);
	}

	//////////////////////////////////////////////////////////////////////////
	xmlrpc_value * xmlrpc_ReadSafetyGuardHold(xmlrpc_env* const envP,
		xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo)
	{
        xmlrpc_int nVal = HMRC_Board_IsSaftyGuradHold() ? 1 : 0;
        return xmlrpc_build_value(envP, "i", nVal);
    }

	//////////////////////////////////////////////////////////////////////////
	xmlrpc_value * xmlrpc_ReadSwitchOnMonitor(xmlrpc_env* const envP,
		xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo)
	{
        xmlrpc_int nVal = HMRC_Board_IsSwitchOnEnable() ? 1 : 0;
        return xmlrpc_build_value(envP, "i", nVal);
	}

	//////////////////////////////////////////////////////////////////////////
	xmlrpc_value * xmlrpc_ReadConveyorConfig(xmlrpc_env* const envP,
		xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo)
	{
		xmlrpc_int nRbtID = 0;
		xmlrpc_decompose_value(envP, paramArray, "(i)", &nRbtID);
		xmlrpc_int nDirection = 0;
		xmlrpc_int nDccWindow = 0;
		xmlrpc_int nStoppedWindow = 0;
		xmlrpc_int nRet = HMRC_Config_ReadConveyorConfig(nRbtID, nDirection, nDccWindow, nStoppedWindow);
		return xmlrpc_build_value(envP, "(iii)",
			nDirection, nDccWindow, nStoppedWindow);
	}



    //读取安全平面
    xmlrpc_value * xmlrpc_ReadSafetyPanel(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo)
    {
        xmlrpc_int nRbtID = 0;



        return xmlrpc_build_value(envP, "s", "0");
    }
    
    xmlrpc_value * xmlrpc_ReadSafetyScope(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo)
    {
        xmlrpc_int nRbtID = 0;
        return xmlrpc_build_value(envP, "s", "0");
    }

    xmlrpc_value * xmlrpc_ReadRobotsConfig_tmp(xmlrpc_env* const envP,
            xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo)
        {
            string strRespone;
            xmlrpc_int nClientType = 0;
            xmlrpc_int nRbtID = 0;
    
            xmlrpc_decompose_value(envP, paramArray, "(ii)", &nRbtID,&nClientType);
            if (envP->fault_occurred)
            {
                center_trace(center_log_error, "xmlrpc call error %d %s",
                    envP->fault_code,envP->fault_string);
                return nullptr;
            }        
            xmlrpc_int nRet = HMRC_Status_ReadRobotsConfig(strRespone);
    
            strRespone = Xml2Json(strRespone);
    
            int strWhere = strRespone.find("\"TCP\":");
            if (strWhere = strRespone.npos)
            {
                return xmlrpc_build_value(envP, "i", -1);
            }
            string strStart = strRespone.substr(0, strWhere + 6); // + length("\"TCP"\:")
            string strTmp = strRespone.substr(strWhere+1+6);  //剩下的字符串
            int tmpWhere = strTmp.find("[");  //判断原来是否为数组
    
            if (tmpWhere < 20)  //数组
            {
                return xmlrpc_build_value(envP, "s", strRespone.c_str());
            }
    
            int endWhere = strTmp.find("}");
            string strInter = strTmp.substr(0, endWhere + 1);
    
            string strEnd = strTmp.substr(endWhere + 1);
            strRespone = strStart + "[" + strInter + "]" + strEnd;
    
            strWhere = strRespone.find("\"UCS\":");
            if (strWhere < 0)
            {
                return xmlrpc_build_value(envP, "i", -1);
            }
            strStart = strRespone.substr(0, strWhere + 6); // + length("\"TCP"\:")
            strTmp = strRespone.substr(strWhere + 1 + 6);  //剩下的字符串
            tmpWhere = strTmp.find("[");  //判断原来是否为数组
    
            if (tmpWhere < 20)  //数组
            {
                return xmlrpc_build_value(envP, "s", strRespone.c_str());
            }
    
            endWhere = strTmp.find("}");
            strInter = strTmp.substr(0, endWhere + 1);
    
            strEnd = strTmp.substr(endWhere + 1);
            strRespone = strStart + "[" + strInter + "]" + strEnd;
    
            return xmlrpc_build_value(envP, "s", strRespone.c_str());
        }
    

    xmlrpc_value * xmlrpc_ReadConveyorValue(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo)
    {

        xmlrpc_int nRbtID = 0;
        int pValue = 0;

        xmlrpc_decompose_value(envP, paramArray, "(i)", &nRbtID);
        xmlrpc_int nRet = HMRC_Status_ReadConveyorValue(nRbtID, &pValue);

        return xmlrpc_build_value(envP, "i", nRet);

    }*/
}
