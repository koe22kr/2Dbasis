#pragma once
#include "CAStd.h"
#include "CABitmapMgr.h"
class Bit
{
public:
    T_STR BIT_file_name = L"Necro_UI.bmp";
    CABitmapMgr Bitmgr;
    bool Init();
    bool Frame();
    bool Render();
    bool Release();
    float m_fBit_making_term;
    float m_fCur_time;
    
    void BitMake();
    bool BitCheck();

    Bit();
    virtual ~Bit();
};

