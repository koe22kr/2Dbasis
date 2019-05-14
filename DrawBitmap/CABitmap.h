#pragma once
#include "CAStd.h"


class CAPOINT
{public:
    float x = 100.0f;
    float y = 100.0f;
    CAPOINT() {};
    CAPOINT(float inx, float iny) :x(inx), y(iny) {};
};

class CABitmap 
{

public:
    HBITMAP m_bmp;
    HDC m_dc;
    CAPOINT pos;
    RECT rt;
    float fSpeed;


public:
        
    bool	Init();
    void    Set(CAPOINT pos, RECT rt, float fspeed);
    bool    Load(std::wstring filename);
    bool	Frame();
    bool	Render();
    bool    Draw(float x, float y, RECT rt);
    bool	Release();


    CABitmap();
    virtual ~CABitmap();
};

