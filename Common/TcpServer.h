#ifndef __TCP_SERVER_H__
#define __TCP_SERVER_H__
#include "KETTLEPlatform.h"

#include"Acceptor.h"
#include"Thread.h"
namespace KETTLE{
    class TcpServer{
    public:
        TcpServer(const char* ip,KETTLE::uint16 port);
        ~TcpServer(){}

        void start();

        void mainLoop();
        void subLoop();
    private:
        std::unique_ptr<KETTLE::Thread>         _mainReactor;
        std::unique_ptr<KETTLE::Thread>         _subReactor;
        std::unique_ptr<KETTLE::Acceptor>       _acceptor;
        bool                                    _running;
    };
}
#endif