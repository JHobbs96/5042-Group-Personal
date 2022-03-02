#include <cstdio>
#include "RPCServer.h"
#include "RPCImpl.h"
#include <sys/socket.h>

int main(int argc, char const* argv[])
{

    const char* serverIP = argv[1];
    int port = atoi(argv[2]);

    bool statusOk = true;
    RPCServer* serverObj = new RPCServer(serverIP, port);
    int v = socket(AF_INET, SOCK_STREAM, 0);
    RPCImpl* impl = new RPCImpl(v);
    // Print it out

    statusOk = serverObj->StartServer();
    printf("Endless loop, as server is up always\n");
    while (statusOk)
    {
        statusOk = serverObj->ListenForClient();
//        statusOk = serverObj->ProcessRPC(); // Launch thread
        statusOk = impl->ProcessRPC();
    }

    delete serverObj;
    return 0;
}
//
//#if 0
//    std::vector<std::string> tokArray;
//    char buffer[128] = { "connect;mike;mike" };
//    serverObj->ParseTokens(buffer, tokArray);
//#endif
