#include "_server.h"

Server::Server(int port, int pollSize) : opt(1), addrlen(sizeof(address)), nfds(1) {
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "Failed to initialize Winsock" << std::endl;
        exit(EXIT_FAILURE);
    }

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, (const char*)&opt, sizeof(opt)) == -1) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    fds = new pollfd[pollSize];
    fds[0].fd = server_fd;
    fds[0].events = POLLIN;
}

Server::~Server() {
    WSACleanup();

    _close(server_fd);
    delete[] fds;
}

void Server::run() {
    while (true) {
        int ret;

        printf("%i", nfds);

        ret = WSAPoll(fds, nfds, -1);

        if (ret < 0) {
            perror("WSAPoll");
            exit(EXIT_FAILURE);
        }

        if (fds[0].revents & POLLIN) {
            handleNewConnection();
        }

        for (int i = 1; i < nfds; i++) {
            if (fds[i].revents & POLLIN) {
                handleClientData(i);
            }
        }
    }
}

void Server::handleNewConnection() {
    int new_socket;
    //if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (int *)&addrlen)) < 0) {
    if ((new_socket = accept(server_fd, nullptr, nullptr)) < 0) {
        perror("accept");
        exit(EXIT_FAILURE);
    }
    pendingConnections.push(new_socket);


    int index;

    if (!freeIndices.empty()) {
        index = freeIndices.back();
        freeIndices.pop_back();
    } else {
        index = nfds;
        nfds++;
    }

    fds[index].fd = new_socket;
    fds[index].events = POLLIN;
    serverBridge.onNewConnection();

    std::cout << "New client connected" << std::endl;
}

void Server::handleClientData(int index) {
    serverBridge.onReadyRead(fds[index].fd);
}

int Server::nextPendingConnection() {
    if (!pendingConnections.empty()) {
        auto nextConnection = pendingConnections.front();
        pendingConnections.pop();
        return nextConnection;
    }

    return -1;
}

MyServerBridge& Server::getServerBridge(){
    return serverBridge;
};
