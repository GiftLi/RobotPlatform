
#include <string.h>

#include "hrc_if_realtime.h"
#include "HRC_Public/hrc_public_factory/hrc_public_factory.h"
#include "HRC_Public/hrc_public_log/hrc_public_log.h"
#include <arpa/inet.h>

/* */
char HRC_If_RealTime::m_RealTimeTmpData[HRC_IF_REALTIME_MAX_RECVLEN] = {0};
int HRC_If_RealTime::m_RealTimeTmpLen = 0;
unsigned long HRC_If_RealTime::recvRealTimeCnt = 0;

/*
  @ 情况实时状态临时缓存
*/
int HRC_If_RealTime::OnRecvClearRealTimeData()
{
    memset(m_RealTimeTmpData,0,sizeof(m_RealTimeTmpData));
    m_RealTimeTmpLen = 0;

    return 0;
}

/*
  @ 收到实时状态，并组包
*/
int HRC_If_RealTime::OnRecvRealTimeData(int info_index, int client_fd,  char* pBuf, int nLen)
{
    int ret = 0;
    if (pBuf == nullptr || nLen <= 0)
    {
        return 0;
    }

    int nRealTimePackageLen = sizeof(ST_RealTimePackage);
    char *pRealTimeTmpData = m_RealTimeTmpData;

    /* 先将收到的数据cp到缓冲区 */
    if(m_RealTimeTmpLen + nLen < sizeof(m_RealTimeTmpData))
    {
        memcpy(pRealTimeTmpData + m_RealTimeTmpLen, pBuf, nLen);
        m_RealTimeTmpLen += nLen;
    }
    else
    {
        OnRecvClearRealTimeData();
        return -1;
    }

    /* 将收到的数据组成一个完整的实时状态包 */
    if(m_RealTimeTmpLen < nRealTimePackageLen)
    {
        /* 没有收完，等待下一次recv */
        // do nothing
    }
    else if(m_RealTimeTmpLen == nRealTimePackageLen)
    {
        /* 收完了，直接写入缓存 */
        ret = HandleRealTimeData(info_index, client_fd, pRealTimeTmpData,m_RealTimeTmpLen);
        if(ret != 0)
        {
            return -1;
        }

        m_RealTimeTmpLen = 0;
        memset(pRealTimeTmpData,0,sizeof(m_RealTimeTmpData));
    }
    else if( m_RealTimeTmpLen >= nRealTimePackageLen*2 )
    {
        /* 收到了多个数据的时候，写入新数据，放弃老数据 */
        int nPackageNum = m_RealTimeTmpLen / nRealTimePackageLen;
        int nPickOffset = (nPackageNum - 1) * nRealTimePackageLen;
        int nPickOffsetNext = nPickOffset + nRealTimePackageLen;

        ST_RealTimePackage stNewPackage;
        memcpy(&stNewPackage,pRealTimeTmpData + nPickOffset,sizeof(ST_RealTimePackage));
        ret = HandleRealTimeData(info_index, client_fd, (char *)&stNewPackage, sizeof(ST_RealTimePackage));
        if(ret != 0)
        {
            return -1;
        }
        /* 整数包后面的数据不能丢弃，因为那是下一个数据的前面一部分 */
        if(m_RealTimeTmpLen > nRealTimePackageLen*nPackageNum)
        {

            int nTailLen = m_RealTimeTmpLen - nPickOffsetNext;
            char *pStoreMem = (char *)malloc(nTailLen + 1);


            if(pStoreMem == nullptr)
            {
                center_trace(center_log_error, "!!!!!!!!malloc mem fail !!!!!!!!");
                return -1;
            }
            memcpy(pStoreMem, pRealTimeTmpData + nPickOffsetNext, nTailLen);

            memset(m_RealTimeTmpData,0,sizeof(m_RealTimeTmpData));
            memcpy(m_RealTimeTmpData, pStoreMem, nTailLen);
            m_RealTimeTmpLen = nTailLen;

            //center_trace(center_log_debug, "cp nTailLen to mem %d",nTailLen);

            free(pStoreMem);
        }
        else
        {
            memset(m_RealTimeTmpData,0,sizeof(m_RealTimeTmpData));
            m_RealTimeTmpLen = 0;

           // center_trace(center_log_debug, "no nTailLen cp ");

        }
    }
    else
    {
        /* 收到的数据包长度在一个到两个之间 */
        ST_RealTimePackage stNewPackage;
        memcpy(&stNewPackage,pRealTimeTmpData ,sizeof(ST_RealTimePackage));
        ret = HandleRealTimeData(info_index, client_fd, (char *)&stNewPackage, sizeof(ST_RealTimePackage));
        if(ret != 0)
        {
            return -1;
        }

        /* 整数包后面的数据不能丢弃，因为那是下一个数据的前面一部分 */
        int nTailLen = m_RealTimeTmpLen - nRealTimePackageLen;
        char *pStoreMem = (char *)malloc(nTailLen + 1);
        if(pStoreMem == nullptr)
        {
            center_trace(center_log_error, "!!!!!!!!malloc mem fail !!!!!!!!");
            return -1;
        }
        memcpy(pStoreMem, pRealTimeTmpData + nRealTimePackageLen, nTailLen);

        memset(m_RealTimeTmpData,0,sizeof(m_RealTimeTmpData));
        memcpy(m_RealTimeTmpData, pStoreMem, nTailLen);
        m_RealTimeTmpLen = nTailLen;
        free(pStoreMem);
    }

    return 0;
}


/*
  @ 处理一个完整的实时状态包
*/
int HRC_If_RealTime::HandleRealTimeData(int info_index, int client_fd, const char* pData,int nLen)
{
    if(pData == nullptr || nLen <= 0)
        return -1;

    /* 校验数据的正确性 */
    ST_RealTimePackage *stStPackage = (ST_RealTimePackage *)pData;
    if(stStPackage->unCheckSum1 != 0x07070707
        || stStPackage->unCheckSum2 != 0x08080808)
    {
        center_trace(center_log_error, "real time package error ingore it %d %d",stStPackage->unPackageLen,nLen);
        OnRecvClearRealTimeData();
        return -1;
    }

    if(nLen != ntohl(stStPackage->unPackageLen))
    {
        center_trace(center_log_error, "real time package len error ingore it %d %d",
            ntohl(stStPackage->unPackageLen),stStPackage->unPackageLen);
        OnRecvClearRealTimeData();
        return -1;
    }

    if(ntohl(stStPackage->unDataLen) != sizeof(ST_StatusArea))
    {
        center_trace(center_log_error, "real time data len error ingore it %d,%d",
            ntohl(stStPackage->unDataLen),stStPackage->unDataLen);
        OnRecvClearRealTimeData();
        return -1;
    }

    /* 实时状态计数器 ++ */
    recvRealTimeCnt++;

    HRC_Public_Factory::InstallFactory()->GenerateMotionControlFunc()->writeStatus(stStPackage->stData);


    return 0;
}
