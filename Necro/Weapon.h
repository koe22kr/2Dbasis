#pragma once
#include "Std.h"
#include "Chara.h"
class Weapon
{
public:
    int POWER;

    virtual bool Attack(int target_x, int target_y, int chara_x, int chara_y);
    virtual bool Frame() { return true; };
    virtual bool Render() { return true; };
    virtual bool Release() { return true; };

    Weapon();
    virtual ~Weapon();
};



class Sword :public Weapon
{
public:
    bool Attack(int target_x, int target_y, int chara_x, int chara_y);
    Sword();
    ~Sword();

private:

};


class Gratesword :public Weapon
{
public:
    bool Attack(int target_x, int target_y, int chara_x, int chara_y);
    Gratesword();
    ~Gratesword();

private:

};

class Spear :public Weapon
{
public:
    bool Attack(int target_x, int target_y, int chara_x, int chara_y);
    Spear();
    ~Spear();

private:

};