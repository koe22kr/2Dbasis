#pragma once
#include "Protocol.h"
#include "Object_Pool.h"

struct OVERLAPPED2 :Object_Pool<OVERLAPPED2>
{
    OVERLAPPED ov;
    DWORD dw_Flag;
};

class User
{public:
    wstring	    	Name;
    DWORD           UID;

public:
    User();
    virtual ~User();
};

