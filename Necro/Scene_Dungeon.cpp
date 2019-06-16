#include "Scene_Dungeon.h"

bool Scene_Dungeon::Init()
{
    dun.Init();
    cha.Init();
    ui.Init();
    bit.Init();
    Make();
    return true;
}


bool Scene_Dungeon::Frame()
{
    dun.Frame();
    cha.Frame();
    ui.Frame();
    bit.Frame();
    if (cha.Move_done)
    {
        Make();
    }
    return true;
}
bool Scene_Dungeon::Render()
{
    dun.Render();
    cha.Render();
    bit.Render();
    ui.Render();

    return true;
}
bool Scene_Dungeon::Release()
{

    dun.Release();
    bit.Release();
    ui.Release();
    cha.Release();

    return true;
}

void    Scene_Dungeon::Make()
{
    //void Dungeon::Make_dungeon()
    {


        ZeroMemory(rending_arr, sizeof(rending_arr));
        for (int i = 0; i < dun.Dunmgr.m_Obj_list.size(); i++)
        {
            dun.Dunmgr.m_Obj_list[i]->Release();
        }
        dun.Dunmgr.m_Obj_list.clear();

        dun.Map_check(Charactor_list[0]->m_Chara_pos.x, Charactor_list[0]->m_Chara_pos.y);

        start_pos = { Charactor_list[0]->m_Chara_pos.x - (rending_arr_size.x / 2), Charactor_list[0]->m_Chara_pos.y - (rending_arr_size.y / 2) };

        for (int i = 0; i < 16; i++)
        {
            for (int k = 0; k < 18; k++)
            {
                if (start_pos.x + k > 49 || start_pos.x + k < 0 || start_pos.y + i > 39 || start_pos.y + i < 0)
                    continue;
                else if (rending_arr[start_pos.y + i][start_pos.x + k] == true)
                {

                    dun.Load(start_pos.x, start_pos.y, i, k);

                    cha.Load(start_pos.x, start_pos.y, i, k);//괄호 밖에 있엇는데 이곳으로 옴기는게 더 좋을 것 같아서 옴김 190616-20:40;
                }

                

               
            }
        }
    }
    cha.Move_done = false;
    
}



Scene_Dungeon::Scene_Dungeon()
{
}


Scene_Dungeon::~Scene_Dungeon()
{
}
