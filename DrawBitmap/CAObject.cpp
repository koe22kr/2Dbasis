#include "CAObject.h"
#include "CAStd.h"

bool CAObject::Render(int rt_num,DWORD imode)
{
    //m_pbmp->Draw(m_pos.x, m_pos.y, m_rt, imode);

    if (mask_flag)return false;
    if (m_pmask != nullptr)
    {
        m_pmask->Draw(m_pos.x, m_pos.y, m_rt[rt_num-1], SRCAND);
        m_pbmp->Draw(m_pos.x, m_pos.y, m_rt[rt_num-1], SRCINVERT);
        m_pmask->Draw(m_pos.x, m_pos.y, m_rt[rt_num-1], SRCINVERT);
    }
    else
    {
        m_pbmp->Draw(m_pos.x, m_pos.y, m_rt[rt_num-1], SRCCOPY);
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

void CAObject::Setobject(float inx, float iny, RECT rt, float fSpeed)
{
    m_pos.x = inx;
    m_pos.y = iny;
    m_rt[0].left = rt.left;
    m_rt[0].top = rt.top;
    m_rt[0].right = rt.right;
    m_rt[0].bottom = rt.bottom;
    m_fSpeed = fSpeed;
    m_center.x = (rt.right - inx) / 2 + inx;
    m_center.y = (rt.bottom - iny) / 2 + iny;
}


CAObject::CAObject()
{
    
}


CAObject::~CAObject()
{
}
