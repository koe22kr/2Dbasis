#include "UI.h"


bool UI::Init()
{
    HP[0] = UImgr.Load_Object(UI_file_name);
    HP[1] = UImgr.Load_Object(UI_file_name);
    HP[2] = UImgr.Load_Object(UI_file_name);
    HP[3] = UImgr.Load_Object(UI_file_name);
    HP[4] = UImgr.Load_Object(UI_file_name);
    HP[0]->Setobject(L"HP1", 3, 750, 30, { {0,0,23,21},{29,0,23,21},{58,0,23,21} },true);
    HP[1]->Setobject(L"HP1", 3, 700, 30, { {0,0,23,21},{29,0,23,21},{58,0,23,21} },true);
    HP[2]->Setobject(L"HP1", 3, 650, 30, { {0,0,23,21},{29,0,23,21},{58,0,23,21} },true);
    HP[3]->Setobject(L"HP1", 3, 600, 30, { {0,0,23,21},{29,0,23,21},{58,0,23,21} },true);
    HP[4]->Setobject(L"HP1", 3, 550, 30, { {0,0,23,21},{29,0,23,21},{58,0,23,21} },true);
   
        HP[0]->Scale(2, 2);
        HP[0]->Scale(2, 2);
        HP[0]->Scale(2, 2);
        HP[1]->Scale(2, 2);
        HP[1]->Scale(2, 2);
        HP[1]->Scale(2, 2);
        HP[2]->Scale(2, 2);
        HP[2]->Scale(2, 2);
        HP[2]->Scale(2, 2);
        HP[3]->Scale(2, 2);
        HP[3]->Scale(2, 2);
        HP[3]->Scale(2, 2);
        HP[4]->Scale(2, 2);
        HP[4]->Scale(2, 2);
        HP[4]->Scale(2, 2);
   


   CABitmapObject* beat_heart = UImgr.Load_Object(UI_file_name);

   beat_heart->Setobject(L"Beat_heart", 2, 400, 550, { {116,0,40,50},{156,0,40,50 } }, true,true, 0.76);
   UImgr.Init();
   
   
   

    return true;
}

void UI::HP_operate()
{
    //test용 함수
    //test_time += g_fSecondPerFrame;
    //if (test_time > 4)
    //{
    //    dis_count_hp += 1;
    //    test_time -= 4;
    //}

    int i;
    dis_count_hp=min(dis_count_hp, 10);
    for (i = 0; i < dis_count_hp/2; i++)
    {
            HP[i]->m_iRt_num = 2; // 완하트 제거
    }
    if (dis_count_hp % 2 == 1)
    {
        HP[i]->m_iRt_num = 1;
    }

}

bool UI::Frame()
{

   

    HP_operate();
    UImgr.Frame();
    return true;
}
bool UI::Render()
{
    UImgr.Render();
    return true;
}
bool UI::Release()
{
    UImgr.Release();
    return true;
}
UI::UI()
{
}


UI::~UI()
{
}
