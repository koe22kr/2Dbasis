#include "Packet_Pool.h"

Packet Packet_Pool::Get_Top()
{
    return Pool.front();
}

Packet Packet_Pool::Get_Top() const
{
    return Pool.front();
}

Packet Packet_Pool::Pop()
{
    Packet temp = Pool.front();
    Pool.pop_front();
    return temp;
}

list<Packet>& Packet_Pool::Get()
{
    return Pool;
}

//const list<Packet>* Packet_Pool::Get() const //??????????????????????????????????????????????????
//{
//    return &Pool;
//}

void Packet_Pool::Push(Packet packet)
{
    Pool.push_back(packet);
}

Packet_Pool::Packet_Pool()
{
}


Packet_Pool::~Packet_Pool()
{
}

