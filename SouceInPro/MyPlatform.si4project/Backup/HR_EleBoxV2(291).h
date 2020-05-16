#ifndef _HR_ElectricBoxHansV2_H
#define _HR_ElectricBoxHansV2_H

#include "HR_ElectricBoxHAL.h"


#define REGISTER_START_ADDR 0


typedef enum _EN_ReadAreaIndexV2{
	en_V2_RetDO = 0,
	en_V2_RetControlWord,
	en_V2_RetDI,
	en_V2_SaftyIO,
	en_V2_48vActVol ,
	en_V2_5vVol = 5,
	en_V2_AnalogInput2,
	en_V2_AnalogInput1 ,
	en_V2_24vVol ,
	en_V2_24vCur ,
	en_V2_12vVol , // 10
	en_V2_12vCur,
	en_V2_Rbt48vCur1 ,
	en_V2_Rbt48vCur2 ,
	en_V2_Rbt48vVol ,
	en_V2_48vInputVol ,  //15
	en_V2_AC220MISSFLAG,
	en_V2_DC12VFlg,
	en_V2_Ex24vDetect,
	en_V2_DC12V,
	en_V2_EStopResetStatus , //20
	en_V2_EStopShareOut ,
	en_V2_RetCI ,
	en_V2_RetCO , //23
	en_V2_KeySwitch ,
	en_V2_ThreeEnableSwitch ,
	en_V2_EStopStutasCheck ,
	en_V2_CoilSignal ,
	en_V2_EStopShare ,
	en_V2_RetCh1AnalogOutVal , //29
	en_V2_RetCh2AnalogOutVal ,
	en_V2_RetAnalogOutMode ,
	en_V2_STO ,
	en_V2_EStopControl ,
	en_V2_EStopIn ,
	en_V2_CoilSignal3 ,
	en_V2_CoilSignal4 ,
	en_V2_EStopResetDetect ,
	en_V2_ProStopInput0 ,
	en_V2_ProStopReset ,
	en_V2_ProStopInput1 ,
	en_V2_EStopFUZHU ,
	en_V2_CiolSignal2 ,
	en_V2_Cnt

}ReadAreaIndexV2;

typedef enum EN_WriteAreaIndexV2
{
	en_V2_ControlWord=1,
	en_V2_ResetEStop=33,
	en_V2_DO=0,
    en_V2_CO=23,
	en_V2_Ch1AnalogOutVal=29 , //29
	en_V2_Ch2AnalogOutVal =30,
	en_V2_AnalogOutMode=31
}WriteAreaIndexV2;

class HR_ElectricBoxHansV2 : public HR_ElectricBoxHAL
{
private:
    /* data */
public:
    HR_ElectricBoxHansV2(bool bErrorRecovryLINK,int nSlave,const char *device, int baud, char parity,int data_bit, int stop_bit);
    ~HR_ElectricBoxHansV2();

public:
    int Electrify48VOUT();
    int Blackout48VOUT();
    int ResetEmergencyStop();
    int ResetSafetyGuradStop();

    int SetAnalogOUT_Mode(int nIndex,int nAnalogMode);
    int SetAnalogOUT_Value(int nIndex,double dbAnalogOUT);
    int SetDO(int nIndex,int nVal);
    int SetSO(int nIndex,int nVal);

	int HandleSTData(const uint16_t* pBuf);
protected:
    bool TestConnect();
    int Sync();


};

#endif //
