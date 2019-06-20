#include "AsynLog.h"
#include"TemplateFunctions.h"
#include "Log.h"

using namespace KETTLE;

class TestAsynLog{
    typedef std::shared_ptr<Thread>     ThreadPtr;
public:

    static void OutPut(const char* log,int len){
        m_pSelf->asynLog.append(log,len);
    }
    static void Flush(){
        m_pSelf->asynLog.flush();
    }

    TestAsynLog(){
        m_pSelf = this;
        KETTLE::Logger::setOutPutFunc(TestAsynLog::OutPut);
        KETTLE::Logger::setFlushFunc(TestAsynLog::Flush);

        asynLog.start();
        threads.reserve(5);
        for(int32 i = 0; i < 5;++i){
            threads.push_back(std::make_shared<Thread>(std::bind(&TestAsynLog::thread_func,this)));
            //threads[i].reset(new Thread(std::bind(&TestAsynLog::thread_func,this)));
            threads[i]->start();
        }
    }
protected:
    void thread_func(){
        while(1){
            char szInfo[128] = {0};
            snprintf(szInfo,sizeof(szInfo),"%s",CommonFunction::now().c_str());
            LOG_INFO << szInfo;
        }
    }
private:
    std::vector<ThreadPtr>     threads;
    AsynLog         asynLog;
    static TestAsynLog*        m_pSelf;     
};
TestAsynLog* TestAsynLog::m_pSelf = NULL;

int main(int argc,char* argv[]){

    std::unique_ptr<TestAsynLog> testLog(new TestAsynLog());

    while(1){
        ;
    }

    exit(0);
}