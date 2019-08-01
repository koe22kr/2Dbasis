#include "Sender.h"

void Sender::Send()
{
   // char send_buf[PACKET_MAX_DATA_SIZE] = { 0 };
    //DWORD dwSendByte=0;
    int p;
    ////////////////////////////////////////
    for (sPacket spacket : Send_Pool)
    {
        
        //auto pOV = new OVERLAPPED;
        
        p = send(spacket.user_sock, (char*)&spacket.real_packet, spacket.real_packet.ph.len, 0);
        if (p == SOCKET_ERROR)
        {
            E_MSG("S_SEND");
        }
      //  p = WSASend(spacket.user_sock, &send_buf, 1, &dwSb, 0, (LPOVERLAPPED)pOV, NULL);
      // if (p == SOCKET_ERROR||INVALID_SOCKET)
      // {
      //     E_MSG("WSA_SEND");
      // }
      // if (WSAGetLastError() == WSA_INVALID_HANDLE)
      // {
      //     int g = 0;
      // }
       
       int a = WSAGetLastError();
      // int asdf = 0;
    }
    Send_Pool.clear();
    //////////////////////////////////////
    for (Packet packet : Broadcast_Pool)
    {
        for (auto player : I_PLAYER_MGR.Player_map)
        {
            packet.ph.UID = player.second->UID;
            p = send(player.second->Sock, (char*)&packet, packet.ph.len, 0);
            if (p == SOCKET_ERROR)
            {
                E_MSG("B_SEND");
            }
           //auto pOV = new OVERLAPPED2;
           //send_buf.buf = packet.msg;
           //send_buf.len = packet.ph.len;
           //
            //packet.ph.UID = player.second->UID;
            //WSASend(player.second->Sock, &send_buf, 1, &dwSendByte, 0, (LPOVERLAPPED)pOV, NULL);
        }
    }
    Broadcast_Pool.clear();
    /////////////////////////////////////
}

void Sender::Single_Packet_Make(Player* pPlayer, WORD type, char* msg, WORD msg_len)
{
    sPacket new_spacket;
    ZeroMemory(&new_spacket, sizeof(new_spacket));

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
    ZeroMemory(&new_packet, sizeof(new_packet));
    memcpy(new_packet.msg, msg, msg_len);   //패킹
    new_packet.ph.len = msg_len + PACKET_HEADER_SIZE;
    new_packet.ph.type = type;
    //UID 는 SEND시 첨가.
    Broadcast_Pool.push_back(new_packet);
}

Sender::Sender()
{
    WSADATA wsa;
    WSAStartup(MAKEWORD(2, 2), &wsa);
}


Sender::~Sender()
{
}
