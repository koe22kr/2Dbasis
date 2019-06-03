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
    
    bit.Init();
    return true;
}

bool Sample::Frame() //프래임은 Scene별
{
    bit.Frame();
    //    Cur_Scene->Frame();
        //KeyCheck();
    return true;
}
bool Sample::Render()
{
    bit.Render();
    // Cur_Scene->Render();
    return true;
}
bool Sample::Release()
{
    bit.Release();
    // title.Release(); //신 전환시 릴리즈 할지는 생각해보기
    // game.Release();
    return true;
}
void Sample::KeyCheck()
{


    DWORD dwState = I_Input.KeyCheck('W');
    if (dwState == KEY_HOLD)
    {
        I_BITMAPMGR.Move(0, -100, 1);
    }  dwState = I_Input.KeyCheck('S');
    if (dwState == KEY_HOLD)
    {
        I_BITMAPMGR.Move(0, 100, 1);


    }
    dwState = I_Input.KeyCheck('A');
    if (dwState == KEY_HOLD)
    {
        I_BITMAPMGR.Move(-100, 0, 1);

    }
    dwState = I_Input.KeyCheck('D');
    if (dwState == KEY_HOLD)
    {
        I_BITMAPMGR.Move(100, 0, 1);

    }
    dwState = I_Input.KeyCheck('V');
    if (dwState == KEY_HOLD)
    {
        I_BITMAPMGR.Move(-200, 0, 2);

    }
    dwState = I_Input.KeyCheck('B');
    if (dwState == KEY_HOLD)
    {
        I_BITMAPMGR.Move(200, 0, 2);
    }
}


Sample::Sample()
{
}


Sample::~Sample()
{
}

WINRUN_DEFAULT;
