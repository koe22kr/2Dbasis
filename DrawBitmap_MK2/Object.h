#pragma once
#include "Bitmap.h"
class CAPOINT
{
public:
    float x = 100.0f;
    float y = 100.0f;

    CAPOINT() {};
    CAPOINT(float inx, float iny) :x(inx), y(iny) {};
};

class CAObject
{
public:
public:

    CABitmap*        m_pbmp = nullptr;
    CABitmap*        m_pmask = nullptr;
    T_STR            m_Obj_Name;


    int              m_max_frame_num;
    int              m_rt_num = 0; //���� �� �����ӿ��� +1;
    vector<RECT*>     m_rt;

    CAPOINT         m_pos = { 100, 100 }; //
    float            m_fCur_time = 0;
    float            m_fLife_time = 0;
    float            m_Delta_time = 0;
    bool             m_loop_flag = false;
    bool             dead_flag = false;  //�Ҹ� �� ������ �ִ� ������Ʈ�� �Ҹ��.
    float            m_fSpeed = 0.0f;

    bool             mask_flag = false;
public:

    void             Setobject(T_STR name, int max_frame_num, float inx, float iny, 
                               bool loop_flag, float life_time, RECT rt, float fSpeed = 0);
    void             Setobject(T_STR name, int max_frame_num, float inx, float iny, 
                               bool loop_flag, float life_time, vector<RECT> rt_array, float fSpeed = 0);
    bool             Draw(int rt_num = 1, DWORD imode = SRCCOPY);
    bool             Draw_ColorKey(RECT rt, COLORREF color);
    bool    Init();
    bool             Render();
    bool             Frame();
    bool Release();
    CAObject();
    virtual ~CAObject();
};
//bitmap1.bmp rtExplosion 12 100 100 1 0
//������  �ĺ��� �̸� ������ pos.x,y life time, �Ҹ� ���� [1]�̸� �Ҹ�.
