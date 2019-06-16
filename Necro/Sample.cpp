#include "Sample.h"
#include "CAStd.h"
#include "Scene_Title.h"
#include "Scene_Dungeon.h"

POINT start_pos;

bool Sample::Init()
{
    Cur_scene = new Scene_Title;
    Cur_scene->Init();
    return true;
}

bool Sample::Frame() 
{

    Cur_scene->Frame();
    if (Cur_scene->Scene_num == 2)
    {
        Cur_scene->Release();
        Cur_scene = new Scene_Dungeon;
        Cur_scene->Init();
        Cur_scene->Frame();
    }
    return true;
}
bool Sample::Render()
{
    Cur_scene->Render();
    return true;
}
bool Sample::Release()
{
    Cur_scene->Release();
    return true;
}

//LRESULT		Sample::MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
//{
//    //PostMessage(g_hWnd, WM_UICONTRLMSG, dwWParam, dwLParam);
//    DWORD dwWParam=0;
//    DWORD dwLParam=0;
//    PostMessage(g_hWnd, WM_CAMERA_MOVE, dwWParam, dwLParam);
//        return 1;
//}

//void Sample::KeyCheck()
//{
//
//
//    DWORD dwState = I_Input.KeyCheck('W');
//    if (dwState == KEY_PUSH)
//    {
//        if (bit.Bit_success_flag)
//        {
//            Player_Move_pos = { 0,-1 };
//            Move();
//            bit.Bit_success_flag = false;
//        }
//    }
//    dwState = I_Input.KeyCheck('S');
//    if (dwState == KEY_PUSH)
//    {
//        if (bit.Bit_success_flag)
//        {
//            Player_Move_pos = { 0,1 };
//            Move();
//            bit.Bit_success_flag = false;
//        }
//    }
//    dwState = I_Input.KeyCheck('A');
//    if (dwState == KEY_PUSH)
//       
//    {
//        if (bit.Bit_success_flag)
//        {
//            Player_Move_pos = { -1,0 };
//            Move();
//            bit.Bit_success_flag = false;
//        }
//    }
//    dwState = I_Input.KeyCheck('D');
//    if (dwState == KEY_PUSH)
//    {
//        if (bit.Bit_success_flag)
//        {
//            Player_Move_pos = { 1,0 };
//            Move();
//            bit.Bit_success_flag = false;
//        }
//    }
//    
//}


Sample::Sample()
{
}


Sample::~Sample()
{
}

WINRUN_DEFAULT;
