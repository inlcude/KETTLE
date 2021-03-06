#include "Log.h"
#include "TemplateFunctions.h"

static int MAXLINE = 1024;

using namespace KETTLE;

static void err_doit(int errnoflag,int error,const char* fmt,va_list ap)
{
    char buf[MAXLINE];

    vsnprintf(buf,MAXLINE-1,fmt,ap);
    if(errnoflag) snprintf(buf + strlen(buf),MAXLINE - strlen(buf) - 1,":%s",strerror(error));

    strcat(buf,"\n");
    fflush(stdout);
    fputs(buf,stderr);
    fflush(NULL);
}

void err_ret(const char* fmt,...)
{
    va_list ap;

    va_start(ap,fmt);
    err_doit(1,errno,fmt,ap);
    va_end(ap);
    exit(1);
}

void err_sys(const char* fmt,...)
{
    va_list ap;

    va_start(ap,fmt);
    err_doit(1,errno,fmt,ap);
    va_end(ap);
    exit(1);
}

void err_cont(int error,const char* fmt,...)
{
    va_list ap;

    va_start(ap,fmt);
    err_doit(1,error,fmt,ap);
    va_end(ap);
}

void err_exit(int error,const char* fmt,...)
{
    va_list ap;

    va_start(ap,fmt);
    err_doit(1,error,fmt,ap);
    va_end(ap);
    exit(1);
}

void err_dump(const char* fmt,...)
{
    va_list ap;

    va_start(ap,fmt);
    err_doit(1,errno,fmt,ap);
    va_end(ap);
    abort();
    exit(1);
}

void err_msg(const char* fmt,...)
{
    va_list ap;

    va_start(ap,fmt);
    err_doit(0,0,fmt,ap);
    va_end(ap);
}

void err_quit(const char* fmt,...)
{
    va_list ap;

    va_start(ap,fmt);
    err_doit(0,0,fmt,ap);
    va_end(ap);
    exit(1);
}


static const char* LOGGER_LEVEL[] = {
    "LOG_INFO",
    "LOG_TRACE",
    "LOG_DEBUG",
    "LOG_ERROR",
    "LOG_FATA"
};

OutPutFunc Logger::outfunc = Logger::DefaultWrite;
FlushFunc Logger::flushfunc = Logger::DefaultFlush;


Logger::Logger(LogLevel level) : 
logLevel(level){
    stream << "[" << LOGGER_LEVEL[level] << "]" << 
    "[" << std::string(std::move(CommonFunction::now())) << "]"
    << "[" << CommonFunction::GetSelfThreadId() << "]";
}

Logger::~Logger(){
    stream << "\n";
    outfunc(stream.data(),stream.length()+1);
    flushfunc();

    if (outfunc != Logger::DefaultWrite){
        Logger::DefaultWrite(stream.data(),stream.length()+1);
        Logger::DefaultFlush();
    }

    if(logLevel >= KETTLE_LOGGER_LEVEL_FATA)
        std::abort();
}

void Logger::DefaultWrite(const char* log,int len){
    ::fwrite(log,len,1,stdout);
}

void Logger::DefaultFlush(){
    ::fflush(stdout);
}