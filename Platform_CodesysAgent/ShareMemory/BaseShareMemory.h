#pragma once
#include <string>
#include <pthread.h>
#include <unistd.h>


#include "../AgentPublicDef.h"

class ShareMemory
{
public:
	ShareMemory();
	~ShareMemory();

public:
	bool mallocShareMemory(void);

	static void *syncThread(void* pParam);
	bool syncHandle(void);
	
	
	int writeShareMemory(const EN_WRITE_FUNC_CODE enWriteFuncCode,const ST_WriteParam& stWriteParam);

	int readShareMemory(ST_ReadArea& stResponse);

	int sendHeart(void);

protected:
	int updateShmBuf(void);
	int updateReadAreaBuf(void);
	int updateWriteRetBuf(void);
	int updateAgentHeart(void);

private:
	ST_ShmArea* m_pShm;
	ST_WriteArea* m_pWriteArea;
	ST_ReadArea*  m_pReadArea;

	int arrnWriteRetBuf[enWriteRetNum];
	ST_ReadArea m_stReadAreaBuf;
	unsigned int m_nHeartCnt;

	pthread_t m_syncThread;

	SaftLock m_lShmLock;
};



