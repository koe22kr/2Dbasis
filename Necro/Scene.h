#pragma once
class Scene
{
public:
    virtual bool Init() { return true; };
    virtual bool Frame() { return true; };
    virtual  bool Render() { return true; };
    virtual bool Release() { return true; };


    Scene();
    virtual ~Scene();
};

