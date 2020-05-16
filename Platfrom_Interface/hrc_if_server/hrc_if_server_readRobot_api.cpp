
#include "hrc_if_server_api.h"
#include "../public_files/global_error/hrc_public_gerrorcode.h"
#include "HRC_StatusMachine/hrc_status_api.h"
#include "HRC_Public/hrc_public_func.h"
#include "HRC_Public/hrc_public_factory/hrc_public_factory.h"

namespace HRC_If_Server_Api
{
    int IF_ReadTCPByName(vector<string>& vcRequest, string& strResponse)
    {
        if (vcRequest.size() != 4)
        {
            return REC_FormatError;
        }
        int nRbtID = atoi(vcRequest.at(1).c_str());
        string strName = vcRequest.at(2);

        int nActRobotCnt=HMRC_Status_ReadActRobotCnt();
        if((nRbtID < 0) || ( nRbtID >= nActRobotCnt ))
            return REC_RobotNotExist;

        //int nClientType = stoi(vcRequest[vcRequest.size() -1]);
        PointCoord TCPCoord;
        int nRet = HMRC_Status_ReadTCPByName(nRbtID, strName, TCPCoord);
        strResponse.clear();
        strResponse.append(vcRequest[0]);
        strResponse.append(IFSplit);
        if (nRet != REC_Successed)
        {
            strResponse.append(OPTFAIL);
            strResponse.append(IFSplit);
            strResponse.append(CBaseFunc::i_str(nRet));
            strResponse.append(IFEnd);
            return nRet;
        }
        strResponse.append(OPTOK);
        for (int i = 0; i < Max_ActualAxisCnt; ++i)
        {
            strResponse.append(IFSplit);
            strResponse.append(CBaseFunc::d_str(TCPCoord.Axis[i]));
        }

        strResponse.append(IFEnd);
        return nRet;
    }
    int IF_ReadUCSByName(vector<string>& vcRequest, string& strResponse)
    {
        if (vcRequest.size() != 4)
        {
            return REC_FormatError;
        }
        int nRbtID = atoi(vcRequest.at(1).c_str());
        string strName = vcRequest.at(2);
        //int nClientType = stoi(vcRequest[vcRequest.size() -1]);

        int nActRobotCnt=HMRC_Status_ReadActRobotCnt();
        if((nRbtID < 0) || ( nRbtID >= nActRobotCnt ))
            return REC_RobotNotExist;

        PointCoord UCSCoord;
        int nRet = HMRC_Status_ReadUCSByName(nRbtID, strName, UCSCoord);
        strResponse.clear();
        strResponse.append(vcRequest[0]);
        strResponse.append(IFSplit);
        if (nRet != REC_Successed)
        {
            strResponse.append(OPTFAIL);
            strResponse.append(IFSplit);
            strResponse.append(CBaseFunc::i_str(nRet));
            strResponse.append(IFEnd);
            return nRet;
        }
        strResponse.append(OPTOK);
        for (int i = 0; i < Max_ActualAxisCnt; ++i)
        {
            strResponse.append(IFSplit);
            strResponse.append(CBaseFunc::d_str(UCSCoord.Axis[i]));
        }

        strResponse.append(IFEnd);
        return nRet;
    }
    int IF_ReadDefaultTCPName(vector<string>& vcRequest, string& strResponse)
    {
        if (vcRequest.size() != 3)
        {
            return REC_FormatError;
        }
        int nRbtID = atoi(vcRequest.at(1).c_str());

        int nActRobotCnt=HMRC_Status_ReadActRobotCnt();
        if((nRbtID < 0) || ( nRbtID >= nActRobotCnt ))
            return REC_RobotNotExist;

        //int nClientType = stoi(vcRequest[vcRequest.size() -1]);
        string strName="";
        int nRet = HMRC_Status_ReadDefaultTCPName(nRbtID, strName);
        strResponse.clear();
        strResponse.append(vcRequest[0]);
        strResponse.append(IFSplit);
        if (nRet != REC_Successed)
        {
            strResponse.append(OPTFAIL);
            strResponse.append(IFSplit);
            strResponse.append(CBaseFunc::i_str(nRet));
            strResponse.append(IFEnd);
            return nRet;
        }
        strResponse.append(OPTOK);
        strResponse.append(strName);
        strResponse.append(IFEnd);
        return nRet;
    }
    int IF_ReadDefaultUCSName(vector<string>& vcRequest, string& strResponse)
    {
        if (vcRequest.size() != 3)
        {
            return REC_FormatError;
        }
        int nRbtID = atoi(vcRequest.at(1).c_str());

        int nActRobotCnt=HMRC_Status_ReadActRobotCnt();
        if((nRbtID < 0) || ( nRbtID >= nActRobotCnt ))
            return REC_RobotNotExist;

        //int nClientType = stoi(vcRequest[vcRequest.size() -1]);
        string strName="";
        int nRet = HMRC_Status_ReadDefaultUCSName(nRbtID, strName);
        strResponse.clear();
        strResponse.append(vcRequest[0]);
        strResponse.append(IFSplit);
        if (nRet != REC_Successed)
        {
            strResponse.append(OPTFAIL);
            strResponse.append(IFSplit);
            strResponse.append(CBaseFunc::i_str(nRet));
            strResponse.append(IFEnd);
            return nRet;
        }
        strResponse.append(OPTOK);
        strResponse.append(strName);
        strResponse.append(IFEnd);
        return nRet;
    }
    int IF_ReadCurEncode(vector<string>& vcRequest, string& strResponse)
    {
        int nRet = REC_Successed;
        if (vcRequest.size() != 3)
        {
            return REC_FormatError;
        }
        int nRbtID = atoi(vcRequest[1].c_str());
        MultiEndatPos CurEncode;

        int nActRobotCnt=HMRC_Status_ReadActRobotCnt();
        if((nRbtID < 0) || ( nRbtID >= nActRobotCnt ))
            return REC_RobotNotExist;

        nRet = HMRC_Status_ReadEndatPosMulti(nRbtID, CurEncode);
        strResponse.clear();
        strResponse.append(vcRequest[0]);
        strResponse.append(IFSplit);
        if (nRet != REC_Successed)
        {
            strResponse.append(OPTFAIL);
            strResponse.append(IFSplit);
            strResponse.append(CBaseFunc::i_str(nRet));
            strResponse.append(IFEnd);
            return nRet;
        }
        strResponse.append(OPTOK);
        for (int i = 0; i < Max_ActualAxisCnt; ++i)
        {
            strResponse.append(IFSplit);
            strResponse.append(CBaseFunc::d_str(CurEncode.multiEndatPos[i]));
        }

        strResponse.append(IFEnd);
        return nRet;
    }

    int IF_ReadRobotInfoParam(vector<string>& vcRequest, string& strResponse)
    {
        int nRet = REC_Successed;
        if (vcRequest.size() != 3)
        {
            return REC_FormatError;
        }
        int nRbtID = atoi(vcRequest[1].c_str());
        ST_PayloadRecognitionParam PayloadRecParam;

        int nActRobotCnt=HMRC_Status_ReadActRobotCnt();
        if((nRbtID < 0) || ( nRbtID >= nActRobotCnt ))
            return REC_RobotNotExist;

        nRet = HMRC_Status_ReadPayloadRecognitionParam(nRbtID, PayloadRecParam);
        strResponse.clear();
        strResponse.append(vcRequest[0]);
        strResponse.append(IFSplit);
        if (nRet != REC_Successed)
        {
            strResponse.append(OPTFAIL);
            strResponse.append(IFSplit);
            strResponse.append(CBaseFunc::i_str(nRet));
            strResponse.append(IFEnd);
            return nRet;
        }
        strResponse.append(OPTOK);
        for (int i = 0; i < Max_ActualAxisCnt; ++i)
        {
            strResponse.append(IFSplit);
            strResponse.append(CBaseFunc::d_str(PayloadRecParam.JointPositions[i]));
        }
        for (int i = 0; i < Max_ActualAxisCnt; ++i)
        {
            strResponse.append(IFSplit);
            strResponse.append(CBaseFunc::d_str(PayloadRecParam.JointVelocities[i]));
        }
        for (int i = 0; i < Max_ActualAxisCnt; ++i)
        {
            strResponse.append(IFSplit);
            strResponse.append(CBaseFunc::d_str(PayloadRecParam.JointAccelerations[i]));
        }
        for (int i = 0; i < Max_ActualAxisCnt; ++i)
        {
            strResponse.append(IFSplit);
            strResponse.append(CBaseFunc::d_str(PayloadRecParam.SensedJointTorques[i]));
        }
        for (int i = 0; i < Max_ActualAxisCnt; ++i)
        {
            strResponse.append(IFSplit);
            strResponse.append(CBaseFunc::d_str(PayloadRecParam.EstimatedJointTorques[i]));
        }
        for (int i = 0; i < Max_ActualAxisCnt; ++i)
        {
            strResponse.append(IFSplit);
            strResponse.append(CBaseFunc::d_str(PayloadRecParam.MotorCurrent[i]));
        }
        strResponse.append(IFEnd);
        return nRet;
    }

    int IF_ReadActualPos(vector<string>& vcRequest, string& strResponse)
    {
        int nRet = REC_Successed;
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
        RobotPosition ActPos;

        int nActRobotCnt=HMRC_Status_ReadActRobotCnt();
        if((nRbtID < 0) || ( nRbtID >= nActRobotCnt ))
            return REC_RobotNotExist;

        nRet = HMRC_Status_ReadActualPos(nRbtID, ActPos);
        strResponse.clear();
        strResponse.append(vcRequest[0]);
        strResponse.append(IFSplit);
        if (nRet != REC_Successed)
        {
            strResponse.append(OPTFAIL);
            strResponse.append(IFSplit);
            strResponse.append(CBaseFunc::i_str(nRet));
            strResponse.append(IFEnd);
            return nRet;
        }
        strResponse.append(OPTOK);
        for (int i = 0; i < Max_ActualAxisCnt; ++i)
        {
            strResponse.append(IFSplit);
            strResponse.append(CBaseFunc::d_str(ActPos.AcsActualPos.Axis[i]));
        }
        for (int i = 0; i < Max_ActualAxisCnt; ++i)
        {
            strResponse.append(IFSplit);
            strResponse.append(CBaseFunc::d_str(ActPos.PcsActualPos.Axis[i]));
        }
        strResponse.append(IFEnd);
        return nRet;
    }
    int IF_ReadRobotPosInfo(vector<string>& vcRequest, string& strResponse)
    {
        int nRet = REC_Successed;
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
        RobotPosition ActPos;
        RobotPosition CmdPos;

        int nActRobotCnt=HMRC_Status_ReadActRobotCnt();
        if((nRbtID < 0) || ( nRbtID >= nActRobotCnt ))
            return REC_RobotNotExist;

        nRet = HMRC_Status_ReadRobotPosInfo(nRbtID, ActPos, CmdPos);


        strResponse.clear();
        strResponse.append(vcRequest[0]);
        strResponse.append(IFSplit);
        if (nRet != REC_Successed)
        {
            strResponse.append(OPTFAIL);
            strResponse.append(IFSplit);
            strResponse.append(CBaseFunc::i_str(nRet));
            strResponse.append(IFEnd);
            return nRet;
        }
        strResponse.append(OPTOK);
        for (int i = 0; i < Max_ActualAxisCnt; ++i)
        {
            strResponse.append(IFSplit);
            strResponse.append(CBaseFunc::d_str(ActPos.AcsActualPos.Axis[i]));
        }
        for (int i = 0; i < Max_ActualAxisCnt; ++i)
        {
            strResponse.append(IFSplit);
            strResponse.append(CBaseFunc::d_str(ActPos.PcsActualPos.Axis[i]));
        }
        for (int i = 0; i < Max_ActualAxisCnt; ++i)
        {
            strResponse.append(IFSplit);
            strResponse.append(CBaseFunc::d_str(ActPos.RobotAxisCurrent.Axis[i]));
        }
        for (int i = 0; i < Max_ActualAxisCnt; ++i)
        {
            strResponse.append(IFSplit);
            strResponse.append(CBaseFunc::d_str(CmdPos.AcsActualPos.Axis[i]));
        }
        for (int i = 0; i < Max_ActualAxisCnt; ++i)
        {
            strResponse.append(IFSplit);
            strResponse.append(CBaseFunc::d_str(CmdPos.PcsActualPos.Axis[i]));
        }
        for (int i = 0; i < Max_ActualAxisCnt; ++i)
        {
            strResponse.append(IFSplit);
            strResponse.append(CBaseFunc::d_str(CmdPos.RobotAxisCurrent.Axis[i]));
        }
        strResponse.append(IFEnd);
        return nRet;
    }
    int IF_ReadOverride(vector<string>& vcRequest, string& strResponse)
    {
        int nRet = REC_Successed;
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
        double dbOverride = 0.0;

        int nActRobotCnt=HMRC_Status_ReadActRobotCnt();
        if((nRbtID < 0) || ( nRbtID >= nActRobotCnt ))
            return REC_RobotNotExist;

        nRet = HMRC_Status_ReadOverride(nRbtID, dbOverride);

        strResponse.clear();
        strResponse.append(vcRequest[0]);
        strResponse.append(IFSplit);
        if (nRet != REC_Successed)
        {
            strResponse.append(OPTFAIL);
            strResponse.append(IFSplit);
            strResponse.append(CBaseFunc::i_str(nRet));
            strResponse.append(IFEnd);
            return nRet;
        }
        strResponse.append(OPTOK);
        strResponse.append(IFSplit);
        strResponse.append(CBaseFunc::d_str(dbOverride));
        strResponse.append(IFEnd);
        return nRet;
    }

    int IF_ReadControlMode(vector<string>& vcRequest, string& strResponse)
    {
        int nRet = REC_Successed;
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
        int nState = 0;

        int nActRobotCnt=HMRC_Status_ReadActRobotCnt();
        if((nRbtID < 0) || ( nRbtID >= nActRobotCnt ))
            return REC_RobotNotExist;

        nRet = HMRC_Status_ReadControlMode(nRbtID,nState);

        strResponse.clear();
        strResponse.append(vcRequest[0]);
        strResponse.append(IFSplit);
        strResponse.append(OPTOK);
        strResponse.append(IFSplit);
        strResponse.append(CBaseFunc::i_str(nState));
        strResponse.append(IFEnd);
        return nRet;

    }

    
    int IF_ReadRobotState(vector<string>& vcRequest, string& strResponse)
    {
        int nRet = REC_Successed;
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

        int nActRobotCnt=HMRC_Status_ReadActRobotCnt();
        if((nRbtID < 0) || ( nRbtID >= nActRobotCnt ))
            return REC_RobotNotExist;

        int status[20];
        nRet = HRC_GET_MC()->ReadRobotRealTimeStatus(nRbtID,status);
        
        strResponse.clear();
        strResponse.append(vcRequest[0]);
        strResponse.append(IFSplit);
        if (nRet != REC_Successed)
        {
            strResponse.append(OPTFAIL);
            strResponse.append(IFSplit);
            strResponse.append(CBaseFunc::i_str(nRet));
            strResponse.append(IFEnd);
            return nRet;
        }

        strResponse.append(OPTOK);
        strResponse.append(IFSplit);
        strResponse.append(CBaseFunc::i_str(status[0]));
        strResponse.append(IFSplit);
        strResponse.append(CBaseFunc::i_str(status[1]));
        strResponse.append(IFSplit);
        strResponse.append(CBaseFunc::i_str(status[2]));
        strResponse.append(IFSplit);
        strResponse.append(CBaseFunc::i_str(status[3]));
        strResponse.append(IFSplit);
        strResponse.append(CBaseFunc::i_str(status[4]));
        strResponse.append(IFSplit);
        strResponse.append(CBaseFunc::i_str(status[5]));
        strResponse.append(IFSplit);
        strResponse.append(CBaseFunc::i_str(status[6]));
        strResponse.append(IFSplit);
        strResponse.append(CBaseFunc::i_str(status[7]));
        strResponse.append(IFSplit);
        strResponse.append(CBaseFunc::i_str(status[8]));
        strResponse.append(IFSplit);
        strResponse.append(CBaseFunc::i_str(status[9]));
        strResponse.append(IFSplit);
        strResponse.append(CBaseFunc::i_str(status[10]));
        strResponse.append(IFSplit);
        strResponse.append(CBaseFunc::i_str(status[11]));   
        strResponse.append(IFEnd);
        return nRet;
    }

    int IF_Base2TCPUCS(vector<string>& vcRequest, string& strResponse)
    {
        if (vcRequest.size() != 21)
        {
            return REC_FormatError;
        }
        int nRet = REC_Successed;
        for(int i = 1; i < 20; ++i)
        {
            if(!CBaseFunc::IsNumber(vcRequest[i]))
                return REC_ParamError;
        }
        //int nRbtID = atoi(vcRequest[1].c_str());
        PointCoord BaseCoord;
        PointCoord TargetTCPCoord;
        PointCoord TargetUCSCoord;
        PointCoord TargetPcs;
        BaseCoord.Axis[0] = atof(vcRequest.at(2).c_str());
        BaseCoord.Axis[1] = atof(vcRequest.at(3).c_str());
        BaseCoord.Axis[2] = atof(vcRequest.at(4).c_str());
        BaseCoord.Axis[3] = atof(vcRequest.at(5).c_str());
        BaseCoord.Axis[4] = atof(vcRequest.at(6).c_str());
        BaseCoord.Axis[5] = atof(vcRequest.at(7).c_str());

        TargetTCPCoord.Axis[0] = atof(vcRequest.at(8).c_str());
        TargetTCPCoord.Axis[1] = atof(vcRequest.at(9).c_str());
        TargetTCPCoord.Axis[2] = atof(vcRequest.at(10).c_str());
        TargetTCPCoord.Axis[3] = atof(vcRequest.at(11).c_str());
        TargetTCPCoord.Axis[4] = atof(vcRequest.at(12).c_str());
        TargetTCPCoord.Axis[5] = atof(vcRequest.at(13).c_str());

        TargetUCSCoord.Axis[0] = atof(vcRequest.at(14).c_str());
        TargetUCSCoord.Axis[1] = atof(vcRequest.at(15).c_str());
        TargetUCSCoord.Axis[2] = atof(vcRequest.at(16).c_str());
        TargetUCSCoord.Axis[3] = atof(vcRequest.at(17).c_str());
        TargetUCSCoord.Axis[4] = atof(vcRequest.at(18).c_str());
        TargetUCSCoord.Axis[5] = atof(vcRequest.at(19).c_str());
        //int nClientType = stoi(vcRequest[vcRequest.size() -1]);
        HRC_GET_RM()->Base2UcsTcp(BaseCoord,TargetTCPCoord,TargetUCSCoord,TargetPcs);

        strResponse.clear();
        strResponse.append(vcRequest[0]);
        strResponse.append(IFSplit);
        if (nRet != REC_Successed)
        {
            strResponse.append(OPTFAIL);
            strResponse.append(IFSplit);
            strResponse.append(CBaseFunc::i_str(nRet));
            strResponse.append(IFEnd);
            return nRet;
        }
        strResponse.append(OPTOK);
        for (int i = 0; i < Max_ActualAxisCnt; ++i)
        {
            strResponse.append(IFSplit);
            strResponse.append(CBaseFunc::d_str(TargetPcs.Axis[i]));
        }

        strResponse.append(IFEnd);
        return nRet;
    }
    int IF_PCS2ACS(vector<string>& vcRequest, string& strResponse)
    {
        if (vcRequest.size() != 27)
        {
            return REC_FormatError;
        }
        int nRet = REC_Successed;
        for(int i = 1; i < 26; ++i)
        {
            if(!CBaseFunc::IsNumber(vcRequest[i]))
                return REC_ParamError;
        }
        //int nRbtID = atoi(vcRequest[1].c_str());
        PointCoord BaseCoord;
        PointCoord RawACSCoord;
        PointCoord TargetTCPCoord;
        PointCoord TargetUCSCoord;
        PointCoord TargetPcs;
        BaseCoord.Axis[0] = atof(vcRequest.at(2).c_str());
        BaseCoord.Axis[1] = atof(vcRequest.at(3).c_str());
        BaseCoord.Axis[2] = atof(vcRequest.at(4).c_str());
        BaseCoord.Axis[3] = atof(vcRequest.at(5).c_str());
        BaseCoord.Axis[4] = atof(vcRequest.at(6).c_str());
        BaseCoord.Axis[5] = atof(vcRequest.at(7).c_str());

        RawACSCoord.Axis[0] = atof(vcRequest.at(8).c_str());
        RawACSCoord.Axis[1] = atof(vcRequest.at(9).c_str());
        RawACSCoord.Axis[2] = atof(vcRequest.at(10).c_str());
        RawACSCoord.Axis[3] = atof(vcRequest.at(11).c_str());
        RawACSCoord.Axis[4] = atof(vcRequest.at(12).c_str());
        RawACSCoord.Axis[5] = atof(vcRequest.at(13).c_str());

        TargetTCPCoord.Axis[0] = atof(vcRequest.at(14).c_str());
        TargetTCPCoord.Axis[1] = atof(vcRequest.at(15).c_str());
        TargetTCPCoord.Axis[2] = atof(vcRequest.at(16).c_str());
        TargetTCPCoord.Axis[3] = atof(vcRequest.at(17).c_str());
        TargetTCPCoord.Axis[4] = atof(vcRequest.at(18).c_str());
        TargetTCPCoord.Axis[5] = atof(vcRequest.at(19).c_str());

        TargetUCSCoord.Axis[0] = atof(vcRequest.at(20).c_str());
        TargetUCSCoord.Axis[1] = atof(vcRequest.at(21).c_str());
        TargetUCSCoord.Axis[2] = atof(vcRequest.at(22).c_str());
        TargetUCSCoord.Axis[3] = atof(vcRequest.at(23).c_str());
        TargetUCSCoord.Axis[4] = atof(vcRequest.at(24).c_str());
        TargetUCSCoord.Axis[5] = atof(vcRequest.at(25).c_str());
        //int nClientType = stoi(vcRequest[vcRequest.size() -1]);

        HRC_GET_RM()->PCS2ACS(BaseCoord,TargetTCPCoord,TargetUCSCoord,RawACSCoord,TargetPcs);

        strResponse.clear();
        strResponse.append(vcRequest[0]);
        strResponse.append(IFSplit);
        if (nRet != REC_Successed)
        {
            strResponse.append(OPTFAIL);
            strResponse.append(IFSplit);
            strResponse.append(CBaseFunc::i_str(nRet));
            strResponse.append(IFEnd);
            return nRet;
        }
        strResponse.append(OPTOK);
        for (int i = 0; i < Max_ActualAxisCnt; ++i)
        {
            strResponse.append(IFSplit);
            strResponse.append(CBaseFunc::d_str(TargetPcs.Axis[i]));
        }

        strResponse.append(IFEnd);
        return nRet;
    }
}
