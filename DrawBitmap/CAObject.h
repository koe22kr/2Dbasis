#pragma once
//#include "CABitmap.h"
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
    TCHAR            m_Obj_ID[255];
    

    int              m_max_frame_num;
    int              m_rt_num = 0; //랜더 전 프레임에서 +1;
    vector<RECT>     m_rt;

     CAPOINT         m_pos = { 100, 100 }; //
     CAPOINT         m_center = { 0,0 };
    float            m_fCur_time = 0;
    float            m_fLife_time = 0;

    bool             m_loop_flag = false;
    bool             dead_flag = false;  //소멸 할 예정이 있는 오브젝트는 소멸용.
    float            m_fSpeed = 100.0f;

    bool             mask_flag = false;
public:
    void             Setobject(float inx, float iny, RECT rt, float fSpeed);
    bool             Draw_ColorKey(RECT rt, COLORREF color);
    bool             Render(int rt_num = 0, DWORD imode = SRCCOPY);
    bool             Frame();
    CAObject();
    virtual ~CAObject();
};
//bitmap1.bmp rtExplosion 12 100 100 1 0
//파일이  식별용 이름 프래임 pos.x,y life time, 소멸 여부 [1]이면 소멸.
