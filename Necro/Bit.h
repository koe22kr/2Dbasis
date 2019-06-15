#pragma once
#include "CAStd.h"
#include "CABitmapMgr.h"
#include "Std.h"
#include "Chara.h"

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
    float m_fBit_making_term = g_fSpeed;
    float m_fCur_time;
    bool m_bBit_maked_flag;

    void BitMake();
    bool BitCheck();
    bool KeyCheck();
    bool Turn_flag;
    //bool Bit_success_flag = false;
    bool Key_push;
    Bit();
    virtual ~Bit();
};

