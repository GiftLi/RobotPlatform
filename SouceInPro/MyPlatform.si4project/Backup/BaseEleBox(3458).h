#pragma once
#include <string>
#include "../../Platform_Public/publicDef.h"
#include "/usr/local/include/modbus/modbus.h"

using namespace std;
                
class BaseEleBox
{
public:
    BaseEleBox(){};
    virtual ~BaseEleBox(){};

    virtual int connectEleBox(modbus_error_recovery_mode enMode)=0;
    virtual void closeEleBox(void)=0;
    virtual bool isConnectToEleBox(void)=0;

    virtual bool electrify48vOut(void)=0;
    virtual bool blackout48vOut(void)=0;
    virtual bool is48vOut(void)=0;

    virtual int resetEStop(void)=0;
    virtual bool isEStop(void)=0;
    virtual bool isEStopResetSignal(void)=0;

    virtual int resetSafetyGuradStop(void)=0; 
    virtual bool isSafetyGuardStop(void)=0;
    virtual bool isSafetyGuradStopResetSignal(void)=0;

    virtual bool isRemoteSignal(void)=0;
    virtual bool isThreeStepSwitch(void)=0;

    virtual int readPower_12vInput(double& dResponseVolVal, double& dResponseCurVal)=0;
    virtual int readPower_24vInput(double& dResponseVolVal, double& dResponseCurVal)=0;
    virtual int readPower_48vInput(double& dResponseVolVal, double& dResponseCurVal)=0;
    virtual int readPower_48vOutput(double& dResponseVolVal, double& dResponseCurVal)=0;

    virtual int readAnalogInput(const int& index, double& dResponseVal)=0;
    virtual int readAnalogOutput(const int& index, double& dResponseVal)=0;
    virtual int readAnalogOutputMode(const int& index, int& nMode)=0;
    virtual int setAnalogOutputMode(const int& index, const int& nMode)=0;
    virtual int setAnalogOutputValue(const int& index, const double& dVal)=0;

    virtual int readDI(int& nDI0,int& nDI1,int& nDI2,int& nDI3,int& nDI4,int& nDI5,int& nDI6,int& nDI7)=0;
    virtual int readDO(int& nDO0,int& nDO1,int& nDO2,int& nDO3,int& nDO4,int& nDO5,int& nDO6,int& nDO7)=0;
    virtual int readCI(int& nCI0,int& nCI1,int& nCI2,int& nCI3,int& nCI4,int& nCI5,int& nCI6,int& nCI7)=0;
    virtual int readCO(int& nCO0,int& nCO1,int& nCO2,int& nCO3,int& nCO4,int& nCO5,int& nCO6,int& nCO7)=0;

    virtual int setDO(const int& nIndex,const int& nVal)=0;
    virtual int setCO(const int& nIndex,const int& nVal)=0;

	/*get st_elebox info (all eleBox Info)*/
    virtual bool getEleBoxStInfo(ST_EleBoxBuf& stResponse)=0;
};

