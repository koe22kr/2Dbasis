#include "Sample.h"
#include "CAStd.h"

bool Sample::Init()
{
    
    I_BITMAPMGR.Load_Bitmap_Script(L"../../data/bitmap_object.txt");
    
    return true;
}
bool Sample::Frame()
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
Sample::Sample()
{
}


Sample::~Sample()
{
}

WINRUN_DEFAULT;
