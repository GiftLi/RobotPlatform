
#include "hrc_if_server_api.h"
#include "../public_files/global_error/hrc_public_gerrorcode.h"
#include "HRC_StatusMachine/hrc_status_api.h"
#include "HRC_Public/hrc_public_func.h"
#include "HRC_Public/hrc_public_factory/hrc_public_factory.h"


using namespace HRC_If_Server_Api;
namespace HRC_If_Server_Api
{
    int IF_ReadHomePosition(vector<string>& vcRequest, string& strResponse)
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

        int nActRobotCnt=HMRC_Status_ReadActRobotCnt();
        if((nRbtID < 0) || ( nRbtID >= nActRobotCnt ))
            return REC_RobotNotExist;

        MultiEndatPos stHomeMultiEndatPos;
        int nRet = HRC_GET_CFG()->HRC_Cfg_ReadHomePosition(nRbtID, stHomeMultiEndatPos);
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
            strResponse.append(CBaseFunc::i_str(stHomeMultiEndatPos.multiEndatPos[i]));
        }
        strResponse.append(IFEnd);
        return nRet;
    }

}


