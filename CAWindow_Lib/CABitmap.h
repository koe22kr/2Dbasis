#pragma once
#include "CAStd.h"


//load �� m_bmp ����� release �� ������.
class CABitmap
{

public:

  
    HBITMAP m_bmp;
    HDC m_dc;


    BITMAP m_BitmapInfo;
public:

    virtual bool	Init();
    virtual bool	Frame();
    virtual bool	Render();
    virtual bool	Release();

    virtual bool    Load(T_STR filename);
    bool    Draw(float x, float y, RECT rt, DWORD imode = SRCCOPY, bool draw_center = 1);
    bool    Draw(float inx, float iny, RECT rt, BLENDFUNCTION bf, bool draw_center = 1);
    bool    Draw(float inx, float iny, RECT Srcrt, RECT Deskrt, BLENDFUNCTION bf, bool draw_center = 1);

   


    CABitmap();
    virtual ~CABitmap();
};

