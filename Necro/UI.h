#pragma once
#include "CAStd.h"
#include "CABitmapMgr.h"
#include <stdlib.h>
#include "Bit.h"
#include "Std.h"

class UI
{
public:

    T_STR UI_file_name = L"Necro_UI.bmp";
    float heart_speed;
    int maxHP = 10;
    int dis_count_hp; //hp �Ҹ�, ü���� ��
    CABitmapObject* HP[5] = {0};
    //CABitmapObject* HP1;
    //CABitmapObject* HP2;
    //CABitmapObject* HP3;
    //CABitmapObject* HP4;
    //CABitmapObject* HP5;
    float test_time;
    CABitmapMgr UImgr;
    void HP_operate();          // HPü�� m_rt_num ={ 2, 1, 0} 1~5������ ü�°���
    bool Init();
    bool Frame();
    bool Render();
    bool Release();
    UI();
    virtual ~UI();



};

