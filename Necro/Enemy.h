#pragma once
#include "Std.h"
#include "Chara.h"

class Enemy :public Chara
{
public:
    virtual bool Init();
    virtual void Process();
    virtual void Move();
    virtual void Mining();
    virtual void Attack();
    virtual void Change_rt();
    bool Astar();
    POINT Direction_for_search[4];
    Enemy();
    virtual ~Enemy();
};

class MyClass
{
public:
    MyClass();
    ~MyClass();

private:

};

MyClass::MyClass()
{
}

MyClass::~MyClass()
{
}