#include "Dungeon.h"
#include "Charamgr.h"

int Dungeon_world[40][50];
POINT rending_arr_size = { 16,12 };//짝수만 사용
bool rending_arr[40][50] = { 0 };
float g_fSpeed = 0.8;

bool Dungeon::Init()
{
    //../../data/bitmap/
    //../../data/bitmap/   
    Dunmgr.Load_Bitmap(L"walls.bmp");
    Dunmgr.Load_Bitmap(L"floors.bmp");
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
           _stscanf_s(buffer, _T("%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d"), &Dungeon_world[i][0], &Dungeon_world[i][1], &Dungeon_world[i][2], &Dungeon_world[i][3], &Dungeon_world[i][4], &Dungeon_world[i][5], &Dungeon_world[i][6], &Dungeon_world[i][7], &Dungeon_world[i][8], &Dungeon_world[i][9], &Dungeon_world[i][10], &Dungeon_world[i][11], &Dungeon_world[i][12], &Dungeon_world[i][13], &Dungeon_world[i][14], &Dungeon_world[i][15], &Dungeon_world[i][16], &Dungeon_world[i][17], &Dungeon_world[i][18], &Dungeon_world[i][19], &Dungeon_world[i][20], &Dungeon_world[i][21], &Dungeon_world[i][22], &Dungeon_world[i][23], &Dungeon_world[i][24], &Dungeon_world[i][25], &Dungeon_world[i][26], &Dungeon_world[i][27], &Dungeon_world[i][28], &Dungeon_world[i][29], &Dungeon_world[i][30], &Dungeon_world[i][31], &Dungeon_world[i][32], &Dungeon_world[i][33], &Dungeon_world[i][34], &Dungeon_world[i][35], &Dungeon_world[i][36], &Dungeon_world[i][37], &Dungeon_world[i][38], &Dungeon_world[i][39], &Dungeon_world[i][40], &Dungeon_world[i][41], &Dungeon_world[i][42], &Dungeon_world[i][43], &Dungeon_world[i][44], &Dungeon_world[i][45], &Dungeon_world[i][46], &Dungeon_world[i][47], &Dungeon_world[i][48], &Dungeon_world[i][49] );

          
   }
   
   
   //Make_dungeon();
    I_SoundMgr.PlayBGM("zone3_2c.ogg");
   Dunmgr.Init();
    return true;
}
void Dungeon::Map_check(int x, int y,int count)
{
    //count++;
    //if (count > 45)
    //{
    //    return;
    //}
    if (rending_arr[y][x] == true)
    {
        return;
    }
    if (x <= 49 && x>=0 && y <= 39 && y>=0
        && Charactor_list[0]->m_Chara_pos.x - (rending_arr_size.x / 2)-1 < x 
        &&Charactor_list[0]->m_Chara_pos.x + (rending_arr_size.x / 2)+1 > x
        &&Charactor_list[0]->m_Chara_pos.y - (rending_arr_size.y / 2)-1 <y
        &&Charactor_list[0]->m_Chara_pos.y + (rending_arr_size.y / 2)+1 > y)
    {
        rending_arr[y][x] = true;
        for (Chara* cha : Charactor_list)
        {
            if (cha->m_Chara_pos.x == x&& cha->m_Chara_pos.y == y)
            {
                cha->Chara_active_flag = true;
            }
        }
        if (Dungeon_world[y][x] == 0)
        {
           // Map_check(x - 1, y - 1, count);
           // Map_check(x - 1, y + 1, count);
           // Map_check(x + 1, y - 1,count );
            
            Map_check(x + 1, y + 1,count );
            Map_check(x, y - 1, count);
            Map_check(x + 1, y, count);
            Map_check(x, y + 1, count);
            Map_check(x - 1, y, count);
           
        }

        //Charactor_list[0]->m_Chara_pos.x - (rending_arr_size.x / 2), Charactor_list[0]->m_Chara_pos.y - (rending_arr_size.y / 2
        //
    }
    return;
}
void Dungeon::Load(int inx, int iny,int i,int k)
{
    //Dungeon_world[start_pos.y+i][start_pos.x+k]
    if (Dungeon_world[iny + i][inx + k] != WALL1 &&
        Dungeon_world[iny + i][inx + k] != WALL2 &&
        Dungeon_world[iny + i][inx + k] != WALL3 &&
        Dungeon_world[iny + i][inx + k] != IRONWALL1 &&
        Dungeon_world[iny + i][inx + k] != IRONWALL2)
    {
        CABitmapObject* floors = Dunmgr.Load_Object(L"floors.bmp");
        floors->Setobject(L"tile", 1, (k * 48), (i * 48)-12 , { 0,0,24,24 }, false, false);
        floors->m_iRt_num = FLOOR;
        floors->Scale(2, 2);
        //wall->m_bDraw_flag = false;
        if (Dungeon_world[iny + i][inx + k] == 6 ||
            Dungeon_world[iny + i][inx + k] == 7)
        {
            CABitmapObject* floors = Dunmgr.Load_Object(L"walls.bmp");
            floors->Setobject(L"door", 8, (k * 48), (i * 48)-48 , rt_list, false, false);
            floors->m_iRt_num = Dungeon_world[iny + i][inx + k];
            floors->Scale(2, 2);
        }
    }
    else
    {
        CABitmapObject* wall = Dunmgr.Load_Object(L"walls.bmp");
        wall->Setobject(L"wall", 8, (k * 48), (i * 48)-48 , rt_list, false, false);
        wall->m_iRt_num = Dungeon_world[iny + i][inx + k];
        wall->Scale(2, 2);
    }
}

//void Dungeon::Make_dungeon()
//{
//
//
//    ZeroMemory(rending_arr, sizeof(rending_arr));
//    for (int i = 0; i < Dunmgr.m_Obj_list.size(); i++)
//    {
//        Dunmgr.m_Obj_list[i]->Release();
//    }
//    Dunmgr.m_Obj_list.clear();
//
//    Map_check(m_Camera_pos.x, m_Camera_pos.y);
//
//    POINT start_pos = { m_Camera_pos.x - (rending_arr_size.x / 2), m_Camera_pos.y - (rending_arr_size.y / 2) };
//
//    for (int i = 0; i < 20; i++)
//    {
//        for (int k = 0; k < 16; k++)
//        {
//            if (start_pos.x + k > 49 || start_pos.x + k < 0 || start_pos.y + i > 39 || start_pos.y + i < 0)
//                int a = 0;
//            else if (rending_arr[start_pos.y + i][start_pos.x + k] == true)
//            {
//                //Dungeon_world[start_pos.y+i][start_pos.x+k]
//                if (Dungeon_world[start_pos.y + i][start_pos.x + k] != 1 &&
//                    Dungeon_world[start_pos.y + i][start_pos.x + k] != 2 &&
//                    Dungeon_world[start_pos.y + i][start_pos.x + k] != 3 &&
//                    Dungeon_world[start_pos.y + i][start_pos.x + k] != 4 &&
//                    Dungeon_world[start_pos.y + i][start_pos.x + k] != 5)
//                {
//                    CABitmapObject* floors = Dunmgr.Load_Object(L"floors.bmp");
//                    floors->Setobject(L"tile", 1, (k * 48) - 48, (i * 48) - 48, { 0,0,24,24 }, false, false);
//                    floors->m_iRt_num = 0;
//                    floors->Scale(2, 2);
//                    //wall->m_bDraw_flag = false;
//                    if (Dungeon_world[start_pos.y + i][start_pos.x + k] == 6 ||
//                        Dungeon_world[start_pos.y + i][start_pos.x + k] == 7)
//                    {
//                        CABitmapObject* floors = Dunmgr.Load_Object(L"walls.bmp");
//                        floors->Setobject(L"door", 8, (k * 48) - 48, (i * 48) - 78, rt_list, false, false);
//                        floors->m_iRt_num = Dungeon_world[start_pos.y + i][start_pos.x + k];
//                        floors->Scale(2, 2);
//                    }
//                }
//                else
//                {
//                    CABitmapObject* wall = Dunmgr.Load_Object(L"walls.bmp");
//                    wall->Setobject(L"wall", 8, (k * 48) - 48, (i * 48) - 78, rt_list, false, false);
//                    wall->m_iRt_num = Dungeon_world[start_pos.y + i][start_pos.x + k];
//                    wall->Scale(2, 2);
//                }
//            }
//        }
//
//
//
//
//    }
//}
//void Dungeon::Camera_move()
//{
//    m_bCamera_move_flag = true;
//    switch (m_iInput_Key)
//    {
//        case UP:
//        {
//            Player_Move_pos.y = -1;
//            break;
//        }
//        case DOWN:
//        {
//            Player_Move_pos.y = 1;
//            break;
//        }
//        case LEFT:
//        {
//            Player_Move_pos.x = -1;
//            break;
//        }
//        case RIGHT:
//        {
//            Player_Move_pos.x = 1;
//            break;
//        }
//    }
//    Make_dungeon();
//}
void Dungeon::Dungeon_move()
{
  m_fDelta_time2 += 20 * g_fSecondPerFrame; //0.5초 동안 이동
  if (m_fDelta_time2 >= 1)
  {
      m_bCamera_move_flag = false;
      m_fDelta_time2 = 0;
  
      m_Camera_pos.x += Charactor_list[0]->m_Move_pos.x;
      m_Camera_pos.y += Charactor_list[0]->m_Move_pos.y;
      
     // Make_dungeon();
      //Player_Move_pos = { 0,0 };
  }
  for (auto obj : Dunmgr.m_Obj_list)
  {
      obj->m_pos.x -= (48 *20* g_fSecondPerFrame * Charactor_list[0]->m_Move_pos.x);
      obj->m_pos.y -= (48 *20* g_fSecondPerFrame * Charactor_list[0]->m_Move_pos.y);
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
