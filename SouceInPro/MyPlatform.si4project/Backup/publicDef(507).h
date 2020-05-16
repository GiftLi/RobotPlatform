#ifndef __PUBLICDEF_H_
#define __PUBLICDEF_H_

// #define ELEBOX_SIMULATION 1

// #ifdef ELEBOX_SIMULATION
// #define ELEBOX_MODBUS_NAME "/dev/pts/2"
// #else
// #define ELEBOX_MODBUS_NAME "/dev/ttyS1"
// #endif // ELEBOX_SIMULATION

#define ELEBOX_MODBUS_PATH "/dev/ttyS1"
#define ELEBOX_MODBUS_BAUD 115200
#define ELEBOX_MODBUS_PARITY 'N'
#define ELEBOX_MODBUS_DATABIT 8
#define ELEBOX_MODBUS_STOPBIT 1




/*
 @ ElectricityBox all only read Info
*/
typedef struct _ST_EleBoxBuf
{
    /* data */
    int nMcs_Ver_Year;
    int nMcs_Ver_Date;

    double dRbt48vVol;
    int nEStopFlg;
    int nEnableSwitch;
    int nCoilMonitorFlg;
    int nAc220vFlg;
    int nStoOnOutMonitor;
    int nDc12vPoweroffFlg;
    int nBtnOffIn;
    double dAnalogInput1;
    double dAnalogInput2;
    int nDI;
    int nCI;

    int nRetDO;
    int nRetCO;
    int nRetCh1AnalogOutMode;
    int nRetCh2AnalogOutMode;
    double dRetCh1AnalogVal;
    double dRetCh2AnalogVal;
    int nRetControlWord;

    double dRbt48vCurrent1;
    double dRbt48vCurrent2;
    double d12vVol;
    double d12vCurrent;
    double d48vInputVol;
    double d48vVol;
    double d5vVol;
    double d24vVol;
    double d24vCurrent;
    int nProStopInputFlg;
    int nEncoderCount;
    int nPowerErrorCode;

    _ST_EleBoxBuf():nMcs_Ver_Year(0),nMcs_Ver_Date(0),dRbt48vVol(0.0),
        nEStopFlg(0),nEnableSwitch(0),nCoilMonitorFlg(0),nAc220vFlg(0),
        nStoOnOutMonitor(0),nDc12vPoweroffFlg(0),nBtnOffIn(0),dAnalogInput1(0.0),
        dAnalogInput2(0.0),nDI(0),nCI(0),nRetDO(0),nRetCO(0),nRetCh1AnalogOutMode(0),
        nRetCh2AnalogOutMode(0),dRetCh1AnalogVal(0.0),dRetCh2AnalogVal(0.0),nRetControlWord(0),
        dRbt48vCurrent1(0.0),dRbt48vCurrent2(0.0),d12vVol(0.0),d12vCurrent(0.0),d48vInputVol(0.0),
        d48vVol(0.0),d5vVol(0.0),d24vVol(0.0),d24vCurrent(0.0),nProStopInputFlg(0),nEncoderCount(0),
        nPowerErrorCode(0)
        {}

}ST_EleBoxBuf;

/*
 @ EleBox Buffer index <-->func
*/
typedef enum _EN_ReadArea_BoxIndex{
    en_EleBox_McsVerYear = 0,
    en_EleBox_McsVerDate,
    en_EleBox_Rbt48vVol,
    en_EleBox_EStopFlg,
    en_EleBox_EnableSwitch,
    en_EleBox_CoilMonitorFlg = 5,
    en_EleBox_AC220vFlg,
    en_EleBox_STOOnOutMonitor,
    en_EleBox_DC12vPoweroffFlg,
    en_EleBox_BtnOffIn,
    en_EleBox_AnalogInput1 = 10,
    en_EleBox_AnalogInput2,
    en_EleBox_DI,
    en_EleBox_CI,
    en_EleBox_RetDO,
    en_EleBox_RetCO = 15,
    en_EleBox_RetCh1AnalogOutMode,
    en_EleBox_RetCh2AnalogOutMode,
    en_EleBox_RetCh1AnalogOutVal,
    en_EleBox_RetCh2AnalogOutVal,
    en_EleBox_RetControlWord = 20,
    en_EleBox_Rbt48vCur1,
    en_EleBox_Rbt48vCur2,
    en_EleBox_12vVol,
    en_EleBox_12vCur,
    en_EleBox_48vInputVol = 25,
    en_EleBox_48vVol,
    en_EleBox_5vVol,
    en_EleBox_24vVol,
    en_EleBox_24vCur,
    en_EleBox_ProStopInputFlg = 30,
    en_EleBox_EncoderCount,
    en_EleBox_PowerErrorCode,
    en_EleBox_Cnt

}ReadArea_BoxIndex;

typedef enum _EN_WriteArea_BoxIndex{
    en_EleBox_Cnt
}WriteArea_BoxIndex;

#endif // !__PUBLICDEF_H_

