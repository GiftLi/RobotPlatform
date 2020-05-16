#include "hrc_if_xmlrpc_modbus_api.h"
#include "HRC_Public/hrc_public_factory/hrc_public_factory.h"
#include "../public_files/global_error/hrc_public_gerrorcode.h"
#include "../HRC_Modbus/HRC_Modbus.h"

namespace xmlrpcServer
{
    xmlrpc_value * xmlrpc_WriteModbusData(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo)
    {
        int nRbtID = 0;
        int nClientType = 0;
        char* strName = nullptr;
        char* valName = nullptr;
        int nValue = 0;

        xmlrpc_int nRet = 0;

        HRC_NOUSE_2PARAMTER(serInfo,channelInfo);

        xmlrpc_decompose_value(envP, paramArray, "(iissi)", &nRbtID, &nClientType,
                               &strName, &valName,&nValue);

        if (envP->fault_occurred)
        {
            center_trace(center_log_error, "xmlrpc call error %d %s",
                envP->fault_code,envP->fault_string);

            nRet = REC_ParamError;
            return xmlrpc_build_value(envP, "i", nRet);
        }

        if(nullptr == strName)
        {
            nRet = REC_DeviceNotExist;
            return xmlrpc_build_value(envP, "i", nRet);
        }

        nRet = HRC_GET_MDB()->SetModbusServerValue(strName,valName,nValue);
        if(!nRet)
        {
            center_trace(center_log_error, "xmlrpc modbus client no exist![name : %s]",
                strName);
            nRet = REC_DeviceNotExist;
            return xmlrpc_build_value(envP, "i", nRet);
        }

        free(strName);
        free(valName);

        return xmlrpc_build_value(envP, "i", nRet);
    }


    xmlrpc_value * xmlrpc_ReadModbusData(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo)
    {
        int nRbtID = 0;
        int nClientType = 0;

        xmlrpc_int nRet = 0;

        HRC_NOUSE_2PARAMTER(serInfo,channelInfo);

        xmlrpc_decompose_value(envP, paramArray, "(ii)", &nRbtID, &nClientType);

        if (envP->fault_occurred)
        {
            center_trace(center_log_error, "xmlrpc call error %d %s",
                envP->fault_code,envP->fault_string);
            nRet = REC_ParamError;
            return xmlrpc_build_value(envP, "i", nRet);
        }

        vector<st_ModbusDeviceInfo> vAllDevicesInfo;

        if(!HRC_GET_MDB()->GetAllModbusClientDeviceInfo(vAllDevicesInfo))
        {
            xmlrpc_int nRet = -1;
            return xmlrpc_build_value(envP, "i",nRet);
        }

        cJSON *js_MdbClient,*js_modbus,*js_modbusArray;
        cJSON *root = cJSON_CreateObject();
        cJSON_AddItemToObject(root,"HMRC", js_MdbClient = cJSON_CreateObject());
        cJSON_AddItemToObject(js_MdbClient,"modbusClient",js_modbus = cJSON_CreateObject());
        cJSON_AddItemToObject(js_modbus,"modbus",js_modbusArray = cJSON_CreateArray());

        //handle Info
        vector<st_ModbusDeviceInfo>::iterator vDevicesInfo;
        cJSON*js_Device = nullptr;
        for(vDevicesInfo=vAllDevicesInfo.begin(); vDevicesInfo!=vAllDevicesInfo.end(); vDevicesInfo++)
        {
            cJSON_AddItemToArray(js_modbusArray, js_Device = cJSON_CreateObject());

            cJSON_AddStringToObject(js_Device,"connectStatus",to_string((vDevicesInfo->m_isConnect)).c_str());
            cJSON_AddStringToObject(js_Device,"errorCode",to_string((vDevicesInfo->m_ErrorCode)).c_str());
            cJSON_AddStringToObject(js_Device,"name",(vDevicesInfo->m_name).c_str());
            cJSON_AddStringToObject(js_Device,"deviceId",to_string((vDevicesInfo->m_nDeviceID)).c_str());
            cJSON_AddStringToObject(js_Device,"ip",(vDevicesInfo->m_sIp).c_str());
            cJSON_AddStringToObject(js_Device,"port",to_string((vDevicesInfo)->m_port).c_str());


            map<string,st_ModbusGroupInfo>::iterator mGroupsInfo = vDevicesInfo->m_mGroupInfo.begin();
            cJSON*js_GroupArray = nullptr;
            cJSON_AddItemToObject(js_Device,"group",js_GroupArray = cJSON_CreateArray());
            for(; mGroupsInfo!=vDevicesInfo->m_mGroupInfo.end(); mGroupsInfo++)
            {
                st_ModbusGroupInfo st_MGroupInfo = mGroupsInfo->second;
                cJSON*js_GroupInfo = nullptr;
                cJSON_AddItemToArray(js_GroupArray, js_GroupInfo = cJSON_CreateObject());

                cJSON_AddStringToObject(js_GroupInfo,"groupId",(st_MGroupInfo.strGroupID).c_str());
                cJSON_AddStringToObject(js_GroupInfo,"isSelect",(st_MGroupInfo.isSelect).c_str());
                cJSON_AddStringToObject(js_GroupInfo,"number",to_string(st_MGroupInfo.nNb).c_str());
                cJSON_AddStringToObject(js_GroupInfo,"funCode",to_string(st_MGroupInfo.nFunCode).c_str());


                map<string,st_VarInfo>::iterator mVarsInfo = st_MGroupInfo.mSignalInfo.begin();
                cJSON*js_VarArray = nullptr;
                cJSON_AddItemToObject(js_GroupInfo,"signal",js_VarArray = cJSON_CreateArray());
                for(; mVarsInfo != st_MGroupInfo.mSignalInfo.end(); mVarsInfo++)
                {
                    st_VarInfo st_varInfo = mVarsInfo->second;
                    cJSON*js_VarInfo = nullptr;
                    cJSON_AddItemToArray(js_VarArray, js_VarInfo = cJSON_CreateObject());

                    cJSON_AddStringToObject(js_VarInfo,"addr",to_string(st_varInfo.nAddr).c_str());
                    cJSON_AddStringToObject(js_VarInfo,"varName",(st_varInfo.strName).c_str());
                    cJSON_AddStringToObject(js_VarInfo,"value",to_string(st_varInfo.nValue).c_str());
                }

            }
        }

        string strRet = cJSON_Print(root);
//        center_trace(center_log_debug, "xmlrpc call read modbus data :[%s]",strRet.c_str());

        if(root)
        {
            cJSON_Delete(root);
        }

        return xmlrpc_build_value(envP, "s", strRet.c_str());
    }

    xmlrpc_value * xmlrpc_GetModbusClientIsConnection(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo)
    {
        int nRbtID = 0;
        int nClientType = 0;
        char* strName = nullptr;

        xmlrpc_int nRet = 0;

        HRC_NOUSE_2PARAMTER(serInfo,channelInfo);

        xmlrpc_decompose_value(envP, paramArray, "(iis)", &nRbtID, &nClientType,&strName);

        if (envP->fault_occurred)
        {
            center_trace(center_log_error, "xmlrpc call error %d %s",
                envP->fault_code,envP->fault_string);
            nRet = REC_ParamError;
            return xmlrpc_build_value(envP, "i", nRet);
        }

        if(nullptr == strName)
        {
            nRet = REC_DeviceNotExist;
            return xmlrpc_build_value(envP, "i", nRet);
        }

        int nIsConnect = 0;
        int nErrorCode = 0;
        nRet = HRC_GET_MDB()->getDeviceIsConnectByName(strName,nIsConnect,nErrorCode);
        if(nRet)
        {
            center_trace(center_log_error, "xmlrpc modbus client no exist![name : %s] [ret : %d]",
                strName,nRet);

            return xmlrpc_build_value(envP, "i", nRet);
        }

        cJSON *js_modbusInfo;
        cJSON *root = cJSON_CreateObject();
        cJSON_AddItemToObject(root,"modbus", js_modbusInfo = cJSON_CreateObject());


        cJSON_AddStringToObject(js_modbusInfo,"connectStatus",to_string(nIsConnect).c_str());
        cJSON_AddStringToObject(js_modbusInfo,"errorCode",to_string(nErrorCode).c_str());

        free(strName);

        string strRet = cJSON_Print(root);
        if(root)
        {
            cJSON_Delete(root);
        }

        return xmlrpc_build_value(envP, "s", strRet.c_str());
    }

}
