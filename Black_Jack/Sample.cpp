#include "Sample.h"
Sample CLIENT;
bool Init_Flag = true;
bool Login_Flag = false;
HWND g_hLogin;
HWND g_hLogin_Name;
HWND g_hLogin_New_Button;
HWND g_hLogin_Login_Button;
HWND g_hLogin_Exit_Button;
HWND g_hNew_Account;
HWND g_hNew_Name;
HWND g_hNew_Ok_Button;
HWND g_hNew_Cancel_Button;

  //msg
//HWND        hwnd;
//UINT        message;
//WPARAM      wParam;
//LPARAM      lParam;
//DWORD       time;
//POINT       pt;

 // IDD_LOGIN
        //     IDD_NEW_ACCOUNT
        //     ID_LOGIN_NAME
        //     ID_LOGIN_NEW_BUTTON
        //     ID_LOGIN_LOGIN_BUTTON
        //     ID_LOGIN_EXIT_BUTTON
        //     ID_NEW_NAME
        //     ID_NEW_OK_BUTTON
        //     ID_NEW_CANCEL_BUTTON
        //     ID_STATIC


LRESULT New_Proc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
    case WM_INITDIALOG:
    {
        g_hNew_Account = hWnd;
        g_hNew_Name = GetDlgItem(hWnd, ID_NEW_NAME);
        g_hNew_Ok_Button = GetDlgItem(hWnd, ID_NEW_OK_BUTTON);
        g_hNew_Cancel_Button = GetDlgItem(hWnd, ID_NEW_CANCEL_BUTTON);
    }
    break;

    case WM_COMMAND:
    {
        switch (LOWORD(wParam))
        {
            case ID_NEW_CANCEL_BUTTON:
            {
                EndDialog(hWnd, IDOK);
                return true;
            }break;
           
            case ID_NEW_OK_BUTTON:
            {
                TCHAR buf[30];
                
                
                GetDlgItemText(hWnd, GetDlgCtrlID(g_hNew_Name), buf, 1024);
                if (wcslen(buf) > 8)
                {
                    MessageBox(g_hNew_Account, L"닉네임이 너무 길어요! (8자 이하)", L"개긴 이름", MB_OK);
                }
                else
                {
                    char buf2[20] = { 0 };
                    wcstombs(buf2, buf, sizeof(buf2));
                    CLIENT.g_pConnecter->Send(PACKET_NEW_ACCOUNT_RQ, buf2, MSG_USER_NAME_SIZE);
                }
                
            }

        }
    }
    }//case_end
    return 0;
}

LRESULT Login_Proc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    if (Init_Flag == true)
    {
        CLIENT.g_pConnecter->Init(10000,"192.168.0.61");
        CLIENT.g_pConnecter->CreateThread_Recv_Run();
        //디버그용 비활성
        Init_Flag = false;
    }
   


    switch (msg)
    {
    case WM_INITDIALOG:
    {

        g_hLogin = hWnd;
        g_hLogin_Name = GetDlgItem(hWnd, ID_LOGIN_NAME);
        g_hLogin_New_Button = GetDlgItem(hWnd, ID_LOGIN_NEW_BUTTON);
        g_hLogin_Login_Button = GetDlgItem(hWnd, ID_LOGIN_LOGIN_BUTTON);
        g_hLogin_Exit_Button = GetDlgItem(hWnd, ID_LOGIN_EXIT_BUTTON);

    }break;

    case WM_COMMAND:
    {
        switch (LOWORD(wParam))
        {
        case ID_LOGIN_EXIT_BUTTON:
        {
            EndDialog(hWnd, IDOK);
            return true;
        }break;

        case ID_LOGIN_NEW_BUTTON:
        {
            DialogBox(g_hInstance, MAKEINTRESOURCE(IDD_NEW_ACCOUNT), hWnd, New_Proc);
        }break;
        case ID_LOGIN_LOGIN_BUTTON:
        {
            TCHAR buf[30];
            GetDlgItemText(hWnd, GetDlgCtrlID(g_hNew_Name), buf, 1024);
            if (wcslen(buf) > 8)
            {
                MessageBox(g_hNew_Account, L"닉네임을 확인해주세요! (8자 이하)", L"싫으면 또 만들든가", MB_OK);
            }
            else
            {
                char buf2[20] = { 0 };
                wcstombs(buf2, buf, sizeof(buf2));
                CLIENT.g_pConnecter->Send(PACKET_LOGIN_RQ, buf2, MSG_USER_NAME_SIZE);
                wcscpy(CLIENT.g_pConnecter->m_szName, buf);
            }
           // EndDialog(g_hLogin, IDOK);  //디버그용
           // Login_Flag = true;          //디버그용
        }break;

        }
    }
    }
    return 0;
}

void Sample::Join_Thread()
{
    while (true)
    {


        for (auto iter =  CLIENT.g_pConnecter->m_Packet_Pool.begin();iter!= CLIENT.g_pConnecter->m_Packet_Pool.end();)
        {
            switch (iter->ph.type)
            {

            case PACKET_NEW_ACCOUNT_ACK:
            {
                MessageBox(g_hWnd, _T("생성 완료."), L"회원가입", MB_OK);
            }
            case PACKET_JOIN_NEW_USER:
            {
                User_Info user;
                memcpy(&user, iter->msg, MSG_USER_INFO_SIZE);
                //CHAR_NOTICE(user.name, L"님이 입장하였습니다.");
            }
            case PACKET_LOGIN_ACK:
            {
                char flag = iter->msg[0];
                if (flag == 1)
                {
                    CLIENT.g_pConnecter->m_iUID = iter->ph.UID;
                    
                    EndDialog(g_hLogin, IDOK);
                    Login_Flag = true;
                    CLIENT.g_pConnecter->m_Packet_Pool.erase(iter);
                    return;
                    //           MSGBOX("로그인 중? or 스킵");
                    
                }
                else
                {
                    MessageBox(g_hWnd, _T("이름을 확인해주세요."), L"로그인 오류", MB_OK);
                }
            }
            }
            CLIENT.g_pConnecter->m_Packet_Pool.erase(iter);
        }
    }
}

bool Sample::Init()
{
    BJ.Init();
    return true;
}
bool Sample::Frame()
{
    BJ.Frame();
    return true;
}
bool Sample::Render()
{
    BJ.Render();
    return true;
}
bool Sample::Release()
{
    BJ.Release();
    return true;
}

Sample::Sample()
{
    g_pConnecter = &I_CONNECTER;
}

Sample::~Sample()
{
}

unsigned int WINAPI Handle_Runner(LPVOID prameter)
{
    Sample* ptThread = (Sample*)prameter;
    ptThread->Join_Thread();
    return 0;
}
int APIENTRY  wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
    unsigned int m_iID = 0;

    HANDLE dlghThread = (HANDLE)_beginthreadex(NULL, 0, Handle_Runner, (LPVOID)&CLIENT, 0, &m_iID);
    DialogBox(hInstance, MAKEINTRESOURCE(IDD_LOGIN), HWND_DESKTOP, Login_Proc);
    
    if (Login_Flag)
    {
        CLIENT.InitWindow(hInstance, 0, 0, 800, 600);
        CLIENT.Run();
    }
   
   // CLIENT.InitWindow(hInstance, 0, 0, 800, 600);
   // CLIENT.Run();
}
