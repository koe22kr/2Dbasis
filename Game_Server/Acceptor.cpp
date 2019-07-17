#include "Acceptor.h"
#include "IOCP.h"
#include "User.h"

bool Acceptor::Set(int iPort, const char* address)
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
    cout << "서버 시작!!!" << endl;

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

bool Acceptor::Thread_Runner()
{
    int addlen = sizeof(SOCKADDR);
    while (1)
    {
        User* puser = new User;
        puser->Sock = accept(m_Listen_Sock, (SOCKADDR*)&puser->Client_Addr, &addlen);
        if (puser->Sock == INVALID_SOCKET)
        {
            E_MSG("Server::accept");
        }


        I_IOCP.SetSocketBind(puser->Sock, (ULONG_PTR)puser);
        I_UserMgr.AddUser(user);
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
