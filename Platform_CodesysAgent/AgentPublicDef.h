#pragma once



#define INT_PARAM_LENGHT 32
#define DOUBLE_PARAM_LENGHT 32

typedef enum _EN_WriteRetVal
{
	enMoveCmdRet=0,
    enInitCmdAreaRet,
    enConfigCmdAreaRet,
    enSdoDataCmdAreaRet,
    enWriteRetNum
    
}EN_WriteRetVal;


typedef enum _EN_WRITE_FUNC_CODE
{
	enWriteConfigCmd=0,
	enWriteInitCmd,
	enWriteMoveCmd,
	enWriteSDOCmd,
	enWriteCmdCnt
}EN_WRITE_FUNC_CODE;

typedef struct _ST_UserKernelParam
{
	/* user KernelCmd Param */
	int nCmdSubIndex;
	int nIntParamNb;
	int nDoubleParamNb;
	
    int nrParam[INT_PARAM_LENGHT];
    double drParam[DOUBLE_PARAM_LENGHT];

	_ST_UserKernelParam():nCmdSubIndex(0)
		{
			memset(nrParam,0,sizeof(int)*INT_PARAM_LENGHT);
			memset(drParam,0,sizeof(int)*INT_PARAM_LENGHT);
		}

}ST_UserKernelParam;

typedef struct _ST_UserSDOParam
{
	int nReadOrWrite;
	int nSlaveID;
	int nType;

	_ST_UserKernelParam():nReadOrWrite(0),nSlaveID(0),nType(0){};

}ST_UserSDOParam;


typedef struct _ST_WriteParam
{
	/* public Param */
	int nCmdIndex;
	int nStateMachine;
    int nInstructionGUID;
	
	/* KernelCmd Param */
    ST_UserKernelParam stKernelUserParam;

	/* SDOCmd Param */
	ST_UserSDOParam stSDOUserParam;

	_ST_WriteParam():nStateMachine(0),nInstructionGUID(0),nCmdIndex(0){};
	
}ST_WriteParam;

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
    int nrParam[INT_PARAM_LENGHT];
    double drParam[DOUBLE_PARAM_LENGHT];
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

typedef struct _ST_ShmArea
{
	ST_WriteArea stWriteArea;
	ST_ReadArea stReadArea;
	
}ST_ShmArea;

typedef struct _ST_KernelCmdArea
{
    ST_KernelCmd         st_RobotMoveCmdArea;          //404byte
    ST_KernelCmd         st_RobotInitCmdArea;          //404byte
    ST_KernelCmd         st_RobotConfigCmdArea;        //404byte
    ST_SDOCmd            st_SdoDataCmdArea;            //36byte
    ST_EleBoxBuf         st_EleBoxInfo;
	
    unsigned int         AgentHeartNb;
	int                  nReserved;

	_ST_KernelCmdArea():AgentHeartNb(0),nReserved(0)
	{	
		memset(&st_RobotMoveCmdArea,0,sizeof(st_RobotMoveCmdArea));
		memset(&st_RobotInitCmdArea,0,sizeof(st_RobotInitCmdArea));
		memset(&st_RobotConfigCmdArea,0,sizeof(st_RobotConfigCmdArea));
		memset(&st_SdoDataCmdArea,0,sizeof(st_SdoDataCmdArea));
		memset(&ST_EleBoxBuf,0,sizeof(ST_EleBoxBuf));
	}
}ST_WriteArea;

typedef struct _ST_ReadCmdArea
{
    //Write Area      Actual =1208Byte     totle=4096Byte---4KB 
    ST_RobotRTStatu st_StatusArea;
    ST_ScopeInfo st_ScopeArea;
	ST_KernelCmd st_BoxCmd;
	
}ST_ReadArea;





