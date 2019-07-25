#pragma once
#include "Server_std.h"
#include "IOCP.h"
#include "Acceptor.h"
#include "Packet_Pool.h"
#include "Player_Mgr.h"
#include "Dealer.h"
#include "Sender.h"
//#include "ODBC_Query.h"
enum Game_Phase
{
    Waitting_Ready   = 101,
    All_Player_Ready = 102,
    Set_Up_Turn      = 103,
    Player_Turn      = 104,
    Dealer_Turn      = 105,
    ALL_Turn_Over    = 106,
    Re_Set           = 107
};

class Server_Game :public Thread
{
    Dealer m_Dealer;


    WSADATA wsa;
    SOCKET listensock;
    SOCKADDR_IN sa_in;
public:
    int m_iReady_Count;
    int m_iTurn_End_Count;
    time_t Ready_Timer;
    time_t Delta_Time;
    DWORD m_dwPhase;
    
    void Init();
    void I_Wanna_Go_Home();

    void Frame();


    void Pre_Frame();
    void Post_Frame();

public:
    Server_Game();
    virtual ~Server_Game();
};

