#pragma once
#include "Thread.h"
#include "Player_Mgr.h"
class Sender : public Thread, public Singleton<Sender>
{
    friend Singleton<Sender>;
public:
    vector<sPacket> Send_Pool;
    vector<Packet> Broadcast_Pool;
public:
    void Send();
    void Single_Packet_Make(Player* pPlayer, WORD type, char* msg = nullptr, WORD msg_len = 0);
    void Broadcast_Packet_Make(WORD type, char* msg = nullptr, WORD msg_len = 0);
public:
    Sender();
    virtual ~Sender();
};

#define I_SENDER Sender::GetInstance()
