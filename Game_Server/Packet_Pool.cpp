#include "Packet_Pool.h"

Packet2 Packet_Pool::Get_Top()
{
    return Pool.front();
}

Packet2 Packet_Pool::Get_Top() const
{
    return Pool.front();
}

Packet2 Packet_Pool::Pop()
{
    Packet2 temp = Pool.front();
    Pool.pop_front();
    return temp;
}

list<Packet2>& Packet_Pool::Get()
{
    return Pool;
}


//const list<Packet>* Packet_Pool::Get() const //??????????????????????????????????????????????????
//{
//    return &Pool;
//}
//void Packet_Pool::Push(Packet packet)
//{
//    Packet2 temp;
//    strcpy(temp.msg, packet.msg);
//    temp.ph = packet.ph;
//    temp.pPlayer = nullptr;
//}

void Packet_Pool::Push(Packet2 packet)
{
    Pool.push_back(packet);
}

Packet_Pool::Packet_Pool()
{
}


Packet_Pool::~Packet_Pool()
{
}

