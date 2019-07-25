#pragma once
#include "Protocol.h"
class Server_Obj
{
public:
    CRITICAL_SECTION m_cs;
public:
    Server_Obj();
    virtual ~Server_Obj();
};

