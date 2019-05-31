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

    bool	Init();
    bool    Load(T_STR filename);
    bool	Frame();
    bool	Render();

    bool    Draw(float x, float y, RECT rt, DWORD imode = SRCCOPY);
    bool    Draw(float inx, float iny, RECT rt, BLENDFUNCTION bf);
    bool    Draw(float inx, float iny, RECT Srcrt, RECT Deskrt, BLENDFUNCTION bf);

    bool	Release();


    CABitmap();
    virtual ~CABitmap();
};

