#pragma once
#include "CAStd.h"
#include "Std.h"
#include "Chara.h"
class Weapon
{
public:
    int POWER;

    virtual bool Attack(int x,int y);
    virtual bool Frame() { return true; };
    virtual bool Render() { return true; };
    virtual bool Release() { return true; };

    Weapon();
    virtual ~Weapon();
};



class Sword :public Weapon
{
public:
    bool Attack(int x, int y);
    Sword();
    ~Sword();

private:

};


class Gratesword :public Weapon
{
public:
    bool Attack(int x, int y);
    Gratesword();
    ~Gratesword();

private:

};

class Spear :public Weapon
{
public:
    bool Attack(int x, int y);
    Spear();
    ~Spear();

private:

};