#ifndef HRC_INTERFACE_H
#define HRC_INTERFACE_H

#include "hrc_interface_global.h"

#include "hrc_if_server/hrc_if_server.h"
#include "hrc_if_realtime/hrc_if_realtime.h"
#include "hrc_if_xmlrpc_server/hrc_if_xmlrpcServer.h"


using namespace  xmlrpcServer;

class HRC_INTERFACESHARED_EXPORT HRC_Interface
{

public:
    HRC_Interface();
    ~HRC_Interface();
    int Init();

    static int ResponseIFMsg(int info_index, int client_fd, const char* pData,int nLen);
    static void* If_Server_Handle(void*);
    static void* Realtime_Server_Handle(void*);

    static void* Readtime_Modbus_Handle(void*);
    static void* Readtime_ConfigIO_Handle(void*);
    
private:
    pthread_t m_IFThread;			//Ïß³ÌID
    pthread_t m_RealTimeThread;
    pthread_t m_ModbusThread;
    pthread_t m_ConfigIO;
};

#endif // HRC_INTERFACE_H
