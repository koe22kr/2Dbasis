#pragma once
#include "CAStd.h"
#include "CACore.h"
#include "Bit.h"

class Sample :public CACore
{
public:
    Bit bit;
    bool Init();
    bool Frame();
    bool Render();
    bool Release();

    void KeyCheck();



    Sample();
    virtual ~Sample();
};

