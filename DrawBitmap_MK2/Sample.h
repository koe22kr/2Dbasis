#pragma once
#include "CAStd.h"
#include "CACore.h"
#include "Bitmap.h"
#include "BitmapMgr.h"

class Sample : public CACore
{
public:
    CABitmap* m_player;
    CABitmap* m_npc;
    CABitmap* m_bk;
    CABitmapMgr mgr;


    bool Init();
    bool Frame();
    bool Render();
    bool Release();
public:
    // LRESULT MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
public:
    Sample();
    ~Sample();

};


