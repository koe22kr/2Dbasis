#include "Scene_Title.h"



bool Scene_Title::Init()        
{

    //페이즈0
    if (m_iphase_num == 0)
    {
        CABitmapObject* title = ui.UImgr.Load_Object(L"title.bmp");
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

        frameeffect01->Setobject(L"effect", 10, 0, 0, rt1, false, true, 1, 0, 0, 120, 0);
        frameeffect01->Scale(2.0, 2.0);
        CABitmapObject* pushenter = ui.UImgr.Load_Object(L"PAK.bmp");
        pushenter->Setobject(L"Push_Enter", 1, 400, 300, { 0,0,268,76 }, true);


        I_MSG.Msg_list.clear();
        I_SoundMgr.PlayBGM("main.mp3");
    }
    //페이즈1
    if (m_iphase_num == 1)
    {
        CABitmapObject* start = ui.UImgr.Load_Object(L"bstart.bmp");
        start->Setobject(L"START", 1, 400, 450, { 0,0,183,76 }, true);

        CABitmapObject* option = ui.UImgr.Load_Object(L"boption.bmp");
        option->Setobject(L"OPTION", 1, 400, 500, { 0,0,190,76 }, true);

        CABitmapObject* exit = ui.UImgr.Load_Object(L"bexit.bmp");
        exit->Setobject(L"EXIT", 1, 400, 550, { 0,0,134,76 }, true);
    

        m_icur_button_num = 1;
    }
   





    //I_SoundMgr.PlayBGM("zone1_2.ogg");


    return true;
}
bool Scene_Title::Frame()
{
    for (MSG dwkey : I_MSG.Msg_list)
    {
        if (dwkey.message == WM_ACTIVATE && LOWORD(dwkey.wParam) == WA_INACTIVE)
        {
            Active_flag = false;
            int a = 0;
        }
        else if (dwkey.message == WM_ACTIVATE && (LOWORD(dwkey.wParam) == WA_ACTIVE || LOWORD(dwkey.wParam) == WA_CLICKACTIVE))
        {
            Active_flag = true;
        }

    }

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

        if (Active_flag)
        {
            //페이즈 0
            for (MSG dwkey : I_MSG.Msg_list)
            {

                if (LOWORD(dwkey.wParam) == WA_INACTIVE)
                {

                }
                else if (dwkey.message == WM_KEYDOWN)
                {
                    m_iphase_num = 1;
                    I_SoundMgr.PlaySE("select2.mp3");
                    ui.UImgr.m_Obj_list[2]->m_bDead_flag = true;
                    Init();
                }
            }
        }
    } //페이즈1
    if (m_iphase_num == 1&& Active_flag)
    {
        for (MSG dwkey : I_MSG.Msg_list)
        {


            DWORD dwState = I_Input.KeyCheck('W');
                if (dwState == KEY_PUSH)
                {
                    I_SoundMgr.PlaySE("select.mp3");
                    m_icur_button_num -= 1;
                    if (m_icur_button_num == 0)
                    {
                        m_icur_button_num = 3;
                    }
                }

            dwState = I_Input.KeyCheck('S');
            if (dwState == KEY_PUSH)
            {
                I_SoundMgr.PlaySE("select.mp3");
                m_icur_button_num += 1;
                if (m_icur_button_num == 4)
                {
                    m_icur_button_num = 1;
                }
            }

            if (m_icur_button_num == 1)
            {
                ui.UImgr.m_Obj_list[2]->Scale(1.2, 1.2);
                ui.UImgr.m_Obj_list[3]->Scale(1, 1);
                ui.UImgr.m_Obj_list[4]->Scale(1, 1);
                dwState = I_Input.KeyCheck(VK_RETURN);
                if (dwState == KEY_PUSH)
                {
                    I_SoundMgr.PlaySE("select2.mp3");
                    m_iNext_Scene_num = 2;
                    //ui.UImgr.m_Obj_list.clear();
                }
            }

            if (m_icur_button_num == 2)
            {
                ui.UImgr.m_Obj_list[2]->Scale(1, 1);
                ui.UImgr.m_Obj_list[3]->Scale(1.2, 1.2);
                ui.UImgr.m_Obj_list[4]->Scale(1, 1);
                dwState = I_Input.KeyCheck(VK_RETURN);
                if (dwState == KEY_PUSH)
                {
                    I_SoundMgr.PlaySE("select2.mp3");

                    m_iNext_Scene_num = 2;
                    //
                }
            }

            if (m_icur_button_num == 3)
            {
                ui.UImgr.m_Obj_list[2]->Scale(1, 1);
                ui.UImgr.m_Obj_list[3]->Scale(1, 1);
                ui.UImgr.m_Obj_list[4]->Scale(1.2, 1.2);
                dwState = I_Input.KeyCheck(VK_RETURN);
                if (dwState == KEY_PUSH)
                {
                    ui.UImgr.m_Obj_list.clear();
                    PostQuitMessage(0);

                }
            }
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
   
    ui.Release();
    
//    ui.UImgr.Release();
   // ui.UImgr.m_Obj_list.clear();
    return true;
}


Scene_Title::Scene_Title()
{
    m_iNext_Scene_num = 0;
    m_iphase_num = 0;
    m_icur_button_num = 0;
}


Scene_Title::~Scene_Title()
{
}
