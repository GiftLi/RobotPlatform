#include "BaseModbus.h"

void BaseModbus::close(void)
{
	AutoSaftMutex modbusLock(&m_lModbusLock);

    if(m_bConnectFlg)
    {
        modbus_close(m_pModbus);
        m_bConnectFlg = false;
    }

    modbus_free(m_pModbus);

    m_pModbus = nullptr;
}

void BaseModbus::setModbusInfo(const ST_ModbusInfo& st_ModbusInfo)
{
	m_stModbusInfo = st_ModbusInfo;
}

void BaseModbus::getModbusInfo(ST_ModbusInfo& st_ModbusInfo)
{
	st_ModbusInfo = m_stModbusInfo;
}

bool BaseModbus::AskIsConnect(void)
{
	uint16_t dest=0;
	
    m_bConnectFlg = readHoldingRegister(0,1,&dest) < 0 ? false : true;

	return m_bConnectFlg;
}

int BaseModbus::getErrorInfo(string& strResponse)
{
	strResponse = modbus_strerror(errno);

    return 0;
}

int BaseModbus::readCoilBits(int addr, int nb, uint8_t *dest)
{
	AutoSaftMutex modbusLock(&m_lModbusLock);

	if(nullptr == m_pModbus)
    {
        return -1;
    }
	
	return modbus_read_bits(m_pModbus, addr, nb, dest);
}

int BaseModbus::readInputBits(int addr, int nb, uint8_t *dest)
{
	AutoSaftMutex modbusLock(&m_lModbusLock);

	if(nullptr == m_pModbus)
    {
        return -1;
    }
	
	return modbus_read_input_bits(m_pModbus, addr, nb, dest);
}

int BaseModbus::readHoldingRegister(int addr, int nb, uint16_t *dest)
{
	AutoSaftMutex modbusLock(&m_lModbusLock);

    if(nullptr == m_pModbus)
    {
        return -1;
    }

	struct timeval    tv;
	gettimeofday(&tv,nullptr);
	__time_t nSec = tv.tv_sec;
	__suseconds_t mUsec = nSec*1000 + tv.tv_usec/1000;

   int ret = modbus_read_registers(m_pModbus, addr, nb, dest);

	gettimeofday(&tv,nullptr);
	nSec = tv.tv_sec;
	mUsec = (nSec*1000 + tv.tv_usec/1000) - mUsec;
	char pBuf[125] = {0};
	sprintf(pBuf,"%ld",mUsec);
	m_log << pBuf << endl;
   
    if(ret < 0)
    {
		if(errno == 110)
		{
		    m_logTimeout << pBuf << endl;
		}
		else if(errno == 112345691){
		    m_logInvalid << pBuf << endl;
		}        else if(errno == 112345690){
		   m_logCRC << pBuf << endl;
		}
		else if(errno == 112345695){
		    m_logSlave << pBuf << endl;
		}
		
		printf("readHoldingRegister Error: [erron = %d]  [ErrorInfo : %s]\n",errno,modbus_strerror(errno));

	}

    return ret;

}

int BaseModbus::readInputRegister(int addr, int nb, uint16_t *dest)
{
	if(nullptr == m_pModbus)
    {
        return -1;
    }
	
	return modbus_read_input_registers(m_pModbus, addr, nb, dest);
}


int BaseModbus::writeCoilBit(int coil_addr, int status)
{
	if(nullptr == m_pModbus)
    {
        return -1;
    }

	return 0;
}

int BaseModbus::writeCoilBits(int addr, int nb, uint8_t *dest)
{
	if(nullptr == m_pModbus)
    {
        return -1;
    }
	
	return 0;
}

int BaseModbus::writeHoldingRegister(int reg_addr, const uint16_t value)
{
	if(nullptr == m_pModbus)
    {
        return -1;
    }
	
	int ret = modbus_write_register(m_pModbus, reg_addr, value);

    if(ret < 0)
    {
    	printf("writeHoldingRegister Error: [erron = %d]  [ErrorInfo : %s]\n",errno,modbus_strerror(errno));
		
        return -1;
    }

    return 0;
}

int BaseModbus::writeHoldingRegisters(int addr, int nb, const uint16_t *data)
{
	if(nullptr == m_pModbus)
    {
        return -1;
    }
}


