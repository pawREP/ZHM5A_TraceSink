#include "Connection.h"

Connection::Connection() : clientSocket(INVALID_SOCKET) {
    WSADATA wsaData;
    int iResult = 0;

    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != NO_ERROR)
        return;

    SOCKET listenSocket = INVALID_SOCKET;
    listenSocket = socket(AF_INET, SOCK_STREAM, NULL);
    if (listenSocket == INVALID_SOCKET)
        return;

    sockaddr_in service;
    service.sin_family = AF_INET;
    service.sin_addr.s_addr = inet_addr(ip);
    service.sin_port = htons(port);

    iResult = bind(listenSocket, (SOCKADDR*)&service, sizeof(service));
    if (iResult == SOCKET_ERROR) {
        closesocket(listenSocket);
        return;
    }

    iResult = listen(listenSocket, SOMAXCONN);
    if (iResult == SOCKET_ERROR) {
        closesocket(listenSocket);
        return;
    }

    clientSocket = accept(listenSocket, NULL, NULL);

    closesocket(listenSocket);
}

Connection::~Connection() {
    closesocket(clientSocket);
    WSACleanup();
}

bool Connection::isOpen() const {
    return clientSocket != INVALID_SOCKET;
}

int Connection::receive(char* recvBuf, int recvBufSize) const {
    auto size = recv(clientSocket, recvBuf, recvBufSize, 0);
    if (size <= 0)
        closesocket(clientSocket);
    return size;
}
