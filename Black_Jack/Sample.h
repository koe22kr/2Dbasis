#pragma once
#include "CAStd.h"

#include "CACore.h"

class Sample :public CACore
{
public:
    bool Init();
    bool Frame();
    bool Render();
    bool Release();

    Sample();
    virtual ~Sample();
};

