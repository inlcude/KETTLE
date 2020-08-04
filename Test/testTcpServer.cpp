#include "Log.h"
#include "TcpServer.h"

using namespace KETTLE;

void read_cb(TcpServer::TcpConnectionPtr ptr,std::string& message)
{

}

void write_cb(TcpServer::TcpConnectionPtr ptr,std::string& message)
{

}

void error_cb(TcpServer::TcpConnectionPtr ptr,std::string& message)
{
}



int main(int argc,char* argv){
    TcpServer server("0.0.0.0",9527,8,read_cb,write_cb,error_cb);
    server.start();

    return 0;
}