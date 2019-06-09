#pragma once


class Weapon
{
public:
    int POWER;

    virtual void Attack();
    virtual bool Init() { return true; };
    virtual bool Frame() { return true; };
    virtual bool Render() { return true; };
    virtual bool Release() { return true; };

    Weapon();
    virtual ~Weapon();
};
Weapon::Weapon()
{
}
Weapon::~Weapon()
{
}


class Sword :public Weapon
{
public:
    void Attack();
    Sword();
    ~Sword();

private:

};
Sword::Sword()
{
    POWER = 1;
}
Sword::~Sword()
{

    
}

class Gratesword :public Weapon
{
public:
    void Attack();
    Gratesword();
    ~Gratesword();

private:

};
Gratesword::Gratesword()
{
    POWER = 2;
}
Gratesword::~Gratesword()
{
}

class Spear :public Weapon
{
public:
    void Attack();
    Spear();
    ~Spear();

private:

};
Spear::Spear()
{
    POWER = 2;
}
Spear::~Spear()
{
}