#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/prctl.h>

#include "hrc_interface.h"
#include "HRC_Public/hrc_public_func.h"
#include "HRC_Public/hrc_public_factory/hrc_public_factory.h"
#include "hrc_if_xmlrpc_server/hrc_if_xmlrpcServer.h"
#include "HRC_Public/hrc_public_define/hrc_public_if_cmd.h"


using namespace std;
static socket_thread_param_s g_if_server_param;
static socket_thread_param_s g_realtime_server_param;

HRC_Interface::HRC_Interface()
{

}

HRC_Interface::~HRC_Interface()
{

}

int HRC_Interface::Init()
{
    int xmlrpc_port;
    int IF_port;
    int script_Port;
    int realtime_port;

    /* */
    if(HRC_GET_CFG()->HRC_Cfg_ReadNetWorkPorts(xmlrpc_port,IF_port,script_Port,realtime_port) != 0)
    {
        center_trace(center_log_error,"read network port fail!!");
        return -1;
    }

    /* */
    if(HRDCS_xmlrpcServer::Instance()->InitServer(xmlrpc_port) != 0)
    {
        center_trace(center_log_error,"HRDCS_xmlrpcServer init fail!!");
        return -1;
    }

    /* ��ʼ��if�ӿں����� */
    HRC_Public_Factory::InstallFactory()->GetIFServer()->InitIFMsgHandleFunc();
    HRC_If_RealTime::recvRealTimeCnt = 0;

    /* ����IF�ӿڷ�������ʼ��Ϣ */
    snprintf(g_if_server_param.scis[0].ip, sizeof(g_if_server_param.scis[0].ip) -1, "0.0.0.0");
    g_if_server_param.scis[0].server_port = IF_port;
    g_if_server_param.scis[0].connect_name = string("IF");
    g_if_server_param.scis[0].fd = -1;
    g_if_server_param.scis[0].OnRecv = HRC_If_Server::OnRecvIF;
    g_if_server_param.scis[0].allow_client = 5;

    snprintf(g_if_server_param.scis[1].ip, sizeof(g_if_server_param.scis[1].ip) -1, "0.0.0.0");
    g_if_server_param.scis[1].server_port = script_Port;
    g_if_server_param.scis[1].connect_name = string("Script");
    g_if_server_param.scis[1].fd = -1;
    g_if_server_param.scis[1].OnRecv = HRC_If_Server::OnRecvIF;
    g_if_server_param.scis[1].allow_client = 5;
    
    g_if_server_param.num = 2; 


    /* ����ʵʱ״̬�ӿڳ�ʼ��Ϣ */
    snprintf(g_realtime_server_param.scis[0].ip, sizeof(g_realtime_server_param.scis[0].ip) -1, "0.0.0.0");
    g_realtime_server_param.scis[0].server_port = realtime_port;
    g_realtime_server_param.scis[0].connect_name = string("realtime");
    g_realtime_server_param.scis[0].fd = -1;
    g_realtime_server_param.scis[0].allow_client = 1;
    g_realtime_server_param.scis[0].OnRecv = HRC_If_RealTime::OnRecvRealTimeData;
    
    g_realtime_server_param.num = 1;


    /* if�ӿ��߳� */
    if(pthread_create(&m_IFThread, nullptr, If_Server_Handle, nullptr) != 0)
    {
        center_trace(center_log_error,"pthread_create m_serverThread fail!!");
        return -1;
    }

    /* ʵʱ�����߳� */
    if(pthread_create(&m_RealTimeThread, nullptr, Realtime_Server_Handle, nullptr) != 0)
    {
        center_trace(center_log_error,"pthread_create m_serverThread fail!!");
        return -1;
    }

    /* modbus connect */
    if(pthread_create(&m_ModbusThread, nullptr, Readtime_Modbus_Handle, nullptr) != 0)
    {
        center_trace(center_log_error,"pthread_create m_ModbusThread fail!!");
        return -1;
    }

    if(pthread_create(&m_ConfigIO, nullptr, Readtime_ConfigIO_Handle, nullptr) != 0)
    {
        center_trace(center_log_error,"pthread_create m_ConfigIO fail!!");
        return -1;
    }

    return 0;
}


int HRC_Interface::ResponseIFMsg(int info_index, int client_fd, const char* pData,int nLen)
{

    socket_pipe_data_s pipe_data;
    pipe_data.data = new char[nLen];			/*����new���������ݣ���send��Ϻ��ͷ�*/
    pipe_data.data_len = nLen;
    pipe_data.client_fd = client_fd;
    pipe_data.info_index = info_index;
    pipe_data.data_type = en_IFResponse;
    memcpy(pipe_data.data, pData, static_cast<unsigned long>(nLen));

    epollServer *if_server = HRC_Public_Factory::InstallFactory()->GetIFEpollServer();
    if(write(if_server->g_send_pipe_fd[1], &pipe_data, sizeof(socket_pipe_data_s)) < 0)
    {
        center_trace(center_log_error, "write pipe error");
        return -1;
    }

    return 0;
}



void* HRC_Interface::If_Server_Handle(void*)
{
	prctl(PR_SET_NAME, "if_server");

    epollServer *if_server = HRC_Public_Factory::InstallFactory()->GetIFEpollServer();
    if_server->Init_SInfo(g_if_server_param);
    
    if(pipe(if_server->g_send_pipe_fd)<0)
    {
        center_trace(center_log_error,"pipe g_send_pipe_fd fail!!");
        return nullptr;
    }

    if(if_server->socket_bind() != 0)
        return nullptr;

    if(if_server->init_epoll() != 0)
        return nullptr;

    while(1)
    {
        if_server->epoll_work();
    }
    
}

void* HRC_Interface::Realtime_Server_Handle(void*)
{
	prctl(PR_SET_NAME, "realtime_server");

    epollServer *realtime_server = HRC_Public_Factory::InstallFactory()->GetRealtimeEpollServer();
    realtime_server->Init_SInfo(g_realtime_server_param);
    if(pipe(realtime_server->g_send_pipe_fd)<0)
    {
        center_trace(center_log_error,"pipe g_send_pipe_fd fail!!");
        return nullptr;
    }

    if(realtime_server->socket_bind() != 0)
        return nullptr;

    if(realtime_server->init_epoll() != 0)
        return nullptr;

    while(1)
    {
        realtime_server->epoll_work();
    }
    
}


void* HRC_Interface::Readtime_Modbus_Handle(void*)
{
    prctl(PR_SET_NAME, "realtime_modbus");

    while (1)
    {
        HRC_GET_MDB()->Readtime_update_Modbus();

        sleep(1);
    }
}

void* HRC_Interface::Readtime_ConfigIO_Handle(void*)
{
    prctl(PR_SET_NAME, "realtime_ConfigIO_Handler");

    while(1)
    {
        //input
        for(int nIndex=0; nIndex < CI_CNT; nIndex++)
        {
            int nCurState = 0;
            if(HRC_GET_MC()->SysBoard_ReadSpeConfigDI(0,nIndex,nCurState))
            {
                continue;
            }

            HRC_GET_CFGIO()->handleInputIOChanged(nIndex,nCurState);
        }
        //output
        for(int nIndex=0; nIndex < CO_CNT; nIndex++)
        {
            int nCurState = 0;
            if(HRC_GET_MC()->SysBoard_ReadSpeConfigDO(0,nIndex,nCurState))
            {
                continue;
            }

            HRC_GET_CFGIO()->handleOutputIOChanged(nIndex,nCurState);
        }

        usleep(100*1000);
    }
}

