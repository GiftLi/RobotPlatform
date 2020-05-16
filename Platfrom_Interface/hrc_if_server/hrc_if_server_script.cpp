#include "hrc_if_server_api.h"

#include "../public_files/global_error/hrc_public_gerrorcode.h"
#include "HRC_StatusMachine/hrc_status_api.h"
#include "HRC_Public/hrc_public_func.h"
#include "HRC_Public/hrc_public_factory/hrc_public_factory.h"

namespace HRC_If_Server_Api
{
    /*启动脚本*/
    int IF_StartScript(vector<string>& vcRequest, string& strResponse)
    {
        if (vcRequest.size() != 3)
        {
            return REC_FormatError;
        }
        for(int i = 1; i < 2; ++i)
        {
            if(!CBaseFunc::IsNumber(vcRequest[i]))
                return REC_ParamError;
        }
        int nRbtID = atoi(vcRequest[1].c_str());
        int nClientType = stoi(vcRequest[vcRequest.size() -1]);
        
        int nActRobotCnt=HMRC_Status_ReadActRobotCnt();
        if((nRbtID < 0) || ( nRbtID >= nActRobotCnt ))
            return REC_RobotNotExist;

        int nRet = HMRC_Status_StartScript(nRbtID, nClientType);
        return _GeneralRespones(vcRequest[0], nRet, strResponse);
    }
    
    /* 停止运行脚本 */
    int IF_StopScript(vector<string>& vcRequest, string& strResponse)
    {
        if (vcRequest.size() != 3)
        {
            return REC_FormatError;
        }
        for(int i = 1; i < 2; ++i)
        {
            if(!CBaseFunc::IsNumber(vcRequest[i]))
                return REC_ParamError;
        }
        int nRbtID = atoi(vcRequest[1].c_str());
        int nClientType = stoi(vcRequest[vcRequest.size() -1]);
        
        int nActRobotCnt=HMRC_Status_ReadActRobotCnt();
        if((nRbtID < 0) || ( nRbtID >= nActRobotCnt ))
            return REC_RobotNotExist;

        int nRet = HMRC_Status_StopScript(nRbtID, nClientType);

        return _GeneralRespones(vcRequest[0], nRet, strResponse);       

    }
    
    /* 暂停 */
    int IF_PauseScript(vector<string>& vcRequest, string& strResponse)
    {
        if (vcRequest.size() != 3)
        {
            return REC_FormatError;
        }
        for(int i = 1; i < 2; ++i)
        {
            if(!CBaseFunc::IsNumber(vcRequest[i]))
                return REC_ParamError;
        }
        int nRbtID = atoi(vcRequest[1].c_str());
        int nClientType = stoi(vcRequest[vcRequest.size() -1]);
        
        int nActRobotCnt=HMRC_Status_ReadActRobotCnt();
        if((nRbtID < 0) || ( nRbtID >= nActRobotCnt ))
            return REC_RobotNotExist;

        int nRet = HMRC_Status_ScriptHold(nRbtID, nClientType);

        return _GeneralRespones(vcRequest[0], nRet, strResponse);         
    }

    
    /* 继续 */
    int IF_ContinueScript(vector<string>& vcRequest, string& strResponse)
    {
        if (vcRequest.size() != 3)
        {
            return REC_FormatError;
        }
        for(int i = 1; i < 2; ++i)
        {
            if(!CBaseFunc::IsNumber(vcRequest[i]))
                return REC_ParamError;
        }
        int nRbtID = atoi(vcRequest[1].c_str());
        int nClientType = stoi(vcRequest[vcRequest.size() -1]);
        
        int nActRobotCnt=HMRC_Status_ReadActRobotCnt();
        if((nRbtID < 0) || ( nRbtID >= nActRobotCnt ))
            return REC_RobotNotExist;

        int nRet = HMRC_Status_ScriptContinue(nRbtID, nClientType);

        return _GeneralRespones(vcRequest[0], nRet, strResponse);      
    }    

    /* 下一步 */
    int IF_NextStepScript(vector<string>& vcRequest, string& strResponse)
    {
        if (vcRequest.size() != 3)
        {
            return REC_FormatError;
        }
        for(int i = 1; i < 2; ++i)
        {
            if(!CBaseFunc::IsNumber(vcRequest[i]))
                return REC_ParamError;
        }
        int nRbtID = atoi(vcRequest[1].c_str());
        int nClientType = stoi(vcRequest[vcRequest.size() -1]);
        
        int nActRobotCnt=HMRC_Status_ReadActRobotCnt();
        if((nRbtID < 0) || ( nRbtID >= nActRobotCnt ))
            return REC_RobotNotExist;

        int nRet = HMRC_Status_ScriptStepNext(nRbtID, nClientType);

        return _GeneralRespones(vcRequest[0], nRet, strResponse);
    }

    int IF_NextBreakPoint(vector<string>& vcRequest, string& strResponse)
    {
        if (vcRequest.size() != 3)
        {
            return REC_FormatError;
        }
        for(int i = 1; i < 2; ++i)
        {
            if(!CBaseFunc::IsNumber(vcRequest[i]))
                return REC_ParamError;
        }
        int nRbtID = atoi(vcRequest[1].c_str());
        int nClientType = stoi(vcRequest[vcRequest.size() -1]);
        
        int nActRobotCnt=HMRC_Status_ReadActRobotCnt();
        if((nRbtID < 0) || ( nRbtID >= nActRobotCnt ))
            return REC_RobotNotExist;

        int nRet = HMRC_Status_ScriptNextBreakPoint(nRbtID, nClientType);

        return _GeneralRespones(vcRequest[0], nRet, strResponse);
    }


    /* 接收脚本过来的cmdid */
    int IF_RecvCmdID(vector<string>& vcRequest, string& strResponse)
    {
        if (vcRequest.size() != 5)
        {
            return REC_FormatError;
        }

        int nRbtID = atoi(vcRequest[1].c_str());
        string strCmdID = vcRequest[2];
        int nThreadID = atoi(vcRequest[3].c_str());
        int nClientType = stoi(vcRequest[vcRequest.size() -1]);

        int nRet = HMRC_Status_ScriptCmdID(nRbtID, strCmdID, nThreadID, nClientType);         
        return _GeneralRespones(vcRequest[0], nRet, strResponse);  
     }

     
    /* 接收脚本过来的变量 */
    int IF_RecvVarValue(vector<string>& vcRequest, string& strResponse)
    {
        if (vcRequest.size() != 5)
        {
            return REC_FormatError;
        }

        int nRbtID = atoi(vcRequest[1].c_str());
        string varName = vcRequest[2];
        string varValue = vcRequest[3];
        int nClientType = stoi(vcRequest[vcRequest.size() -1]);

        
        int nRet = HMRC_Status_ScriptVarValue(nRbtID,varName, varValue, nClientType);         
        return _GeneralRespones(vcRequest[0], nRet, strResponse);  
    }

    /* 接收脚本过来的终止信息 */
    int IF_RecvFinish(vector<string>& vcRequest, string& strResponse)
    {
        if (vcRequest.size() != 4)
        {
            return REC_FormatError;
        }

        int nRbtID = atoi(vcRequest[1].c_str());
        int nErrorCode = atoi(vcRequest[2].c_str());
        int nClientType = stoi(vcRequest[vcRequest.size() -1]);

        int nRet = HMRC_Status_ScriptFinish(nRbtID, nErrorCode , nClientType);
        return _GeneralRespones(vcRequest[0], nRet, strResponse);  
    }

    int IF_RecvScriptMsg(vector<string>& vcRequest, string& strResponse)
    {
        if (vcRequest.size() != 4)
        {
            return REC_FormatError;
        }

        //int nRbtID = atoi(vcRequest[1].c_str());
        string strMsg = vcRequest[2];
        //int nClientType = stoi(vcRequest[vcRequest.size() -1]);
        center_trace(center_log_info, "script message: %s", strMsg.c_str());
        return _GeneralRespones(vcRequest[0], REC_Successed, strResponse);
    }
}

