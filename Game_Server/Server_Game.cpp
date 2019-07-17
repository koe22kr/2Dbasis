#include "Server_Game.h"

void Server_Game::Init()
{
    
}

void Server_Game::Pre_Frame()   
{
    Recv();
    //수신한 패킷 분류해서 데이터로 보내기? MSG 로 넣고 데이터에서 MSG 열어서 확인하는 방식으로 하는것도 나쁘지 않을듯 싶다.
    //일단 전처리 용 프래임
}

void Server_Game::Post_Frame()
{
    Send();
    //처리후 패킷 보내는 파트.
    //
}


Server_Game::Server_Game()
{
   /* WSAStartup(MAKEWORD(2, 2), &wsa);
    listensock = socket(AF_INET, SOCK_STREAM, 0);
    ZeroMemory(&sa_in, sizeof(sa_in));
    sa_in.sin_family = AF_INET;
    sa_in.sin_port = htons(10000);
    sa_in.sin_addr.s_addr = htonl(INADDR_ANY);
    int ret = bind(listensock, (SOCKADDR*)&sa_in, sizeof(sa_in));
    if (ret == SOCKET_ERROR)
    {
        E_MSG("Server::bind");
        return;
    }
    ret = listen(listensock, SOMAXCONN);
    if (ret == SOCKET_ERROR)
    {
        E_MSG("Server::listen");
        return;
    }
    unsigned long iMode = 1;
    ioctlsocket(listensock, FIONBIO, &iMode);*/
}


Server_Game::~Server_Game()
{
}

