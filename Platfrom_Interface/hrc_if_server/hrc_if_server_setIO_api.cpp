#include "hrc_if_server_api.h"


#include "../public_files/global_error/hrc_public_gerrorcode.h"
#include "HRC_StatusMachine/hrc_status_api.h"
#include "HRC_RobotManage/hrc_robot_mgr.h"
#include "HRC_Public/hrc_public_func.h"
#include "HRC_Public/hrc_public_factory/hrc_public_factory.h"

namespace HRC_If_Server_Api
{
    /* 设置通用DO */
    int IF_SetBoxDO(vector<string>& vcRequest, string& strResponse)
    {
        int nRet = REC_Successed;
        if (vcRequest.size() != 4)
        {
            return REC_FormatError;
        }
        for(int i = 1; i < 3; ++i)
        {
            if(!CBaseFunc::IsNumber(vcRequest[i]))
                return REC_ParamError;
        }
        int nBit = atoi(vcRequest.at(1).c_str());
        int nVal = atoi(vcRequest.at(2).c_str());
        //int nClientType = stoi(vcRequest[vcRequest.size() -1]);
        center_trace(center_log_debug, "\n[cmd]SetBoxDO: %d %d\n",nBit,nVal);

        if((nBit<0 || nBit>7) || (nVal<0 || nVal>1))
        {
            return _GeneralRespones(vcRequest[0], REC_ParamError, strResponse);
        }

        int nParam[2] = { nBit,nVal};
        nRet = HRC_GET_MC()->ExecutiveSysboardCtrlCmd(0, enCmdSystemBoard_setSpeSerialDO,2,nParam);

        center_trace(center_log_debug, "\n[cmd]SetBoxDO return: %d\n",nRet);
        return _GeneralRespones(vcRequest[0], nRet, strResponse);
    }

    /* 设置可配置DO */
    int IF_SetBoxCO(vector<string>& vcRequest, string& strResponse)
    {
        if (vcRequest.size() != 4)
        {
            return REC_FormatError;
        }
        for(int i = 1; i < 3; ++i)
        {
            if(!CBaseFunc::IsNumber(vcRequest[i]))
                return REC_ParamError;
        }
        int nBit = atoi(vcRequest.at(1).c_str());
        int nVal = atoi(vcRequest.at(2).c_str());
        //int nClientType = stoi(vcRequest[vcRequest.size() -1]);

        if((nBit<0 || nBit>7) || (nVal<0 || nVal>1))
        {
            return _GeneralRespones(vcRequest[0], REC_ParamError, strResponse);
        }

        int nParam[2] = { nBit,nVal};
        int nRet =HRC_GET_MC()->ExecutiveSysboardCtrlCmd(0, enCmdSystemBoard_setSpeConfigDO,2,nParam);

        return _GeneralRespones(vcRequest[0], nRet, strResponse);
    }

    /* 设置模拟量输出 */
    int IF_SetBoxAO(vector<string>& vcRequest, string& strResponse)
    {
        if (vcRequest.size() != 5)
        {
            return REC_FormatError;
        }
        for(int i = 1; i < 4; ++i)
        {
            if(!CBaseFunc::IsNumber(vcRequest[i]))
                return REC_ParamError;
        }
        int nIndex = atoi(vcRequest.at(1).c_str());
        double dState = atof(vcRequest.at(2).c_str());
        int nPattern = atoi(vcRequest.at(3).c_str());

        if(nPattern<0 || nPattern>1)
        {
            return _GeneralRespones(vcRequest[0], REC_ParamError, strResponse);
        }
        int nRet = REC_Successed;

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
            return _GeneralRespones(vcRequest[0], REC_ParamError, strResponse);
            
        
        return _GeneralRespones(vcRequest[0], nRet, strResponse);
    }

    /* 设置模拟量输出模式 */
    int IF_SetBoxAOMode(vector<string>& vcRequest, string& strResponse)
    {
        int nRet = REC_Successed;

        if (vcRequest.size() != 4)
        {
            return REC_FormatError;
        }
        int nIndex = atoi(vcRequest.at(1).c_str());
        if (nIndex < 0 || nIndex > 1)
        {
            return REC_ParamError;
        }

        int nPattern = atoi(vcRequest.at(2).c_str());
        if (nPattern < 0 || nPattern > 1)
        {
            return REC_ParamError;
        }
        for(int i = 1; i < 3; ++i)
        {
            if(!CBaseFunc::IsNumber(vcRequest[i]))
                return REC_ParamError;
        }

        int nParam[1] = {nPattern};
        if(nIndex==0)
            nRet = HRC_GET_MC()->ExecutiveSysboardCtrlCmd(0, enCmdSystemBoard_setCh1AnalogOutMode,1,nParam);
        else if(nIndex==1)
            nRet = HRC_GET_MC()->ExecutiveSysboardCtrlCmd(0, enCmdSystemBoard_setCh2AnalogOutMode,1,nParam);
        else
            return _GeneralRespones(vcRequest[0], REC_ParamError, strResponse);
        
        return _GeneralRespones(vcRequest[0], nRet, strResponse);
    }


    /* 设置末端DO */
    int IF_SetEndDO(vector<string>& vcRequest, string& strResponse)
    {
        if (vcRequest.size() != 5)
        {
            return REC_FormatError;
        }
        for(int i = 1; i < 4; ++i)
        {
            if(!CBaseFunc::IsNumber(vcRequest[i]))
                return REC_ParamError;
        }
        int nRobotID = atoi(vcRequest.at(1).c_str());
        int nBit = atoi(vcRequest.at(2).c_str());
        int nVal = atoi(vcRequest.at(3).c_str());

        int nRet = CRobotMgr::Instance()->Set_SetModbusEndDO(nRobotID, nBit, nVal);
        return _GeneralRespones(vcRequest[0], nRet, strResponse);
    }

    /*
    int IF_SetLEDColour(vector<string>& vcRequest, string& strResponse)
    {
        if (vcRequest.size() != 4)
        {
            return REC_FormatError;
        }
        int nRbtID = atoi(vcRequest[1].c_str());
        int nLEDColour = atoi(vcRequest[2].c_str());
        int nClientType = stoi(vcRequest[vcRequest.size() -1]);
        int nRet = HMRC_Status_Set_LEDColour(nRbtID, nLEDColour);

        return _GeneralRespones(vcRequest[0], nRet, strResponse);
    }*/
    
}
