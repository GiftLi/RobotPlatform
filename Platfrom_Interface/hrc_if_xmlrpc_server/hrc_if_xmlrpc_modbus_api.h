#ifndef HRC_IF_XMLRPC_MODBUS_API_H
#define HRC_IF_XMLRPC_MODBUS_API_H

#include <xmlrpc-c/base.h>
#include <xmlrpc-c/server.h>
#include <xmlrpc-c/server_abyss.h>
#include "xmlrpc-c/config.h"


namespace xmlrpcServer
{

    xmlrpc_value * xmlrpc_ReadModbusData(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo);

    xmlrpc_value * xmlrpc_WriteModbusData(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo);

    xmlrpc_value * xmlrpc_GetModbusClientIsConnection(xmlrpc_env* const envP,
        xmlrpc_value* const paramArray, void* const serInfo, void* const channelInfo);
}

#endif // HRC_IF_XMLRPC_MODBUS_API_H_H
