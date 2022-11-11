#include "Hook.h"

#include <Windows.h>


Hook::Hook(void* address, size_t size)
    :
    m_Address(static_cast<uint8_t*>(address)),
    m_Size(size),
    m_OriginalBytes(new uint8_t[m_Size])
{
    memcpy_s(m_OriginalBytes, m_Size, m_Address, m_Size);
}

Hook::~Hook()
{
    if (m_Active)
    {
        Disable();
    }

    delete[] m_OriginalBytes;
}

void Hook::Enable(const void* function)
{
    m_Thunk = static_cast<uint8_t*>(VirtualAlloc(nullptr, 5 + m_Size + 5, MEM_RESERVE | MEM_COMMIT, PAGE_EXECUTE_READWRITE));
    if (m_Thunk == nullptr)
    {
        return;
    }
    
    m_Thunk[0x0] = 0xE8;
    *reinterpret_cast<uint32_t*>(m_Thunk + 0x1) = reinterpret_cast<const uint8_t*>(function) - m_Thunk - 0x5;
    memcpy_s(m_Thunk + 0x5, m_Size, m_Address, m_Size);
    m_Thunk[0x5 + m_Size] = 0xE9;
    *reinterpret_cast<uint32_t*>(m_Thunk + 0x5 + m_Size + 0x1) = (m_Address + 0x5) - (m_Thunk + 0x5 + m_Size) - 0x5;

    DWORD oldProtection = 0;
    VirtualProtect(m_Address, m_Size, PAGE_EXECUTE_READWRITE, &oldProtection);
    m_Address[0x0] = 0xE9;
    *reinterpret_cast<uint32_t*>(m_Address + 0x1) = m_Thunk - m_Address - 0x5;
    memset(m_Address + 0x5, 0x90, m_Size - 5);
    VirtualProtect(m_Address, m_Size, oldProtection, &oldProtection);

    m_Active = true;
}

void Hook::Disable()
{
    DWORD oldProtection = 0;
    VirtualProtect(m_Address, m_Size, PAGE_EXECUTE_READWRITE, &oldProtection);
    memcpy_s(m_Address, m_Size, m_OriginalBytes, m_Size);
    VirtualProtect(m_Address, m_Size, oldProtection, &oldProtection);

    VirtualFree(m_Thunk, 0, MEM_RELEASE);

    m_Active = false;
}