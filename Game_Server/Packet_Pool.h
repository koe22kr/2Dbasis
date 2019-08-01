#pragma once
#include "Player.h"
class Packet_Pool :public Singleton<Packet_Pool>
{
    friend Singleton<Packet_Pool>;
public:
    list<Packet2> Pool;
    list<Packet2>& Get();

    //const list<Packet>* Get() const;

    Packet2 Get_Top();
    Packet2 Get_Top() const;
    Packet2 Pop();
    //void Push(Packet packet);
    void Push(Packet2 packet);

public:

    Packet_Pool();
    virtual ~Packet_Pool();
};

#define I_Packet_Pool Packet_Pool::GetInstance()