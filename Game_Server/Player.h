#pragma once
#include "User.h"
#include "Card.h"
class Player :public User ,public Singleton<Player>
{
    friend class Singleton<Player>;
public:
    //map<int, Player> Player_map;
    bool m_bBe_Ready;
    int Score;
    int Ace_Counter;
    vector<Card> Card_List;
public:
    bool Hit_Card(Card hit_card);//get_score도 내부에서 함
    void  Set_Score();

public:

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