#pragma once
#include "CAStd.h"
#include "CABitmapObject.h"
//#include "Status.h"

#include "CABitmapMgr.h"
class Dante :public CABitmapObject
{
public:
    // Status stat;
    int HP = 10;
    int Cur_Action = 0;
   //Dante* NewObject() { return new Dante; };
  
    void Attack1();
    void Attack2();
    void Attack3();
    
   void Move();
    Dante();
    virtual ~Dante();
};

