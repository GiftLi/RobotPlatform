#pragma once
#include <pthread.h>
#include <unistd.h>
#include "BaseEleBox.h"
#include "../Modbus/ModbusMaster.h"

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
    ElectricityBoxHAL(int nSlaveId, string strIp,int nPort);
    ElectricityBoxHAL(string strSerialPath);
    virtual ~ElectricityBoxHAL();

    /*update buf of Register Buffer*/
    virtual bool syncBuf(void) = 0;

public:
    int connectEleBox(modbus_error_recovery_mode enMode);
    void closeEleBox(void);
    bool isConnectToEleBox(void);
    
    bool is48vOut(void);
    bool isEStop(void);
    bool isEStopResetSignal(void);
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
    

    int readDI(int& nDI0,int& nDI1,int& nDI2,int& nDI3,int& nDI4,int& nDI5,int& nDI6,int& nDI7);
    int readDO(int& nDO0,int& nDO1,int& nDO2,int& nDO3,int& nDO4,int& nDO5,int& nDO6,int& nDO7);
    int readCI(int& nCI0,int& nCI1,int& nCI2,int& nCI3,int& nCI4,int& nCI5,int& nCI6,int& nCI7);
    int readCO(int& nCO0,int& nCO1,int& nCO2,int& nCO3,int& nCO4,int& nCO5,int& nCO6,int& nCO7);

	/*get st_elebox info (all eleBox Info)*/
    bool getEleBoxStInfo(ST_EleBoxBuf& stResponse);

public:
	int readCoilBits(int addr, int nb, uint8_t *dest);
	int readInputBits(int addr, int nb, uint8_t *dest);
	int readHoldingRegister(int addr, int nb, uint16_t *dest);
	int readInputRegister(int addr, int nb, uint16_t *dest);

	int writeCoilBit(int coil_addr, int status);
	int writeCoilBits(int addr, int nb, uint8_t *dest);
	int writeHoldingRegister(int reg_addr, const uint16_t value);
	int writeHoldingRegisters(int addr, int nb, const uint16_t *data);

};