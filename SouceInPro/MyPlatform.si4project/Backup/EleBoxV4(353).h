#pragma once
#include "ElectricityBoxHAL.h"

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

class EleBoxV4:public ElectricityBoxHAL
{
public:
    EleBoxV4(int nSlaveId, string strIp,int nPort):ElectricityBoxHAL(EN_ModbusTCP)
    {
        ST_ModbusInfo stTmpModbusInfo;
        stTmpModbusInfo.enType = EN_ModbusTCP;
		
		stTmpModbusInfo.nSlaveID = nSlaveId;
        stTmpModbusInfo.strIp = strIp;
        stTmpModbusInfo.nPort = nPort;

        m_pModbus->setModbusInfo(stTmpModbusInfo);
    };
	
    EleBoxV4(string strPath):ElectricityBoxHAL(EN_ModbusRTU)
    {
        ST_ModbusInfo stTmpModbusInfo;
		
        stTmpModbusInfo.enType = EN_ModbusRTU;
        stTmpModbusInfo.strSerialPath = strPath;

        m_pModbus->setModbusInfo(stTmpModbusInfo);
    };

    virtual ~EleBoxV4();

	bool syncBuf(void) = 0;
    /*update buf of Register Buffer*/
    bool handleSTBuf(uint16_t* pBuf);

};