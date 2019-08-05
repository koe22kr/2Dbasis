#include "Chat.h"
#include "resource.h"
WNDPROC old_wndproc;
 LRESULT Edit_Proc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
    case WM_KEYDOWN:
    {

        if (wParam == VK_RETURN)
        {
            int a = 0;
        }
    }
    default:
        break;

        {

        }
    }
    return CallWindowProc(old_wndproc, hWnd, msg, wParam, lParam);

}

void Chat::Init()
{
    
   DWORD style = WS_CHILD | WS_VISIBLE ;
   m_hEdit = CreateWindow(L"edit", NULL, style,
       g_rtClient.right-300, g_rtClient.bottom-100, 240, 100, g_hWnd, (HMENU)100,
       g_hInstance, NULL);
  
   style = WS_CHILD | WS_VISIBLE | WS_HSCROLL| WS_VSCROLL;
   m_hList = CreateWindow(L"listbox", NULL, style,
       g_rtClient.right-300, g_rtClient.top, 300, g_rtClient.bottom-100, g_hWnd, (HMENU)200,
       g_hInstance, NULL);
  
  
   style = WS_CHILD | WS_VISIBLE;
   m_hButton = CreateWindow(L"button", L"보내기", style,
       g_rtClient.right-60, g_rtClient.bottom-100, 60, 100, g_hWnd, (HMENU)300,
       g_hInstance, NULL);
   
   style = WS_CHILD;
   m_hReady_Cancel = CreateWindow(L"button", L"준비 취소", style,
       g_rtClient.left, g_rtClient.top, 100, 100, g_hWnd, (HMENU)500,
       g_hInstance, NULL);

   style = WS_CHILD | WS_VISIBLE;
   m_hReady = CreateWindow(L"button", L"준 비", style,
       g_rtClient.left, g_rtClient.top, 100, 100, g_hWnd, (HMENU)400,
       g_hInstance, NULL);
  
   style = WS_CHILD;
   m_hHit = CreateWindow(L"button", L"H I T", style,
       g_rtClient.left + 300, g_rtClient.top + 200, 100, 100, g_hWnd, (HMENU)600,
       g_hInstance, NULL);

   style = WS_CHILD ;
   m_hStay = CreateWindow(L"button", L"S T A Y", style,
       g_rtClient.left + 400, g_rtClient.top + 200, 100, 100, g_hWnd, (HMENU)700,
       g_hInstance, NULL);
   
   

    //style = WS_CHILD | WS_VISIBLE | WS_VSCROLL | WS_HSCROLL;
    //m_hList = CreateWindow(L"listbox", NULL, style,
    //    10, 10, 400, 500, g_hWnd, (HMENU)400,
    //    g_hInstance, NULL);
    SendMessage(m_hList, LB_ADDSTRING, 0, (LPARAM)L"채팅시작합니다.");
    //CreateDialog()
      old_wndproc = (WNDPROC)SetWindowLongPtr(m_hEdit, GWLP_WNDPROC, (LONG_PTR)Edit_Proc);

}


void Chat::Frame()
{
    //SetWindowPos(m_hEdit, NULL, g_rtClient.right - 300, g_rtClient.bottom - 100, 170, 100, SWP_NOZORDER);
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
                }break;
                case 400:
                {
                    //준비 패킷 송신;
                    g_pConnecter->Send(PACKET_GAME_READY);

                    Notice("준비");
                    //DWORD newstyle = WS_CHILD | WS_VISIBLE;
                    //DWORD newstyle2 = WS_CHILD;
                    //SetWindowLongPtr(m_hReady, GWL_STYLE, newstyle2);
                    //SetWindowLongPtr(m_hReady_Cancel, GWL_STYLE, newstyle);
                    SetWindowPos(m_hReady, NULL, 0, 0, 100, 100, SWP_HIDEWINDOW);
                    SetWindowPos(m_hReady_Cancel, NULL, 0, 0, 100, 100, SWP_SHOWWINDOW);
                }break;
                case 500:
                {
                    g_pConnecter->Send(PACKET_GAME_READY_CANCEL);

                    Notice("준비취소");
                    //DWORD newstyle = WS_CHILD | WS_VISIBLE;
                    //DWORD newstyle2 = WS_CHILD;
                    //SetWindowLongPtr(m_hReady, GWL_STYLE, newstyle);
                    //SetWindowLongPtr(m_hReady_Cancel, GWL_STYLE, newstyle2);


                    SetWindowPos(m_hReady, NULL, 0, 0, 100, 100, SWP_SHOWWINDOW);
                    SetWindowPos(m_hReady_Cancel, NULL, 0, 0, 100, 100, SWP_HIDEWINDOW);
                }break;
                case 600://hit
                {
                    g_pConnecter->Send(PACKET_COMMAND_HIT);

                }break;
                case 700://stay
                {
                    g_pConnecter->Send(PACKET_COMMAND_STAY);

                }
            }
    
    
        
            
        }
        Sleep(1);
    }
    I_MSG.Msg_list.clear();
}

void Chat::Make_Hit_Stay()
{
    SetWindowPos(m_hHit, NULL, g_rtClient.left + 300, g_rtClient.top + 200, 100, 100, SWP_SHOWWINDOW);
    SetWindowPos(m_hStay, NULL, g_rtClient.left + 400, g_rtClient.top + 200, 100, 100, SWP_SHOWWINDOW);
    
    

}

void Chat::Reset_Windows()
{
    SetWindowPos(m_hHit, NULL, g_rtClient.left + 300, g_rtClient.top + 200, 100, 100, SWP_HIDEWINDOW);
    SetWindowPos(m_hStay,NULL, g_rtClient.left + 400, g_rtClient.top + 200, 100, 100, SWP_HIDEWINDOW);
    SetWindowPos(m_hReady, NULL, 0, 0, 100, 100, SWP_SHOWWINDOW);
    SetWindowPos(m_hReady_Cancel, NULL, 0, 0, 100, 100, SWP_HIDEWINDOW);
}

void Chat::Notice(const WCHAR* notice)
{
    SendMessage(m_hList, LB_ADDSTRING, 0, (LPARAM)notice);
    int a = 0;
}



void Chat::Notice(const char* notice)
{
    SendMessageA(m_hList, LB_ADDSTRING, 0, (LPARAM)notice);
    int a = 0;
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
    CHAR name2[20] = { 0 };
    wcstombs(name2, name, wcslen(name));
    
    string buffer;
    buffer = name2;
    buffer += " : ";
    buffer += packet.msg;
    SendMessageA(m_hList, LB_ADDSTRING, 0, (LPARAM)buffer.c_str());
    
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
