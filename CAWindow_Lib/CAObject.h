#include "CAStd.h"
#include "CABitmap.h"
#pragma once

class CAObject 
{
public:
    
    //vector<CAObject*> m_Obj_list;
   // virtual bool Draw() = 0;
   // virtual void Move() = 0;
    CAObject() {};
    virtual ~CAObject() {};
    virtual bool             Init() = 0;
    virtual bool             Render() = 0;
    virtual bool             Frame() = 0;
    virtual bool             Release() = 0;
private:

};
