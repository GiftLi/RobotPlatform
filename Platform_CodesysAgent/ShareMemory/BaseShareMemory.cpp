#include "BaseShareMemory.h"

ShareMemory::ShareMemory():m_nHeartCnt(0)
{
	memset(arrnWriteRetBuf,0,sizeof(int)*enWriteRetNum);
	
	mallocShareMemory();
	
	/* 创建线程 */
	if(-1 == pthread_create(&m_syncThread, nullptr, syncThread, this))
	{
		printf("create pthread error on ShareMemory\n");

		return;
	}
}

	
ShareMemory::~ShareMemory();
{
	if (munmap(m_pShm, sizeof(ST_ShmArea)) == -1)
	{
	  printf("munmap error\n");
	  
	  return;
	}
}

bool ShareMemory::mallocShareMemory(void)
{
	/* 申请内存 */
	char sSharedMemReadName[100] = "HansRobot_SharedMemory";

    int fd = shm_open(sSharedMemReadName, O_CREAT | O_RDWR, S_IRWXU | S_IRWXG);

	if(0 > fd)
	{
		//共享内存可能已经存在
		fd = shm_open(sSharedMemReadName, O_RDWR, 0777);
        if(fd < 0)  //打开失败
        {
            printf("error open shm object\n");
            return false;
        }
		
	}
	
	int nSHMLen = sizeof(ST_ShmArea);
    int ret = ftruncate(fd, nSHMLen);

	if(0 > ret)
	{
		printf("Shm ftruncate error [ret=%d]\n",ret);
		close(fd);
		return false;
	}

	/* 空间映射 */
	m_pShm = (ST_ShmArea *)mmap(0, nSHMLen, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

	if (m_pShm==nullptr)
	{
		printf("mmap error on shareMemory\n");
		close(fd);
		return false;
	}
	
	m_pWriteArea = &(m_pShm->stWriteArea);
    m_pReadArea = &(m_pShm->stReadArea);
	
    printf("Init ShareMemory successful : [name=%s]\t[fd=%d]\n",sSharedMemReadName, fd);

	return true;
}


void* ShareMemory::syncThread(void* pParam)
{
	/* 执行周期需要严格测试 */
	__useconds_t MS_20 = 20 * 1000; 
	
	while(true)
	{
		syncHandle();
		
		usleep(MS_20);
	}
}

bool ShareMemory::syncHandle(void)
{
	updateShmBuf();

	return true;
}

int ShareMemory::updateShmBuf(void)
{
	AutoSaftMutex ShmLock(&m_lShmLock);

	//获取数据：读区域
	updateReadAreaBuf();
	
	//获取数据：写返回
	updateWriteRetBuf();
	
	//喂狗
	updateAgentHeart();
	
}

int ShareMemory::updateReadAreaBuf(void)
{
	memcpy(&m_stReadAreaBuf,m_pReadArea,sizeof(ST_ReadArea));

	return 0;
}

int ShareMemory::updateWriteRetBuf(void)
{
	arrnWriteRetBuf[enMoveCmdRet] = m_pWriteArea->st_RobotMoveCmdArea.nOptResult;
	arrnWriteRetBuf[enInitCmdAreaRet] = m_pWriteArea->st_RobotInitCmdArea.nOptResult;
	arrnWriteRetBuf[enConfigCmdAreaRet] = m_pWriteArea->st_RobotConfigCmdArea.nOptResult;
	arrnWriteRetBuf[enSdoDataCmdAreaRet] = m_pWriteArea->st_SdoDataCmdArea.nOptResult;

	return 0;
}

int ShareMemory::updateAgentHeart(void)
{
	m_pWriteArea->AgentHeartNb == ++m_nHeartCnt;

    return 0;
}




