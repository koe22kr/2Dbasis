#pragma once
#include "CABitmapObject.h"
#include "CAStd.h"
#include "CAObject.h"
#include "CABitmapMgr.h"
class Dante :public CABitmapObject
{
public:

    int Action = 0;
   //Dante* NewObject() { return new Dante; };
   void Attack1();
   void Move();
    Dante();
    virtual ~Dante();
};

