#pragma once
#include "Thread.h"
#include "IOCP.h"


class Acceptor :public Thread , public Singleton<Acceptor>
{
    friend Singleton<Acceptor>;
public:

    SOCKET  m_Listen_Sock;
public:
    bool	Init(int iPort = 10000, const char* address = nullptr);
public:
    virtual bool Thread_Runner() override;
public:
    Acceptor();
    virtual ~Acceptor();
};

#define I_ACCEPTOR Acceptor::GetInstance()