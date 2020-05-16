
#include <map>
#include <unistd.h>

#include "hrc_if_server.h"
#include "hrc_if_server_api.h"
#include "HRC_Public/hrc_public_define/hrc_public_if_cmd.h"
#include "HRC_Public/hrc_public_factory/hrc_public_factory.h"
#include "HRC_Public/hrc_public_func.h"
#include "../public_files/global_error/hrc_public_gerrorcode.h"
#include "../hrc_interface.h"

typedef int(*IFMsgHandleFunc)(vector<string>& vRequest, string& strResponse);
typedef map<string, IFMsgHandleFunc> MapIFMsgHandleFunc;

MapIFMsgHandleFunc g_mIFMsgHandleFunc;

int HRC_If_Server::InitIFMsgHandleFunc()
{
    /*setRobot*/
    g_mIFMsgHandleFunc.insert(make_pair(Protocol_GrpPowerOff, HRC_If_Server_Api::IF_GrpPowerOff));
    g_mIFMsgHandleFunc.insert(make_pair(Protocol_GrpPowerOn, HRC_If_Server_Api::IF_GrpPowerOn));
    g_mIFMsgHandleFunc.insert(make_pair(Protocol_GrpReset, HRC_If_Server_Api::IF_GrpReset));
    g_mIFMsgHandleFunc.insert(make_pair(Protocol_GrpResetEStop, HRC_If_Server_Api::IF_ResetEStop));
    g_mIFMsgHandleFunc.insert(make_pair(Protocol_GrpResetSGuard, HRC_If_Server_Api::IF_ResetESGuard));
    g_mIFMsgHandleFunc.insert(make_pair(Protocol_GrpStop, HRC_If_Server_Api::IF_GrpStop));
    g_mIFMsgHandleFunc.insert(make_pair(Protocol_SetOverride, HRC_If_Server_Api::IF_SetOverride));
    g_mIFMsgHandleFunc.insert(make_pair(Protocol_SetSimulation, HRC_If_Server_Api::IF_SetSimulation));
    g_mIFMsgHandleFunc.insert(make_pair(Protocol_Electrify, HRC_If_Server_Api::IF_Electrify));
    g_mIFMsgHandleFunc.insert(make_pair(Protocol_Blackout, HRC_If_Server_Api::IF_Blackout));
    g_mIFMsgHandleFunc.insert(make_pair(Protocol_StartMaster, HRC_If_Server_Api::IF_StartMaster));
    g_mIFMsgHandleFunc.insert(make_pair(Protocol_CloseMaster, HRC_If_Server_Api::IF_CloseMaster));
    g_mIFMsgHandleFunc.insert(make_pair(Protocol_StartAssistiveMode, HRC_If_Server_Api::IF_StartAssistiveMode));
    g_mIFMsgHandleFunc.insert(make_pair(Protocol_CloseAssistiveMode, HRC_If_Server_Api::IF_CloseAssistiveMode));
    g_mIFMsgHandleFunc.insert(make_pair(Protocol_GrpInterrupt, HRC_If_Server_Api::IF_GrpPause));
    g_mIFMsgHandleFunc.insert(make_pair(Protocol_GrpContinue, HRC_If_Server_Api::IF_GrpContinue));
    g_mIFMsgHandleFunc.insert(make_pair(Protocol_SetBreakMode, HRC_If_Server_Api::IF_GrpSetBreakMode));
    g_mIFMsgHandleFunc.insert(make_pair(Protocol_SetHomeStep2, HRC_If_Server_Api::IF_GrpSetSetHomeStep2));
    g_mIFMsgHandleFunc.insert(make_pair(Protocol_SetHomeEncode, HRC_If_Server_Api::IF_GrpSetHomePositon));

    /*moveing*/
    g_mIFMsgHandleFunc.insert(make_pair(Protocol_ShortJogJ, HRC_If_Server_Api::IF_ShortJogJ));
    g_mIFMsgHandleFunc.insert(make_pair(Protocol_ShortJogL, HRC_If_Server_Api::IF_ShortJogL));
    g_mIFMsgHandleFunc.insert(make_pair(Protocol_LongJogJ, HRC_If_Server_Api::IF_LongJogJ));
    g_mIFMsgHandleFunc.insert(make_pair(Protocol_LongJogL, HRC_If_Server_Api::IF_LongJogL));
    g_mIFMsgHandleFunc.insert(make_pair(Protocol_MoveJ, HRC_If_Server_Api::IF_MoveJ));
    g_mIFMsgHandleFunc.insert(make_pair(Protocol_MoveL, HRC_If_Server_Api::IF_MoveL));
    g_mIFMsgHandleFunc.insert(make_pair(Protocol_MoveRelJ, HRC_If_Server_Api::IF_MoveRelJ));
    g_mIFMsgHandleFunc.insert(make_pair(Protocol_MoveRelL, HRC_If_Server_Api::IF_MoveRelL));
    g_mIFMsgHandleFunc.insert(make_pair(Protocol_StartPushBlending, HRC_If_Server_Api::IF_StartPushBlending));
    g_mIFMsgHandleFunc.insert(make_pair(Protocol_PushBlendingPoint, HRC_If_Server_Api::IF_PushBlendingPoint));
    g_mIFMsgHandleFunc.insert(make_pair(Protocol_StartBlendingMotion, HRC_If_Server_Api::IF_StartBlendingMotion));
    g_mIFMsgHandleFunc.insert(make_pair(Protocol_WayPoint, HRC_If_Server_Api::IF_WayPoint));
    g_mIFMsgHandleFunc.insert(make_pair(Protocol_WayPointRel, HRC_If_Server_Api::IF_WayPointRel));


    /*setIO*/
    g_mIFMsgHandleFunc.insert(make_pair(Protocol_SetBoxDO, HRC_If_Server_Api::IF_SetBoxDO));
    g_mIFMsgHandleFunc.insert(make_pair(Protocol_SetBoxCO, HRC_If_Server_Api::IF_SetBoxCO));
    g_mIFMsgHandleFunc.insert(make_pair(Protocol_SetBoxAO, HRC_If_Server_Api::IF_SetBoxAO));
    g_mIFMsgHandleFunc.insert(make_pair(Protocol_SetBoxAOMode, HRC_If_Server_Api::IF_SetBoxAOMode));
    g_mIFMsgHandleFunc.insert(make_pair(Protocol_SetEndDO, HRC_If_Server_Api::IF_SetEndDO));

    /*set modbus*/
    g_mIFMsgHandleFunc.insert(make_pair(Protocol_SetModbusServerData, HRC_If_Server_Api::IF_SetModbusServerBit));
    g_mIFMsgHandleFunc.insert(make_pair(Protocol_ReadModbusServerData, HRC_If_Server_Api::IF_ReadModbusServerBit));


    /*readRobot*/    
    g_mIFMsgHandleFunc.insert(make_pair(Protocol_ReadCurEncode, HRC_If_Server_Api::IF_ReadCurEncode));
    g_mIFMsgHandleFunc.insert(make_pair(Protocol_ReadActualPos, HRC_If_Server_Api::IF_ReadActualPos));
    g_mIFMsgHandleFunc.insert(make_pair(Protocol_ReadRobotPosInfo, HRC_If_Server_Api::IF_ReadRobotPosInfo));
    g_mIFMsgHandleFunc.insert(make_pair(Protocol_ReadOverride, HRC_If_Server_Api::IF_ReadOverride));
    g_mIFMsgHandleFunc.insert(make_pair(Protocol_ReadRobotState, HRC_If_Server_Api::IF_ReadRobotState));
    g_mIFMsgHandleFunc.insert(make_pair(Protocol_ReadCControlMode, HRC_If_Server_Api::IF_ReadControlMode));
    g_mIFMsgHandleFunc.insert(make_pair(Protocol_ReadRobotInfoParam, HRC_If_Server_Api::IF_ReadRobotInfoParam));

    /*readIO*/
    g_mIFMsgHandleFunc.insert(make_pair(Protocol_ReadBoxDI, HRC_If_Server_Api::IF_ReadDI));
    g_mIFMsgHandleFunc.insert(make_pair(Protocol_ReadBoxCI, HRC_If_Server_Api::IF_ReadCI));
    g_mIFMsgHandleFunc.insert(make_pair(Protocol_ReadBoxDO, HRC_If_Server_Api::IF_ReadDO));
    g_mIFMsgHandleFunc.insert(make_pair(Protocol_ReadBoxCO, HRC_If_Server_Api::IF_ReadCO));
    g_mIFMsgHandleFunc.insert(make_pair(Protocol_ReadBoxC1AO, HRC_If_Server_Api::IF_ReadC1AO));
    g_mIFMsgHandleFunc.insert(make_pair(Protocol_ReadBoxC1AI, HRC_If_Server_Api::IF_ReadC1AI));
    g_mIFMsgHandleFunc.insert(make_pair(Protocol_ReadBoxC2AO, HRC_If_Server_Api::IF_ReadC2AO));
    g_mIFMsgHandleFunc.insert(make_pair(Protocol_ReadBoxC2AI, HRC_If_Server_Api::IF_ReadC2AI));
    g_mIFMsgHandleFunc.insert(make_pair(Protocol_ReadEndDI, HRC_If_Server_Api::IF_ReadEI));
    g_mIFMsgHandleFunc.insert(make_pair(Protocol_ReadEndDO, HRC_If_Server_Api::IF_ReadEO));
    g_mIFMsgHandleFunc.insert(make_pair(Protocol_ReadEndAI1, HRC_If_Server_Api::IF_ReadEAI1));
    g_mIFMsgHandleFunc.insert(make_pair(Protocol_ReadEndAI2, HRC_If_Server_Api::IF_ReadEAI2));


    /*script*/
    g_mIFMsgHandleFunc.insert(make_pair(Protocol_StartScript, HRC_If_Server_Api::IF_StartScript));
    g_mIFMsgHandleFunc.insert(make_pair(Protocol_StopScript, HRC_If_Server_Api::IF_StopScript));
    g_mIFMsgHandleFunc.insert(make_pair(Protocol_PauseScript, HRC_If_Server_Api::IF_PauseScript));
    g_mIFMsgHandleFunc.insert(make_pair(Protocol_ContinueScript, HRC_If_Server_Api::IF_ContinueScript));
    g_mIFMsgHandleFunc.insert(make_pair(Protocol_NextStepScript, HRC_If_Server_Api::IF_NextStepScript));
    g_mIFMsgHandleFunc.insert(make_pair(Protocol_NextBreakPoint, HRC_If_Server_Api::IF_NextBreakPoint));
    g_mIFMsgHandleFunc.insert(make_pair(Protocol_SendCmdID, HRC_If_Server_Api::IF_RecvCmdID));
    g_mIFMsgHandleFunc.insert(make_pair(Protocol_SendVarValue, HRC_If_Server_Api::IF_RecvVarValue));
    g_mIFMsgHandleFunc.insert(make_pair(Protocol_SendScriptFinish, HRC_If_Server_Api::IF_RecvFinish));
    g_mIFMsgHandleFunc.insert(make_pair(Protocol_SendScriptMsg, HRC_If_Server_Api::IF_RecvScriptMsg));

    /*setconfig*/
    g_mIFMsgHandleFunc.insert(make_pair(Protocol_SetTCPByName, HRC_If_Server_Api::IF_SetTCPByName));
    g_mIFMsgHandleFunc.insert(make_pair(Protocol_SetUCSByName, HRC_If_Server_Api::IF_SetUCSByName));
    g_mIFMsgHandleFunc.insert(make_pair(Protocol_ReadTCPByName, HRC_If_Server_Api::IF_ReadTCPByName));
    g_mIFMsgHandleFunc.insert(make_pair(Protocol_ReadUCSByName, HRC_If_Server_Api::IF_ReadUCSByName));
    g_mIFMsgHandleFunc.insert(make_pair(Protocol_ReadDefaultTCPName, HRC_If_Server_Api::IF_ReadDefaultTCPName));
    g_mIFMsgHandleFunc.insert(make_pair(Protocol_ReadDefaultTCPName, HRC_If_Server_Api::IF_ReadDefaultTCPName));
    g_mIFMsgHandleFunc.insert(make_pair(Protocol_Base2TCPUCS, HRC_If_Server_Api::IF_Base2TCPUCS));
    g_mIFMsgHandleFunc.insert(make_pair(Protocol_PCS2ACS, HRC_If_Server_Api::IF_PCS2ACS));
    g_mIFMsgHandleFunc.insert(make_pair(Protocol_SetToolCoordinateMotion, HRC_If_Server_Api::IF_SetToolCoordinateMotion));

    /*Set Slave Config*/
    g_mIFMsgHandleFunc.insert(make_pair(Protocol_SetSlaveType, HRC_If_Server_Api::IF_SetSlaveType));
    g_mIFMsgHandleFunc.insert(make_pair(Protocol_SetEndIOType, HRC_If_Server_Api::IF_SetEndIOType));
    g_mIFMsgHandleFunc.insert(make_pair(Protocol_SetEncodeType, HRC_If_Server_Api::IF_SetEncodeType));
    g_mIFMsgHandleFunc.insert(make_pair(Protocol_SetEncodeRatio, HRC_If_Server_Api::IF_SetEncodeRatio));
    g_mIFMsgHandleFunc.insert(make_pair(Protocol_SetGearRatio, HRC_If_Server_Api::IF_SetGearRatio));

    /*g_mIFMsgHandleFunc.insert(make_pair(Protocol_SetCollideStopPayload, HRC_If_Server_Api::IF_SetCollideStopPayload));
    g_mIFMsgHandleFunc.insert(make_pair(Protocol_SetMoveJointMotionLimits, HRC_If_Server_Api::IF_SetMoveJointMotionLimits));
    g_mIFMsgHandleFunc.insert(make_pair(Protocol_SetMovePcsMotionLimits, HRC_If_Server_Api::IF_SetMovePcsMotionLimits));
    g_mIFMsgHandleFunc.insert(make_pair(Protocol_SetStopJointMotionLimits, HRC_If_Server_Api::IF_SetStopJointMotionLimits));
    g_mIFMsgHandleFunc.insert(make_pair(Protocol_SetStopPcsMotionLimits, HRC_If_Server_Api::IF_SetStopPcsMotionLimits));
    g_mIFMsgHandleFunc.insert(make_pair(Protocol_SetBaseMountingAngle, HRC_If_Server_Api::IF_SetBaseMountingAngle));
    g_mIFMsgHandleFunc.insert(make_pair(Protocol_SetToolCoordinateMotion, HRC_If_Server_Api::IF_SetToolCoordinateMotion));
    g_mIFMsgHandleFunc.insert(make_pair(Protocol_SetCollisionStopMode, HRC_If_Server_Api::IF_SetCollisionStopMode));
    g_mIFMsgHandleFunc.insert(make_pair(Protocol_SetCollisionMomentum, HRC_If_Server_Api::IF_SetCollisionMomentumThresholds));
    */
    // 暂时用不到的
    // g_mIFMsgHandleFunc.insert(make_pair(Protocol_ReadAnalogInput, HRC_If_Server_Api::IF_ReadAnalogInput));
    // g_mIFMsgHandleFunc.insert(make_pair(Protcol_SetLEDColour, HRC_If_Server_Api::IF_SetLEDColour));
    // g_mIFMsgHandleFunc.insert(make_pair(Protcol_ReadInIOState, HRC_If_Server_Api::IF_ReadInIOState));
    // g_mIFMsgHandleFunc.insert(make_pair(Protcol_ReadControlInIOState, HRC_If_Server_Api::IF_ReadControlInIOState));
    // g_mIFMsgHandleFunc.insert(make_pair(Protcol_ReadOutIOState, HRC_If_Server_Api::IF_ReadOutIOState));
    // g_mIFMsgHandleFunc.insert(make_pair(Protcol_ReadSerialAnalog, HRC_If_Server_Api::IF_ReadSerialAnalog));
    // g_mIFMsgHandleFunc.insert(make_pair(Protcol_ElfinHomeStep2, HRC_If_Server_Api::IF_ElfinHomeStep2));
    // g_mIFMsgHandleFunc.insert(make_pair(Protocol_EncoderSetHomeEndatPos, HRC_If_Server_Api::IF_EncoderSetHomeEndatPos));

    return 0;
}


int HRC_If_Server::OnRecvIF(int info_index,int client_fd,  char* pBuf, int nLen)
{
    // if 接口监听两个端口
    // 第0个是 10003，给if客户端使用，
    // 第1个是 1789，给脚本使用。
      
    EN_ClientType enClientType = en_IF_Client;
    if(info_index == 0){
        //center_trace(center_log_debug, "recv cmd from IF: %s", pBuf);
        enClientType = en_IF_Client;
    }
    else if(info_index == 1) {
        //center_trace(center_log_debug, "recv cmd from Script: %s", pBuf);
        enClientType = en_Script_client;
    }
    else{
        // 目前只监听了两个端口，代码不会走到这里，
        // 如果后续添加其他端口，在这里添加打印信息。
        center_trace(center_log_error, "recv cmd from error client: %s", pBuf);
        return -1;
    }    
    
    if ((NULL == pBuf) || (0 == nLen))
    {
        return 0;
    }
    string strHandle(pBuf, nLen);
    string m_strRecv="";
    string strRespone = "";

    m_strRecv.clear();
    m_strRecv.append(strHandle);

    int nPosFind = m_strRecv.rfind(IFEnd);
    if (nPosFind == string::npos)
    {
        center_trace(center_log_error, "had no IFEND while OnRecvIF %s", pBuf);

        strRespone.append("errorcmd");
        strRespone.append(IFSplit);
        strRespone.append(OPTFAIL);
        strRespone.append(IFSplit);
        strRespone.append(CBaseFunc::i_str(REC_ParamError));
        strRespone.append(IFEnd);
        HRC_Interface::ResponseIFMsg(info_index,  client_fd, strRespone.c_str(),strRespone.size());

        return 0;
    }
    nPosFind += 2;
    strHandle = m_strRecv.substr(0,nPosFind);
    m_strRecv = m_strRecv.substr(nPosFind);
    vector<string> vecMsg;
    CBaseFunc::SplitString(strHandle, ";", vecMsg);

    for (int i = 0; i < vecMsg.size(); ++i)
    {
        vecMsg[i].append(";");

        //center_trace(center_log_debug, "****interface exec %s total:%d, now %d",
         //   vecMsg[i].c_str(), vecMsg.size(), i);

        HandleIFMsg(info_index, client_fd, enClientType, vecMsg[i].c_str(), vecMsg[i].size());
    }
    return 0;
}

int HRC_If_Server::HandleIFMsg(int info_index, int client_fd, int enClientType, const char* pData,int nLen)
{
    string sMsg = string(pData,nLen);

    if (sMsg.empty())
    {
        return -1;
    }
    string::iterator posMsg = sMsg.begin();
    while (posMsg != sMsg.end())
    {
        if ((*posMsg) == '\n' ||
            (*posMsg) == '\b' ||
            (*posMsg) == '\r')
        {
            posMsg = sMsg.erase(posMsg);
        }
        else if((*posMsg) == '"')
        {
            ++posMsg;
            while (posMsg != sMsg.end())
            {
                if((*posMsg) == '"')
                {
                    ++posMsg;
                    break;
                }
                ++posMsg;
            }
        }
        else
        {
            ++posMsg;
        }
    }
    vector<string> vcCmdRecv;
    vcCmdRecv.clear();

    string sMark = ";";
    string::size_type stPos = string::npos, tmpPos = string::npos;
    string sTmp = sMsg;
    string sValTmp = "";
    int iLen = sMark.size();
    stPos = sTmp.find(sMark);
    while (stPos != string::npos)
    {
        stPos += iLen;
        sValTmp = sTmp.substr(0, stPos);
        vcCmdRecv.push_back(sValTmp);

        sTmp = sTmp.substr(stPos, sTmp.length());
        stPos = sTmp.find(sMark);
    }
    if (!sTmp.empty())
    {
        vcCmdRecv.push_back(sTmp);
    }
    string strRespone = "";
    if (vcCmdRecv.empty())
    {
        vcCmdRecv.push_back(sMsg);
    }

    for (int i = 0; i < vcCmdRecv.size(); i++)
    {
        strRespone.clear();
        if (vcCmdRecv[i].empty())
        {
            continue;
        }
        string strCmd = vcCmdRecv[i];
        if (strCmd[strCmd.size() - 1] == ';')
        {
            strCmd.pop_back();
        }
        vector<string> vcCmdParam;
        CBaseFunc::SplitString(strCmd, IFSplit, vcCmdParam);
        if (vcCmdParam.size() <= 0)
        {
            continue;
        }
        if (vcCmdParam[vcCmdParam.size() - 1] == ";")
        {
            vcCmdParam.pop_back();
        }
        if (vcCmdParam.size() < 1)
        {
            return -1;
        }

        vcCmdParam.push_back(CBaseFunc::i_str(enClientType));

        int nHandleRet = REC_Successed;// 处理结果存放在最后一位
        string strCmdName = vcCmdParam[0];
        string strCmdNameRaw = vcCmdParam[0];
        bool bParamErr = (vcCmdRecv[i].find(IFEnd) == string::npos);
        for (int iParam = 0; iParam < vcCmdParam.size(); ++iParam)
        {
            if (vcCmdParam[iParam].empty()){bParamErr = true; break;}
        }
        if (bParamErr)
        {
            nHandleRet = REC_ParamError;

            strRespone.append(strCmdNameRaw);
            strRespone.append(IFSplit);
            strRespone.append(OPTFAIL);
            strRespone.append(IFSplit);
            strRespone.append(CBaseFunc::i_str(REC_ParamError));
            strRespone.append(IFEnd);
            HRC_Interface::ResponseIFMsg(info_index,  client_fd, strRespone.c_str(),strRespone.size());
            continue;
        }
        try
        {
            if (g_mIFMsgHandleFunc.count(strCmdName) > 0)
            {
                int nPosFind = strCmd.find("Read");
                if (nPosFind == string::npos)
                {

                }
                nHandleRet = g_mIFMsgHandleFunc[strCmdName](vcCmdParam, strRespone);

            }
            else
            {
                nHandleRet = REC_CmdInvalid; // 命令无效
            }
            if (nHandleRet != 0 && strRespone.empty())
            {
                strRespone.append(strCmdNameRaw);
                strRespone.append(IFSplit);
                strRespone.append(OPTFAIL);
                strRespone.append(IFSplit);
                strRespone.append(CBaseFunc::i_str(nHandleRet));
                strRespone.append(IFEnd);
            }
        }
        catch (...)
        {
            nHandleRet = REC_CCCrash;
        }
        HRC_Interface::ResponseIFMsg(info_index,  client_fd, strRespone.c_str(),strRespone.size());
    }
    return 0;
}
