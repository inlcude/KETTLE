#ifndef __CONNECTOR_H__
#define __CONNECTOR_H__

#include "KETTLEPlatform.h"

using namespace KETTLE;

class Channel;
class EventLoop;
namespace KETTLE{
    class Connector{
        typedef std::function<void(int32 sockfd)>  CONNECT_CALLBACK;
    public:
        Connector();

    private:

        std::unique_ptr<Channel>            _channel;
        EventLoop*                          _loop;
        CONNECT_CALLBACK                    _connect_cb;
    };
}
#endif