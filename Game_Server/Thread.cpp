#include "Thread.h"



//bool Thread::Thread_Runner()
//{
//    return true;
//}


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
        m_hThread = _beginthreadex(NULL, 0, Handle_Runner, (LPVOID)this, 0, &m_iID);
        
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
}
