#ifndef EPOLLSERVER_H
#define EPOLLSERVER_H

#include <sys/epoll.h>
#include <string>
#include <vector>
#include <map>


using namespace std;

#define MAX_LISTEN_PORT_NUM                     16            /* 最多监听16个端口 */
#define EPOLL_MAX_READ_SIZE                     (1024*3+1)    /* 接收数据缓存区长度 */

enum {LISTEN_FD=1, ClIENT_FD};
enum {CC_SOCKET_SERVER=1, CC_SOCKET_CLIENT};

struct socket_connect_info_s
{
    unsigned long allow_client;                             /* 允许的最多客户端连接个数*/
    int server_port;                                        /* 绑定端口号 */
    map<int, int> client_fds;                                /* 存储每个客户端的句柄 */
    string connect_name;                                    /* 为每个监听服务取个名字 */
    int (*OnRecv)(int,int, char*,int);
    int fd;                                                 /* socket句柄 */
    char socket_type;                                       /* socket 类型，服务器或者客户端*/
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
    int g_send_pipe_fd[2];                                      /*epoll发送数据管道，当有数据需要发送给客户端时，先将数据写入该管道*/

#define LISTEN_REAL_NUM  (m_connect_infos.size())
    int  m_epollfd;
    vector<socket_connect_info_s> m_connect_infos;              /* 存储网络服务器基本信息*/

    
    char * m_recv_tmpbuf;                                       /* 接收数据缓存 */
    unsigned long m_recv_tmpbuf_len;
    socket_pipe_data_s m_pipe_data;                             /* 管道，*/
                                                                // 服务器需要进行send时，将数据写进管道
                                                                // epoll 从管道读取数据，进行send
                                                                
    int m_have_sendData;                                        /* 是否有数据要进行发送 */


    
};


#endif // EPOLLSERVER_H
