#include "Client.h"

#include <WS2tcpip.h>


Client::Client()
{
    m_Socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
}

Client::~Client()
{
    if (m_Connected)
    {
        Disconnect();
    }

    closesocket(m_Socket);
}

void Client::Connect(const char* ip, int port) const
{
    sockaddr_in address = {};
    address.sin_family = AF_INET;
    address.sin_port = htons(port);
    inet_pton(AF_INET, ip, &address.sin_addr);
    
    connect(m_Socket, reinterpret_cast<sockaddr*>(&address), sizeof(address));
    m_Connected = true;
}

void Client::Disconnect() const
{
    shutdown(m_Socket, SD_BOTH);
    m_Connected = false;
}

void Client::SendData(const void* data, size_t size) const
{
    send(m_Socket, static_cast<const char*>(data), size, 0);
}