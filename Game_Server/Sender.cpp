#include "Sender.h"

void Sender::Send()
{
    WSABUF send_buf;
    DWORD dwSendByte;

    ////////////////////////////////////////
    for (sPacket spacket : Send_Pool)
    {
        auto pOV = new OVERLAPPED2;
        send_buf.buf = spacket.real_packet.msg;
        send_buf.len = spacket.real_packet.ph.len;

        WSASend(spacket.user_sock, &send_buf, 1, &dwSendByte, 0, (LPOVERLAPPED)pOV, NULL);
    }
    Send_Pool.clear();
    //////////////////////////////////////
    for (Packet packet : Broadcast_Pool)
    {
        for (auto player : I_PLAYER_MGR.Player_map)
        {
            auto pOV = new OVERLAPPED2;
            send_buf.buf = packet.msg;
            send_buf.len = packet.ph.len;

            packet.ph.UID = player.second->UID;
            WSASend(player.second->Sock, &send_buf, 1, &dwSendByte, 0, (LPOVERLAPPED)pOV, NULL);
        }
    }
    Broadcast_Pool.clear();
    /////////////////////////////////////
}

void Sender::Single_Packet_Make(Player* pPlayer, WORD type, char* msg, WORD msg_len)
{
    sPacket new_spacket;
    memcpy(new_spacket.real_packet.msg, msg, msg_len); //패킹
    new_spacket.user_sock = pPlayer->Sock;
    new_spacket.real_packet.ph.len = msg_len + PACKET_HEADER_SIZE;
    new_spacket.real_packet.ph.type = type;
    new_spacket.real_packet.ph.UID = pPlayer->UID;
    Send_Pool.push_back(new_spacket);
}

void Sender::Broadcast_Packet_Make(WORD type, char* msg, WORD msg_len)
{
    Packet new_packet;
    memcpy(new_packet.msg, msg, msg_len);   //패킹
    new_packet.ph.len = msg_len + PACKET_HEADER_SIZE;
    new_packet.ph.type = type;
    //UID 는 SEND시 첨가.
    Broadcast_Pool.push_back(new_packet);
}

Sender::Sender()
{
}


Sender::~Sender()
{
}
