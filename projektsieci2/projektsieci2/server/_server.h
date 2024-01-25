// Server.h

#ifndef SERVER_H
#define SERVER_H

#ifdef _WIN32
#include <winsock2.h>
#include <io.h>
#pragma comment(lib, "ws2_32.lib")
#endif
#include <vector>
#include <cstring>
#include <queue>

#include <iostream>


#include "MyServerBridge.h"


class Server {
public:
    Server(int port, int pollSize);
    ~Server();

    void run();
    MyServerBridge& getServerBridge();
    int nextPendingConnection();
private:
    MyServerBridge serverBridge;
    std::queue<int> pendingConnections;
    int server_fd;
    struct sockaddr_in address;
    int opt;
    int addrlen;
    const int BUFFER_SIZE = 1024;
    char buffer[1024];

    struct pollfd* fds;
    int nfds;



    std::vector<int> freeIndices;

    void handleNewConnection();

    void handleClientData(int index);
    void sendData(int fd, const char* data, size_t dataSize);
};

#endif // SERVER_H
