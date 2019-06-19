#pragma once
#include "CAStd.h"
#define WM_WEAPON  (WM_USER+1)
#define WM_CAMERA_MOVED (WM_USER+2)

class CAPOINT;
class Chara;
enum map_obj
{
    FLOOR, WALL1, WALL2, WALL3, IRONWALL1, IRONWALL2, DOOR1, DOOR2
};

//enum Key
//{
//    UP=1,DOWN,LEFT,RIGHT
//};
extern int World_Charactor_pos[40][50];   //1== player   2==skeleton
extern vector<Chara*> Charactor_list;

//extern CAPOINT Player_Move_pos;  //상대적 이동위치 로 하자.
extern POINT start_pos;
extern int Dungeon_world[40][50];
extern  bool rending_arr[40][50];  //위아래 한칸씩 여유두기
extern bool Turn_flag;
//extern bool Bit_success_flag;
extern bool Key_push;
extern POINT rending_arr_size;
//extern POINT m_Camera_pos;
extern float g_fSpeed;
extern bool Move_flag;
extern void Scene_change(int scene_num);