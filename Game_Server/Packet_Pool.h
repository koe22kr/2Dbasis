#pragma once
#include "Protocol.h"
class Packet_Pool :public Singleton<Packet_Pool>
{
    friend Singleton<Packet_Pool>;
    list<Packet> Pool;
public:
    list<Packet>& Get();
    //const list<Packet>* Get() const;


    Packet Get_Top();
    Packet Get_Top() const;
    Packet Pop();
    void Push(Packet packet);

public:

    Packet_Pool();
    virtual ~Packet_Pool();
};

#define I_Packet_Pool Packet_Pool::GetInstance()