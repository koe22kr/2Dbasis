#pragma once
#include "Protocol.h"

class User
{public:
    wstring	    	Name;
    DWORD           UID;

public:
    User();
    virtual ~User();
};

