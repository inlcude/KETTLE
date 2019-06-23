#ifndef __EVENT_LOOP_H__
#define __EVENT_LOOP_H__
#include"KETTLEPlatform.h"
#include"Channel.h"

using namespace KETTLE;
namespace KETTLE{
    class EpollPoller;
    class EventLoop{
        
    public:
        EventLoop();
        ~EventLoop();

        void runInLoop(const Channel* channel);
        void exitInLoop(const char* Channel);
        void startLoop();
        void stopLoop();
    private:
        bool            _running;
        std::unique_ptr<EpollPoller>        _poller;
    };
}

#endif