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
           _stscanf_s(buffer, _T("%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d"), &Dungeon_map[i][0], &Dungeon_map[i][1], &Dungeon_map[i][2], &Dungeon_map[i][3], &Dungeon_map[i][4], &Dungeon_map[i][5], &Dungeon_map[i][6], &Dungeon_map[i][7], &Dungeon_map[i][8], &Dungeon_map[i][9], &Dungeon_map[i][10], &Dungeon_map[i][11], &Dungeon_map[i][12], &Dungeon_map[i][13], &Dungeon_map[i][14], &Dungeon_map[i][15], &Dungeon_map[i][16], &Dungeon_map[i][17], &Dungeon_map[i][18], &Dungeon_map[i][19], &Dungeon_map[i][20], &Dungeon_map[i][21], &Dungeon_map[i][22], &Dungeon_map[i][23], &Dungeon_map[i][24], &Dungeon_map[i][25], &Dungeon_map[i][26], &Dungeon_map[i][27], &Dungeon_map[i][28], &Dungeon_map[i][29], &Dungeon_map[i][30], &Dungeon_map[i][31], &Dungeon_map[i][32], &Dungeon_map[i][33], &Dungeon_map[i][34], &Dungeon_map[i][35], &Dungeon_map[i][36], &Dungeon_map[i][37], &Dungeon_map[i][38], &Dungeon_map[i][39], &Dungeon_map[i][40], &Dungeon_map[i][41], &Dungeon_map[i][42], &Dungeon_map[i][43], &Dungeon_map[i][44], &Dungeon_map[i][45], &Dungeon_map[i][46], &Dungeon_map[i][47], &Dungeon_map[i][48], &Dungeon_map[i][49] );

          
   }
   
   
   Make_dungeon();
   Dunmgr.Init();
    return true;
}
void Dungeon::Map_check(int x, int y)
{
    //Map_check(m_Camera_pos.x,m_Camera_pos.y);
    if (rending_map[y][x] == true)
    {
        return;
    }
    if (x < 49 && x>0 && y < 39 && y>0)
    {
        rending_map[y][x] = true;
        if (Dungeon_map[y][x] == 0)
        {
           // Map_check(x - 1, y - 1);
            Map_check(x, y - 1);
            //Map_check(x + 1, y - 1);

            Map_check(x - 1, y);
            Map_check(x + 1, y);

            //Map_check(x - 1, y + 1);
            Map_check(x, y + 1);
           // Map_check(x + 1, y + 1);
        }
    }
    return;
}
void Dungeon::temp2()
{
    ZeroMemory(rending_map, sizeof(rending_map));
    for (int i = 0; i < Dunmgr.m_Obj_list.size(); i++)
    {
        Dunmgr.m_Obj_list[i]->Release();
    }
    Dunmgr.m_Obj_list.clear();

    Map_check(m_Camera_pos.x, m_Camera_pos.y);

    POINT start_pos = { m_Camera_pos.x - (rending_map_size.x / 2), m_Camera_pos.y - (rending_map_size.y / 2) };
    
    for (int i = 0; i < 20; i++)
    {
        for (int k = 0; k < 16; k++)
        {
            if (start_pos.x + k > 49 || start_pos.x + k < 0 || start_pos.y + i > 39 || start_pos.y + i < 0)
                int a = 0;
            else if (rending_map[start_pos.y+i][start_pos.x+k] == true)
            {
                //Dungeon_map[start_pos.y+i][start_pos.x+k]
                if (Dungeon_map[start_pos.y + i][start_pos.x + k] != 1 &&
                    Dungeon_map[start_pos.y + i][start_pos.x + k] != 2 &&
                    Dungeon_map[start_pos.y + i][start_pos.x + k] != 3 &&
                    Dungeon_map[start_pos.y + i][start_pos.x + k] != 4 &&
                    Dungeon_map[start_pos.y + i][start_pos.x + k] != 5)
                {
                    CABitmapObject* floors = Dunmgr.Load_Object(L"floors.bmp");
                    floors->Setobject(L"tile", 1, (k * 48) - 48, (i * 48) - 48, { 0,0,24,24 }, false, false);
                    floors->m_iRt_num = 0;
                    floors->Scale(2, 2);
                    //wall->m_bDraw_flag = false;
                    if (Dungeon_map[start_pos.y + i][start_pos.x + k] == 6 ||
                        Dungeon_map[start_pos.y + i][start_pos.x + k] == 7)
                    {
                        CABitmapObject* floors = Dunmgr.Load_Object(L"walls.bmp");
                        floors->Setobject(L"door", 8, (k * 48) - 48, (i * 48) - 78, rt_list, false, false);
                        floors->m_iRt_num = Dungeon_map[start_pos.y + i][start_pos.x + k];
                        floors->Scale(2, 2);
                    }
                }
                else
                {
                    CABitmapObject* wall = Dunmgr.Load_Object(L"walls.bmp");
                    wall->Setobject(L"wall", 8, (k * 48) - 48, (i * 48) - 78, rt_list, false, false);
                    wall->m_iRt_num = Dungeon_map[start_pos.y + i][start_pos.x + k];
                    wall->Scale(2, 2);
                }
            }
        }
    }
}
void Dungeon::temp()
{
    for (int i = 0; i < Dunmgr.m_Obj_list.size(); i++)
    {
        Dunmgr.m_Obj_list[i]->Release();
    }
    Dunmgr.m_Obj_list.clear();


    ZeroMemory(rending_map, sizeof(rending_map));
    POINT start_pos = { m_Camera_pos.x - (rending_map_size.x / 2), m_Camera_pos.y - (rending_map_size.y / 2) };
    
    for (int i=0;i<rending_map_size.y; i++)
    {
        
        for (int k=0 ;k< rending_map_size.x; k++)
        {
            if (Dungeon_map[start_pos.y+i][start_pos.x+k] == 0)
            {
                
                rending_map[i ][k ] = true;
                rending_map[i ][k+1] = true;
                rending_map[i ][k +2] = true;
                            
                rending_map[i+1][k ] = true;
                rending_map[i+1][k+1] = true;
                rending_map[i+1][k +2] = true;
                            
                rending_map[i + 2][k ] = true;
                rending_map[i + 2][k+1] = true;
                rending_map[i + 2][k + 2] = true;
            }
            return;
        }
   
    }
    
    for (int i=0;i<20;i++)
    {
        for (int k=0;k<16;k++)
        {
            if (start_pos.x + k > 49 || start_pos.x + k < 0 || start_pos.y + i > 39 || start_pos.y + i < 0)
                int a = 0;
            else if (rending_map[i + 1][k + 1] == true)
            {
                //Dungeon_map[start_pos.y+i][start_pos.x+k]
                if (Dungeon_map[start_pos.y + i][start_pos.x + k] != 1 &&
                    Dungeon_map[start_pos.y + i][start_pos.x + k] != 2 &&
                    Dungeon_map[start_pos.y + i][start_pos.x + k] != 3 &&
                    Dungeon_map[start_pos.y + i][start_pos.x + k] != 4 &&
                    Dungeon_map[start_pos.y + i][start_pos.x + k] != 5)
                {
                    CABitmapObject* floors = Dunmgr.Load_Object(L"floors.bmp");
                    floors->Setobject(L"tile", 1, (k * 48) - 48, (i * 48) - 48, { 0,0,24,24 }, false, false);
                    floors->m_iRt_num = 0;
                    floors->Scale(2, 2);
                    //wall->m_bDraw_flag = false;
                    if (Dungeon_map[start_pos.y + i][start_pos.x + k] == 6 ||
                        Dungeon_map[start_pos.y + i][start_pos.x + k] == 7)
                    {
                        CABitmapObject* floors = Dunmgr.Load_Object(L"walls.bmp");
                        floors->Setobject(L"door", 8, (k * 48) - 48, (i * 48) - 78, rt_list, false, false);
                        floors->m_iRt_num = Dungeon_map[start_pos.y + i][start_pos.x + k];
                        floors->Scale(2, 2);
                    }
                }
                else
                {
                    CABitmapObject* wall = Dunmgr.Load_Object(L"walls.bmp");
                    wall->Setobject(L"wall", 8, (k * 48) - 48, (i * 48) - 78, rt_list , false, false);
                    wall->m_iRt_num = Dungeon_map[start_pos.y + i][start_pos.x + k];
                    wall->Scale(2, 2);
                }

               



            }
        }
    }
    int kkk = 0;

}

void Dungeon::Make_dungeon()
{
    
    temp2();
    

    //
    //
    //for (int i = 0; i < Dunmgr.m_Obj_list.size(); i++)
    //{
    //    Dunmgr.m_Obj_list[i]->Release();
    //}
    //    Dunmgr.m_Obj_list.clear();
    //a
    //
    //    int y = 0;
    //
    //    for (int i = m_Camera_pos.y - (rending_map_size.y / 2); i < m_Camera_pos.y + (rending_map_size.y / 2); i++)
    //    {
    //        int x = 0;
    //        for (int k = m_Camera_pos.x - (rending_map_size.x / 2); k < m_Camera_pos.x + (rending_map_size.x / 2); k++)
    //        {
    //            if (k > 49 || k < 0
    //                || i > 39 || i < 0)
    //            {
    //                int a = 0;
    //            }
    //            else
    //            {
    //
    //                if (Dungeon_map[i][k] != 1 && Dungeon_map[i][k] != 2 && Dungeon_map[i][k] != 3 && Dungeon_map[i][k] != 4 && Dungeon_map[i][k] != 5)
    //                {
    //                    CABitmapObject* floors = Dunmgr.Load_Object(L"floors.bmp");
    //                    floors->Setobject(L"tile", 1, (x * 48)-48, (y * 48)-48, { 0,0,24,24 }, false, false);
    //                    floors->m_iRt_num = 0;
    //                    floors->Scale(2, 2);
    //                    //wall->m_bDraw_flag = false;
    //                    if (Dungeon_map[i][k] == 6 || Dungeon_map[i][k] == 7)
    //                    {
    //                        CABitmapObject* floors = Dunmgr.Load_Object(L"walls.bmp");
    //                        floors->Setobject(L"door", 8, (x * 48)-48, (y * 48) - 78, rt_list[Dungeon_map[i][k]]/*rt_list*/, false, false);
    //                        floors->m_iRt_num = 0; //Dungeon_map[i][k];
    //                        floors->Scale(2, 2);
    //                    }
    //                }
    //                else
    //                {
    //                    CABitmapObject* wall = Dunmgr.Load_Object(L"walls.bmp");
    //                    wall->Setobject(L"wall", 8, (x * 48)-48, (y * 48) - 78, rt_list[Dungeon_map[i][k]] /*rt_list*/, false, false);
    //                    wall->m_iRt_num = 0; //Dungeon_map[i][k];
    //                    wall->Scale(2, 2);
    //                }
    //
    //            }
    //
    //            x++;
    //        }
    //        y++;
    //    }
    //   
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
   
        m_Camera_pos.x += m_Move_pos.x;
        m_Camera_pos.y += m_Move_pos.y;
        
        Make_dungeon();
        m_Move_pos = { 0,0 };
    }
    for (auto obj : Dunmgr.m_Obj_list)
    {
        obj->m_pos.x -= (48 *20* g_fSecondPerFrame * m_Move_pos.x);
        obj->m_pos.y -= (48 *20* g_fSecondPerFrame * m_Move_pos.y);
    }
    
}
bool Dungeon::Frame()
{
    
    
    
    //CABitmapObject* walls = Dunmgr.Load_Object(L"walls.bmp");
    Dunmgr.Frame();

    if(m_bCamera_move_flag==true)
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
