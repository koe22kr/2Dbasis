#pragma once
#include "CAStd.h"
#include "Std.h"
#include "Chara.h"
class Weapon
{
public:
    int POWER;
    virtual WINT Attack(POINT chara_pos, POINT chara_move_pos);
    virtual bool Check(WINT target);

    virtual bool Frame() { return true; };
    virtual bool Render() { return true; };
    virtual bool Release() { return true; };
    Weapon();
    virtual ~Weapon();
};



class Sword :public Weapon
{
public:
    WINT Attack(POINT chara_pos, POINT chara_move_pos);
    bool Check(WINT target);
    Sword();
    ~Sword();

private:

};


class Gratesword :public Weapon
{
public:
    WINT Attack(POINT chara_pos, POINT chara_move_pos);
    bool Check(WINT target);
    Gratesword();
    ~Gratesword();

private:

};

class Spear :public Weapon
{
public:
    WINT Attack(POINT chara_pos, POINT chara_move_pos);
    bool Check(WINT target);
    Spear();
    ~Spear();

private:

};