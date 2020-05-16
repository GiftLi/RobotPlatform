#ifndef HRC_IF_SERVER_H
#define HRC_IF_SERVER_H

#include <string>
#include <vector>


using namespace std;

class HRC_If_Server
{
public:
    int InitIFMsgHandleFunc();

    static int OnRecvIF(int info_index,int client_fd,  char* pBuf, int nLen);
    static int HandleIFMsg(int info_index, int client_fd, int enClientType,const char* pData,int nLen);

};


#endif // HRC_IF_SERVER_H
