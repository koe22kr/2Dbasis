#pragma once
#include "Thread.h"

#define MAX_IOCP_THREAD 1

class IOCP :public Thread, public Singleton<IOCP>
{
private:
    friend Singleton<IOCP>;
public:
    HANDLE	m_hIOCP;
    HANDLE  m_hWorkThread[MAX_IOCP_THREAD];
public:
    bool Init();
    bool Release();
    void SetSocketBind(SOCKET sock, ULONG_PTR key);

public:
    IOCP();
    virtual ~IOCP();
};

#define I_IOCP IOCP::GetInstance()