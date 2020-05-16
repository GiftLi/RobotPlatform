
#include "hrc_if_server_api.h"
#include "../public_files/global_error/hrc_public_gerrorcode.h"
#include "HRC_StatusMachine/hrc_status_api.h"
#include "HRC_Public/hrc_public_func.h"

using namespace HRC_If_Server_Api;

namespace HRC_If_Server_Api
{
    int _GeneralRespones(string strCmd, int nRet, string& strResponse)
    {
        strResponse.clear();
        strResponse.append(strCmd);
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

    int IF_ShortJogJ(vector<string>& vcRequest, string& strResponse)
    {
        if (vcRequest.size() != 5)
        {
            return REC_FormatError;
        }
        /*for(int i = 1; i < 4; ++i)
        {
            if(!CBaseFunc::IsNumber(vcRequest[i]))
                return REC_ParamError;
        }*/
        int nRbtID = atoi(vcRequest[1].c_str());
        int nAxisID = atoi(vcRequest[2].c_str());
        int nDirection = atoi(vcRequest[3].c_str());
        int nClientType = stoi(vcRequest[vcRequest.size() -1]);

        int nActRobotCnt=HMRC_Status_ReadActRobotCnt();
        if((nRbtID < 0) || ( nRbtID >= nActRobotCnt ))
            return REC_RobotNotExist;

        int nRet = HMRC_Status_ShortJogAcs(nRbtID, nAxisID, nDirection, nClientType);
        return _GeneralRespones(vcRequest[0], nRet, strResponse);
    }
    int IF_ShortJogL(vector<string>& vcRequest, string& strResponse)
    {
        if (vcRequest.size() != 5)
        {
            return REC_FormatError;
        }
        /*for(int i = 1; i < 4; ++i)
        {
            if(!CBaseFunc::IsNumber(vcRequest[i]))
                return REC_ParamError;
        }*/
        int nRbtID = atoi(vcRequest[1].c_str());
        int nAxisID = atoi(vcRequest[2].c_str());
        int nDirection = atoi(vcRequest[3].c_str());
        int nClientType = stoi(vcRequest[vcRequest.size() -1]);

        int nActRobotCnt=HMRC_Status_ReadActRobotCnt();
        if((nRbtID < 0) || ( nRbtID >= nActRobotCnt ))
            return REC_RobotNotExist;

        int nRet = HMRC_Status_ShortJogPcs(nRbtID, nAxisID, nDirection, nClientType);
        return _GeneralRespones(vcRequest[0], nRet, strResponse);
    }
    int IF_LongJogJ(vector<string>& vcRequest, string& strResponse)
    {
        if (vcRequest.size() != 6)
        {
            return REC_FormatError;
        }
        /*for(int i = 1; i < 5; ++i)
        {
            if(!CBaseFunc::IsNumber(vcRequest[i]))
                return REC_ParamError;
        }*/
        int nRbtID = atoi(vcRequest[1].c_str());
        int nAxisID = atoi(vcRequest[2].c_str());
        int nDirection = atoi(vcRequest[3].c_str());
        int nState = atoi(vcRequest[4].c_str());
        int nClientType = stoi(vcRequest[vcRequest.size() -1]);

        int nActRobotCnt=HMRC_Status_ReadActRobotCnt();
        if((nRbtID < 0) || ( nRbtID >= nActRobotCnt ))
            return REC_RobotNotExist;

        int nRet = HMRC_Status_LongJogAcs(nRbtID, nAxisID, nDirection,nState, nClientType);
        return _GeneralRespones(vcRequest[0], nRet, strResponse);
    }
    int IF_LongJogL(vector<string>& vcRequest, string& strResponse)
    {
        if (vcRequest.size() != 6)
        {
            return REC_FormatError;
        }
        /*for(int i = 1; i < 5; ++i)
        {
            if(!CBaseFunc::IsNumber(vcRequest[i]))
                return REC_ParamError;
        }*/
        int nRbtID = atoi(vcRequest[1].c_str());
        int nAxisID = atoi(vcRequest[2].c_str());
        int nDirection = atoi(vcRequest[3].c_str());
        int nState = atoi(vcRequest[4].c_str());
        int nClientType = stoi(vcRequest[vcRequest.size() -1]);

        int nActRobotCnt=HMRC_Status_ReadActRobotCnt();
        if((nRbtID < 0) || ( nRbtID >= nActRobotCnt ))
            return REC_RobotNotExist;

        int nRet = HMRC_Status_LongJogPcs(nRbtID, nAxisID, nDirection,nState, nClientType);
        return _GeneralRespones(vcRequest[0], nRet, strResponse);
    }
    int IF_MoveJ(vector<string>& vcRequest, string& strResponse)
    {
        if (vcRequest.size() != 9)
        {
            return REC_FormatError;
        }
        /*for(int i = 1; i < 8; ++i)
        {
            if(!CBaseFunc::IsNumber(vcRequest[i]))
                return REC_ParamError;
        }*/
        int nRbtID = atoi(vcRequest[1].c_str());
        PointCoord coord;
        coord.Axis[0] = atof(vcRequest.at(2).c_str());
        coord.Axis[1] = atof(vcRequest.at(3).c_str());
        coord.Axis[2] = atof(vcRequest.at(4).c_str());
        coord.Axis[3] = atof(vcRequest.at(5).c_str());
        coord.Axis[4] = atof(vcRequest.at(6).c_str());
        coord.Axis[5] = atof(vcRequest.at(7).c_str());
        int nClientType = stoi(vcRequest[vcRequest.size() -1]);

        int nActRobotCnt=HMRC_Status_ReadActRobotCnt();
        if((nRbtID < 0) || ( nRbtID >= nActRobotCnt ))
            return REC_RobotNotExist;

        int nRet = HMRC_Status_MoveJ(nRbtID, coord, nClientType);
        return _GeneralRespones(vcRequest[0], nRet, strResponse);
    }
    int IF_MoveL(vector<string>& vcRequest, string& strResponse)
    {
        if (vcRequest.size() != 9)
        {
            return REC_FormatError;
        }
        /*for(int i = 1; i < 8; ++i)
        {
            if(!CBaseFunc::IsNumber(vcRequest[i]))
                return REC_ParamError;
        }*/
        int nRbtID = atoi(vcRequest[1].c_str());
        PointCoord coord;
        coord.Axis[0] = atof(vcRequest.at(2).c_str());
        coord.Axis[1] = atof(vcRequest.at(3).c_str());
        coord.Axis[2] = atof(vcRequest.at(4).c_str());
        coord.Axis[3] = atof(vcRequest.at(5).c_str());
        coord.Axis[4] = atof(vcRequest.at(6).c_str());
        coord.Axis[5] = atof(vcRequest.at(7).c_str());
        int nClientType = stoi(vcRequest[vcRequest.size() -1]);

        int nActRobotCnt=HMRC_Status_ReadActRobotCnt();
        if((nRbtID < 0) || ( nRbtID >= nActRobotCnt ))
            return REC_RobotNotExist;

        int nRet = HMRC_Status_MoveL(nRbtID, coord,nClientType);
        return _GeneralRespones(vcRequest[0], nRet, strResponse);
    }

    int IF_MoveC(vector<string>& vcRequest, string& strResponse)
    {
        if (vcRequest.size() != 14)
        {
            return REC_FormatError;
        }
        /*for(int i = 1; i < 3; ++i)
        {
            if(!CBaseFunc::IsNumber(vcRequest[i]))
                return REC_ParamError;
        }*/
        int nRbtID = atoi(vcRequest[1].c_str());
        PointCoord ViaCoord;
        PointCoord GoalCoord;
        ViaCoord.Axis[0] = atof(vcRequest.at(2).c_str());
        ViaCoord.Axis[1] = atof(vcRequest.at(3).c_str());
        ViaCoord.Axis[2] = atof(vcRequest.at(4).c_str());
        GoalCoord.Axis[0] = atof(vcRequest.at(5).c_str());
        GoalCoord.Axis[1] = atof(vcRequest.at(6).c_str());
        GoalCoord.Axis[2] = atof(vcRequest.at(7).c_str());
        GoalCoord.Axis[3] = atof(vcRequest.at(8).c_str());
        GoalCoord.Axis[4] = atof(vcRequest.at(9).c_str());
        GoalCoord.Axis[5] = atof(vcRequest.at(10).c_str());
        int fixedPosure = atoi(vcRequest.at(11).c_str());
        int nMoveCType =  atoi(vcRequest.at(12).c_str());
        double nRadLen = atof(vcRequest.at(13).c_str());
        int nClientType = stoi(vcRequest[vcRequest.size() -1]);

        int nActRobotCnt=HMRC_Status_ReadActRobotCnt();
        if((nRbtID < 0) || ( nRbtID >= nActRobotCnt ))
            return REC_RobotNotExist;

        int nRet = HMRC_Status_MoveC(nRbtID, ViaCoord, GoalCoord, fixedPosure,nMoveCType,nRadLen, nClientType);
        return _GeneralRespones(vcRequest[0], nRet, strResponse);
    }


    int IF_MoveRelJ(vector<string>& vcRequest, string& strResponse)
    {
        if (vcRequest.size() != 6)
        {
            return REC_FormatError;
        }
        /*for(int i = 1; i < 5; ++i)
        {
            if(!CBaseFunc::IsNumber(vcRequest[i]))
                return REC_ParamError;
        }*/
        int nRbtID = atoi(vcRequest[1].c_str());
        int nAxisID = atoi(vcRequest[2].c_str());
        int nDirection = atoi(vcRequest[3].c_str());
        double dDistance = atof(vcRequest[4].c_str());
        int nClientType = stoi(vcRequest[vcRequest.size() -1]);

        int nActRobotCnt=HMRC_Status_ReadActRobotCnt();
        if((nRbtID < 0) || ( nRbtID >= nActRobotCnt ))
            return REC_RobotNotExist;

        int nRet = HMRC_Status_MoveRelJ(nRbtID, nAxisID, nDirection, dDistance, nClientType);
        return _GeneralRespones(vcRequest[0], nRet, strResponse);
    }
    int IF_MoveRelL(vector<string>& vcRequest, string& strResponse)
    {
        if (vcRequest.size() != 6)
        {
            return REC_FormatError;
        }
        /*for(int i = 1; i < 5; ++i)
        {
            if(!CBaseFunc::IsNumber(vcRequest[i]))
                return REC_ParamError;
        }*/
        int nRbtID = atoi(vcRequest[1].c_str());
        int nAxisID = atoi(vcRequest[2].c_str());
        int nDirection = atoi(vcRequest[3].c_str());
        double dDistance = atof(vcRequest[4].c_str());
        int nClientType = stoi(vcRequest[vcRequest.size() -1]);

        int nActRobotCnt=HMRC_Status_ReadActRobotCnt();
        if((nRbtID < 0) || ( nRbtID >= nActRobotCnt ))
            return REC_RobotNotExist;

        int nRet = HMRC_Status_MoveRelL(nRbtID, nAxisID, nDirection, dDistance, nClientType);
        return _GeneralRespones(vcRequest[0], nRet, strResponse);
    }

    int IF_StartPushBlending(vector<string>& vcRequest, string& strResponse)
    {
        if (vcRequest.size() != 3)
        {
            return REC_FormatError;
        }
        /*for(int i = 1; i < 2; ++i)
        {
            if(!CBaseFunc::IsNumber(vcRequest[i]))
                return REC_ParamError;
        }*/
        int nRbtID = atoi(vcRequest[1].c_str());
        int nClientType = stoi(vcRequest[vcRequest.size() -1]);

        int nActRobotCnt=HMRC_Status_ReadActRobotCnt();
        if((nRbtID < 0) || ( nRbtID >= nActRobotCnt ))
            return REC_RobotNotExist;

        int nRet = HMRC_Status_StartPushBlending(nRbtID, nClientType);
        return _GeneralRespones(vcRequest[0], nRet, strResponse);
    }

    
    int IF_PushBlendingPoint(vector<string>& vcRequest, string& strResponse)
    {
        if (vcRequest.size() != 14)
        {
            return REC_FormatError;
        }
        /*for(int i = 1; i < 12; ++i)
        {
            if(!CBaseFunc::IsNumber(vcRequest[i]))
                return REC_ParamError;
        }*/
        double dPostion[Max_ActualAxisCnt] = {0};

        int nRbtID = stoi(vcRequest[1]);
        dPostion[0] = stod(vcRequest[2]);
        dPostion[1] = stod(vcRequest[3]);
        dPostion[2] = stod(vcRequest[4]);
        dPostion[3] = stod(vcRequest[5]);
        dPostion[4] = stod(vcRequest[6]);
        dPostion[5] = stod(vcRequest[7]);
        double dVel = stod(vcRequest[8]);
        double dAcc = stod(vcRequest[9]);
        double dRadius = stod(vcRequest[10]);
        int nType = stoi(vcRequest[11]);
        int nPointGuid = stoi(vcRequest[12]);
        

        int nActRobotCnt=HMRC_Status_ReadActRobotCnt();
        if((nRbtID < 0) || ( nRbtID >= nActRobotCnt ))
            return REC_RobotNotExist;

        int nClientType = stoi(vcRequest[vcRequest.size() -1]);
        int nRet = HMRC_Status_PushBlendingPoint(nRbtID,
                        nClientType,dPostion,dVel,dAcc,dRadius,nType,nPointGuid);
        
        return _GeneralRespones(vcRequest[0], nRet, strResponse);
    }    

    int IF_StartBlendingMotion(vector<string>& vcRequest, string& strResponse)
    {
        if (vcRequest.size() != 3)
        {
            return REC_FormatError;
        }
        /*for(int i = 1; i < 2; ++i)
        {
            if(!CBaseFunc::IsNumber(vcRequest[i]))
                return REC_ParamError;
        }*/
        int nRbtID = atoi(vcRequest[1].c_str());
        int nClientType = stoi(vcRequest[vcRequest.size() -1]);

        int nActRobotCnt=HMRC_Status_ReadActRobotCnt();
        if((nRbtID < 0) || ( nRbtID >= nActRobotCnt ))
            return REC_RobotNotExist;

        int nRet = HMRC_Status_StartBlendingMotion(nRbtID, nClientType);
        return _GeneralRespones(vcRequest[0], nRet, strResponse);
    }

    int IF_WayPoint(vector<string>& vcRequest, string& strResponse)
    {
        if (vcRequest.size() != 22)
        {
            return REC_FormatError;
        }
        /*for(int i = 1; i < 14; ++i)
        {
            if(!CBaseFunc::IsNumber(vcRequest[i]))
                return REC_ParamError;
        }
        for(int i = 16; i < 20; ++i)
        {
            if(!CBaseFunc::IsNumber(vcRequest[i]))
                return REC_ParamError;
        }*/
        double dPostion[Max_ActualAxisCnt] = {0};
        double dAcsPostion[Max_ActualAxisCnt] = {0};

        int nRbtID = stoi(vcRequest[1]);
        dPostion[0] = stod(vcRequest[2]);
        dPostion[1] = stod(vcRequest[3]);
        dPostion[2] = stod(vcRequest[4]);
        dPostion[3] = stod(vcRequest[5]);
        dPostion[4] = stod(vcRequest[6]);
        dPostion[5] = stod(vcRequest[7]);
        dAcsPostion[0] = stod(vcRequest[8]);
        dAcsPostion[1] = stod(vcRequest[9]);
        dAcsPostion[2] = stod(vcRequest[10]);
        dAcsPostion[3] = stod(vcRequest[11]);
        dAcsPostion[4] = stod(vcRequest[12]);
        dAcsPostion[5] = stod(vcRequest[13]);
        string strTCPName = vcRequest[14];
        string strUCSName = vcRequest[15];
        double dVel = stod(vcRequest[16]);
        double dAcc = stod(vcRequest[17]);
        double dRadius = stod(vcRequest[18]);
        int nType = stoi(vcRequest[19]);//0 moveJ
        string nPointGuid = vcRequest[20];

        int nActRobotCnt=HMRC_Status_ReadActRobotCnt();
        if((nRbtID < 0) || ( nRbtID >= nActRobotCnt ))
            return REC_RobotNotExist;

        int nClientType = stoi(vcRequest[vcRequest.size() -1]);
        int nRet = HMRC_Status_WayPoint(nRbtID,
                        nClientType,dPostion,dAcsPostion,strTCPName,strUCSName,dVel,dAcc,dRadius,nType,nPointGuid);
        
        return _GeneralRespones(vcRequest[0], nRet, strResponse);

    }
    int IF_WayPointRel(vector<string>& vcRequest, string& strResponse)
    {
        if (vcRequest.size() != 14)
        {
            return REC_FormatError;
        }
        /*for(int i = 1; i < 6; ++i)
        {
            if(!CBaseFunc::IsNumber(vcRequest[i]))
                return REC_ParamError;
        }
        for(int i = 8; i < 12; ++i)
        {
            if(!CBaseFunc::IsNumber(vcRequest[i]))
                return REC_ParamError;
        }*/
        int nRbtID = stoi(vcRequest[1]);
        //MoveRelJ/MoveRelL
        int nMoveType = stoi(vcRequest[2]);
        //0:AbsPos/1:RelPos
        int nRelMoveType = stoi(vcRequest[3]);
        int nAxis = stoi(vcRequest[4]);
        double dDistance = stod(vcRequest[5]);
        string strTCPName = vcRequest[6];
        string strUCSName = vcRequest[7];
        double dVel = stod(vcRequest[8]);
        double dAcc = stod(vcRequest[9]);
        double dRadius = stod(vcRequest[10]);
        int nIsJoint = stoi(vcRequest[11]);
        string nPointGuid = vcRequest[12];

        int nActRobotCnt=HMRC_Status_ReadActRobotCnt();
        if((nRbtID < 0) || ( nRbtID >= nActRobotCnt ))
            return REC_RobotNotExist;

        int nClientType = stoi(vcRequest[vcRequest.size() -1]);
        int nRet=HMRC_Status_WayPointRel(nRbtID,
                                        nClientType,
                                        nMoveType,
                                         nRelMoveType,
                                        nAxis,
                                        dDistance,
                                        strTCPName,
                                        strUCSName,
                                        dVel,
                                        dAcc,
                                        dRadius,
                                        nIsJoint,
                                        nPointGuid);
         return _GeneralRespones(vcRequest[0], nRet, strResponse);
    }
}

