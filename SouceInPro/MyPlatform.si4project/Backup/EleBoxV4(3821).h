#pragma once

class EleBoxV4:public ElectricityBoxHAL
{
public:
    EleBoxV4(string strIp,int nPort):ElectricityBoxHAL(EN_ModbusTCP)
    {
        ST_ModbusInfo stTmpModbusInfo;
        stTmpModbusInfo.enType = EN_ModbusTCP;
        stTmpModbusInfo.strIp = strIp;
        stTmpModbusInfo.nPort = nPort;

        m_pModbus->setModbusInfo(stTmpModbusInfo);
    };
    EleBoxV4(string strPath):ElectricityBoxHAL(EN_ModbusRTU)
    {
        ST_ModbusInfo stTmpModbusInfo;
        stTmpModbusInfo.enType = EN_ModbusRTU;
        stTmpModbusInfo.strDeviceName = strPath;

        m_pModbus->setModbusInfo(stTmpModbusInfo);
    };

    virtual ~EleBoxV4();

    void handleMapData(void);

};