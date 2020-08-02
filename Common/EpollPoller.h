#ifndef __EPOLL_POLLER_H__
#define __EPOLL_POLLER_H__
#include "KETTLEPlatform.h"

using namespace KETTLE;
namespace KETTLE{

    enum EO_EVENTS{
        EO_ADD      = 1,
        EO_DEL      = 2,
        EO_MOD      = 3,
    };
    class Channel;
    class EpollPoller{
        typedef std::map<int32,Channel*>     ChannelList;
        typedef ChannelList::iterator ItrChannel;
    public:
        EpollPoller();

        void registerInPoller(Channel* channel);
        void removeChannel(Channel* Channel);
        void poller();
        void updateChannel(EO_EVENTS operation,Channel* channel);
        void updateChannel(Channel* channel);
    private:
        int32                         _epollfd;
        ChannelList                   _channelList;
        std::vector<struct epoll_event >  _events;


        static const int32 INIT_DEFAULT_EVENTS_SIZE = 16;
    };
}
#endif
