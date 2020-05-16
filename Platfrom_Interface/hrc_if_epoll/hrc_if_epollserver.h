#ifndef EPOLLSERVER_H
#define EPOLLSERVER_H

#include <sys/epoll.h>
#include <string>
#include <vector>
#include <map>


using namespace std;

#define MAX_LISTEN_PORT_NUM                     16            /* ������16���˿� */
#define EPOLL_MAX_READ_SIZE                     (1024*3+1)    /* �������ݻ��������� */

enum {LISTEN_FD=1, ClIENT_FD};
enum {CC_SOCKET_SERVER=1, CC_SOCKET_CLIENT};

struct socket_connect_info_s
{
    unsigned long allow_client;                             /* ��������ͻ������Ӹ���*/
    int server_port;                                        /* �󶨶˿ں� */
    map<int, int> client_fds;                                /* �洢ÿ���ͻ��˵ľ�� */
    string connect_name;                                    /* Ϊÿ����������ȡ������ */
    int (*OnRecv)(int,int, char*,int);
    int fd;                                                 /* socket��� */
    char socket_type;                                       /* socket ���ͣ����������߿ͻ���*/
    char ip[32];

};

struct socket_thread_param_s
{
    int num;
    socket_connect_info_s scis[MAX_LISTEN_PORT_NUM];
};

struct socket_pipe_data_s
{
    char *data;
    int data_len;
    int data_type;
    int info_index;
    int client_fd;
};


class epollServer
{
public:
    epollServer();
    ~epollServer();
    int Init_SInfo(socket_thread_param_s& s);

    int  socket_bind();
    int init_epoll();
    int epoll_work();
    int handle_accpet(int listenfd, unsigned long info_index);
    int handle_recv(int client_fd, unsigned long info_index);
    int handle_send(int client_fd, unsigned long info_index);
    int handle_pipe();
    int add_event(int fd,unsigned int state);
    int modify_event(int fd,unsigned int state);
    int delete_event(int fd,unsigned int state);
    int  setnonblocking(int sock);
    int close_clientFd(int error_fd, unsigned long info_index);
    int restart_listenFd(int error_fd, unsigned long info_index);

    int find_fd_type(int fd, int& index);

public:
    int g_send_pipe_fd[2];                                      /*epoll�������ݹܵ�������������Ҫ���͸��ͻ���ʱ���Ƚ�����д��ùܵ�*/

#define LISTEN_REAL_NUM  (m_connect_infos.size())
    int  m_epollfd;
    vector<socket_connect_info_s> m_connect_infos;              /* �洢���������������Ϣ*/

    
    char * m_recv_tmpbuf;                                       /* �������ݻ��� */
    unsigned long m_recv_tmpbuf_len;
    socket_pipe_data_s m_pipe_data;                             /* �ܵ���*/
                                                                // ��������Ҫ����sendʱ��������д���ܵ�
                                                                // epoll �ӹܵ���ȡ���ݣ�����send
                                                                
    int m_have_sendData;                                        /* �Ƿ�������Ҫ���з��� */


    
};


#endif // EPOLLSERVER_H
