#include "hrc_if_epollserver.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/epoll.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/timerfd.h>

#include "HRC_Public/hrc_public_factory/hrc_public_factory.h"


epollServer::epollServer()
{  
}

epollServer::~epollServer()
{
    if(m_recv_tmpbuf)
        free(m_recv_tmpbuf);
}

int epollServer::Init_SInfo(socket_thread_param_s& s_param)
{
    /* 初始化成员变量 */
    m_epollfd = -1;
    m_connect_infos.clear();
    m_have_sendData = 0; 
    m_recv_tmpbuf = nullptr;

    /* 初始化网络服务器信息 */
    for(int i = 0 ; i<s_param.num; i++)
    {
        socket_connect_info_s c_info;
        snprintf(c_info.ip, sizeof(c_info.ip) -1, "%s",s_param.scis[i].ip);
        c_info.server_port = s_param.scis[i].server_port;
        c_info.allow_client = s_param.scis[i].allow_client;
        c_info.fd = -1;
        c_info.connect_name = s_param.scis[i].connect_name;
        c_info.OnRecv = s_param.scis[i].OnRecv;

        m_connect_infos.push_back(c_info);
    }

    return 0;
    
}


int epollServer::setnonblocking(int sock)
{
    int opts;
    opts = fcntl(sock,F_GETFL);
    if (opts < 0)
    {
        return -1;
    }
    opts = opts|O_NONBLOCK;
    if (fcntl(sock, F_SETFL, opts) < 0)
    {
        return -1;
    }

    return 0;
}

int epollServer::socket_bind()
{
    int  listenfd;
    struct sockaddr_in servaddr;
    unsigned int optval = 0x01;

    for(unsigned long i = 0; i < LISTEN_REAL_NUM; i++)
    {
        /**/
        listenfd = socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, 0);
        if (listenfd == -1)
        {
            center_trace(center_log_error, "socket error");
            return -1;
        }

        /*设置非阻塞*/
        if(setnonblocking(listenfd) < 0)
        {
            center_trace(center_log_error, "setnonblocking error");
            return -1;
        }

        setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));

        /*绑定端口*/
        bzero(&servaddr,sizeof(servaddr));
        servaddr.sin_family = AF_INET;
        inet_pton(AF_INET,m_connect_infos[i].ip,&servaddr.sin_addr);
        servaddr.sin_port = htons(static_cast<unsigned short>(m_connect_infos[i].server_port));
        
        if (bind(listenfd,(struct sockaddr*)&servaddr,sizeof(servaddr)) == -1)
        {
            center_trace(center_log_error, "bind port %d error",m_connect_infos[i].server_port);
            center_trace(center_log_error, "maybe another CenterControl is running !!!!!!!");
            center_trace(center_log_error, "I am exit!!!!!!");
            exit(0);
        }

        /*保存句柄*/
        m_connect_infos[i].fd = listenfd;
        
    }


    return 0;
}


/*某一个服务器监听句柄出错，将该句柄从epoll中摘下来，并重启该监听工作*/
int epollServer::restart_listenFd(int error_fd, unsigned long info_index)
{
    int  listenfd;
    struct sockaddr_in servaddr;
    unsigned int optval = 0x01;
    int ret;

    center_trace(center_log_waring, "restart_listenFd %d ",info_index);
    if(info_index >= LISTEN_REAL_NUM)
    {
        return -1;
    }

    /* 关闭错误句柄 */
    close(error_fd);

    /*从epoll中剔除该句柄*/
    delete_event(error_fd, EPOLLIN | EPOLLERR | EPOLLHUP);

    /*重建linsten fd*/
    listenfd = socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, 0);
    if (listenfd == -1)
    {
        center_trace(center_log_error, "socket error");
        return -1;
    }

    /*设置非阻塞*/
    if(setnonblocking(listenfd) < 0)
    {
        center_trace(center_log_error, "setnonblocking error");
        return -1;
    }

    /*设置快速启动*/
    setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));

    /*绑定端口*/
    bzero(&servaddr,sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    inet_pton(AF_INET,m_connect_infos[info_index].ip,&servaddr.sin_addr);
    servaddr.sin_port = htons(static_cast<unsigned short>(m_connect_infos[info_index].server_port));

    
    if (bind(listenfd,(struct sockaddr*)&servaddr,sizeof(servaddr)) == -1)
    {
        center_trace(center_log_error, "bind port %d error",m_connect_infos[info_index].server_port);
        center_trace(center_log_error, "maybe another CenterControl is running !!!!!!!");
        center_trace(center_log_error, "I am exit!!!!!!");
        exit(0);
    }


    /*重新加入epoll监听序列*/    
    ret = add_event(listenfd, EPOLLIN | EPOLLERR | EPOLLHUP);
    if(ret != 0)
    {
        return -1;
    }

    if(listen(listenfd,5) != 0)
    {
        return -1;
    }
    
    /*刷新句柄*/
    m_connect_infos[info_index].fd = listenfd;
    m_connect_infos[info_index].client_fds.clear();

    return 0;
}

/*
  @ 某一个客户端连接出错，或者该连接已经被客户端关闭
    将该句柄从储存表中剔除
*/
int epollServer::close_clientFd(int error_fd, unsigned long info_index)
{
    center_trace(center_log_debug, "close_clientFd %d",info_index);


    /*从epoll中剔除该句柄*/
    delete_event(error_fd, EPOLLIN | EPOLLERR | EPOLLHUP);


    /*将该连接句柄从 m_connect_infos中删除*/
    if(m_connect_infos[info_index].client_fds.count(error_fd) > 0)
    {
        m_connect_infos[info_index].client_fds.erase(error_fd);
    }

    /* 关闭错误句柄 */
    close(error_fd);

    return 0;
}
int epollServer::add_event(int fd,unsigned int state)
{
    struct epoll_event ev;
    ev.events = state;
    ev.data.fd = fd;
    return epoll_ctl(m_epollfd,EPOLL_CTL_ADD,fd,&ev);
}

int epollServer::delete_event( int fd, unsigned int state)
{
    struct epoll_event ev;
    ev.events = state;
    ev.data.fd = fd;
    return epoll_ctl(m_epollfd,EPOLL_CTL_DEL,fd,&ev);
}

int epollServer::modify_event( int fd, unsigned int state)
{
    struct epoll_event ev;
    ev.events = state;
    ev.data.fd = fd;
    return epoll_ctl(m_epollfd,EPOLL_CTL_MOD,fd,&ev);
}


/*
    目前epoll主程序一共做三件事情
    1: 监听 listen 端口，从客户端读取数据
    2：监听 pipe管道，将管道中的数据写到socket中，发送给客户端
    3, 监听 定时器，定时发送给10004, 10005端口

*/
int epollServer::init_epoll()
{
    int ret;

    //创建一个描述符
    if( (m_epollfd = epoll_create(1024)) < 0)
    {
        printf("create epoll error \n");
        return -1;
    }

    //添加监听网络端口
    for(unsigned long i = 0; i<LISTEN_REAL_NUM; i++)
    {
        ret = add_event(m_connect_infos[i].fd, EPOLLIN | EPOLLERR | EPOLLHUP);
        if(ret != 0)
        {
            return -1;
        }

        if(listen(m_connect_infos[i].fd,5) != 0)
            return -1;
    }

    /*启动并监听 10004定时器
    struct itimerspec new10004_value;
    new10004_value.it_value.tv_sec = 2;                  // 2m后第一次启动
    new10004_value.it_value.tv_nsec = 0;
    new10004_value.it_interval.tv_sec = 1;
    new10004_value.it_interval.tv_nsec = 100000000;       // 每隔100ms启动一次

    m_10004_timer_fd = timerfd_create(CLOCK_MONOTONIC,0);
    if (m_10004_timer_fd < 0)
    {
        return -1;
    }

    ret = timerfd_settime(m_10004_timer_fd, 0, &new10004_value, nullptr);
    if (ret < 0) {
        close(m_10004_timer_fd);
        return -1;
    }
    add_event(m_10004_timer_fd, EPOLLIN);*/


    /*启动并监听 10005定时器
    struct itimerspec new10005_value;
    new10005_value.it_value.tv_sec = 2;                  // 2m后第一次启动
    new10005_value.it_value.tv_nsec = 0;
    new10005_value.it_interval.tv_sec = 1;
    new10005_value.it_interval.tv_nsec = 100000000;       // 每隔100ms启动一次

    m_10005_timer_fd = timerfd_create(CLOCK_MONOTONIC,0);
    if (m_10005_timer_fd < 0)
    {
        return -1;
    }

    ret = timerfd_settime(m_10005_timer_fd, 0, &new10005_value, nullptr);
    if (ret < 0) {
        close(m_10005_timer_fd);
        return -1;
    }
    add_event(m_10005_timer_fd, EPOLLIN);*/

    /*监听管道*/  
    add_event(g_send_pipe_fd[0], EPOLLIN);    

    /*数据接收区, 在初始化时申请一次，反复使用，不用释放*/
    m_recv_tmpbuf = static_cast<char *>(malloc(EPOLL_MAX_READ_SIZE));
    if(m_recv_tmpbuf == nullptr) 
    {
        center_trace(center_log_waring, "!!!!!!!!!!!!!!!malloc mem fail!!!!!!!!!!!");
        return -1;
    }
    m_recv_tmpbuf_len = EPOLL_MAX_READ_SIZE;

    return 0;
}

int epollServer::handle_accpet(int listenfd, unsigned long info_index)
{
    int clifd;
    struct sockaddr_in cliaddr;
    socklen_t  cliaddrlen;

    clifd = accept(listenfd,(struct sockaddr*)&cliaddr,&cliaddrlen);
    if (clifd == -1)
    {
        return -1;
    }

    if(info_index >= LISTEN_REAL_NUM)
    {
        return -1;
    }
    
    /*如果连接数超过了最大连接数，则通知客户端，并关闭连接*/
    if(m_connect_infos[info_index].client_fds.size() >= m_connect_infos[info_index].allow_client)
    {
        write(clifd, "Connect full, You are out!", strlen("Connect full, You are out!"));
        close(clifd);
        return 0;
    }
    
    /*设置非阻塞*/
    if(setnonblocking(clifd) < 0)
    {
        center_trace(center_log_error, "setnonblocking error");
        return -1;
    }

    //添加一个客户描述符和事件
    add_event(clifd, EPOLLIN | EPOLLERR | EPOLLHUP);

    m_connect_infos[info_index].client_fds.insert(make_pair(clifd, clifd));

    return 0;
}

int epollServer::handle_recv(int client_fd, unsigned long info_index)
{
    char read_tmpbuf[1024] = {0};
    long read_len = 0;
    int read_total_len = 0;
    int read_cnt = 0;
    int read_total_cnt = EPOLL_MAX_READ_SIZE / sizeof(read_tmpbuf);
    
    memset(m_recv_tmpbuf,0,m_recv_tmpbuf_len);
    do
    {
        read_len = read(client_fd, read_tmpbuf, sizeof(read_tmpbuf));
        if(read_len > 0)
        {
            memcpy(m_recv_tmpbuf + read_total_len, read_tmpbuf, static_cast<unsigned long>(read_len));
            read_total_len += read_len;
            memset(read_tmpbuf,0,sizeof(read_tmpbuf));
                
            read_cnt++;
            if(read_cnt >= read_total_cnt)
            {
                /* 避免内存申请 最多读取3次 */
                break;
            }
            
        }
        else if(read_len < 0)
        {
            if (errno == EAGAIN){ break;}
            else
            {
                center_trace(center_log_error, "read socket error in %s %d",
                    m_connect_infos[info_index].connect_name.c_str(),read_len);
                return -1;
            }
        }
        else
        {
            /*客户端主动关闭连接*/
            center_trace(center_log_info, "client close this socket %s",
                        m_connect_infos[info_index].connect_name.c_str());
            return -1;
        }
    }while(true);


    /* 执行回调 */
    if(read_total_len > 0)
    {
        if(m_connect_infos[info_index].OnRecv != nullptr)
            m_connect_infos[info_index].OnRecv(info_index,client_fd,m_recv_tmpbuf,read_total_len);

    }
    
    return 0;
}

int epollServer::handle_pipe()
{
    char buf[128];
    char recv_buf[128];
    int read_ret;
    int read_offset = 0;    
 
    do
    {
        read_ret = read(g_send_pipe_fd[0], recv_buf, sizeof(socket_pipe_data_s));
        if(read_ret > 0)
        {
            memcpy(buf+read_offset , recv_buf, read_ret);
            read_offset += read_ret;
            if(sizeof(socket_pipe_data_s) == read_offset)
            {
                break;
            }
            else
            {
                /**/
                center_trace(center_log_waring, "handle_pipe read less!!");
                continue;
            }
        }
        else 
        {
            center_trace(center_log_error, "read a error in pipe");
            return -1;
        }

    }while(true);

    
    m_pipe_data.data = ((socket_pipe_data_s*)buf)->data;
    m_pipe_data.data_len = ((socket_pipe_data_s*)buf)->data_len;
    m_pipe_data.info_index = ((socket_pipe_data_s*)buf)->info_index;
    m_pipe_data.client_fd = ((socket_pipe_data_s*)buf)->client_fd;
    m_pipe_data.data_type = ((socket_pipe_data_s*)buf)->data_type;
    
    /* 发送给脚本的命令 */
    if(m_pipe_data.data_type == en_SendScriptCmd &&
        m_connect_infos[m_pipe_data.info_index].connect_name == "Script_IF")
    {
        if(m_connect_infos.size() < 2)
        {
            center_trace(center_log_error, "script has not in this epoll server");
            return -1;
        }

        if(m_connect_infos[m_pipe_data.info_index].client_fds.size() != 1)
        {
            center_trace(center_log_error, "may be script connect have not exist !!");
            return -1;            
        }

        /*获取脚本连接的tcp通道句柄*/
        m_pipe_data.client_fd  = m_connect_infos[m_pipe_data.info_index].client_fds.begin()->first;
    }
    

    if(m_pipe_data.client_fd != -1)
    {    
        int info_index;
        int fd_type = find_fd_type(m_pipe_data.client_fd,info_index);
        if(fd_type != ClIENT_FD) {
            center_trace(center_log_error, "read a error clientFD in pipe");
            delete[] m_pipe_data.data;
            return -1;
        }
    
        if(modify_event(m_pipe_data.client_fd,EPOLLIN | EPOLLERR | EPOLLHUP | EPOLLOUT) != 0)
        {
            center_trace(center_log_error, "modify_event to write fail");
            delete[] m_pipe_data.data;
            return -1;
        }
        else
        {
            m_have_sendData = 1;
        }
    }
    else{
        center_trace(center_log_error, "read a error clientFD in pipe");
        delete[] m_pipe_data.data;
        return -1;
    }

    return 0;
}


int epollServer::handle_send(int client_fd, unsigned long info_index)
{
    char *buf = m_pipe_data.data;
    int len = m_pipe_data.data_len;
    int send_ret;
    int send_offset = 0;
    int send_len = len;
    
    do
    {
        send_ret = write(client_fd, buf+send_offset, send_len);
        if(send_ret > 0)
        {
            send_len -= send_ret;
            send_offset += send_ret;
        }
        else if(send_ret < 0)
        {
            if (errno == EAGAIN || errno == EINTR)    
            {
                //本次发送失败，继续
                center_trace(center_log_waring, "send not over continue %d",errno);
                continue;
            }
            else
            {
                /*出错*/
                center_trace(center_log_error, "send error %d",errno);
                m_have_sendData = 0;
                delete[] m_pipe_data.data;
                return -1;
            }
        }
        else
        {
            /*客户端主动关闭连接*/
            center_trace(center_log_error, "send while client close");
            m_have_sendData = 0;
            delete[] m_pipe_data.data;
            return -1;
        }

    }while(send_offset < len);

    modify_event(client_fd,EPOLLIN | EPOLLERR | EPOLLHUP);
    m_have_sendData = 0;
    delete[] m_pipe_data.data;
    
    return 0;
}


int epollServer::find_fd_type(int fd, int& index)
{
    for(unsigned long i = 0; i<LISTEN_REAL_NUM; i++)
    {
        if(fd == m_connect_infos[i].fd) 
        {
            index = i;
            return LISTEN_FD;
        }

        if(m_connect_infos[i].client_fds.count(fd) > 0)
        {
            index = i;
            return ClIENT_FD;
        }
    }

    return -1;
    
}

int epollServer::epoll_work()
{
    struct epoll_event events[128];
    memset(events,0,sizeof(events));
    int num = 0;
    int fd = -1;
    int ret = -1;
    int info_index = -1;

    num = epoll_wait(m_epollfd,events,128,-1);

    for (int i = 0; i < num; i++)
    {
        fd = events[i].data.fd;
        int fd_type = find_fd_type(fd,info_index);


        if((fd_type == LISTEN_FD) && events[i].events & EPOLLIN)
        {
            /*监听句柄 接收到新的连接*/
            if(handle_accpet(fd,info_index) != 0)
            {
                restart_listenFd(fd,info_index);
            }
        }
        else if((fd_type == ClIENT_FD) && events[i].events & EPOLLIN)
        {
            /* 处理接收数据*/
            int ff = handle_recv(fd,info_index);
            if(ff != 0)
            {
                close_clientFd(fd,info_index);
                
                center_trace(center_log_debug, "close_clientFd %d ",fd);
            }

        }
        else if((fd_type == ClIENT_FD) && events[i].events & EPOLLOUT)
        {
            /* 处理数据*/
            //center_trace(center_log_debug, "get a package send to client");
            if(handle_send(fd,info_index) != 0)
            {
                close_clientFd(fd,info_index);
                
            }

        }
        else if(fd == g_send_pipe_fd[0] && events[i].events & EPOLLIN)
        {
            // 当 m_have_sendData == 1表示 上次的数据还有没有发送完
            // 则缓一下 等数据发完在从管道中读取要发送的数据
            if(m_have_sendData == 1)
            {
                continue;
            }

            handle_pipe();
        
        }
        /*else if(fd == m_10004_timer_fd)
        {
            char buf[16];
            read(fd, buf, sizeof(uint64_t));

            handle_10004Timer();
        }
        else if(fd == m_10005_timer_fd)
        {
            char buf[16];
            read(fd, buf, sizeof(uint64_t));

            handle_10004Timer();
        }*/
		
        else if((fd_type == LISTEN_FD) && events[i].events&EPOLLERR || events[i].events&EPOLLHUP)
        {
            /* 监听出现异常，重启服务 */
            restart_listenFd(fd,info_index); 
        }
        else if((fd_type == ClIENT_FD) && events[i].events&EPOLLERR || events[i].events&EPOLLHUP)
        {
            /**/
            close_clientFd(fd,info_index); 
        }
		else 
		{
			center_trace(center_log_waring, "epoll no evnet %d %d %d!!",fd,fd_type,events[i].events);
			continue;
		}
    }

    return 0;
}










