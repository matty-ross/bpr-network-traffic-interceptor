#pragma once


#include <WinSock2.h>


class Client
{
public:
    Client();
    ~Client();

    void Connect(const char* ip, int port) const;
    void Disconnect() const;

    void SendData(const void* data, size_t size) const;

private:
    SOCKET m_Socket = INVALID_SOCKET;
    mutable bool m_Connected = false;
};