#include "Thread.h"



bool Thread::Thread_Runner()
{
    return true;
}


unsigned int WINAPI Thread::Handle_Runner(LPVOID prameter)
{
    Thread* ptThread = (Thread*)prameter;
    ptThread->Thread_Runner();
    return 0;
}

void Thread::CreateThread()
{
    if (m_bStarted == false)
    {
        m_hThread = (HANDLE)_beginthreadex(NULL, 0, Handle_Runner, (LPVOID)this, 0, &m_iID);
        
        m_bStarted = true;
    }
}

Thread::Thread()
{
    m_hThread = 0;
    m_iID = 0;
    m_bStarted = false;
}


Thread::~Thread()
{
    if (m_hThread != 0)
    {
        CloseHandle(m_hThread);
    }
}
wcstombs(new_user_info.name, target_iter->second->Name.c_str(), MAX_NAME_SIZE * 2);
