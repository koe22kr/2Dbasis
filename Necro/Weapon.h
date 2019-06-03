#pragma once
class Weapon
{
public:

    virtual bool Init() { return true; };
    virtual bool Frame() { return true; };
    virtual bool Render() { return true; };
    virtual bool Release() { return true; };

    Weapon();
    virtual ~Weapon();
};

