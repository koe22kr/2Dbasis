#include "Object.h"
#include "CAStd.h"

bool CAObject::Render()
{

    return true;
}
bool CAObject::Draw(int rt_num, DWORD imode)// 1start;
{
    //m_pbmp->Draw(m_pos.x, m_pos.y, m_rt, imode);


    
    if (m_pmask != nullptr)
    {
        m_pmask->Draw(m_pos.x, m_pos.y, *m_rt[rt_num -1], SRCAND);
        m_pbmp->Draw(m_pos.x, m_pos.y, *m_rt[rt_num -1], SRCINVERT);
        m_pmask->Draw(m_pos.x, m_pos.y, *m_rt[rt_num -1], SRCINVERT);
    }
    else
    {
        m_pbmp->Draw(m_pos.x, m_pos.y, *m_rt[rt_num -1], SRCCOPY);
    }
    return true;
}
bool CAObject::Frame()
{

    return true;
}

bool CAObject::Draw_ColorKey(RECT rt, COLORREF color)
{
    //DC->DC
    TransparentBlt(g_hOffScreenDC, rt.left, rt.top, rt.right, rt.bottom,
        m_pbmp->m_dc, rt.left, rt.top, rt.right, rt.bottom,
        color);
    return true;
}


void CAObject::Setobject(T_STR name, int max_frame_num, float inx, float iny, 
                         bool loop_flag, float life_time, RECT rt, float fSpeed)
{
    //rtExplosion 12    100  100   1         0          1
       //name        frame posx posy  loop_flag life_time  dummy[dead_flag]
    m_Obj_Name = name;
    m_max_frame_num = max_frame_num;
    m_pos = { inx,iny };
    m_loop_flag = loop_flag;
    m_fLife_time = life_time;
    m_fSpeed = fSpeed;
    RECT* NewRect = new RECT;

    NewRect->left = rt.left;
    NewRect->top = rt.top;
    NewRect->right = rt.right;
    NewRect->bottom = rt.bottom;

    m_rt.push_back(NewRect);
}
void CAObject::Setobject(T_STR name, int max_frame_num, float inx, float iny,
                         bool loop_flag, float life_time, vector<RECT> rt_array, float fSpeed)
{
    m_Obj_Name = name;
    m_max_frame_num = max_frame_num;
    m_pos = { inx,iny };
    m_loop_flag = loop_flag;
    m_fLife_time = life_time;
    m_fSpeed = fSpeed;
    RECT* NewRect = new RECT;


    for (int i = 0; m_rt.begin() + i != m_rt.end(); i++)
    {
        m_rt[i]->left = rt_array[i].left;
        m_rt[i]->top = rt_array[i].top;
        m_rt[i]->right = rt_array[i].right;
        m_rt[i]->bottom = rt_array[i].bottom;
    }
    m_rt.push_back(NewRect);
}

CAObject::CAObject()
{

}


CAObject::~CAObject()
{
}
