#include "stdafx.h"
#include "EpollPoller.h"
#include "Channel.h"
#include "Log.h"

const int32 epoll_ctl_events[] = {
    0,
    EPOLL_CTL_ADD,
    EPOLL_CTL_DEL,
    EPOLL_CTL_MOD
};

EpollPoller::EpollPoller():
_epollfd(::epoll_create(INIT_DEFAULT_EVENTS_SIZE)){
    _events.resize(INIT_DEFAULT_EVENTS_SIZE);
}

void EpollPoller::registerInPoller(Channel* channel){
    _channelList[channel->getSockfd()] = channel;
    updateChannel(EO_ADD,channel);
}

void EpollPoller::removeChannel(Channel* channel){
    ItrChannel itr = _channelList.find(channel->getSockfd());
    if(itr != _channelList.end())
        _channelList.erase(itr);
}

void EpollPoller::updateChannel(EO_EVENTS operation,Channel* channel){

    const int32 sockfd = channel->getSockfd();
    const int32 events = channel->getEvents();

    struct epoll_event e_event;
    memset(&e_event,0,sizeof(e_event));
    e_event.events = events;
    e_event.data.ptr = channel;

    int32 op = epoll_ctl_events[operation];

    if(::epoll_ctl(_epollfd,op,sockfd,&e_event) != 0)
        LOG_FATA << "cpoll_ctl failed,reason:" << strerror(errno);
}

void EpollPoller::poller(){
    int32 nActiveNum = ::epoll_wait(_epollfd,&_events[0],_events.size(),0);
    for(int32 i = 0; i < nActiveNum;++i){
        Channel* channel = static_cast<Channel*>(_events[i].data.ptr);
        int32 events = _events[i].events;
        channel->handleEvent(events);
    }

    if(nActiveNum == _events.size())
        _events.resize(_events.size() * 2);
}