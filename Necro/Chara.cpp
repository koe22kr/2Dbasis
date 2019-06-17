#include "Chara.h"

CABitmapMgr Chara::Action_bitmap_mgr;
bool Chara::Init()
{
   
    return true;
}
bool Chara::Frame() 
{
    return true;
}
 bool Chara::Render() 
 {
     return true;
     }
 bool Chara::Release()
 {
     return true;
     }

void Chara::Process()
{
    
}

 void Chara::Move()
{

}
 bool Chara::Mining()
 {
     return true;
 }

 WINT Chara::Attack()
 {
     return { 0,0 };
 }

 bool Chara::Weapon_swap(int weapon_num)
 {
     return true;
 }

Chara::Chara()
{
    active_motion_flag = false;
}


Chara::~Chara()
{
}
