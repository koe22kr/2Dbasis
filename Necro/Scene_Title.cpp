#include "Scene_Title.h"



bool Scene_Title::Init()        
{

    //페이즈0
    CABitmapObject* title =ui.UImgr.Load_Object(L"title.bmp");
    title->Setobject(L"Title", 1, 0, 0, { 0,0,600,400 });
    title->Scale(1.5, 1.5);

    CABitmapObject* frameeffect01 = ui.UImgr.Load_Object(L"frameeffects001m.bmp");
    vector<RECT> rt1 = {
                        {0,0,400,300},{400,0,400,300},
                        {0,300,400,300},{400,300,400,300},
                        {0,600,400,300},{400,600,400,300},
                        {0,900,400,300},{400,900,400,300},
                        {0,1200,400,300},{400,1200,400,300},
                        };
    
    frameeffect01->Setobject(L"effect", 10, 0, 0,rt1,false,true,1,0,0,120,0);
    frameeffect01->Scale(2.0, 2.0);
    CABitmapObject* pushenter = ui.UImgr.Load_Object(L"PAK.bmp");
    pushenter->Setobject(L"Push_Enter", 1, 400, 300, {0,0,268,76},true);
    
    m_iphase_num = 0;
    
    //페이즈1


    return true;
}
bool Scene_Title::Frame()
{
    //페이즈 0
    m_fScene_deltatime_1s += g_fSecondPerFrame;
    if (m_iphase_num == 0)
    {

        if (m_Scene_scale_flag)
        {
            ui.UImgr.m_Obj_list[2]->Scale(1 + 0.2*m_fScene_deltatime_1s, 1 + 0.2*m_fScene_deltatime_1s);
        }
        else
        {
            ui.UImgr.m_Obj_list[2]->Scale(1.2 - 0.2*m_fScene_deltatime_1s, 1.2 - 0.2*m_fScene_deltatime_1s);
        }
        if (m_fScene_deltatime_1s > 1)
        {
            m_fScene_deltatime_1s -= 1;
            m_Scene_scale_flag = !m_Scene_scale_flag;
        }

        for (MSG dwkey : I_MSG.Msg_list)
        {

            if (LOWORD(dwkey.wParam) == WA_INACTIVE)
            {
                
            }
            else if(dwkey.message==WM_KEYDOWN)
            {
                m_iphase_num = 1;
                ui.UImgr.m_Obj_list.clear();//여기 해야함
                여기부터 해야함 빨간줄
            }
            
        }

    }
       

    //페이즈1


   
    if (m_iphase_num == 1)
    {
        DWORD dwState = I_Input.KeyCheck(VK_RETURN);
        if (dwState == KEY_PUSH)
        {
            Scene_num = 2;
        }
    }
    ui.UImgr.Frame();
    return true;
    }
bool Scene_Title::Render()
{
    ui.UImgr.Render();
    return true;
    }
bool Scene_Title::Release()
{
    ui.UImgr.Release();
    return true;
}


Scene_Title::Scene_Title()
{
}


Scene_Title::~Scene_Title()
{
}
