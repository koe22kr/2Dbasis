#include "Lock.h"



Lock::Lock(Server_Obj* lock_target) : m_obj(lock_target)
{
    if (m_obj != nullptr)
    {
        EnterCriticalSection(&m_obj->m_cs);
    }
}


Lock::~Lock()
{
    if (m_obj != nullptr)
    {
        LeaveCriticalSection(&m_obj->m_cs);
    }
}
