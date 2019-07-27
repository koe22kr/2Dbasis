#pragma once
#include "Server_std.h"
#include "IOCP.h"
#include "Acceptor.h"
#include "Packet_Pool.h"
#include "Player_Mgr.h"
#include "Dealer_FSM.h"
#include "Sender.h"
//#include "ODBC_Query.h"


class Server_Game :public Thread
{
    Dealer_FSM FSM;
    WSADATA wsa;
    SOCKET listensock;
    SOCKADDR_IN sa_in;
public:
 
   // time_t Ready_Timer;
   // time_t Delta_Time;
public:
    //void Hit(Player* pPlayer);

public:
    void Init();
    void I_Wanna_Go_Home();
    void Frame();
  //  void Pre_Frame();
  //  void Post_Frame();

public:
    Server_Game();
    virtual ~Server_Game();
};

