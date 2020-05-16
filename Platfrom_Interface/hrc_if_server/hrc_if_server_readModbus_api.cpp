#include "hrc_if_server_api.h"
#include "../public_files/global_error/hrc_public_gerrorcode.h"
#include "HRC_StatusMachine/hrc_status_api.h"
#include "HRC_Public/hrc_public_func.h"
#include "HRC_Public/hrc_public_factory/hrc_public_factory.h"


using namespace HRC_If_Server_Api;
namespace HRC_If_Server_Api
{
    int IF_ReadModbusServerBit(vector<string>& vcRequest, string& strResponse)
    {
        int nRet = REC_Successed;
        if (vcRequest.size() != 4)
        {
            return REC_FormatError;
        }

        string strName = vcRequest.at(1);
        string valName = vcRequest.at(2);

        center_trace(center_log_debug, "\n[cmd]ReadModbusServerBit: %s->%s\n",strName.c_str(),valName.c_str());

        int nState = 0;
        nRet = HRC_GET_MDB()->ReadModbusServerValue(strName,valName,nState);

        center_trace(center_log_debug, "\n[cmd]ReadModbusServerBit [ret = %d]  [value = %d]",nRet,nState);

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
        strResponse.append(CBaseFunc::i_str(nState));
        strResponse.append(IFEnd);

        return nRet;
    }
}
