#pragma once
#include "Thread.h"
#include "IOCP.h"

class Acceptor :public Thread
{

public:

    SOCKET  m_Listen_Sock;
public:
    bool	Set(int iPort = 10000, const char* address = nullptr);
public:
    virtual bool Thread_Runner() override;
public:
    Acceptor();
    virtual ~Acceptor();
};

