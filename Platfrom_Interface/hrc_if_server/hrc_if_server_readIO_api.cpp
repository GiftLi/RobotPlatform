
#include "hrc_if_server_api.h"
#include "../public_files/global_error/hrc_public_gerrorcode.h"
#include "HRC_StatusMachine/hrc_status_api.h"
#include "HRC_Public/hrc_public_func.h"
#include "HRC_Public/hrc_public_factory/hrc_public_factory.h"

namespace HRC_If_Server_Api
{
    int IF_ReadDI(vector<string>& vcRequest, string& strResponse)
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
        int nBit = atoi(vcRequest[1].c_str());
        int nState = 0;

        nRet = HRC_GET_MC()->SysBoard_ReadSpeSerialDI(0,nBit, nState);
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


    int IF_ReadDO(vector<string>& vcRequest, string& strResponse)
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
        int nBit = atoi(vcRequest[1].c_str());
        int nState = 0;

        nRet = HRC_GET_MC()->SysBoard_ReadSpeSerialDO(0,nBit, nState);
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

    
    int IF_ReadCI(vector<string>& vcRequest, string& strResponse)
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
        int nBit = atoi(vcRequest[1].c_str());// + 8;
        int nState = 0;

        nRet =  HRC_GET_MC()->SysBoard_ReadSpeConfigDI(0,nBit,nState);
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


    int IF_ReadCO(vector<string>& vcRequest, string& strResponse)
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
        int nBit = atoi(vcRequest[1].c_str());// + 8;
        int nState = 0;

        nRet = HRC_GET_MC()->SysBoard_ReadSpeConfigDO(0,nBit,nState);
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


   
    int IF_ReadC1AO(vector<string>& vcRequest, string& strResponse)
    {
        int nRet = REC_Successed;
        if (vcRequest.size() != 2)
        {
            return REC_FormatError;
        }
        double dState = 0;

        nRet = HRC_GET_MC()->SysBoard_ReadCh1AnalogOutValue(0,dState);
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
        strResponse.append(CBaseFunc::d_str(dState));
        strResponse.append(IFEnd);
        return nRet;
    }

    int IF_ReadC2AO(vector<string>& vcRequest, string& strResponse)
    {
        int nRet = REC_Successed;
        if (vcRequest.size() != 2)
        {
            return REC_FormatError;
        }

        double dState = 0;

        nRet = HRC_GET_MC()->SysBoard_ReadCh2AnalogOutValue(0,dState);
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
        strResponse.append(CBaseFunc::d_str(dState));
        strResponse.append(IFEnd);
        return nRet;
    }


    int IF_ReadC1AI(vector<string>& vcRequest, string& strResponse)
    {
        int nRet = REC_Successed;
        if (vcRequest.size() != 2)
        {
            return REC_FormatError;
        }
        
        double dState = 0;

        nRet = HRC_GET_MC()->SysBoard_ReadCh1AnalogInValue(0,dState);
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
        strResponse.append(CBaseFunc::d_str(dState));
        strResponse.append(IFEnd);
        return nRet;
    }

    int IF_ReadC2AI(vector<string>& vcRequest, string& strResponse)
    {
        int nRet = REC_Successed;
        if (vcRequest.size() != 2)
        {
            return REC_FormatError;
        }

        double dState = 0;

        nRet = HRC_GET_MC()->SysBoard_ReadCh2AnalogInValue(0,dState);
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
        strResponse.append(CBaseFunc::d_str(dState));
        strResponse.append(IFEnd);
        return nRet;
    }

    int IF_ReadEI(vector<string>& vcRequest, string& strResponse)
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
       int nBit = atoi(vcRequest[2].c_str());
       int nState = 0;

       nRet = HRC_GET_MC()->ReadEndDIState(0,nBit,nState);
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

    int IF_ReadEO(vector<string>& vcRequest, string& strResponse)
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
       int nBit = atoi(vcRequest[2].c_str());
       int nState = 0;

       nRet = HRC_GET_MC()->ReadEndDOState(0,nBit,nState);
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


    int IF_ReadEAI1(vector<string>& vcRequest, string& strResponse)
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
       double dState=0;
       int nRbtID = atoi(vcRequest[1].c_str());
       int nClientType = stoi(vcRequest[vcRequest.size() -1]);
       int nActRobotCnt=HMRC_Status_ReadActRobotCnt();
       if((nRbtID < 0) || ( nRbtID >= nActRobotCnt ))
           return REC_RobotNotExist;
       nRet = HRC_GET_MC()->ReadEndA1(nRbtID,dState);
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
       strResponse.append(CBaseFunc::d_str(dState));
       strResponse.append(IFEnd);
       return nRet;
    }


    int IF_ReadEAI2(vector<string>& vcRequest, string& strResponse)
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
       double dState = 0;
       int nRbtID = atoi(vcRequest[1].c_str());
       int nClientType = stoi(vcRequest[vcRequest.size() -1]);
       int nActRobotCnt=HMRC_Status_ReadActRobotCnt();
       if((nRbtID < 0) || ( nRbtID >= nActRobotCnt ))
           return REC_RobotNotExist;
       nRet = HRC_GET_MC()->ReadEndA2(nRbtID,dState);
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
       strResponse.append(CBaseFunc::d_str(dState));
       strResponse.append(IFEnd);
       return nRet;
    }
    

    /*

    int IF_ReadAnalogInput(vector<string>& vcRequest, string& strResponse)
    {
        int nRet = REC_Successed;
        if (vcRequest.size() != 4)
        {
            return REC_FormatError;
        }
        int nRbtID = atoi(vcRequest[1].c_str());
        int nAnalogIndex = atoi(vcRequest[2].c_str());
        double dState = 0;
        nRet = HMRC_Status_ReadAnalogInput(nRbtID, nAnalogIndex, dState);
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
        strResponse.append(CBaseFunc::d_str(dState));
        strResponse.append(IFEnd);
        return nRet;
    }
    int IF_ReadInIOState(vector<string>& vcRequest, string& strResponse)
	{
		int nRet = REC_Successed;
		if (vcRequest.size() != 4)
		{
			return REC_FormatError;
		}
		int nRbtID = atoi(vcRequest[1].c_str());
		int nIndex = atoi(vcRequest[2].c_str());
		int nState = 0;
		nRet = HMRC_Status_ReadInIOState(nRbtID, nIndex, nState);
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

    int IF_ReadControlInIOState(vector<string>& vcRequest, string& strResponse)
	{
		int nRet = REC_Successed;
		if (vcRequest.size() != 4)
		{
			return REC_FormatError;
		}
		int nRbtID = atoi(vcRequest[1].c_str());
		int nIndex = atoi(vcRequest[2].c_str());
		int nState = 0;
		nRet = HMRC_Status_ReadControlInIOState(nRbtID, nIndex, nState);
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
    int IF_ReadOutIOState(vector<string>& vcRequest, string& strResponse)
    {
        int nRet = REC_Successed;
        if (vcRequest.size() != 4)
        {
            return REC_FormatError;
        }
        int nRbtID = atoi(vcRequest[1].c_str());
        int nIndex = atoi(vcRequest[2].c_str());
        int nState = 0;
        nRet = HMRC_Status_ReadOutIOState(nRbtID, nIndex, nState);
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
    int IF_ReadSerialAnalog(vector<string>& vcRequest, string& strResponse)
    {
        int nRet = REC_Successed;
        if (vcRequest.size() != 3)
        {
            return REC_FormatError;
        }
        int nIndex = atoi(vcRequest[1].c_str());
        double nVal = 0;
        nRet = HMRC_Status_ReadSerialAnalog(nIndex, nVal);
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
        strResponse.append(CBaseFunc::d_str(nVal));
        strResponse.append(IFEnd);
        return nRet;
    }

    */
}
