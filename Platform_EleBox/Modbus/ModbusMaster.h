#pragma once
#include <string.h>
#include "BaseModbus.h"


class Modbus_RTU_Master:public BaseModbus
{
public:
    Modbus_RTU_Master(string strSerialPath)
    {
        ST_ModbusInfo stTmpModbusInfo;
		
        stTmpModbusInfo.enType = EN_ModbusRTU;
        stTmpModbusInfo.strSerialPath = strSerialPath;

        setModbusInfo(stTmpModbusInfo);

        m_pModbus = modbus_new_rtu(m_stModbusInfo.strSerialPath.c_str(), 
                    m_stModbusInfo.nBaud, m_stModbusInfo.cParity,
                    m_stModbusInfo.nDataBit, m_stModbusInfo.nStopBit);
    
        if(nullptr == m_pModbus){
            m_bConnectFlg = false;
            return;
        }
        modbus_set_slave(m_pModbus,1);
        modbus_set_response_timeout(m_pModbus,1,0);
    };

    virtual ~Modbus_RTU_Master(){};

    bool connect(modbus_error_recovery_mode enMode);
};

class Modbus_TCP_Client:public BaseModbus
{
public:
    Modbus_TCP_Client(int nSlaveId, string strIp,int nPort)
    {
        ST_ModbusInfo stTmpModbusInfo;
        stTmpModbusInfo.enType = EN_ModbusTCP;
		
	    stTmpModbusInfo.nSlaveID = nSlaveId;
        stTmpModbusInfo.strIp = strIp;
        stTmpModbusInfo.nPort = nPort;

        setModbusInfo(stTmpModbusInfo);

        m_pModbus = modbus_new_tcp(m_stModbusInfo.strIp.c_str(), 
                    m_stModbusInfo.nPort);
    
        if(nullptr == m_pModbus){
            m_bConnectFlg = false;
            return ;
        }

        modbus_set_response_timeout(m_pModbus,1,0);
	    modbus_set_slave(m_pModbus,m_stModbusInfo.nSlaveID);
    };

    virtual ~Modbus_TCP_Client(){};

    bool connect(modbus_error_recovery_mode enMode);
};




