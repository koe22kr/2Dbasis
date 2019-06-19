
#include "CAStd.h"
#include ""
#include "Sample.h"

//Bitmap-> Bitmap //blit  비트맵은 비트맵에만 뿌릴수있.
//DC->DC 디바이스 컨넥에서.. DC 로만; HDC를 bitmap당 하나씩 만들어야함. memdc도 하나..//device context



bool Sample::Init()
{
    
   
    //mgr.Load_Object(L"wall.bmp");
    //mgr.Load_Object(L"bitmap1.bmp");
    mgr.Load_Bitmap_Script(L"../../data/bitmap_object.txt");
    //mgr.m_Obj_list[0]->Setobject(L"Backwall", 1, 0, 0, { 0,0,800,600 });
    //mgr.m_Obj_list[1]->m_fAngle = 30;
   //mgr.m_Obj_list[2]->m_fAngle = 40;
    //mgr.m_Obj_list[2]->m_fAlpha = 128;

    
    //mgr.m_Obj_list[1]->Setobject(L"Player", 1, 100, 100, 0, 0, { 90,1,40,60 }, 0);
    
    
    
    mgr.Init();
    return true;
}

bool Sample::Render()
{
    mgr.Render();
    //m_bk.Render();
    //m_player.Render();
    return true;
}

bool Sample::Frame()
{
    mgr.Frame();

     DWORD dwState = I_Input.KeyCheck('W');
     if (dwState == KEY_HOLD)
     {
        mgr.Move(0,-100,1);
     }  dwState = I_Input.KeyCheck('S');
     if (dwState == KEY_HOLD)
     {
         mgr.Move(0, 100, 1);
    
     }
     dwState = I_Input.KeyCheck('A');
     if (dwState == KEY_HOLD)
     {
         mgr.Move(-100,0, 1);
    
     }
     dwState = I_Input.KeyCheck('D');
     if (dwState == KEY_HOLD)
     {
         mgr.Move(100,0, 1);
    
     }
     dwState = I_Input.KeyCheck('V');
     if (dwState == KEY_HOLD)
     {
         mgr.Move(-200,0, 2);

     }
     dwState = I_Input.KeyCheck('B');
     if (dwState == KEY_HOLD)
     {
         mgr.Move(200,0, 2);

     }
     
    return true;

}


bool Sample::Release()
{
    mgr.Release();
    // m_player.Release();
    return true;
}

Sample::Sample()
{


}


Sample::~Sample()
{
}

WINRUN_DEFAULT;




