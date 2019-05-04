#ifndef __CHANNEL_H__
#define __CHANNEL_H__

#include "KETTLEPlatform.h"

namespace KETTLE{
    class Channel{
    public:
        typedef std::function<void()>        EventCallback;
        Channel(EventCallback read_event
        ,EventCallback write_event
        ,EventCallback error_event);


        ~Channel();

        void handleEvent(int event);

     private:
        EventCallback       _read;
        EventCallback       _write;
        EventCallback       _error;
    };
}

#endif