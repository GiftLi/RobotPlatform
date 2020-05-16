#include <iostream>
#include <string>
#include <unistd.h>

#include <limits.h>
#include <stdio.h>
#include <string.h>

#include "../Platform_EleBox/ElectricityBox/BaseEleBox.h"



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

    GET_ELEBOX_TCP_INSTANCE(4,1,"172.18.34.38",502);
    
    return 0;
}
