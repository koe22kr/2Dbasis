#pragma once
#include "CAStd.h"
#include "CAMessageList.h"
#include "Connecter.h"
class Chat : public Singleton<Chat>
{
    friend Singleton<Chat>;
public:
    HWND			m_hEdit;
    HWND			m_hList;
    HWND			m_hButton;
    Connecter* g_pConnecter;//생성자필
    void Talk(Packet packet,const TCHAR* name);
    void Notice(Packet packet, const char* notice);
    void Init();
    void Frame();
    void Render();
    void Release();
    Chat();
    ~Chat();
};
#define I_CHAT Chat::GetInstance()
