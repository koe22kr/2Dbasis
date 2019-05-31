#include "Sample.h"
#include "CAStd.h"
#include "CABitmapObject.h"
#include "CABitmapMgr.h"

bool Sample::Init()
{
    
    I_BITMAPMGR.Load_Bitmap_Script(L"../../data/bitmap_object.txt");
    //I_SoundMgr.
    //UI = START EXIT OPTION.
    return true;
    I_BITMAPMGR.m_Obj_list[8]->m_bScale_flag = true;
    I_BITMAPMGR.m_Obj_list[8]->m_Desk_rt = { 0,0,300,300 };

    
}

bool Sample::Frame()
{
    KeyCheck();
    return true;
}
bool Sample::Render()
{
   
    return true;
}
bool Sample::Release() 
{
    
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
