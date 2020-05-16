#pragma once
#include "ModbusMaster.h"
#include <pthread.h>



/*
 @ ElectricityBox all only read Info
*/
typedef struct _ST_EleBoxBuf
{
    /* data */
    int nVerYear;
    int nVerDate;
    int nEmergencyStop;
    int nSafetyGuardStop;
    int nResetSignal_EmergencyStop;
    int nResetSignal_SafetyGuardStop;
    int nRemoteSignal;
    int nThreeStageSwitch_Signal;
    int nDI[en_IO_Number];
    int nDO[en_IO_Number];
    int nSI[en_IO_Number];
    int nSO[en_IO_Number];
    
    int nAnalogIN[en_AnalogIO_Number];
    int nAnalogOutMode[en_AnalogIO_Mode_Number];
    double dbAnalogOut[en_AnalogIO_Number];
    
    double db12V_Voltag;
    double db12V_Current;
    double db24V_Voltag;
    double db24V_Current;
    double db48VIN_Voltag;
    double db48VIN_Current;
    double db48VOUT_Voltag;
    double db48VOUT_Current;

    _ST_EleBoxBuf():nVerYear(0),nVerDate(0),nEmergencyStop(0),nSafetyGuardStop(0),
        nResetSignal_EmergencyStop(0),nResetSignal_SafetyGuardStop(0),
        nRemoteSignal(0),nThreeStageSwitch_Signal(0.0),db12V_Voltag(0.0),
        db12V_Current(0),db24V_Voltag(0),db24V_Current(0),db48VIN_Voltag(0),
        db48VIN_Current(0),db48VOUT_Voltag(0),db48VOUT_Current(0.0)
    {
    	memset(nDI,0,sizeof(int)*en_IO_Number);
		memset(nDO,0,sizeof(int)*en_IO_Number);
		memset(nSI,0,sizeof(int)*en_IO_Number);
		memset(nSO,0,sizeof(int)*en_IO_Number);

		memset(nAnalogIN,0,sizeof(int)*en_AnalogIO_Number);
		memset(nAnalogOutMode,0,sizeof(int)*en_AnalogIO_Mode_Number);
		memset(dbAnalogOut,0,sizeof(int)*en_AnalogIO_Number);
    }

}ST_EleBoxBuf;


class ElectricityBoxHAL:public BaseEleBox
{
public:
	ST_EleBoxBuf m_stBufInfo;
	SaftLock m_lBufLock;

private:
	BaseModbus* m_pModbus;
	pthread_t m_syncThread;
	
    static void* syncBufThread(void* pParam);
	void SyncHandle();

public:
    ElectricityBoxHAL(EN_CommunicationType enType);
    virtual ~ElectricityBoxHAL();

    /*update buf of Register Buffer*/
    virtual bool syncBuf(void) = 0;

public:
    int connectEleBox(void);
    void closeEleBox(void);
    bool isConnectToEleBox(void);

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

	/*get st_elebox info (all eleBox Info)*/
    bool getEleBoxStInfo(ST_EleBoxBuf& stResponse);

public:
	int readCoilBits(int addr, int nb, uint8_t *dest);
	int readInputBits(int addr, int nb, uint8_t *dest);
	int readHoldingRegister(int addr, int nb, uint16_t *dest);
	int readInputRegister(int addr, int nb, uint16_t *dest);

	int writeCoilBits(int coil_addr, int status);
	int writeCoilBits(int addr, int nb, uint8_t *dest);
	int writeHoldingRegister(int reg_addr, const uint16_t value);
	int writeHoldingRegister(int addr, int nb, const uint16_t *data);

};