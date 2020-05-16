#pragma once

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
	
}ST_ShmSyncData;



