#pragma once


#include <cstdint>


class Hook
{
public:
    Hook(void* address, size_t size);
    ~Hook();

    void Enable(const void* function);
    void Disable();

private:
    uint8_t* m_Address = nullptr;
    size_t m_Size = 0;
    uint8_t* m_OriginalBytes = nullptr;
    uint8_t* m_Thunk = nullptr;
    bool m_Active = false;
};