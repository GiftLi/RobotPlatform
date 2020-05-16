#include "EleBoxHAL.h"

ElectricityBoxHAL::ElectricityBoxHAL(EN_CommunicationType enType)
{
	if(enType == EN_ModbusRTU)
	{
		m_pModbus = new Modbus_RTU_Master();
	}
	else if(enType == EN_ModbusTCP)
	{
		m_pModbus = new Modbus_TCP_Client();
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
		while(!isConnectToEleBox())
	    {
	        if(handleSTBuf()!=0)
	        {
	            break;
	        }
			
	        usleep(ms_10);
	    }

		usleep(ms_10 * 50);
	}
	
}

int ElectricityBoxHAL::connectEleBox(void)
{
	return m_pModbus->connect();
}

void ElectricityBoxHAL::closeEleBox(void)
{
	return m_pModbus->close();
}

bool ElectricityBoxHAL::isConnectToEleBox(void)
{
	return m_pModbus->AskIsConnect();
}

int ElectricityBoxHAL::electrify48vOut(void)
{
	
}
bool ElectricityBoxHAL::blackout48vOut(void)
{

}

bool ElectricityBoxHAL::is48vOut(void)
{

}


int ElectricityBoxHAL::resetEStop(void)
{

}

bool ElectricityBoxHAL::isEStop(void)
{

}

bool ElectricityBoxHAL::isEStopResetSignal(void)
{

}


int ElectricityBoxHAL::resetSafetyGuradStop(void)
{

}

bool ElectricityBoxHAL::isSafetyGuardStop(void)
{

}

bool ElectricityBoxHAL::isSafetyGuradStopResetSignal(void)
{

}


bool ElectricityBoxHAL::isRemoteSignal(void)
{

}

bool ElectricityBoxHAL::isThreeStepSwitch(void)
{

}


int ElectricityBoxHAL::readPower_12vInput(double& dResponseVolVal, double& dResponseCurVal)
{

}

int ElectricityBoxHAL::readPower_24vInput(double& dResponseVolVal, double& dResponseCurVal)
{

}

int ElectricityBoxHAL::readPower_48vInput(double& dResponseVolVal, double& dResponseCurVal)
{

}

int ElectricityBoxHAL::readPower_48vOutput(double& dResponseVolVal, double& dResponseCurVal)
{

}


int ElectricityBoxHAL::readAnalogInput(const int& index, double& dResponseVal)
{

}

int ElectricityBoxHAL::readAnalogOutput(const int& index, double& dResponseVal)
{

}

int ElectricityBoxHAL::readAnalogOutputMode(const int& index, int& nMode)
{

}

int ElectricityBoxHAL::setAnalogOutputMode(const int& index, const int& nMode)
{

}

int ElectricityBoxHAL::setAnalogOutputValue(const int& index, const double& dVal)
{

}


int ElectricityBoxHAL::readDI(int& nDI0,int& nDI1,int& nDI2,int& nDI3,int& nDI4,int& nDI5,int& nDI6,int& nDI7)
{

}

int ElectricityBoxHAL::readDO(int& nDO0,int& nDO1,int& nDO2,int& nDO3,int& nDO4,int& nDO5,int& nDO6,int& nDO7)
{

}

int ElectricityBoxHAL::readCI(int& nCI0,int& nCI1,int& nCI2,int& nCI3,int& nCI4,int& nCI5,int& nCI6,int& nCI7)
{

}

int ElectricityBoxHAL::readCO(int& nCO0,int& nCO1,int& nCO2,int& nCO3,int& nCO4,int& nCO5,int& nCO6,int& nCO7)
{

}


int ElectricityBoxHAL::setDO(const int& nIndex,const int& nVal)
{

}

int ElectricityBoxHAL::setCO(const int& nIndex,const int& nVal)
{

}


/*get st_elebox info (all eleBox Info)*/
bool ElectricityBoxHAL::getEleBoxStInfo(ST_EleBoxBuf& stResponse)
{

}


int ElectricityBoxHAL::readCoilBits(int addr, int nb, uint8_t *dest)
{

}

int ElectricityBoxHAL::readInputBits(int addr, int nb, uint8_t *dest)
{

}

int ElectricityBoxHAL::readHoldingRegister(int addr, int nb, uint16_t *dest)
{

}

int ElectricityBoxHAL::readInputRegister(int addr, int nb, uint16_t *dest)
{

}


int ElectricityBoxHAL::writeCoilBits(int coil_addr, int status)
{

}

int ElectricityBoxHAL::writeCoilBits(int addr, int nb, uint8_t *dest)
{

}

int ElectricityBoxHAL::writeHoldingRegister(int reg_addr, const uint16_t value)
{

}

int ElectricityBoxHAL::writeHoldingRegister(int addr, int nb, const uint16_t *data)
{

}


