#pragma once

class ElectricityBoxHAL:public BaseEleBox
{
public:
    /* the registers of only readed area info */
    vector<uint16_t> m_vRegisterBuf;
    SaftLock m_lVecLock;
    
    Modbus* m_pModbus;
    
    map<ReadArea_BoxIndex,uint16_t> m_mapReadAreaVal;
    SaftLock m_lMapLock;

    pthread_t m_syncThread;

private:
    static void* syncBufThread(void* pParam);

public:
    ElectricityBoxHAL(EN_CommunicationType enComnunicationType);
    virtual ~ElectricityBoxHAL();

    /* init ,start thread to update Data*/
    bool init(EN_CommunicationType enComnunicationType);
    /*update buf of Register Buffer*/
    bool syncVectorBuf(void* pBuf);
    int getVectorBuf(vector<uint16_t>& vecResponse);

    /*get st_elebox info (all eleBox Info)*/
    bool getEleBoxStInfo(ST_EleBoxBuf& stResponse);

    virtual void handleMapData(void) = 0;

public:
    int connectEleBox(void)=0;
    void closeEleBox(void)=0;
    bool isConnectToEleBox(void)=0;

    int electrify48vOut(void);
    bool blackout48vOut(void);
    bool is48vOut(void);

    int resetEStop(void);
    bool isEStop(void);
    bool isEStopResetSignal(void);

    int resetSafetyGuradStop(void); 
    bool isSafetyGuardStop(void);
    bool isSafetyGuradStopResetSignal(void);

    bool isRemoteSignal(void);
    bool isThreeStepSwitch(void);

    int readPower_12vInput(double& dResponseVolVal, double& dResponseCurVal);
    int readPower_24vInput(double& dResponseVolVal, double& dResponseCurVal);
    int readPower_48vInput(double& dResponseVolVal, double& dResponseCurVal);
    int readPower_48vOutput(double& dResponseVolVal, double& dResponseCurVal);

    int readAnalogInput(const int& index, double& dResponseVal);
    int readAnalogOutput(const int& index, double& dResponseVal);
    int readAnalogOutputMode(const int& index, int& nMode);
    int setAnalogOutputMode(const int& index, const int& nMode);
    int setAnalogOutputValue(const int& index, const double& dVal);

    int readDI(int& nDI0,int& nDI1,int& nDI2,int& nDI3,int& nDI4,int& nDI5,int& nDI6,int& nDI7);
    int readDO(int& nDO0,int& nDO1,int& nDO2,int& nDO3,int& nDO4,int& nDO5,int& nDO6,int& nDO7);
    int readCI(int& nCI0,int& nCI1,int& nCI2,int& nCI3,int& nCI4,int& nCI5,int& nCI6,int& nCI7);
    int readCO(int& nCO0,int& nCO1,int& nCO2,int& nCO3,int& nCO4,int& nCO5,int& nCO6,int& nCO7);

    int setDO(const int& nIndex,const int& nVal);
    int setCO(const int& nIndex,const int& nVal);

protected:
    /* Read point register value */
    bool getRegisVal(ReadArea_BoxIndex enIndex, int& nResponValue);
    bool getRegisVal(ReadArea_BoxIndex enIndex, double& dResponValue); 
    /* Write point register value */
    bool writeRegister(WriteArea_BoxIndex, const uint16_t nValue);
};