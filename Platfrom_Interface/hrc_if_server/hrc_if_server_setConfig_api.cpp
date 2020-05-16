#include "hrc_if_server_api.h"
#include "../public_files/global_error/hrc_public_gerrorcode.h"
#include "HRC_StatusMachine/hrc_status_api.h"
#include "HRC_Public/hrc_public_func.h"


namespace HRC_If_Server_Api
{
    int IF_SetToolCoordinateMotion(vector<string>& vcRequest, string& strResponse)
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
        int nState = atof(vcRequest[2].c_str());
        int nClientType = stoi(vcRequest[vcRequest.size() -1]);
        int nActRobotCnt=HMRC_Status_ReadActRobotCnt();
        if((nRbtID < 0) || ( nRbtID >= nActRobotCnt ))
            return REC_RobotNotExist;
        int nRet = HMRC_Status_Set_ToolCoordinateMotion(nRbtID, nState, nClientType);
        return _GeneralRespones(vcRequest[0], nRet, strResponse);
    }    

    /* 通过用户坐标名称设置用户坐标 */
    int IF_SetUCSByName(vector<string>& vcRequest, string& strResponse)
    {
        if (vcRequest.size() != 4)
        {
            return REC_FormatError;
        }
        if(!CBaseFunc::IsNumber(vcRequest[1]))
            return REC_ParamError;
        int nRbtID = atoi(vcRequest.at(1).c_str());  
        string strUcsName = vcRequest.at(2);
        int nClientType = stoi(vcRequest[vcRequest.size() -1]);
        int nActRobotCnt=HMRC_Status_ReadActRobotCnt();
        if((nRbtID < 0) || ( nRbtID >= nActRobotCnt ))
            return REC_RobotNotExist;
        int nRet = HRC_Status_SetUCSByName(nRbtID, strUcsName, nClientType);
        return _GeneralRespones(vcRequest[0], nRet, strResponse);
    }

    /* 通过刀具坐标名称设置刀具坐标 */
    int IF_SetTCPByName(vector<string>& vcRequest, string& strResponse)
    {
        if (vcRequest.size() != 4)
        {
            return REC_FormatError;
        }
        if(!CBaseFunc::IsNumber(vcRequest[1]))
            return REC_ParamError;
        int nRbtID = atoi(vcRequest.at(1).c_str());  
        string strTCPName = vcRequest.at(2);
        int nClientType = stoi(vcRequest[vcRequest.size() -1]);
        int nActRobotCnt=HMRC_Status_ReadActRobotCnt();
        if((nRbtID < 0) || ( nRbtID >= nActRobotCnt ))
            return REC_RobotNotExist;
        int nRet = HRC_Status_SetTCPByName(nRbtID, strTCPName, nClientType);
        return _GeneralRespones(vcRequest[0], nRet, strResponse);
    }



    /*
    int IF_SetBaseMountingAngle(vector<string>& vcRequest, string& strResponse)
    {
        if (vcRequest.size() != 4)
        {
            return REC_FormatError;
        }
        int nRbtID = atoi(vcRequest[1].c_str());
        double dRotation = atof(vcRequest[2].c_str());
        double dTilt = atof(vcRequest[3].c_str());
        int nScriptFunc = 0;
        int nRet = HRC_Status_SetBaseMountingAngle(nRbtID, dRotation, dTilt, nScriptFunc);
        if (nRet != REC_Successed)
        {
            return nRet;
        }
        return _GeneralRespones(vcRequest[0], nRet, strResponse);
    }

    
    int IF_SetCollideStopPayload(vector<string>& vcRequest, string& strResponse)
    {
        if (vcRequest.size() != 6)
        {
            return REC_FormatError;
        }
        int nRbtID = atoi(vcRequest.at(1).c_str());
        Payload stPayLoad;
        stPayLoad.mass = atof(vcRequest.at(2).c_str());
        stPayLoad.masscenterX = atof(vcRequest.at(3).c_str());
        stPayLoad.masscenterY = atof(vcRequest.at(4).c_str());
        stPayLoad.masscenterZ = atof(vcRequest.at(5).c_str());
        int nScriptFunc = 0;
        int nRet = HMRC_Status_Set_GravityPayload(nRbtID, stPayLoad, nScriptFunc);
        return _GeneralRespones(vcRequest[0], nRet, strResponse);
    }

    int IF_SetMoveJointMotionLimits(vector<string>& vcRequest, string& strResponse)
    {
        if (vcRequest.size() != 20)
        {
            return REC_FormatError;
        }
        int nRbtID = atoi(vcRequest.at(1).c_str());
        JointMotionLimits jointMotionLimits;
        for (int i = 0, n = 2; i < Max_ActualAxisCnt; ++i)
        {
            jointMotionLimits.Speed[i] = atof(vcRequest.at(n++).c_str());
            jointMotionLimits.Acc[i] = atof(vcRequest.at(n++).c_str());
            jointMotionLimits.Jerk[i] = atof(vcRequest.at(n++).c_str());
        }
        int nScriptFunc = 0;
        int nRet = HMRC_Status_SetMoveJointMotionLimits(nRbtID, jointMotionLimits, nScriptFunc);
        return _GeneralRespones(vcRequest[0], nRet, strResponse);
    }

    int IF_SetStopJointMotionLimits(vector<string>& vcRequest, string& strResponse)
    {
        if (vcRequest.size() != 20)
        {
            return REC_FormatError;
        }
        int nRbtID = atoi(vcRequest.at(1).c_str());
        JointMotionLimits jointMotionLimits;
        for (int i = 0, n = 2; i < Max_ActualAxisCnt; ++i)
        {
            jointMotionLimits.Speed[i] = atof(vcRequest.at(n++).c_str());
            jointMotionLimits.Acc[i] = atof(vcRequest.at(n++).c_str());
            jointMotionLimits.Jerk[i] = atof(vcRequest.at(n++).c_str());
        }
        int nScriptFunc = 0;
        int nRet = HMRC_Status_SetStopJointMotionLimits(nRbtID, jointMotionLimits, nScriptFunc);
        return _GeneralRespones(vcRequest[0], nRet, strResponse);
    }
    int IF_SetMovePcsMotionLimits(vector<string>& vcRequest, string& strResponse)
    {
        if (vcRequest.size() != 8)
        {
            return REC_FormatError;
        }
        int nRbtID = atoi(vcRequest.at(1).c_str());
        PcsMotionLimits PcsMotionLimits;
        PcsMotionLimits.Linear_Speed = atoi(vcRequest.at(2).c_str());
        PcsMotionLimits.Linear_Acc = atoi(vcRequest.at(3).c_str());
        PcsMotionLimits.Linear_Jerk = atoi(vcRequest.at(4).c_str());
        PcsMotionLimits.Angular_Speed = atoi(vcRequest.at(5).c_str());
        PcsMotionLimits.Angular_Acc = atoi(vcRequest.at(6).c_str());
        PcsMotionLimits.Angular_Jerk = atoi(vcRequest.at(7).c_str());
        int nScriptFunc = 0;
        int nRet = HMRC_Status_SetMovePcsMotionLimits(nRbtID, PcsMotionLimits, nScriptFunc);
        return _GeneralRespones(vcRequest[0], nRet, strResponse);
    }
    int IF_SetStopPcsMotionLimits(vector<string>& vcRequest, string& strResponse)
    {
        if (vcRequest.size() != 8)
        {
            return REC_FormatError;
        }
        int nRbtID = atoi(vcRequest.at(1).c_str());
        PcsMotionLimits PcsMotionLimits;
        PcsMotionLimits.Linear_Speed = atoi(vcRequest.at(2).c_str());
        PcsMotionLimits.Linear_Acc = atoi(vcRequest.at(3).c_str());
        PcsMotionLimits.Linear_Jerk = atoi(vcRequest.at(4).c_str());
        PcsMotionLimits.Angular_Speed = atoi(vcRequest.at(5).c_str());
        PcsMotionLimits.Angular_Acc = atoi(vcRequest.at(6).c_str());
        PcsMotionLimits.Angular_Jerk = atoi(vcRequest.at(7).c_str());
        int nScriptFunc = 0;
        int nRet = HMRC_Status_SetStopPcsMotionLimits(nRbtID, PcsMotionLimits, nScriptFunc);
        return _GeneralRespones(vcRequest[0], nRet, strResponse);
    }

    int IF_SetCollisionStopMode(vector<string>& vcRequest, string& strResponse)
    {
        if (vcRequest.size() != 3)
        {
            return REC_FormatError;
        }
        int nRbtID = atoi(vcRequest.at(1).c_str());
        int  nMode = atoi(vcRequest.at(2).c_str());
        int nScriptFunc = 0;
        int nRet = HMRC_Status_SetCollisionStopMode(nRbtID, nMode, nScriptFunc);
        return _GeneralRespones(vcRequest[0], nRet, strResponse);
    }
    int IF_SetCollisionMomentumThresholds(vector<string>& vcRequest, string& strResponse)
    {
        if (vcRequest.size() != 8)
        {
            return REC_FormatError;
        }
        int nRbtID = atoi(vcRequest.at(1).c_str());
        int nScriptFunc = 0;
        Threshold stThreshold;
        stThreshold.J1 = atoi(vcRequest.at(2).c_str());
        stThreshold.J2 = atoi(vcRequest.at(3).c_str());
        stThreshold.J3 = atoi(vcRequest.at(4).c_str());
        stThreshold.J4 = atoi(vcRequest.at(5).c_str());
        stThreshold.J5 = atoi(vcRequest.at(6).c_str());
        stThreshold.J6 = atoi(vcRequest.at(7).c_str());
        int nRet = HMRC_Status_SetCollisionMomentumThresholds(nRbtID, stThreshold, nScriptFunc);
        return _GeneralRespones(vcRequest[0], nRet, strResponse);
    }

    int IF_SetBaseMountingAngle(vector<string>& vcRequest, string& strResponse)
    {
        if (vcRequest.size() != 4)
        {
            return REC_FormatError;
        }
        int nRbtID = atoi(vcRequest[1].c_str());
        double dRotation = atof(vcRequest[2].c_str());
        double dTilt = atof(vcRequest[3].c_str());
        int nScriptFunc = 0;
        int nRet = HMRC_Status_SetBaseMountingAngle(nRbtID, dRotation, dTilt, nScriptFunc);
        if (nRet != REC_Successed)
        {
            return nRet;
        }
        return _GeneralRespones(vcRequest[0], nRet, strResponse);
    }


    int IF_ElfinHomeStep2(vector<string>& vcRequest, string& strResponse)
    {
        if (vcRequest.size() != 4)
        {
            return REC_FormatError;
        }
        int nRbtID = atoi(vcRequest[1].c_str());
        int nAxisID = atoi(vcRequest[2].c_str());
        int nDirection = atoi(vcRequest[3].c_str());
        int nScriptFunc = 0;
        int nRet = HMRC_Status_ElfinHomeStep2(nRbtID, nAxisID, nDirection, nScriptFunc);
        return _GeneralRespones(vcRequest[0], nRet, strResponse);
    }

    int IF_EncoderSetHomeEndatPos(vector<string>& vcRequest, string& strResponse)
    {
        if (vcRequest.size() != 2)
        {
            return REC_FormatError;
        }
        int nRbtID = atoi(vcRequest[1].c_str());

        int nScriptFunc = 0;
        int nRet = HMRC_Status_EncoderSetHomeEndatPos(nRbtID, nScriptFunc);
        return _GeneralRespones(vcRequest[0], nRet, strResponse);
    }

    */

}
