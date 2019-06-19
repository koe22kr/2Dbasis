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
    int dis_count_hp; //hp 소모량, 체력의 역
    CABitmapObject* HP[5] = {0};
    //CABitmapObject* HP1;
    //CABitmapObject* HP2;
    //CABitmapObject* HP3;
    //CABitmapObject* HP4;
    //CABitmapObject* HP5;
    float test_time;
    CABitmapMgr UImgr;
    void HP_operate();          // HP체력 m_rt_num ={ 2, 1, 0} 1~5순으로 체력감소
    bool Init();
    bool Frame();
    bool Render();
    bool Release();
    UI();
    virtual ~UI();



};

