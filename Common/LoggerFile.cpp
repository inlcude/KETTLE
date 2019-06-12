#include "stdafx.h"
#include"KETTLEPlatform.h"
#include"TemplateFunctions.h"
#include "LoggerFile.h"


LoggerFile::LoggerFile(){
    char szFileName[128] = {0};
    /*
     *  YYYY_MMDD_HHMMSS_PROCESSNAME.log
     */
    snprintf(szFileName,128,"%s_%s.log",CommonFunction::now().c_str(),CommonFunction::GetAppName().c_str());
    file = fopen(szFileName,"wa+");
}

void LoggerFile::flush(){

}