#pragma once

#include <windows.h>

#pragma comment(lib, "ws2_32.lib")

class Connection {
private:
    constexpr static char* ip = "127.0.0.1";
    constexpr static u_short port = 15200;

    SOCKET clientSocket;

public:
    Connection();
    Connection(const Connection&) = delete;
    Connection(const Connection&&) = delete;
    ~Connection();

    Connection& operator=(Connection&) = delete;
    Connection& operator=(Connection&&) = delete;

    bool isOpen() const;
    int receive(char* recvBuf, int recvBufSize) const;
};