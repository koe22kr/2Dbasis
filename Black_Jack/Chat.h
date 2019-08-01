#pragma once
#include "CAStd.h"
#include "CAMessageList.h"
class Chat
{
public:
    HWND			m_hEdit;
    HWND			m_hList;
    HWND			m_hButton;

    void Init();
    void Frame();
    void Render();
    void Release();
    Chat();
    ~Chat();
};

