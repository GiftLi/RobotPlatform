#pragma once
#include <unistd.h>
#include "EleBoxHAL.h"

/*
 @ EleBox Buffer index <-->func
*/
typedef enum _EN_ReadArea_V4{
	en_V4_StartAddr = 0,
    en_V4_McsVerYear = 0,
    en_V4_McsVerDate,
    en_V4_Rbt48vVol,
    en_V4_EStopFlg,
    en_V4_EnableSwitch,
    en_V4_CoilMonitorFlg = 5,
    en_V4_AC220vFlg,
    en_V4_STOOnOutMonitor,
    en_V4_DC12vPoweroffFlg,
    en_V4_BtnOffIn,
    en_V4_AnalogInput1 = 10,
    en_V4_AnalogInput2,
    en_V4_DI,
    en_V4_CI,
    en_V4_RetDO,
    en_V4_RetCO = 15,
    en_V4_RetCh1AnalogOutMode,
    en_V4_RetCh2AnalogOutMode,
    en_V4_RetCh1AnalogOutVal,
    en_V4_RetCh2AnalogOutVal,
    en_V4_RetControlWord = 20,
    en_V4_Rbt48vCur1,
    en_V4_Rbt48vCur2,
    en_V4_12vVol,
    en_V4_12vCur,
    en_V4_48vInputVol = 25,
    en_V4_48vVol,
    en_V4_5vVol,
    en_V4_24vVol,
    en_V4_24vCur,
    en_V4_ProStopInputFlg = 30,
    en_V4_EncoderCount,
    en_V4_PowerErrorCode,
    en_V4_Cnt

}ReadArea_V4;

typedef enum EN_WriteAreaIndexV4
{
	en_V4_ControlWord=40,
	en_V4_ResetEStop,
	en_V4_DO,
	en_V4_CO,
	en_V4_DC12,
	en_V4_CH1AnalogOutMode,
	en_V4_CH1AnalogOutValue,
	en_V4_CH2AnalogOutMode,
	en_V4_CH2AnalogOutValue
}WriteAreaIndexV4;

class EleBoxV4:public ElectricityBoxHAL
{
public:
    EleBoxV4(int nSlaveId, string strIp,int nPort):
            ElectricityBoxHAL(nSlaveId,strIp,nPort){};
	
    EleBoxV4(string strPath):ElectricityBoxHAL(strPath){};

    virtual ~EleBoxV4();

	bool electrify48vOut(void);
	bool blackout48vOut(void);
	
	int resetEStop(void);
	int resetSafetyGuradStop(void); 
	
	int setAnalogOutputMode(const int& index, const int& nMode);
    int setAnalogOutputValue(const int& index, const double& dVal);

	int setDO(const int& nIndex,const int& nVal);
    int setCO(const int& nIndex,const int& nVal);

	bool syncBuf(void);
    /*update buf of Register Buffer*/
    bool handleSTBuf(uint16_t* pBuf);

};