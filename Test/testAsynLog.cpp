#include "AsynLog.h"
#include"TemplateFunctions.h"

using namespace KETTLE;

class TestAsynLog{
    typedef std::unique_ptr<Thread>     ThreadPtr;
public:
    TestAsynLog(){
        asynLog.start();
        threads.reserve(5);
        for(int32 i = 0; i < 5;++i){
            threads[i].reset(new Thread(std::bind(&TestAsynLog::thread_func,this)));
            threads[i]->start();
        }
    }
protected:
    void thread_func(){
        while(1){
            char szInfo[128] = {0};
            snprintf(szInfo,sizeof(szInfo),"%s",CommonFunction::now().c_str());
            asynLog.append(szInfo,sizeof(szInfo));
        }
    }
private:
    std::vector<ThreadPtr>     threads;
    AsynLog         asynLog;
};

int main(int argc,char* argv[]){

    std::unique_ptr<TestAsynLog> testLog(new TestAsynLog());

    while(1){
        ;
    }

    exit(0);
}