#pragma once
#include "Server_Obj.h"
class Lock
{
public:
    Server_Obj* m_obj;
public:
    Lock(Server_Obj* lock_target);
    virtual ~Lock();
};

