#pragma once

#include "../AgentPublicDef.h"
#include "../ShareMemory/BaseShareMemory.h"
#include "../../Platform_Public/PublibDef.h"

class CodesysAgent
{
public:
	CodesysAgent(); //实例化组合
	~CodesysAgent();

public:
	static void *syncCodesysRequest(void* pParam);
	static void *syncEleBoxInfo(void* pParam);
	bool handleCodesysRequest(void);

	/* 操作写区域的接口函数 */
	int callRobotMoveCmd(const ST_UserKernelParam& stParam);
	int callRobotConfigCmd(const ST_UserKernelParam& stParam);
    int callRobotInitCmd(const ST_UserKernelParam& stParam);
	int sendEleBoxInfoToCodesys(const ST_EleBoxBuf &stEleBoxInfo);

	/* 操作读区域的接口函数 */
	bool getCodesysCmd(ST_KernelCmd &st_CodesysCmd);
	bool readStatusInfo(ST_RobotRTStatu& rbtState);
	bool readScopeInfo(const int nRbtID, ST_ScopeInfo& rbtScope);
	bool readConnectStatus(void);

private:
	ShareMemory* pShmInstance;
	BaseEleBox* pEleBoxInstance;
	
	pthread_t m_syncRequestThread;
	pthread_t m_syncEleBoxInfoThread;
};



