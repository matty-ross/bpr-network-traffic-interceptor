#include "WinSockManager.h"

#include <WinSock2.h>


WinSockManager::WinSockManager()
{
    WSADATA wsaData = {};
    [[maybe_unused]] const int _ = WSAStartup(MAKEWORD(2, 2), &wsaData);
}

WinSockManager::~WinSockManager()
{
    WSACleanup();
}