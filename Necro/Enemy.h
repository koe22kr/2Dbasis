#pragma once
#include "Std.h"
#include "Chara.h"


class Pather
{
public:
    Pather* pre_pather = nullptr;
    POINT pos = { 0,0 };
    int Score = 0;
    int direction;
    int Getdirection();
    Pather();
    ~Pather();

private:

};

class Enemy :public Chara
{
public:

    virtual bool Init();
    bool release();
    virtual void Process();
    virtual void Move();
    virtual bool Mining();
    virtual void Attack();
    virtual void Change_rt(int start_rt,int end_rt);
    POINT Astar();
    vector<POINT> Direction_for_search;
    vector<POINT> path;
    set <Pather*> Openlist;
    set <Pather*> Closelist;
    Pather* find_Pather_in_openlist(set<Pather*> openlist, Pather* newpather);

    Enemy();
    virtual ~Enemy();
};
