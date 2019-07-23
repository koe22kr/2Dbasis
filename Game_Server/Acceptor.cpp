#include "Acceptor.h"
#include "IOCP.h"
#include "Player_Mgr.h"

bool Acceptor::Init(int iPort, const char* address)
{
    
    m_Listen_Sock = socket(AF_INET, SOCK_STREAM, 0);
    SOCKADDR_IN sa;
    ZeroMemory(&sa, sizeof(sa));
    sa.sin_family = AF_INET;
    sa.sin_port = htons(iPort);
    if (address == nullptr)//주소 지정 안하면 모든 주소 다받음
        sa.sin_addr.s_addr = htonl(INADDR_ANY);
    else
        sa.sin_addr.s_addr = inet_addr(address);

    int ret = bind(m_Listen_Sock, (SOCKADDR*)&sa, sizeof(sa));
    if (ret == SOCKET_ERROR)
    {
        E_MSG("Server::bind");
        return false;
    }
    ret = listen(m_Listen_Sock, SOMAXCONN);
    if (ret == SOCKET_ERROR)
    {
        E_MSG("Server::listen");
        return false;
    }
    cout << "Server_Open" << endl;

    /*int socketType;
    int typeLen = sizeof(socketType);
    if (getsockopt(m_Listen_Sock, SOL_SOCKET, SO_SNDBUF, (char*)&socketType,
        &typeLen) == SOCKET_ERROR)
    {
        E_MSG("Server::listen");
    }
    if (getsockopt(m_Listen_Sock, SOL_SOCKET, SO_RCVBUF, (char*)&socketType,
        &typeLen) == SOCKET_ERROR)
    {
        E_MSG("Server::listen");
    }*/

    CreateThread();

    return true;
}

bool Acceptor::Thread_Runner()                                                                  ////로그인 전 서버 연결 부분
{
    int addlen = sizeof(SOCKADDR);
    while (1)
    {
        Player* puser = new Player;
        puser->Sock = accept(m_Listen_Sock, (SOCKADDR*)&puser->Client_Addr, &addlen);
        if (puser->Sock == INVALID_SOCKET)
        {
            E_MSG("Server::accept");
        }


        I_IOCP.SetSocketBind(puser->Sock, (ULONG_PTR)puser);   
        I_PLAYER_MGR.Add_Access_user(puser);
    }
    closesocket(m_Listen_Sock);
    return true;
}
Acceptor::Acceptor()
{
    WSADATA wsa;
    WSAStartup(MAKEWORD(2, 2), &wsa);
}


Acceptor::~Acceptor()
{
}
