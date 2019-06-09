#include "Sample.h"
#include "CAStd.h"
#include "CABitmapObject.h"
#include "CABitmapMgr.h"


bool Sample::Init()//모든 세팅은 이곳에서 하는게 나을듯.
{
    //I_BITMAPMGR.Load_Bitmap_Script(L"../../data/bitmap_object.txt");
    ////I_SoundMgr.
    ////UI = START EXIT OPTION.
    //I_BITMAPMGR.m_Obj_list[7]->m_bScale_flag = true;
    //// 
    //I_BITMAPMGR.m_Obj_list[7]->m_Desk_rt[0]->right = 400;
    //I_BITMAPMGR.m_Obj_list[7]->m_Desk_rt[0]->bottom = 400;
    dun.Init();
   // scene.Init();
  //  ui.Init();
   // bit.Init();
    return true;
}

bool Sample::Frame() //프래임은 Scene별
{
    dun.Frame();
    //scene.Frame();
   // ui.Frame();
   // bit.Frame();
    //    Cur_Scene->Frame();
        KeyCheck();
    return true;
}
bool Sample::Render()
{
    dun.Render();
    //scene.Render();
  //  ui.Render();
    //bit.Render();
    // Cur_Scene->Render();
    return true;
}
bool Sample::Release()
{
    dun.Release();
    //scene.Release();
  //  ui.Release();
   // bit.Release();
    // title.Release(); //신 전환시 릴리즈 할지는 생각해보기
    // game.Release();
    return true;
}
void Sample::KeyCheck()
{


    DWORD dwState = I_Input.KeyCheck('W');
    
    if (dwState == KEY_PUSH)
    {
        dun.m_iInput_Key = UP;
        dun.m_bCamera_move_flag = true;
        dun.m_Move_pos = { 0,-1 };
    }
    dwState = I_Input.KeyCheck('S');
    if (dwState == KEY_PUSH)
    {
        dun.m_iInput_Key = DOWN;
        dun.m_bCamera_move_flag = true;
        dun.m_Move_pos = { 0,1 };
    }
    dwState = I_Input.KeyCheck('A');
    if (dwState == KEY_PUSH)
       
    {
        dun.m_iInput_Key = LEFT;
        dun.m_bCamera_move_flag = true;
        dun.m_Move_pos = { -1,0 };
        
    }
    dwState = I_Input.KeyCheck('D');
    if (dwState == KEY_PUSH)
    {
        dun.m_iInput_Key = RIGHT;
        dun.m_bCamera_move_flag = true;
        dun.m_Move_pos = { 1,0 };
    }
    
}


Sample::Sample()
{
}


Sample::~Sample()
{
}

WINRUN_DEFAULT;
