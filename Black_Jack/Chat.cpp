#include "Chat.h"
#include "resource.h"




void Chat::Init()
{
    
   DWORD style = WS_CHILD | WS_VISIBLE ;
   m_hEdit = CreateWindow(L"edit", NULL, style,
       g_rtClient.right-200, g_rtClient.bottom-100, 170, 100, g_hWnd, (HMENU)100,
       g_hInstance, NULL);
  
   style = WS_CHILD | WS_VISIBLE | WS_HSCROLL| WS_VSCROLL;
   m_hList = CreateWindow(L"listbox", NULL, style,
       g_rtClient.right-200, g_rtClient.top, 200, g_rtClient.bottom-100, g_hWnd, (HMENU)200,
       g_hInstance, NULL);
  
  
   style = WS_CHILD | WS_VISIBLE;
   m_hButton = CreateWindow(L"button", L"보내기", style,
       g_rtClient.right-30, g_rtClient.bottom-100, 30, 100, g_hWnd, (HMENU)300,
       g_hInstance, NULL);
   
    
   

    //style = WS_CHILD | WS_VISIBLE | WS_VSCROLL | WS_HSCROLL;
    //m_hList = CreateWindow(L"listbox", NULL, style,
    //    10, 10, 400, 500, g_hWnd, (HMENU)400,
    //    g_hInstance, NULL);
    SendMessage(m_hList, LB_ADDSTRING, 0, (LPARAM)L"채팅시작합니다.");
    //CreateDialog()
    int a = 0;
}

void Chat::Frame()
{
    SetWindowPos(m_hEdit, NULL, g_rtClient.right - 200, g_rtClient.bottom - 100, 170, 100, SWP_NOZORDER);
    for (auto msg : I_MSG.Msg_list)
    {
        if (msg.message == WM_COMMAND)
        {
            switch (LOWORD(msg.wParam))
            {
            case 300:
            {
                char buffer[2048] = { 0 };
                 SendMessageA(m_hEdit, WM_GETTEXT, MAX_PATH, (LPARAM)buffer);
                
                 if (strlen(buffer) > 0)
                 {
                     SendMessageA(m_hEdit, WM_SETTEXT, MAX_PATH, NULL);
                     //SendMessageA(m_hList, LB_ADDSTRING, 0, (LPARAM)buffer);

                     g_pConnecter->Send(PACKET_CHAT_MSG, buffer, strlen(buffer));
                 }
            }
            }

        }
        I_MSG.Msg_list.clear();
    }
}

void Chat::Notice(Packet packet,const char* notice)
{
    User_Info user;
    memcpy(&user, packet.msg, sizeof(User_Info));
    char cname[10] = { 0 };
    
    strncpy(cname, user.name, strlen(user.name));
    string buf;
    buf = cname;
    buf += notice;
    //SendMessageA(m_hList, LB_ADDSTRING, 0, (LPARAM)user.name);
    SendMessageA(m_hList, LB_ADDSTRING, 0, (LPARAM)buf.c_str());
}

void Chat::Talk(Packet packet,const TCHAR* name)
{
    TCHAR msg[20] = { 0 };
    mbstowcs(msg, packet.msg, strlen(packet.msg));
    wstring buffer;
    buffer = name;
    buffer += L" : ";
    buffer += msg;
    SendMessage(m_hList, LB_ADDSTRING, 0, (LPARAM)buffer.c_str());
    //SendMessage(m_hList, LB_ADDSTRING, 0, (LPARAM)buffer.c_str());
    //SendMessageA(m_hList, LB_ADDSTRING, 0, (LPARAM)packet.msg);


   /* char buffer[2048] = { 0 };
    strcpy(buffer, packet.msg);
    SendMessageA(m_hList, LB_ADDSTRING, 0, (LPARAM)buffer);
    int a = 0;*/
    
}


void Chat::Render()
{

}
void Chat::Release()
{

}
Chat::Chat()
{
    g_pConnecter = &I_CONNECTER;

}


Chat::~Chat()
{
}
