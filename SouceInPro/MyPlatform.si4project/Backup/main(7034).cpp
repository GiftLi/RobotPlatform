#include <iostream>
#include <string>
#include <unistd.h>
#include "MotionConfig.h"
#include "../ElectricityBox/myModbusMaster.h"
#include "../Public/publicFactory.h"

#include <limits.h>
#include <stdio.h>
#include <string.h>

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
    MOTION_GET_LOG()->initLog(strPath);
    /*
    if(argc < 2)
    {
        printf("%s Version %d.%d\n",argv[0],Motion_VERSION_MAJOR,Motion_VERSION_MINOR);
        printf("Usage: %s number\n",argv[0]);
        return 1;
    }

    double inputNb1 = atof(argv[1]);
    double inputNb2 = atof(argv[2]);

    double outputSum = inputNb1 + inputNb2;

    printf("Express : %f + %f = %f\n",inputNb1,inputNb2,outputSum);
    
    motion_modbus_rtu_master* tmp = new motion_modbus_rtu_master();
    if(!tmp->connect())
    {
        string strError = "";
        tmp->getErrorInfo(strError);
        printf(" modbus connect error :%s\n",strError.c_str());
    }
    else
    {
        printf("connect successful~~\n");

        //printf("read add[4]_value = %d\n",tmp->readData());

        printf("write ret = %d\n",tmp->writeDate(4, 1));

        sleep(1);



        tmp->close();
    }
    */

    /*
    printf("write ret = %d\n",tmp->writeDate(0, 1));

    string strError = "";
    tmp->getErrorInfo(strError);
    printf(" modbus write error :%s\n",strError.c_str());

    printf("hello word!\n");
    */
    
    
    return 0;
}
