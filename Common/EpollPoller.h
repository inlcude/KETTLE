#ifndef __EPOLL_POLLER_H__
#define __EPOLL_POLLER_H__
#include "KETTLEPlatform.h"

using namespace KETTLE;
namespace KETTLE{
    class Channel;
    class EpollPoller{
        typedef std::list<std::weak_ptr<Channel>>     ChannelList;
    public:
        EpollPoller();

        void start();
        void registerInPoller(Channel* channel);
    private:

        ChannelList                   _channelLIst;
    };
}
#endif
