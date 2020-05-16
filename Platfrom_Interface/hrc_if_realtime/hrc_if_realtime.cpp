
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
  @ ���ʵʱ״̬��ʱ����
*/
int HRC_If_RealTime::OnRecvClearRealTimeData()
{
    memset(m_RealTimeTmpData,0,sizeof(m_RealTimeTmpData));
    m_RealTimeTmpLen = 0;

    return 0;
}

/*
  @ �յ�ʵʱ״̬�������
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

    /* �Ƚ��յ�������cp�������� */
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

    /* ���յ����������һ��������ʵʱ״̬�� */
    if(m_RealTimeTmpLen < nRealTimePackageLen)
    {
        /* û�����꣬�ȴ���һ��recv */
        // do nothing
    }
    else if(m_RealTimeTmpLen == nRealTimePackageLen)
    {
        /* �����ˣ�ֱ��д�뻺�� */
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
        /* �յ��˶�����ݵ�ʱ��д�������ݣ����������� */
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
        /* ��������������ݲ��ܶ�������Ϊ������һ�����ݵ�ǰ��һ���� */
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
        /* �յ������ݰ�������һ��������֮�� */
        ST_RealTimePackage stNewPackage;
        memcpy(&stNewPackage,pRealTimeTmpData ,sizeof(ST_RealTimePackage));
        ret = HandleRealTimeData(info_index, client_fd, (char *)&stNewPackage, sizeof(ST_RealTimePackage));
        if(ret != 0)
        {
            return -1;
        }

        /* ��������������ݲ��ܶ�������Ϊ������һ�����ݵ�ǰ��һ���� */
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
  @ ����һ��������ʵʱ״̬��
*/
int HRC_If_RealTime::HandleRealTimeData(int info_index, int client_fd, const char* pData,int nLen)
{
    if(pData == nullptr || nLen <= 0)
        return -1;

    /* У�����ݵ���ȷ�� */
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

    /* ʵʱ״̬������ ++ */
    recvRealTimeCnt++;

    HRC_Public_Factory::InstallFactory()->GenerateMotionControlFunc()->writeStatus(stStPackage->stData);


    return 0;
}
