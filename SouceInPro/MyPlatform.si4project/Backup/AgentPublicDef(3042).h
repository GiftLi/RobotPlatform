#pragma once

#define WRITE_RETURN_NB 4

/*************************************************************************
**机器人内核命令结构体
**usStateMachine=状态机
**usInstructionGUID=消息ID
**sCmdIndex=命令索引
**sCmdSubIndex=命令子索引
**nOptResult=操作结果
**nParam=整形参数数组
**dbParam=浮点型参数数组
*************************************************************************/
typedef struct _ST_KernelCmd
{
    int nStateMachine;
    int nInstructionGUID;
    int nCmdIndex;
    int nCmdSubIndex;
    int nrParam[KCMD_IntCnt];
    double drParam[KCMD_DoubleCnt];
    int nOptResult;
	int nReserved;
    _ST_KernelCmd() :nStateMachine(0), nInstructionGUID(0), nCmdIndex(0),
        nCmdSubIndex(0),nOptResult(0),nReserved(0)
    {
        memset(nrParam, 0, sizeof(nrParam));
        memset(drParam, 0, sizeof(drParam));
    }
}ST_KernelCmd;

typedef struct _ST_SDOCmd
{
    int nStateMachine;
    int nInstructionGUID;
    int nReadOrWrite;
    int nSlaveID;
    int nIndex;
    int nSubIndex;
    int nType;
    int nSDOValue;
    int nOptResult;
	int nReserved;

    _ST_SDOCmd() :nStateMachine(0),nInstructionGUID(0), nReadOrWrite(0),
        nSlaveID(0), nIndex(0), nSubIndex(0), nType(0), nSDOValue(0),
        nOptResult(0),nReserved(0)
    {
    }
}ST_SDOCmd;

		

typedef struct _ST_KernelCmdArea
{
    ST_KernelCmd         st_RobotMoveCmdArea;          //404byte
    ST_KernelCmd         st_RobotInitCmdArea;          //404byte
    ST_KernelCmd         st_RobotConfigCmdArea;        //404byte
    ST_SDOCmd            st_SdoDataCmdArea;            //36byte
    ST_EleBoxStatusInfo  st_EleBoxStatusInfo;
	
    unsigned int AgentHeartNb;
	int nReserved;

	_ST_KernelCmdArea():AgentHeartNb(0),nReserved(0)
	{	
		memset(&st_RobotMoveCmdArea,0,sizeof(st_RobotMoveCmdArea));
		memset(&st_RobotInitCmdArea,0,sizeof(st_RobotInitCmdArea));
		memset(&st_RobotConfigCmdArea,0,sizeof(st_RobotConfigCmdArea));
		memset(&st_SdoDataCmdArea,0,sizeof(st_SdoDataCmdArea));
		memset(&st_EleBoxStatusInfo,0,sizeof(st_EleBoxStatusInfo));
	}
}ST_WriteArea;

typedef struct _ST_ReadCmdArea
{
    //Write Area      Actual =1208Byte     totle=4096Byte---4KB 
    ST_RobotRTStatu st_StatusArea;
    ST_ScopeInfo st_ScopeArea;
	ST_KernelCmd st_BoxCmd;
	
}ST_ReadArea;





