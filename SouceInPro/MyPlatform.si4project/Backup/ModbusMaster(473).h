#pragma once
#include "BaseModbus.h"

class Modbus_RTU_Master:public BaseModbus
{
public:
    Modbus_RTU_Master()
    {
    	m_stModbusInfo.enType = EN_ModbusRTU;
    }
    Modbus_RTU_Master(string strSerialPath)
    {
    	m_stModbusInfo.enType = EN_ModbusRTU;
		m_stModbusInfo.strDeviceName = strSerialPath;
    }

    virtual ~Modbus_RTU_Master(){}

    bool connect(void);
};
