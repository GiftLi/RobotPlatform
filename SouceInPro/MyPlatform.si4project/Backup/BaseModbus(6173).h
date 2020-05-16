#pragma once

#include "/usr/local/include/modbus/modbus.h"
#include <string>
#include "../Public/publicDef.h"

#define MODBUS_SERIAL_PATH "/dev/ttyS1"
#define MODBUS_BAUD 115200
#define MODBUS_PARITY 'N'
#define MODBUS_DATABIT 8
#define MODBUS_STOPBIT 1

#define MODBUS_IP "127.0.0.1"
#define MODBUS_PORT 502
#define MODBUS_SLAVE_ID 1

typedef struct _ST_ModbusInfo
{
    EN_CommunicationType enType;

    string strSerialPath;
	int nBaud;
    char cParity;
    int nDataBit;
    int nStopBit;

    string strIp;
    int nPort;
	int nSlaveID;

	_ST_ModbusInfo:enType(EN_ModbusRTU),strSerialPath(MODBUS_SERIAL_PATH),nBaud(MODBUS_BAUD),
		cParity(MODBUS_PARITY),nDataBit(MODBUS_DATABIT),nStopBit(MODBUS_STOPBIT),
		strIp(MODBUS_IP),nPort(MODBUS_PORT),nSlaveID(MODBUS_SLAVE_ID)
		{
		
		}

	_ST_ModbusInfo& operator=(const _ST_ModbusInfo& obj)
	{
		copy(this,obj);
		return this;
	}

private:
	void copy(_ST_ModbusInfo* pthis, const _ST_ModbusInfo& obj)
	{
		pthis.enType = obj.enType ;
		
		pthis.strSerialPath = obj.strSerialPath ;
		pthis.nBaud = obj.nBaud ;
		pthis.cParity = obj.cParity ;
		pthis.nDataBit = obj.nDataBit ;
		pthis.nStopBit = obj.nStopBit ;
		
		pthis.strIp = obj.strIp ;
		pthis.nPort = obj.nPort ;
		pthis.nSlaveID = obj.nSlaveID ;
	}

}ST_ModbusInfo;

typedef enum _EN_CommunicationType
{
    EN_ModbusRTU = 0,
    EN_ModbusTCP,
    EN_CommunicationType_CNT

}EN_CommunicationType;


class BaseModbus
{
public:
    modbus_t* m_pModbus;
    ST_ModbusInfo m_stModbusInfo;

    atomic<bool> m_bConnectFlg;
    atomic<int> m_nErrorCode;

    SaftLock m_lModbusLock;

public:
    BaseModbus();
    virtual BaseModbus();

    virtual bool connect(void)=0;
    void close(void);

    void setModbusInfo(const ST_ModbusInfo& st_ModbusInfo);
	void getModbusInfo(ST_ModbusInfo& st_ModbusInfo);

    bool AskIsConnect(void);
    int getErrorInfo(string& strResponse);

	int readCoilBits(int addr, int nb, uint8_t *dest);
	int readInputBits(int addr, int nb, uint8_t *dest);
	int readHoldingRegister(int addr, int nb, uint16_t *dest);
	int readInputRegister(int addr, int nb, uint16_t *dest);

	int writeCoilBits(int coil_addr, int status);
	int writeCoilBits(int addr, int nb, uint8_t *dest);
	int writeHoldingRegister(int reg_addr, const uint16_t value);
	int writeHoldingRegister(int addr, int nb, const uint16_t *data);

};


