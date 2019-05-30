#pragma once

class CAObject
{
public:
    CAObject() {};
    virtual ~CAObject() {};
   virtual bool             Init() { return true; };
   virtual bool             Render() { return true; };
   virtual bool             Frame() { return true; };
   virtual bool             Release() { return true; };
private:

};
