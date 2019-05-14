#include "CABitmap.h"


bool CABitmap::Init()
{

    return true;
}

void CABitmap::Set(CAPOINT pos,RECT rt,float fspeed)
{
    this->pos = pos;
    this->rt = rt;
    this->fSpeed = fspeed;

}

bool CABitmap::Load(wstring filename)
{
    m_bmp = (HBITMAP)LoadImage(
        g_hInstance,
        filename.c_str(),
        IMAGE_BITMAP,
        0, 0,
        LR_DEFAULTSIZE | LR_LOADFROMFILE);
    m_dc = CreateCompatibleDC(g_hScreenDC);
    SelectObject(m_dc, m_bmp);
    return true;
}

bool CABitmap::Draw(float inx, float iny, RECT rt)
{
    BitBlt(g_hOffScreenDC, inx, iny,
        rt.right,
        rt.bottom,
        m_dc,
        rt.left,
        rt.top, SRCCOPY);
    return true;
}

bool CABitmap::Render()
{
    this->Draw(pos.x,pos.y,rt);

    return true;
}

bool CABitmap::Frame()
{
    return true;
}

bool CABitmap::Release()
{
    DeleteObject(m_bmp);
    return true;
}

CABitmap::CABitmap()
{
}


CABitmap::~CABitmap()
{
}
