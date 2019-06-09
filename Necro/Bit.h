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
    float m_fBit_Speed = 200;
    float m_fBit_making_term = 0.8f;
    float m_fCur_time;
    bool m_bBit_maked_flag;

    void BitMake();
    bool BitCheck();

    Bit();
    virtual ~Bit();
};

