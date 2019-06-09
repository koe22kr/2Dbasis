#include "Dungeon.h"


bool Dungeon::Init()
{
    Dunmgr.Load_Bitmap(L"../../data/bitmap/walls.bmp");
    Dunmgr.Load_Bitmap(L"../../data/bitmap/floors.bmp");
  // CABitmapObject* walls = Dunmgr.Load_Object(L"walls.bmp");
  // walls->Setobject(L"walls", 8, 0, 0, rt_list,false,false);

   //
   FILE* fp = nullptr;

   _wfopen_s(&fp, L"../../data/walls.txt", _T("rt"));
   if (fp == nullptr) return false;
   
   
   
   TCHAR buffer[256] = { 0 };
   
   _fgetts(buffer, _countof(buffer), fp);
   _stscanf_s(buffer, _T("%d %d"), &m_iDungeon_size_y, &m_iDungeon_size_x);
   for (int i = 0; i < m_iDungeon_size_y; i++)
   {
           _fgetts(buffer, _countof(buffer), fp);
           _stscanf_s(buffer, _T("%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d"), &map[i][0], &map[i][1], &map[i][2], &map[i][3], &map[i][4], &map[i][5], &map[i][6], &map[i][7], &map[i][8], &map[i][9], &map[i][10], &map[i][11], &map[i][12], &map[i][13], &map[i][14], &map[i][15], &map[i][16], &map[i][17], &map[i][18], &map[i][19], &map[i][20], &map[i][21], &map[i][22], &map[i][23], &map[i][24], &map[i][25], &map[i][26], &map[i][27], &map[i][28], &map[i][29], &map[i][30], &map[i][31], &map[i][32], &map[i][33], &map[i][34], &map[i][35], &map[i][36], &map[i][37], &map[i][38], &map[i][39], &map[i][40], &map[i][41], &map[i][42], &map[i][43], &map[i][44], &map[i][45], &map[i][46], &map[i][47], &map[i][48], &map[i][49] );

          
   }
   
   
   Make_dungeon();
   Dunmgr.Init();
    return true;
}
void Dungeon::Make_dungeon()
{
    
    
    



    for (int i = 0; i < Dunmgr.m_Obj_list.size(); i++)
    {
        Dunmgr.m_Obj_list[i]->Release();
    }
        Dunmgr.m_Obj_list.clear();


        int y = 0;

        for (int i = m_Camera_pos.y - (rending_map_size.y / 2); i < m_Camera_pos.y + (rending_map_size.y / 2); i++)
        {
            int x = 0;
            for (int k = m_Camera_pos.x - (rending_map_size.x / 2); k < m_Camera_pos.x + (rending_map_size.x / 2); k++)
            {
                if (k > 49 || k < 0
                    || i > 39 || i < 0)
                {
                    int a = 0;
                }
                else
                {

                    if (map[i][k] != 1 && map[i][k] != 2 && map[i][k] != 3 && map[i][k] != 4 && map[i][k] != 5)
                    {
                        CABitmapObject* floors = Dunmgr.Load_Object(L"floors.bmp");
                        floors->Setobject(L"tile", 1, (x * 48)-48, (y * 48)-48, { 0,0,24,24 }, false, false);
                        floors->m_iRt_num = 0;
                        floors->Scale(2, 2);
                        //wall->m_bDraw_flag = false;
                        if (map[i][k] == 6 || map[i][k] == 7)
                        {
                            CABitmapObject* floors = Dunmgr.Load_Object(L"walls.bmp");
                            floors->Setobject(L"door", 8, (x * 48)-48, (y * 48) - 78, rt_list, false, false);
                            floors->m_iRt_num = map[i][k];
                            floors->Scale(2, 2);
                        }
                    }
                    else
                    {
                        CABitmapObject* wall = Dunmgr.Load_Object(L"walls.bmp");
                        wall->Setobject(L"wall", 8, (x * 48)-48, (y * 48) - 78, rt_list, false, false);
                        wall->m_iRt_num = map[i][k];
                        wall->Scale(2, 2);
                    }



                }

                x++;
            }
            y++;
        }
        //for (int i = 0; i < MAP_Y; i++)
        //{

        //    for (int k = 0; k < MAP_X; k++)
        //    {
        //        CABitmapObject* wall = Dunmgr.Load_Object(L"walls.bmp");
        //        int x = k * 24;
        //        int y = i * 42;
        //        
        //        wall->Setobject(L"tile", 8, x, y, rt_list,false,false);
        //        wall->m_iRt_num = map[i][k];

        //        
        //    }

        //}
    }
//void Dungeon::Camera_move()
//{
//    m_bCamera_move_flag = true;
//    switch (m_iInput_Key)
//    {
//        case UP:
//        {
//            m_Move_pos.y = -1;
//            break;
//        }
//        case DOWN:
//        {
//            m_Move_pos.y = 1;
//            break;
//        }
//        case LEFT:
//        {
//            m_Move_pos.x = -1;
//            break;
//        }
//        case RIGHT:
//        {
//            m_Move_pos.x = 1;
//            break;
//        }
//    }
//    Make_dungeon();
//}
void Dungeon::Dungeon_move()
{
    m_fDelta_time += 20 * g_fSecondPerFrame; //0.5초 동안 이동
    if (m_fDelta_time >= 1)
    {
        m_bCamera_move_flag = false;
        m_fDelta_time = 0;
   
        m_Camera_pos.x -= m_Move_pos.x;
        m_Camera_pos.y -= m_Move_pos.y;
        
        Make_dungeon();
        m_Move_pos = { 0,0 };
    }
    for (auto obj : Dunmgr.m_Obj_list)
    {
        obj->m_pos.x += (48 *20* g_fSecondPerFrame * m_Move_pos.x);
        obj->m_pos.y += (48 *20* g_fSecondPerFrame * m_Move_pos.y);
    }
    
}
bool Dungeon::Frame()
{
    
    
    
    //CABitmapObject* walls = Dunmgr.Load_Object(L"walls.bmp");
    Dunmgr.Frame();

    if (m_bCamera_move_flag==true)
    {
        Dungeon_move();
    }
    return true;
    
}
bool Dungeon::Render()
{

    Dunmgr.Render();
    return true;
}

bool Dungeon::Release()
{
    Dunmgr.Release();
    return true;
}

Dungeon::Dungeon()
{
}


Dungeon::~Dungeon()
{
}
