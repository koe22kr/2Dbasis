#pragma once
#include "Server_Obj.h"
#include <process.h>
class Thread :public Server_Obj
{
public:
    HANDLE m_hThread;
    unsigned int m_iID;
    bool		 m_bStarted;
public:
    void CreateThread();
    virtual bool Thread_Runner();
    static unsigned int WINAPI Handle_Runner(LPVOID prameter);
public:
    Thread();
    virtual ~Thread();
};

