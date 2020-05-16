#include "ModbusMaster.h"

bool Modbus_RTU_Master::connect(modbus_error_recovery_mode enMode)
{
    AutoSaftMutex modbusLock(&m_lModbusLock);
    
    uint16_t dest = 0;
    if(modbus_read_registers(m_pModbus, 0, 1, &dest) >= 0)
    {
        return true;
    }

    // if(nullptr != m_pModbus){
    //     modbus_close(m_pModbus);
    //     modbus_free(m_pModbus);

    //     m_pModbus = nullptr;
    // }
    
    modbus_set_error_recovery(m_pModbus, enMode);

    if(-1 == modbus_connect(m_pModbus)){
        printf("%s\n",modbus_strerror(errno));
        modbus_free(m_pModbus);
        m_pModbus = nullptr;

        m_bConnectFlg = false;

        return false;
    }

    return true;
}


bool Modbus_TCP_Client::connect(modbus_error_recovery_mode enMode)
{
    AutoSaftMutex modbusLock(&m_lModbusLock);
    
    uint16_t dest = 0;
    if(modbus_read_registers(m_pModbus, 0, 1, &dest) >= 0)
    {
        return true;
    }

    // if(nullptr == m_pModbus){
    //     modbus_close(m_pModbus);
    //     modbus_free(m_pModbus);

    //     m_pModbus = nullptr;
    // }

    modbus_set_error_recovery(m_pModbus, enMode);
    
    if(-1 == modbus_connect(m_pModbus)){
        modbus_free(m_pModbus);
        m_pModbus = nullptr;

        m_bConnectFlg = false;

        return false;
    }

    return true;
}


