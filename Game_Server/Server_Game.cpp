#include "Server_Game.h"

void Server_Game::Init()
{
    
}

void Server_Game::Pre_Frame()   
{
    Recv();
    //������ ��Ŷ �з��ؼ� �����ͷ� ������? MSG �� �ְ� �����Ϳ��� MSG ��� Ȯ���ϴ� ������� �ϴ°͵� ������ ������ �ʹ�.
    //�ϴ� ��ó�� �� ������
}

void Server_Game::Post_Frame()
{
    Send();
    //ó���� ��Ŷ ������ ��Ʈ.
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

