#include "WinSockManager.h"
#include "Client.h"
#include "Hook.h"


static constexpr const char* const k_ServerIP = "127.0.0.1";
static constexpr const int k_SendPort = 8888;
static constexpr const int k_RecvPort = 9999;


static WinSockManager* s_WinSockManager = nullptr;
static Client* s_SendClient = nullptr;
static Client* s_RecvClient = nullptr;
static Hook* s_SendHook = nullptr;
static Hook* s_RecvHook = nullptr;


__declspec(naked) static void ProxySend()
{
    __asm
    {
        pushfd
        pushad

        push dword ptr [ebp + 0x10]
        push dword ptr [ebp + 0xC]
        mov ecx, s_SendClient
        call Client::SendData

        popad
        popfd

        ret
    }
}

__declspec(naked) static void ProxyRecv()
{
    __asm
    {
        pushfd
        pushad

        push dword ptr [ebp + 0x14]
        push dword ptr [ebp + 0x10]
        mov ecx, s_RecvClient
        call Client::SendData

        popad
        popfd

        ret
    }
}

static void Initialize()
{
    s_WinSockManager = new WinSockManager();
    
    s_SendClient = new Client();
    s_SendClient->Connect(k_ServerIP, k_SendPort);
    s_SendHook = new Hook(reinterpret_cast<void*>(0x03A0CB63), 7);
    s_SendHook->Enable(ProxySend);
    
    s_RecvClient = new Client();
    s_RecvClient->Connect(k_ServerIP, k_RecvPort);
    s_RecvHook = new Hook(reinterpret_cast<void*>(0x03A0D0B1), 5);
    s_RecvHook->Enable(ProxyRecv);
}

static void Shutdown()
{
    delete s_SendHook;
    delete s_SendClient;
    
    delete s_RecvHook;
    delete s_RecvClient;

    delete s_WinSockManager;
}

BOOL WINAPI DllMain(
    _In_ HINSTANCE hinstDLL,
    _In_ DWORD     fdwReason,
    _In_ LPVOID    lpvReserved
)
{
    switch (fdwReason)
    {
    case DLL_PROCESS_ATTACH:
        DisableThreadLibraryCalls(hinstDLL);
        Initialize();
        break;
    
    case DLL_PROCESS_DETACH:
        Shutdown();
        break;
    }

    return TRUE;
}