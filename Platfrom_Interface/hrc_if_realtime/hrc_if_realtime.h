#ifndef HRC_IF_REALTIME_H
#define HRC_IF_REALTIME_H

#include <atomic>
#include <string>

using namespace::std;



#define HRC_IF_REALTIME_MAX_RECVLEN                 10240

class HRC_If_RealTime
{
public:
    static int OnRecvClearRealTimeData();
    static int OnRecvRealTimeData(int info_index, int client_fd,  char* pBuf, int nLen);
    static int HandleRealTimeData(int info_index, int client_fd, const char* pData,int nLen);


    static char m_RealTimeTmpData[HRC_IF_REALTIME_MAX_RECVLEN];
    static int m_RealTimeTmpLen ;
    static unsigned long recvRealTimeCnt ;  /* motion实时状态 计数器 */

};


#endif
