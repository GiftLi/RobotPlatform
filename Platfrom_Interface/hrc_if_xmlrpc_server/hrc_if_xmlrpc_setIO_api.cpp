
#include "hrc_if_xmlrpc_api.h"
#include "../public_files/global_error/hrc_public_gerrorcode.h"
#include "HRC_Public/hrc_public_factory/hrc_public_factory.h"


namespace xmlrpcServer
{
    /* 设置通用DO */
    xmlrpc_value * xmlrpc_SetBoxDO(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo)
    {
        HRC_NOUSE_2PARAMTER(serInfo,channelInfo);

        center_trace(center_log_debug, "recv xmlrpc SetCurrencyDOState ");
        xmlrpc_int nRbtID = 0;
        xmlrpc_int nClientType = 0;
        xmlrpc_int np1 = 0;
        xmlrpc_int np2 = 0;
        xmlrpc_decompose_value(envP, paramArray, "(iiii)", &nRbtID, &nClientType, &np1, &np2);

        if((np1<0 || np1>7) || (np2<0 || np2>1))
        {
            return xmlrpc_build_value(envP, "i", REC_ParamError);
        }

        if (envP->fault_occurred)
        {
            center_trace(center_log_error, "xmlrpc call error %d %s",
                envP->fault_code,envP->fault_string);
            return nullptr;
        }

        int nParam[2] = {np1,np2};
        xmlrpc_int nRet = HRC_GET_MC()->ExecutiveSysboardCtrlCmd(nRbtID, enCmdSystemBoard_setSpeSerialDO,2,nParam);
        return xmlrpc_build_value(envP, "i", nRet);
      
    }

    /* 设置可配置DO */
    xmlrpc_value * xmlrpc_SetBoxCO(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo)
    {
        HRC_NOUSE_2PARAMTER(serInfo,channelInfo);

        center_trace(center_log_debug, "recv xmlrpc SetConfigDOState ");
        xmlrpc_int nRbtID = 0;
        xmlrpc_int nClientType = 0;
        xmlrpc_int np1 = 0;
        xmlrpc_int np2 = 0;
        xmlrpc_decompose_value(envP, paramArray, "(iiii)", &nRbtID, &nClientType, &np1, &np2);
        if (envP->fault_occurred)
        {
            center_trace(center_log_error, "xmlrpc call error %d %s",
                envP->fault_code,envP->fault_string);
            return nullptr;
        }
        int nParam[2] = {np1,np2};
        xmlrpc_int nRet = HRC_GET_MC()->ExecutiveSysboardCtrlCmd(nRbtID, enCmdSystemBoard_setSpeConfigDO,2,nParam);

        return xmlrpc_build_value(envP, "i", nRet);
    }   

    /* 设置末端IO */
    xmlrpc_value * xmlrpc_SetEndDO(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo)
    {
        HRC_NOUSE_2PARAMTER(serInfo,channelInfo);
        DoRobotParameSetDOState(CRobotMgr::Instance()->Set_SetModbusEndDO);
    }

    /*set shutdown time*/
    xmlrpc_value * xmlrpc_SetShutdownTime(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo)
    {
        HRC_NOUSE_2PARAMTER(serInfo,channelInfo);

        center_trace(center_log_debug, "recv xmlrpc SetShutdownTime ");
        xmlrpc_int nRbtID = 0;
        xmlrpc_int nClientType = 0;
        xmlrpc_int np1 = 0;
        xmlrpc_decompose_value(envP, paramArray, "(iii)", &nRbtID, &nClientType, &np1);
        if (envP->fault_occurred)
        {
            center_trace(center_log_error, "xmlrpc call error %d %s",
                envP->fault_code,envP->fault_string);
            return nullptr;
        }

        int nParam[1] = {np1};
        xmlrpc_int nRet = HRC_GET_MC()->ExecutiveSysboardCtrlCmd(nRbtID, enCmdSystemBoard_setShutdownTime,1,nParam);
        return xmlrpc_build_value(envP, "i", nRet);

    }


    /* 设置模拟量模式 */
    xmlrpc_value * xmlrpc_SetBoxAOMode(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo)
    {
        HRC_NOUSE_2PARAMTER(serInfo,channelInfo);

        center_trace(center_log_debug, "recv xmlrpc SetAnalogMode ");
        xmlrpc_int nRbtID = 0;
        xmlrpc_int nClientType = 0;
        xmlrpc_int nIndex = 0;
        xmlrpc_int nBit = 0;
        xmlrpc_int nRet = 0;
        xmlrpc_decompose_value(envP, paramArray, "(iiii)", &nRbtID, &nClientType, &nIndex, &nBit);
        if (envP->fault_occurred)
        {
            center_trace(center_log_error, "xmlrpc call error %d %s",
                envP->fault_code,envP->fault_string);
            return nullptr;
        }

        int nParam[1] = {nBit};
        if(nIndex == 0)
            nRet = HRC_GET_MC()->ExecutiveSysboardCtrlCmd(nRbtID, enCmdSystemBoard_setCh1AnalogOutMode,1,nParam);
        else if(nIndex == 1)
            nRet = HRC_GET_MC()->ExecutiveSysboardCtrlCmd(nRbtID, enCmdSystemBoard_setCh2AnalogOutMode,1,nParam);
        else 
            return xmlrpc_build_value(envP, "i", REC_ParamError);

         return xmlrpc_build_value(envP, "i", nRet);

    }

    /* 设置模拟量值 */
    xmlrpc_value * xmlrpc_SetBoxAO(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo)
    {

        xmlrpc_int nRet;
        xmlrpc_int nRbtID = 0;
        xmlrpc_int nClientID = 0;
        int nIndex = 0;
        int nPattern = 0;
        double dState = 0.0;
        char * strState = nullptr;

        
        HRC_NOUSE_2PARAMTER(serInfo,channelInfo);
        xmlrpc_decompose_value(envP, paramArray, "(iiisi)", &nRbtID, &nClientID,
            &nIndex, &strState, &nPattern);
        
        if (envP->fault_occurred)
        {
            center_trace(center_log_error, "xmlrpc call error %d %s",
                envP->fault_code,envP->fault_string);
            return nullptr;
        }

        if(strState)
        {
            dState = atof(strState);
            free(strState);
        }

        center_trace(center_log_debug, "xmlrpc_SetAnalogOutput %d %f %d",
                        nIndex,dState,nPattern);


        int nParam[1] = {nPattern};
        double pDoubleParam[1] = {dState};
        if(nIndex==0)
        {
            nRet = HRC_GET_MC()->ExecutiveSysboardCtrlCmd(0, enCmdSystemBoard_setCh1AnalogOutMode,1,nParam);
            if(nRet == REC_Successed)
                nRet = HRC_GET_MC()->ExecutiveSysboardCtrlCmd(0, enCmdSystemBoard_setCh1AnalogOutValue,0,                                                            
                                                            nullptr,1,pDoubleParam);
        }
        else if(nIndex==1)
        {
            nRet = HRC_GET_MC()->ExecutiveSysboardCtrlCmd(0, enCmdSystemBoard_setCh2AnalogOutMode,1,nParam);
            if(nRet == REC_Successed)
                nRet = HRC_GET_MC()->ExecutiveSysboardCtrlCmd(0, enCmdSystemBoard_setCh2AnalogOutValue,0,
                                                            nullptr,1,pDoubleParam);
        }
        else 
            return xmlrpc_build_value(envP, "i", REC_FormatError);

        return xmlrpc_build_value(envP, "i", nRet);
    }        



}
