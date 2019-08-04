#include "Log.h"
#include "TcpServer.h"

using namespace KETTLE;

int main(int argc,char* argv){
    TcpServer server("0.0.0.0",65432,4);
    server.start();
}