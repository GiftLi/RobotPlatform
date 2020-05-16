#include "EleBoxHAL.h"

ElectricityBoxHAL::ElectricityBoxHAL(int nSlaveId, string strIp,int nPort)
{
	m_pModbus = new Modbus_TCP_Client(nSlaveId, strIp, nPort);

	if(nullptr == m_pModbus)
	{
		printf("Init Error in ElectricityBoxHAL()\n");
		return;
	}
	
	/* 创建线程 */
	pthread_create(&m_syncThread, nullptr, syncBufThread, this);
}

ElectricityBoxHAL::ElectricityBoxHAL(string strSerialPath)
{
	m_pModbus = new Modbus_RTU_Master(strSerialPath);

	if(nullptr == m_pModbus)
	{
		printf("Init Error in ElectricityBoxHAL()\n");
		return;
	}
	
	/* 创建线程 */
	pthread_create(&m_syncThread, nullptr, syncBufThread, this);
}

ElectricityBoxHAL::~ElectricityBoxHAL()
{
	if(isConnectToEleBox())
	{
		closeEleBox();
	}
	
}


void* ElectricityBoxHAL::syncBufThread(void* pParam)
{
	ElectricityBoxHAL* pThis = (ElectricityBoxHAL*)pParam;
	
	if (pThis!=nullptr)
    {
        pThis->SyncHandle();
    }
	
    return nullptr;	
}


void ElectricityBoxHAL::SyncHandle()
{
	__useconds_t ms_10 = 10*1000;

	while(true)
	{
		while(isConnectToEleBox())
	    {
	        if(!syncBuf())
	        {
	            break;
	        }
			
	        usleep(ms_10);
	    }

		usleep(ms_10 * 50);
	}
	
}

int ElectricityBoxHAL::connectEleBox(modbus_error_recovery_mode enMode)
{
	return m_pModbus->connect(enMode);
}

void ElectricityBoxHAL::closeEleBox(void)
{
	return m_pModbus->close();
}

bool ElectricityBoxHAL::isConnectToEleBox(void)
{
	return m_pModbus->AskIsConnect();
}

bool ElectricityBoxHAL::is48vOut(void)
{
	AutoSaftMutex stBufLock(&m_lBufLock);

	if(m_stBufInfo.db48VOUT_Voltag > 47.0
		&& m_stBufInfo.db48VOUT_Voltag < 49.0)
	{
		return true;
	}

	return false;
	
}

bool ElectricityBoxHAL::isEStop(void)
{
	AutoSaftMutex stBufLock(&m_lBufLock);

	return m_stBufInfo.nEmergencyStop;
	
}

bool ElectricityBoxHAL::isEStopResetSignal(void)
{
	AutoSaftMutex stBufLock(&m_lBufLock);

	return m_stBufInfo.nResetSignal_EmergencyStop;
}


bool ElectricityBoxHAL::isSafetyGuardStop(void)
{
	AutoSaftMutex stBufLock(&m_lBufLock);

	return m_stBufInfo.nSafetyGuardStop;
}

bool ElectricityBoxHAL::isSafetyGuradStopResetSignal(void)
{
	AutoSaftMutex stBufLock(&m_lBufLock);

	return m_stBufInfo.nResetSignal_SafetyGuardStop;
}


bool ElectricityBoxHAL::isRemoteSignal(void)
{
	AutoSaftMutex stBufLock(&m_lBufLock);

	return m_stBufInfo.nRemoteSignal;
}

bool ElectricityBoxHAL::isThreeStepSwitch(void)
{
	AutoSaftMutex stBufLock(&m_lBufLock);

	return m_stBufInfo.nThreeStageSwitch_Signal;
}


int ElectricityBoxHAL::readPower_12vInput(double& dResponseVolVal, double& dResponseCurVal)
{
	AutoSaftMutex stBufLock(&m_lBufLock);

	dResponseVolVal = m_stBufInfo.db12V_Voltag;
	dResponseCurVal = m_stBufInfo.db12V_Current;

	return 0;
}

int ElectricityBoxHAL::readPower_24vInput(double& dResponseVolVal, double& dResponseCurVal)
{
	AutoSaftMutex stBufLock(&m_lBufLock);

	dResponseVolVal = m_stBufInfo.db24V_Voltag;
	dResponseCurVal = m_stBufInfo.db24V_Current;

	return 0;
}

int ElectricityBoxHAL::readPower_48vInput(double& dResponseVolVal, double& dResponseCurVal)
{
	AutoSaftMutex stBufLock(&m_lBufLock);

	dResponseVolVal = m_stBufInfo.db48VIN_Voltag;
	dResponseCurVal = m_stBufInfo.db48VIN_Current;

	return 0;
}

int ElectricityBoxHAL::readPower_48vOutput(double& dResponseVolVal, double& dResponseCurVal)
{
	AutoSaftMutex stBufLock(&m_lBufLock);

	dResponseVolVal = m_stBufInfo.db48VOUT_Voltag;
	dResponseCurVal = m_stBufInfo.db48VOUT_Voltag;

	return 0;
}


int ElectricityBoxHAL::readAnalogInput(const int& index, double& dResponseVal)
{
	if(index > en_AnalogIO_Number 
		|| index < 1)
	{
		return -1;
	}

	AutoSaftMutex stBufLock(&m_lBufLock);
		
	dResponseVal = m_stBufInfo.nAnalogIN[index - 1];

	return 0;
}

int ElectricityBoxHAL::readAnalogOutput(const int& index, double& dResponseVal)
{
	if(index > en_AnalogIO_Number 
		|| index < 1)
	{
		return -1;
	}
		
	AutoSaftMutex stBufLock(&m_lBufLock);

	dResponseVal = m_stBufInfo.dbAnalogOut[index - 1];

	return 0;
}

int ElectricityBoxHAL::readAnalogOutputMode(const int& index, int& nMode)
{
	if(index > en_AnalogIO_Number 
		|| index < 1)
	{
		return -1;
	}
		
	AutoSaftMutex stBufLock(&m_lBufLock);

	nMode = m_stBufInfo.nAnalogOutMode[index - 1];

	return 0;
}

int ElectricityBoxHAL::readDI(int& nDI0,int& nDI1,int& nDI2,int& nDI3,int& nDI4,int& nDI5,int& nDI6,int& nDI7)
{
	AutoSaftMutex stBufLock(&m_lBufLock);

	nDI0 = m_stBufInfo.nDI[0];
	nDI1 = m_stBufInfo.nDI[1];
	nDI2 = m_stBufInfo.nDI[2];
	nDI3 = m_stBufInfo.nDI[3];
	nDI4 = m_stBufInfo.nDI[4];
	nDI5 = m_stBufInfo.nDI[5];
	nDI6 = m_stBufInfo.nDI[6];
	nDI7 = m_stBufInfo.nDI[7];

	return 0;
}

int ElectricityBoxHAL::readDO(int& nDO0,int& nDO1,int& nDO2,int& nDO3,int& nDO4,int& nDO5,int& nDO6,int& nDO7)
{
	AutoSaftMutex stBufLock(&m_lBufLock);

	nDO0 = m_stBufInfo.nDO[0];
	nDO1 = m_stBufInfo.nDO[1];
	nDO2 = m_stBufInfo.nDO[2];
	nDO3 = m_stBufInfo.nDO[3];
	nDO4 = m_stBufInfo.nDO[4];
	nDO5 = m_stBufInfo.nDO[5];
	nDO6 = m_stBufInfo.nDO[6];
	nDO7 = m_stBufInfo.nDO[7];

	return 0;
}

int ElectricityBoxHAL::readCI(int& nCI0,int& nCI1,int& nCI2,int& nCI3,int& nCI4,int& nCI5,int& nCI6,int& nCI7)
{
	AutoSaftMutex stBufLock(&m_lBufLock);

	nCI0 = m_stBufInfo.nSI[0];
	nCI1 = m_stBufInfo.nSI[1];
	nCI2 = m_stBufInfo.nSI[2];
	nCI3 = m_stBufInfo.nSI[3];
	nCI4 = m_stBufInfo.nSI[4];
	nCI5 = m_stBufInfo.nSI[5];
	nCI6 = m_stBufInfo.nSI[6];
	nCI7 = m_stBufInfo.nSI[7];

	return 0;
}

int ElectricityBoxHAL::readCO(int& nCO0,int& nCO1,int& nCO2,int& nCO3,int& nCO4,int& nCO5,int& nCO6,int& nCO7)
{
	AutoSaftMutex stBufLock(&m_lBufLock);

	nCO0 = m_stBufInfo.nSO[0];
	nCO1 = m_stBufInfo.nSO[1];
	nCO2 = m_stBufInfo.nSO[2];
	nCO3 = m_stBufInfo.nSO[3];
	nCO4 = m_stBufInfo.nSO[4];
	nCO5 = m_stBufInfo.nSO[5];
	nCO6 = m_stBufInfo.nSO[6];
	nCO7 = m_stBufInfo.nSO[7];

	return 0;
}

/*get st_elebox info (all eleBox Info)*/
bool ElectricityBoxHAL::getEleBoxStInfo(ST_EleBoxBuf& stResponse)
{
	AutoSaftMutex stBufLock(&m_lBufLock);

	stResponse = m_stBufInfo;

	return 0;
}


int ElectricityBoxHAL::readCoilBits(int addr, int nb, uint8_t *dest)
{
	return m_pModbus->readCoilBits(addr, nb,dest);
}

int ElectricityBoxHAL::readInputBits(int addr, int nb, uint8_t *dest)
{
	return m_pModbus->readInputBits(addr, nb, dest);
}

int ElectricityBoxHAL::readHoldingRegister(int addr, int nb, uint16_t *dest)
{
	return m_pModbus->readHoldingRegister(addr, nb, dest);
}

int ElectricityBoxHAL::readInputRegister(int addr, int nb, uint16_t *dest)
{
	return m_pModbus->readInputRegister(addr, nb, dest);
}


int ElectricityBoxHAL::writeCoilBit(int coil_addr, int status)
{
	return m_pModbus->writeCoilBit(coil_addr, status);
}

int ElectricityBoxHAL::writeCoilBits(int addr, int nb, uint8_t *dest)
{
	return m_pModbus->writeCoilBits(addr, nb, dest);
}

int ElectricityBoxHAL::writeHoldingRegister(int reg_addr, const uint16_t value)
{
	return m_pModbus->writeHoldingRegister(reg_addr, value);
}

int ElectricityBoxHAL::writeHoldingRegisters(int addr, int nb, const uint16_t *data)
{
	return m_pModbus->writeHoldingRegisters(addr, nb, data);
}


