#pragma once
#include "CACore.h"

class Sample : public CACore
{
public:
    bool Init();
    bool Frame();
    bool Render() { return true; };
    bool Release() { return true; };
public:
    
    LRESULT MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
public:
    Sample();
    ~Sample();

};


