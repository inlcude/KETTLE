#include"stdafx.h"
#include"TemplateFunctions.h"
#include "Log.h"

using namespace KETTLE;

void KETTLE::CommonFunction::FunctionSleep(int milsec)
{
#if __WINDOWS__
    Sleep(milsec);
#elif __LINUX__
    ::nanosleep(milsec * 1000 * 1000);
#endif
}

const std::string& CommonFunction::GetAppName(){

    char path[128] = {0};
    int rval = readlink("/proc/self/exe/",path,sizeof(path)-1);
    if(rval <= -1)
        err_exit(errno,"readlink error");
    char* pch = strrchr(path,'/');
    return std::string(pch);
}

const std::string& CommonFunction::now(){
    struct timeval time_struct;
    gettimeofday(&time_struct,NULL);
    tm* tm_time = localtime(&time_struct.tv_sec);

    char szTime[128] = {0};

    snprintf(szTime,128,"%d_%d%d_%d%d%d",
    tm_time->tm_year,tm_time->tm_mon,tm_time->tm_mday,tm_time->tm_hour,tm_time->tm_min,tm_time->tm_sec);

    return std::string(szTime);
}