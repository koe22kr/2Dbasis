#pragma once
#include "Object_Pool.h"
#include "Protocol.h"

struct OVERLAPPED2 :public Object_Pool<OVERLAPPED2>
{
    OVERLAPPED ov;
    DWORD dw_Flag;
};

class User
{
public:
    wstring	    	Name;
    DWORD           UID;

public:
    User();
    virtual ~User();
};

