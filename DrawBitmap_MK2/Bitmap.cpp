#include "Bitmap.h"

bool	CABitmap::Init()
{
    return true;
}
bool	CABitmap::Frame()
{
    return true;
}
bool	CABitmap::Render()
{
    return true;
}
bool	CABitmap::Release()
{
    
    DeleteObject(m_bmp);
    return true;
}

bool    CABitmap::Load(T_STR filename)
{
    m_bmp = (HBITMAP)LoadImage(
        g_hInstance,
        filename.c_str(),
        IMAGE_BITMAP,
        0, 0,
        LR_DEFAULTSIZE | LR_LOADFROMFILE);
    if (m_bmp == NULL)return false;
    m_dc = CreateCompatibleDC(g_hScreenDC);
    SelectObject(m_dc, m_bmp);
    return true;
}

bool    CABitmap::Draw(float inx, float iny, RECT rt, DWORD imode)
{
    BitBlt(g_hOffScreenDC, inx, iny,
        rt.right,
        rt.bottom,
        m_dc,
        rt.left,
        rt.top, imode);
    return true;
}



CABitmap::CABitmap()
{
}


CABitmap::~CABitmap()
{
}
