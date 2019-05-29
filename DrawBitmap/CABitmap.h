#pragma once
#include "CAStd.h"



class CABitmap 
{

public:

    HBITMAP m_bmp;
    HDC m_dc;
   

    
public:
        
    bool	Init();
    bool    Load(T_STR filename);
    bool	Frame();
    bool	Render();
    bool    Draw(float x, float y, RECT rt,DWORD imode= SRCCOPY);
  
    bool	Release();


    CABitmap();
    virtual ~CABitmap();
};

