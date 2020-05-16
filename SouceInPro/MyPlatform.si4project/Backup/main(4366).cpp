#include <iostream>
#include <string>
#include <unistd.h>

#include <limits.h>
#include <stdio.h>
#include <string.h>

#include "../Platform_EleBox/ElectricityBox/EleBoxFactory.h"

using namespace std;



size_t get_executable_path(char* processdir,char*processname,size_t len)
{
    char* path_end;

    if(readlink("/proc/self/exe",processdir,len)<=0)
    {
        return -1;
    }

    path_end = strrchr(processdir,'/');

    if(path_end == nullptr)
    {
        return  -1;
    }

    ++path_end;

    strcpy(processname,path_end);

    *path_end = '\0';

    return (size_t)(path_end - processname);
}

void printfEleBoxInfo(ST_EleBoxBuf& stEleBoxInfo)
{
	printf("[nVerYear=%d ,nVerDate=%d]\n",stEleBoxInfo.nVerYear,stEleBoxInfo.nVerDate);
    printf("[nEmergencyStop=%d]\t",stEleBoxInfo.nEmergencyStop);
    printf("[nSafetyGuardStop=%d]\n",stEleBoxInfo.nSafetyGuardStop);
    printf("[nResetSignal_EmergencyStop=%d]\t",stEleBoxInfo.nResetSignal_EmergencyStop);
    printf("[nResetSignal_SafetyGuardStop=%d]\t",stEleBoxInfo.nResetSignal_SafetyGuardStop);
    printf("[nRemoteSignal=%d]\n",stEleBoxInfo.nRemoteSignal);
    printf("[nThreeStageSwitch_Signal=%d]\n",stEleBoxInfo.nThreeStageSwitch_Signal);
	
	for(int nNb=0; nNb < 8; nNb++)
	{
		printf("[nDI_%d=%d]\t",nNb,stEleBoxInfo.nDI[nNb]);
    	printf("[nDO_%d=%d]\t",nNb,stEleBoxInfo.nDO[nNb]);
    	printf("[nSI_%d=%d]\t",nNb,stEleBoxInfo.nSI[nNb]);
		printf("[nSO_%d=%d]\n",nNb,stEleBoxInfo.nSO[nNb]);
	}
    
	for(int nNb=0; nNb < 2; nNb++)
	{
		printf("[nAnalogIN_CH%d=%d]\t",nNb,stEleBoxInfo.nAnalogIN[nNb]);
    	printf("[nAnalogOutMode_CH%d=%d]\t",nNb,stEleBoxInfo.nAnalogOutMode[nNb]);
    	printf("[dbAnalogOut_CH%d=%f]\n",nNb,stEleBoxInfo.dbAnalogOut[nNb]);
	}
    
	printf("[db12V_Voltag=%f]\t",stEleBoxInfo.db12V_Voltag);
    printf("[db12V_Current=%f]\t",stEleBoxInfo.db12V_Current);
    printf("[db24V_Voltag=%f]\n",stEleBoxInfo.db24V_Voltag);
    printf("[db24V_Current=%f]\t",stEleBoxInfo.db24V_Current);
	printf("[db48VIN_Voltag=%f]\t",stEleBoxInfo.db48VIN_Voltag);
    printf("[db48VIN_Current=%f]\n",stEleBoxInfo.db48VIN_Current);
    printf("[db48VOUT_Voltag=%f]\t",stEleBoxInfo.db48VOUT_Voltag);
    printf("[db48VOUT_Current=%f]\n",stEleBoxInfo.db48VOUT_Current);

    printf("\n\n");
}

int main (int argc, char *argv[])
{
    char path[256];
    char processname[1024];
    get_executable_path(path,processname,sizeof(path));

    printf("directory:%s\nprocessname:%s\n",path,processname);
    string strPath = path;

    if(INIT_ELEBOX_TCP_INSTANCE(en_EleBox_Type_V2,1,"172.18.34.38",502) == nullptr)
    {
        printf("Create EleBox Instance error on Main\n");

        return 0;
    }

    GET_ELEBOX_INSTANCE()->connectEleBox(MODBUS_ERROR_RECOVERY_LINK);

    while(true)
    {
        ST_EleBoxBuf stEleBoxInfo;
        GET_ELEBOX_INSTANCE()->getEleBoxStInfo(stEleBoxInfo);
		
		printfEleBoxInfo(stEleBoxInfo);
        
        sleep(5);
    }
    
    return 0;
}
