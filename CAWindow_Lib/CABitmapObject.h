#pragma once
#include "CABitmap.h"
#include "CAObject.h"
class CAPOINT
{
public:
    float x = 100.0f;
    float y = 100.0f;

    CAPOINT() {};
    CAPOINT(float inx, float iny) :x(inx), y(iny) {};
};

class CABitmapObject :public CAObject
{
public:

    CABitmap*        m_pbmp = nullptr;
    CABitmap*        m_pmask = nullptr;
    T_STR            m_Obj_Name;
    CAPOINT          m_pos = { 100, 100 }; //
    CAPOINT          m_center_pos = { 0,0 };
    CAPOINT          m_curpos = { 0,0 };
    float m_fDirection = 0.f;
    bool m_bMove_flag = 0;
    float m_fSpeed = 0;
    float m_fAngle = 0;
    int              m_iRt_num = 1; //�ε�� 1start 
    int              m_iMax_rt_num;
    float m_fAlpha = 0;
    vector<RECT*>    m_rt;

public:   //��������Ʈ�� �����
    float            m_fCur_time = 0;
    float            m_fSprite_time = 0;
    float            m_fDelta_time = 0;
    float            m_fLife_time = 0;
    
    bool             m_bLoop_flag = false;
    bool             m_bDead_flag = false;  //�Ҹ� �� ������ �ִ� ������Ʈ�� �Ҹ��.


    //bool AlphaBlendRender(RECT rt);
public:
    void             Rt_Operate();
    void Rotation();
    virtual void             Move(float xstep, float ystep);
    bool             Draw(int rt_num = 1, DWORD imode = SRCCOPY);
    bool             Draw_ColorKey(RECT rt, COLORREF color);

    bool             Init();
    bool             Render();
    bool             Frame();
    bool             Release();

    void             Setobject(T_STR name, int max_frame_num, float inx, float iny, RECT rt,
        bool loop_flag = 0, float sprite_time = 0, float life_time = 0, float fSpeed = 0, float alpha = 1, int player_flag = 0);
    void             Setobject(T_STR name, int max_frame_num, float inx, float iny, vector<RECT> rt_array,
        bool loop_flag = 0, float sprite_time = 0, float life_time = 0, float fSpeed = 0, float alpha = 1, int player_flag = 0);
    virtual CABitmapObject* NewObject() { return new CABitmapObject; };
    CABitmapObject();
    virtual ~CABitmapObject();

public:    // �÷��̾� Ŭ���� �ڽ�Ŭ������ ���� �������� �ȱ���. ��ũ��Ʈ�� �װ� �����ϴ°� ���� �����غ��� �ȱ��
    enum Player_Move
    {
        LL = 1, L, Mid, R, RR
    };
    bool             m_bPlayer_flag = false;
    float            m_fplayer_action_flag = 0;
    CAPOINT          m_before_pos = { 0,0 };
    void        Player_Render();

};
//bitmap1.bmp   
//�����̸�      
//rtExplosion 12     100 100 1         0            0          128    0    
//�ĺ��� �̸� ������ pos.x,y loopflag, sprite time, life time, alpha, player_flag   