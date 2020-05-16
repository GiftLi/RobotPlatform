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
	
    m_bConnectFlg = readHoldingRegister(0,1,&dest)==0 ? true : false;

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

    reutrn modbus_read_registers(m_pModbus, addr, nb, dest);

}

int BaseModbus::readInputRegister(int addr, int nb, uint16_t *dest)
{
	if(nullptr == m_pModbus)
    {
        return -1;
    }
	
	reutrn modbus_read_input_registers(m_pModbus, addr, nb, dest);
}


int BaseModbus::writeCoilBits(int coil_addr, int status)
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
        return false;
    }

    return true;
}

int BaseModbus::writeHoldingRegister(int addr, int nb, const uint16_t *data)
{
	if(nullptr == m_pModbus)
    {
        return -1;
    }
}


