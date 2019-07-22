#pragma once
#include "User.h"
class Player :public User ,public Singleton<Player>
{
    friend class Singleton<Player>;
public:
    map<int, Player> Player_map;
    bool			bCan_Chatting;
    bool			bBe_Connected;
    
    DWORD			m_dwStart_Pos;
    DWORD			m_dwWrite_Pos;
    DWORD			m_dwByte_To_Read;

    //OVERLAPPED m_ovRecv_OV;
    //int        i_Flag;
    //OVERLAPPED m_ovDummy_OV;

    SOCKET			Sock;
    SOCKADDR_IN		Client_Addr;

    WSABUF			m_wsaRecv_Buffer;
    WSABUF			m_wsaSend_Buffer;

    int				m_iRecv_Byte;
    char			m_szRecv_Buffer[MAX_USER_BUFFER_SIZE];
    char			m_szPack_Stream[MAX_STREAM_SIZE];
public:
    Player();
    virtual ~Player();
};

#define I_PLAYER Player::GetInstance()