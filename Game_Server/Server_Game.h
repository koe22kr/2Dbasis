#pragma once
#include "Server_std.h"
#include "IOCP.h"



class Server_Game :public Thread
{
    WSADATA wsa;
    SOCKET listensock;
    SOCKADDR_IN sa_in;
public:
    void Init();
    


    void Pre_Frame();
    void Post_Frame();

public:
    Server_Game();
    virtual ~Server_Game();
};

