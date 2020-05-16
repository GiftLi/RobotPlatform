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

protected:
	bool mallocShareMemory(void);

	static void *syncThread(void* pParam);
	bool syncHandle(void);
	
	
	int writeShareMemory(void* pWriteArea,const string& strCmd,
										const int& nIntParamNb,const int* pIntParamList,
										const int& nDoubleParamNb,const double* dDoubleParamNb);

	int readShareMemory(ST_ReadArea& stResponse);

private:
	ST_WriteArea* m_pWriteArea;
	ST_ReadArea*  m_pReadArea;

	int arrnWriteRetBuf[WRITE_RETURN_NB];
	ST_ReadArea m_stReadAreaBuf;

	pthread_t m_syncThread;
};



