#include "stdafx.h"
#include"KETTLEPlatform.h"
#include"TemplateFunctions.h"
#include "LoggerFile.h"
#include "Log.h"


LoggerFile::LoggerFile(){
    char szFileName[128] = {0};
    /*
     *  YYYY_MMDD_HHMMSS_PROCESSNAME.log
     */
    snprintf(szFileName,128,"%s_%s.log",CommonFunction::now().c_str(),CommonFunction::GetAppName().c_str());
    file = fopen(szFileName,"a+");
    if(!file)
        LOG_FATA << "open faile error,filename= " << szFileName << " reson = " << strerror(errno);
}

void LoggerFile::flush(){
    fflush(file);
}

void LoggerFile::append(const char* log,uint32 len){
    uint32 nremain = len;

    while (nremain > 0){
       size_t write_size = fwrite_unlocked(log,nremain,1,file);
       nremain -= write_size;
       if(nremain > 0)
            log += write_size;
    }
    
    flush();
}