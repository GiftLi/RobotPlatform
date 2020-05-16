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

int main (int argc, char *argv[])
{
    char path[256];
    char processname[1024];
    get_executable_path(path,processname,sizeof(path));

    printf("directory:%s\nprocessname:%s\n",path,processname);
    string strPath = path;

    if(INIT_ELEBOX_TCP_INSTANCE(en_EleBox_Type_V2,1,"172.18.34.20",502) == nullptr)
    {
        printf("Create EleBox Instance error on Main\n");

        return 0;
    }

    GET_ELEBOX_INSTANCE()->connectEleBox(MODBUS_ERROR_RECOVERY_LINK);

    while(true)
    {
        ST_EleBoxBuf stEleBoxInfo;
        GET_ELEBOX_INSTANCE()->getEleBoxStInfo(stEleBoxInfo);

        printf("\n",stEleBoxInfo.nVerYear);
        printf("\n",stEleBoxInfo.nVerDate);
        printf("\n",stEleBoxInfo.nEmergencyStop);
        printf("\n",stEleBoxInfo.nSafetyGuardStop);
        printf("\n",stEleBoxInfo.nResetSignal_EmergencyStop);
        printf("\n",stEleBoxInfo.nResetSignal_SafetyGuardStop);
        printf("\n",stEleBoxInfo.);
        printf("\n",stEleBoxInfo.);
        printf("\n",stEleBoxInfo.);
        printf("\n",stEleBoxInfo.);
        printf("\n",stEleBoxInfo.);
        
    int ;
    int nRemoteSignal;
    int nThreeStageSwitch_Signal;
    int nDI[en_IO_Number];
    int nDO[en_IO_Number];
    int nSI[en_IO_Number];
    int nSO[en_IO_Number];
    
    int nAnalogIN[en_AnalogIO_Number];
    int nAnalogOutMode[en_AnalogIO_Mode_Number];
    double dbAnalogOut[en_AnalogIO_Number];
    
    double db12V_Voltag;
    double db12V_Current;
    double db24V_Voltag;
    double db24V_Current;
    double db48VIN_Voltag;
    double db48VIN_Current;
    double db48VOUT_Voltag;
    double db48VOUT_Current;



        sleep(1);
    }
    
    return 0;
}
