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

    CABitmap*        m_pbmp = nullptr;
    CABitmap*        m_pmask = nullptr;
    T_STR            m_Obj_Name;
    CAPOINT          m_pos = { 100, 100 }; //
    CAPOINT          m_center_pos = { 0,0 };

    
    float m_fAngle = 0;
    int              m_rt_num = 1; //1start
    int              m_max_rt_num;
    float m_fAlpha = 0;
    vector<RECT*>    m_rt;

public:   //스프라이트용 멤버들
    float            m_fCur_time = 0;
    float            m_fSprite_time = 0;
    float            m_Delta_time = 0;
    float            m_fLife_time = 0;
    bool             m_loop_flag = false;


    bool             dead_flag = false;  //소멸 할 예정이 있는 오브젝트는 소멸용.
    
    //bool AlphaBlendRender(RECT rt);
public:
    void             Rt_Operate();
    void Rotation();
    void             Move(float xstep, float ystep);
    bool             Draw(int rt_num = 1, DWORD imode = SRCCOPY);
    bool             Draw_ColorKey(RECT rt, COLORREF color);

    bool             Init();
    bool             Render();
    bool             Frame();
    bool             Release();

    void             Setobject(T_STR name, int max_frame_num, float inx, float iny, RECT rt,
                                bool loop_flag=0, float sprite_time=0, float life_time=0,  float fSpeed = 0, float alpha = 1, int player_flag = 0);
    void             Setobject(T_STR name, int max_frame_num, float inx, float iny, vector<RECT> rt_array,
                                bool loop_flag=0, float sprite_time=0, float life_time=0,  float fSpeed = 0, float alpha = 1, int player_flag =  0);

    CAObject();
    virtual ~CAObject();

public:    // 플레이어 클래스 자식클래스로 만들어서 그쪽으로 옴기자. 스크립트로 그걸 설정하는건 조금 생각해보고 옴기기
    enum Player_Move
    {
        LL = 1, L, Mid, R, RR
    };
    bool             m_Player_flag = false;
    float            m_fplayer_action_flag = 0;
    CAPOINT          m_before_pos = { 0,0 };
    void        Player_Render();

};
//bitmap1.bmp   
//파일이름      
//rtExplosion 12     100 100 1         0            0          128    0    
//식별용 이름 프래임 pos.x,y loopflag, sprite time, life time, alpha, player_flag   