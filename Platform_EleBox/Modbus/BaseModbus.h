#pragma once
#include <string>
#include <atomic>
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <sys/time.h>
#include <errno.h>

#include "/usr/local/include/modbus/modbus.h"
#include "../../Platform_Public/publicDef.h"

using namespace std;

#define MODBUS_SERIAL_PATH "/dev/ttyS1"
#define MODBUS_BAUD 115200
#define MODBUS_PARITY 'N'
#define MODBUS_DATABIT 8
#define MODBUS_STOPBIT 1

#define MODBUS_IP "127.0.0.1"
#define MODBUS_PORT 502
#define MODBUS_SLAVE_ID 1

typedef enum _EN_CommunicationType
{
    EN_ModbusRTU = 0,
    EN_ModbusTCP,
    EN_CommunicationType_CNT

}EN_CommunicationType;

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

	_ST_ModbusInfo():enType(EN_ModbusRTU),strSerialPath(MODBUS_SERIAL_PATH),nBaud(MODBUS_BAUD),
		cParity(MODBUS_PARITY),nDataBit(MODBUS_DATABIT),nStopBit(MODBUS_STOPBIT),
		strIp(MODBUS_IP),nPort(MODBUS_PORT),nSlaveID(MODBUS_SLAVE_ID)
	{
		
	}

	_ST_ModbusInfo& operator=(const _ST_ModbusInfo& obj)
	{
		copy(this,obj);
		return *this;
	}

private:
	void copy(_ST_ModbusInfo* pthis, const _ST_ModbusInfo& obj)
	{
		pthis->enType = obj.enType ;
		
		pthis->strSerialPath = obj.strSerialPath ;
		pthis->nBaud = obj.nBaud ;
		pthis->cParity = obj.cParity ;
		pthis->nDataBit = obj.nDataBit ;
		pthis->nStopBit = obj.nStopBit ;
		
		pthis->strIp = obj.strIp ;
		pthis->nPort = obj.nPort ;
		pthis->nSlaveID = obj.nSlaveID ;
	}

}ST_ModbusInfo;


class BaseModbus
{
public:
    modbus_t* m_pModbus;
    ST_ModbusInfo m_stModbusInfo;

    atomic<bool> m_bConnectFlg;
    atomic<int> m_nErrorCode;

    SaftLock m_lModbusLock;

public:
    BaseModbus()
	{
		m_log.open("log.csv");
		m_logTimeout.open("logTimeout.csv");
		m_logInvalid.open("logInvalid.csv");
		m_logCRC.open("logCRC.csv");
		m_logSlave.open("logSlave.csv");
		m_lognomal.open("lognomal.csv");
		
	};
    virtual ~BaseModbus()
	{
		m_log.close();
		m_logTimeout.close();
		m_logInvalid.close();
		m_logCRC.close();
		m_logSlave.close();
		m_lognomal.close();
	};

    virtual bool connect(modbus_error_recovery_mode enMode)=0;
    void close(void);

    void setModbusInfo(const ST_ModbusInfo& st_ModbusInfo);
	void getModbusInfo(ST_ModbusInfo& st_ModbusInfo);

    bool AskIsConnect(void);
    int getErrorInfo(string& strResponse);

	int readCoilBits(int addr, int nb, uint8_t *dest);
	int readInputBits(int addr, int nb, uint8_t *dest);
	int readHoldingRegister(int addr, int nb, uint16_t *dest);
	int readInputRegister(int addr, int nb, uint16_t *dest);

	int writeCoilBit(int coil_addr, int status);
	int writeCoilBits(int addr, int nb, uint8_t *dest);
	int writeHoldingRegister(int reg_addr, const uint16_t value);
	int writeHoldingRegisters(int addr, int nb, const uint16_t *data);

private:
	ofstream m_log;
    ofstream m_logTimeout;
    ofstream m_logInvalid;
    ofstream m_logCRC;
    ofstream m_logSlave;
    ofstream m_lognomal;

};


