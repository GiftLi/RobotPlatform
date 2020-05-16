#include "hrc_if_server_api.h"
#include "../public_files/global_error/hrc_public_gerrorcode.h"
#include "HRC_StatusMachine/hrc_status_api.h"
#include "HRC_Public/hrc_public_func.h"


namespace HRC_If_Server_Api
{
    int IF_Electrify(vector<string>& vcRequest, string& strResponse)
    {
        if (vcRequest.size() != 2)
        {
            return REC_FormatError;
        }
    
        int nClientType = stoi(vcRequest[vcRequest.size() -1]);
        int nRobotId = 0;
        int nRet = HMRC_Status_Electrify(nRobotId,nClientType);
        return _GeneralRespones(vcRequest[0], nRet, strResponse);
    }

    int IF_GrpPowerOff(vector<string>& vcRequest, string& strResponse)
    {
        if (vcRequest.size() != 3)
        {
            return REC_FormatError;
        }
        
        if(!CBaseFunc::IsNumber(vcRequest[1]))
            return REC_ParamError;

        int nRbtID = atoi(vcRequest[1].c_str());
        int nClientType = stoi(vcRequest[vcRequest.size() -1]);  

        int nActRobotCnt=HMRC_Status_ReadActRobotCnt();
        if((nRbtID < 0) || ( nRbtID >= nActRobotCnt ))
            return REC_RobotNotExist;

        int nRet = HMRC_Status_PowerOff(nRbtID, nClientType);
        return _GeneralRespones(vcRequest[0], nRet, strResponse);
    }
    
    int IF_GrpPowerOn(vector<string>& vcRequest, string& strResponse)
    {
        if (vcRequest.size() != 3)
        {
            return REC_FormatError;
        }
        if(!CBaseFunc::IsNumber(vcRequest[1]))
            return REC_ParamError;
        int nRbtID = atoi(vcRequest[1].c_str());
        int nClientType = stoi(vcRequest[vcRequest.size() -1]);
        int nActRobotCnt=HMRC_Status_ReadActRobotCnt();
        if((nRbtID < 0) || ( nRbtID >= nActRobotCnt ))
            return REC_RobotNotExist;
        int nRet = HMRC_Status_PowerOn(nRbtID, nClientType);
        return _GeneralRespones(vcRequest[0], nRet, strResponse);
    }
    int IF_GrpReset(vector<string>& vcRequest, string& strResponse)
    {
        if (vcRequest.size() != 3)
        {
            return REC_FormatError;
        }
        if(!CBaseFunc::IsNumber(vcRequest[1]))
            return REC_ParamError;
        int nRbtID = atoi(vcRequest[1].c_str());
        int nClientType = stoi(vcRequest[vcRequest.size() -1]);
        int nActRobotCnt=HMRC_Status_ReadActRobotCnt();
        if((nRbtID < 0) || ( nRbtID >= nActRobotCnt ))
            return REC_RobotNotExist;
        int nRet = HMRC_Status_Reset(nRbtID, nClientType);
        return _GeneralRespones(vcRequest[0], nRet, strResponse);
    }
    int IF_ResetEStop(vector<string>& vcRequest, string& strResponse)
    {
        if (vcRequest.size() != 3)
        {
            return REC_FormatError;
        }
        if(!CBaseFunc::IsNumber(vcRequest[1]))
            return REC_ParamError;
        int nRbtID = atoi(vcRequest[1].c_str());
        int nClientType = stoi(vcRequest[vcRequest.size() -1]);
        int nActRobotCnt=HMRC_Status_ReadActRobotCnt();
        if((nRbtID < 0) || ( nRbtID >= nActRobotCnt ))
            return REC_RobotNotExist;
        int nRet = HMRC_Status_ResetEStop(nRbtID, nClientType);
        return _GeneralRespones(vcRequest[0], nRet, strResponse);
    }
    int IF_ResetESGuard(vector<string>& vcRequest, string& strResponse)
    {
        if (vcRequest.size() != 3)
        {
            return REC_FormatError;
        }
        if(!CBaseFunc::IsNumber(vcRequest[1]))
            return REC_ParamError;
        int nRbtID = atoi(vcRequest[1].c_str());
        int nClientType = stoi(vcRequest[vcRequest.size() -1]);
        int nActRobotCnt=HMRC_Status_ReadActRobotCnt();
        if((nRbtID < 0) || ( nRbtID >= nActRobotCnt ))
            return REC_RobotNotExist;
        int nRet = HMRC_Status_ResetSGuard(nRbtID, nClientType);
        return _GeneralRespones(vcRequest[0], nRet, strResponse);
    }
    int IF_GrpStopMoving(vector<string>& vcRequest, string& strResponse)
    {
        if (vcRequest.size() != 3)
        {
            return REC_FormatError;
        }
        if(!CBaseFunc::IsNumber(vcRequest[1]))
            return REC_ParamError;
        int nRbtID = atoi(vcRequest[1].c_str());
        int nClientType = stoi(vcRequest[vcRequest.size() -1]);
        int nActRobotCnt=HMRC_Status_ReadActRobotCnt();
        if((nRbtID < 0) || ( nRbtID >= nActRobotCnt ))
            return REC_RobotNotExist;
        int nRet = HMRC_Status_StopMoving(nRbtID, nClientType);
        return _GeneralRespones(vcRequest[0], nRet, strResponse);
    }
    
    int IF_GrpStop(vector<string>& vcRequest, string& strResponse)
    {
        if (vcRequest.size() != 3)
        {
            return REC_FormatError;
        }
        if(!CBaseFunc::IsNumber(vcRequest[1]))
            return REC_ParamError;
        int nRbtID = atoi(vcRequest[1].c_str());
        int nActRobotCnt=HMRC_Status_ReadActRobotCnt();
        if((nRbtID < 0) || ( nRbtID >= nActRobotCnt ))
            return REC_ParamError;
        int nRet = HMRC_Status_Stop(nRbtID, 0);
        return _GeneralRespones(vcRequest[0], nRet, strResponse);
    }

    
    int IF_StartAssistiveMode(vector<string>& vcRequest, string& strResponse)
    {
        if (vcRequest.size() != 3)
        {
            return REC_FormatError;
        }
        if(!CBaseFunc::IsNumber(vcRequest[1]))
            return REC_ParamError;
        int nRbtID = atoi(vcRequest[1].c_str());
        int nClientType = stoi(vcRequest[vcRequest.size() -1]);
        int nActRobotCnt=HMRC_Status_ReadActRobotCnt();
        if((nRbtID < 0) || ( nRbtID >= nActRobotCnt ))
            return REC_ParamError;
        int nRet = HMRC_Status_StartAssistiveMode(nRbtID, nClientType);

        return _GeneralRespones(vcRequest[0], nRet, strResponse);
    }

    int IF_CloseAssistiveMode(vector<string>& vcRequest, string& strResponse)
    {
        if (vcRequest.size() != 3)
        {
            return REC_FormatError;
        }
        if(!CBaseFunc::IsNumber(vcRequest[1]))
            return REC_ParamError;
        int nRbtID = atoi(vcRequest[1].c_str());
        int nClientType = stoi(vcRequest[vcRequest.size() -1]);
        int nActRobotCnt=HMRC_Status_ReadActRobotCnt();
        if((nRbtID < 0) || ( nRbtID >= nActRobotCnt ))
            return REC_ParamError;
        int nRet = HMRC_Status_CloseAssistiveMode(nRbtID, nClientType);

        return _GeneralRespones(vcRequest[0], nRet, strResponse);
    }

    int IF_SetOverride(vector<string>& vcRequest, string& strResponse)
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
        int nRbtID = atoi(vcRequest.at(1).c_str());
        double dOverride = atof(vcRequest.at(2).c_str());
        int nClientType = stoi(vcRequest[vcRequest.size() -1]);
        int nActRobotCnt=HMRC_Status_ReadActRobotCnt();
        if((nRbtID < 0) || ( nRbtID >= nActRobotCnt ))
            return REC_ParamError;
        int nRet = HMRC_Status_SetOverride(nRbtID, dOverride, nClientType);
        return _GeneralRespones(vcRequest[0], nRet, strResponse);
    }

    int IF_SetSimulation(vector<string>& vcRequest, string& strResponse)
    {
        if (vcRequest.size() != 3)
        {
            return REC_FormatError;
        }
        if(!CBaseFunc::IsNumber(vcRequest[1]))
            return REC_ParamError;
        int nSimulation = atoi(vcRequest[1].c_str());
        int nClientType = stoi(vcRequest[vcRequest.size() -1]);
        int nRet = HMRC_Status_SetSimulation(nSimulation, nClientType);
        strResponse.clear();
        strResponse.append(vcRequest[0]);
        strResponse.append(IFSplit);
        if (nRet != REC_Successed)
        {
            strResponse.append(OPTFAIL);
            strResponse.append(IFSplit);
            strResponse.append(CBaseFunc::i_str(nRet));
        }
        else
        {
            strResponse.append(OPTOK);
        }
        strResponse.append(IFEnd);
        return nRet;
    }



    int IF_Blackout(vector<string>& vcRequest, string& strResponse)
    {
        if (vcRequest.size() != 2)
        {
            return REC_FormatError;
        }
    
        int nClientType = stoi(vcRequest[vcRequest.size() -1]);
        int nRobotId = 0;
        int nRet = HMRC_Status_Blackout(nRobotId,nClientType);
        return _GeneralRespones(vcRequest[0], nRet, strResponse);
    }

    int IF_StartMaster(vector<string>& vcRequest, string& strResponse)
    {
        if (vcRequest.size() != 2)
        {
            return REC_FormatError;
        }
    
        int nClientType = stoi(vcRequest[vcRequest.size() -1]);
        int nCurrentStatu = 0;
        int nRobotId = 0;
        int nRet = HMRC_Status_StartMaster(nRobotId,nClientType);
        
        return _GeneralRespones(vcRequest[0], nRet, strResponse);
    }
    
    int IF_CloseMaster(vector<string>& vcRequest, string& strResponse)
    {
        if (vcRequest.size() != 2)
        {
            return REC_FormatError;
        }
    
        int nClientType = stoi(vcRequest[vcRequest.size() -1]);
        int nRobotId = 0;
        int nRet = HMRC_Status_CloseMaster(nRobotId,nClientType);
        return _GeneralRespones(vcRequest[0], nRet, strResponse);
    }

    int IF_GrpPause(vector<string>& vcRequest, string& strResponse)
    {
        if (vcRequest.size() != 3)
        {
            return REC_FormatError;
        }
    
        int nClientType = stoi(vcRequest[vcRequest.size() -1]);
        int nRbtID = 0;
        int nActRobotCnt=HMRC_Status_ReadActRobotCnt();
        if((nRbtID < 0) || ( nRbtID >= nActRobotCnt ))
            return REC_RobotNotExist;
        int nRet = HMRC_Status_GrpInterrupt(nRbtID,nClientType);
        return _GeneralRespones(vcRequest[0], nRet, strResponse);
    }
    int IF_GrpContinue(vector<string>& vcRequest, string& strResponse)
    {
        if (vcRequest.size() != 3)
        {
            return REC_FormatError;
        }
    
        int nClientType = stoi(vcRequest[vcRequest.size() -1]);
        int nRbtID = 0;
        int nActRobotCnt=HMRC_Status_ReadActRobotCnt();
        if((nRbtID < 0) || ( nRbtID >= nActRobotCnt ))
            return REC_RobotNotExist;
        int nRet = HMRC_Status_GrpContinue(nRbtID,nClientType);
        return _GeneralRespones(vcRequest[0], nRet, strResponse);
    }


    int IF_GrpSetBreakMode(vector<string>& vcRequest, string& strResponse)
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
        int nRbtID = atoi(vcRequest[1].c_str());
        int nAxid = atoi(vcRequest[2].c_str());
        int nMode = atoi(vcRequest[3].c_str());
        
        int nClientType = stoi(vcRequest[vcRequest.size() -1]);

        int nActRobotCnt=HMRC_Status_ReadActRobotCnt();
        if((nRbtID < 0) || ( nRbtID >= nActRobotCnt ))
            return REC_RobotNotExist;

        int nRet = HRMC_Status_SetBreakMode(nRbtID,nAxid,nMode,nClientType);
        return _GeneralRespones(vcRequest[0], nRet, strResponse);
    }

    int IF_GrpSetSetHomeStep2(vector<string>& vcRequest, string& strResponse)
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
        int nRbtID = atoi(vcRequest[1].c_str());
        int nAxid = atoi(vcRequest[2].c_str());
        
        int nClientType = stoi(vcRequest[vcRequest.size() -1]);
        int nActRobotCnt=HMRC_Status_ReadActRobotCnt();
        if((nRbtID < 0) || ( nRbtID >= nActRobotCnt ))
            return REC_RobotNotExist;
        int nRet = HRMC_Status_SetHomeStep2(nRbtID, nAxid, nClientType);
        return _GeneralRespones(vcRequest[0], nRet, strResponse);
    }
    
    int IF_GrpSetHomePositon(vector<string>& vcRequest, string& strResponse)
    {
        if (vcRequest.size() != 9)
        {
            return REC_FormatError;
        }
        for(int i = 1; i < 7; ++i)
        {
            if(!CBaseFunc::IsNumber(vcRequest[i]))
                return REC_ParamError;
        }
        int nRbtID = atoi(vcRequest[1].c_str());

        int a[6] = {0};
        a[0] = atoi(vcRequest[2].c_str());
        a[1] = atoi(vcRequest[3].c_str());
        a[2] = atoi(vcRequest[4].c_str());
        a[3] = atoi(vcRequest[5].c_str());
        a[4] = atoi(vcRequest[6].c_str());
        a[5] = atoi(vcRequest[7].c_str());
        
        int nClientType = stoi(vcRequest[vcRequest.size() -1]);

        int nActRobotCnt=HMRC_Status_ReadActRobotCnt();
        if((nRbtID < 0) || ( nRbtID >= nActRobotCnt ))
            return REC_RobotNotExist;
        int nRet = HRMC_Status_SetHomePositon(nRbtID,a, nClientType);
        return _GeneralRespones(vcRequest[0], nRet, strResponse);
    }
    int IF_SetSlaveType(vector<string>& vcRequest, string& strResponse)
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
        int nRbtID = atoi(vcRequest[1].c_str());

        int nSlaveType = atoi(vcRequest[2].c_str());

        int nClientType = stoi(vcRequest[vcRequest.size() -1]);

        int nActRobotCnt=HMRC_Status_ReadActRobotCnt();
        if((nRbtID < 0) || ( nRbtID >= nActRobotCnt ))
            return REC_RobotNotExist;

        int nRet = HRMC_Status_SetSlaveType(nRbtID, nSlaveType, nClientType);
        return _GeneralRespones(vcRequest[0], nRet, strResponse);
    }
    int IF_SetEndIOType(vector<string>& vcRequest, string& strResponse)
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
        int nRbtID = atoi(vcRequest[1].c_str());

        int nEndIOType = atoi(vcRequest[2].c_str());

        int nClientType = stoi(vcRequest[vcRequest.size() -1]);

        int nActRobotCnt=HMRC_Status_ReadActRobotCnt();
        if((nRbtID < 0) || ( nRbtID >= nActRobotCnt ))
            return REC_RobotNotExist;

        int nRet = HRMC_Status_SetEndIOType(nRbtID, nEndIOType, nClientType);
        return _GeneralRespones(vcRequest[0], nRet, strResponse);
    }
    int IF_SetEncodeType(vector<string>& vcRequest, string& strResponse)
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
        int nRbtID = atoi(vcRequest[1].c_str());

        int nEncodeType = atoi(vcRequest[2].c_str());

        int nClientType = stoi(vcRequest[vcRequest.size() -1]);

        int nActRobotCnt=HMRC_Status_ReadActRobotCnt();
        if((nRbtID < 0) || ( nRbtID >= nActRobotCnt ))
            return REC_RobotNotExist;

        int nRet = HRMC_Status_SetEncodeType(nRbtID, nEncodeType, nClientType);
        return _GeneralRespones(vcRequest[0], nRet, strResponse);
    }
    int IF_SetEncodeRatio(vector<string>& vcRequest, string& strResponse)
    {
        if (vcRequest.size() != 9)
        {
            return REC_FormatError;
        }
        for(int i = 1; i < 8; ++i)
        {
            if(!CBaseFunc::IsNumber(vcRequest[i]))
                return REC_ParamError;
        }
        int nRbtID = atoi(vcRequest[1].c_str());

        int a[6] = {0};
        a[0] = atoi(vcRequest[2].c_str());
        a[1] = atoi(vcRequest[3].c_str());
        a[2] = atoi(vcRequest[4].c_str());
        a[3] = atoi(vcRequest[5].c_str());
        a[4] = atoi(vcRequest[6].c_str());
        a[5] = atoi(vcRequest[7].c_str());

        int nClientType = stoi(vcRequest[vcRequest.size() -1]);

        int nActRobotCnt=HMRC_Status_ReadActRobotCnt();
        if((nRbtID < 0) || ( nRbtID >= nActRobotCnt ))
            return REC_RobotNotExist;

        int nRet = HRMC_Status_SetEncodeRatio(nRbtID,a, nClientType);
        return _GeneralRespones(vcRequest[0], nRet, strResponse);
    }
    int IF_SetGearRatio(vector<string>& vcRequest, string& strResponse)
    {
        if (vcRequest.size() != 9)
        {
            return REC_FormatError;
        }
        for(int i = 1; i < 8; ++i)
        {
            if(!CBaseFunc::IsNumber(vcRequest[i]))
                return REC_ParamError;
        }
        int nRbtID = atoi(vcRequest[1].c_str());

        int a[6] = {0};
        a[0] = atoi(vcRequest[2].c_str());
        a[1] = atoi(vcRequest[3].c_str());
        a[2] = atoi(vcRequest[4].c_str());
        a[3] = atoi(vcRequest[5].c_str());
        a[4] = atoi(vcRequest[6].c_str());
        a[5] = atoi(vcRequest[7].c_str());

        int nClientType = stoi(vcRequest[vcRequest.size() -1]);

        int nActRobotCnt=HMRC_Status_ReadActRobotCnt();
        if((nRbtID < 0) || ( nRbtID >= nActRobotCnt ))
            return REC_RobotNotExist;

        int nRet = HRMC_Status_SetGearRatio(nRbtID,a, nClientType);
        return _GeneralRespones(vcRequest[0], nRet, strResponse);
    }
    
}
