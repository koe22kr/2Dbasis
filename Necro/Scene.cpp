#include "Scene.h"



 bool Scene::Init() 
{
    Scenemgr.Load_Object(L"wall.bmp");
    Scenemgr.m_Obj_list[0]->Setobject(L"wall", 1, 400, 300, { 0,0,800,600 },true);
     return true;
 }
 bool Scene::Frame()
 {
     Scenemgr.Frame();
     return true;
 }
 bool Scene::Render()
 {
     Scenemgr.Render();
     return true;
 }
 bool Scene::Release()
 {
     Scenemgr.Release();
     return true;
 }




Scene::Scene()
{
}


Scene::~Scene()
{
}
