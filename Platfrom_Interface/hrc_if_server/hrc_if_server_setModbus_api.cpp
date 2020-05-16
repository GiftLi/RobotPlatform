#include "hrc_if_server_api.h"


#include "../public_files/global_error/hrc_public_gerrorcode.h"
#include "HRC_StatusMachine/hrc_status_api.h"
#include "HRC_RobotManage/hrc_robot_mgr.h"
#include "HRC_Public/hrc_public_func.h"
#include "HRC_Public/hrc_public_factory/hrc_public_factory.h"

namespace HRC_If_Server_Api
{
    int IF_SetModbusServerBit(vector<string>& vcRequest, string& strResponse)
    {
        int nRet = REC_Successed;
        if (vcRequest.size() != 5)
        {
            return REC_FormatError;
        }
        if(!CBaseFunc::IsNumber(vcRequest[3]))
            return REC_ParamError;
        string strName = vcRequest.at(1);
        string valName = vcRequest.at(2);
        int nValue = atoi(vcRequest.at(3).c_str());

        center_trace(center_log_debug, "\n[cmd]SetModbusServerBit: %s->%s[%d]\n",strName.c_str(),valName.c_str(),nValue);

        nRet = HRC_GET_MDB()->SetModbusServerValue(strName,valName,nValue);

        center_trace(center_log_debug, "\n[cmd]SetModbusServerBit return: %d\n",nRet);
        return _GeneralRespones(vcRequest[0], nRet, strResponse);
    }
}
