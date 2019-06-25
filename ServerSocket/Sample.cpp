//#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include "CAServerStd.h"

void main()
{
    WSADATA wsa;
    WSAStartup(MAKEWORD(2, 2), &wsa);
    SOCKET listensock = socket(AF_INET, SOCK_STREAM, 0);  //protocol 0 넣으면 타입에 맞춰서 자동으로 잡아줌 tcp/udp  
    //SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); //이것과 같다.              //datagrame udp[type]  
    SOCKADDR_IN sa;
    ZeroMemory(&sa, sizeof(sa));
    sa.sin_family=AF_INET;
    sa.sin_port = htons(10000); //숏 형이기 때문에,  host to network short
    sa.sin_addr.s_addr = htonl(INADDR_ANY);
    
    int ref = bind(listensock, (SOCKADDR*)&sa, sizeof(sa));
    if(ref==SOCKET_ERROR)
    {
        E_MSG("bind");
        return;
      
    }
    ref = listen(listensock, SOMAXCONN); //somaxconn 는 리슨 최대 수치 엄청큼 갯수제한 가능.
    if (ref == SOCKET_ERROR)
    {
        E_MSG("listen");
        return;
    }


    SOCKADDR_IN clientaddr;
    int addlen = sizeof(SOCKADDR_IN);
    SOCKET clientsock;
    int iCount = 0;
    while (1)
    {
        printf("\n서버 시작 :D");

        char buf[256] = { 0 };
        char buf2[256] = { 0 };

        SOCKET clientsock = accept(listensock, (SOCKADDR*)&clientaddr, &addlen);
        if (clientsock == INVALID_SOCKET)
        {
            E_MSG("accept");
            break;
        }
        printf("접속[%s][%d]", inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port));


        int recvbyte = recv(clientsock, buf2, strlen(buf2), 0);
        if (recvbyte == 0)
        {
            
            printf("정상 종료[%s][%d]",
                inet_ntoa(clientaddr.sin_addr),
                ntohs(clientaddr.sin_port));
            E_MSG("recv");
            break;
        }
        if ( recvbyte == SOCKET_ERROR)
        {
            
            printf("오류 종료[%s][%d]",
                inet_ntoa(clientaddr.sin_addr),
                ntohs(clientaddr.sin_port));
            E_MSG("recv");
            break;

        }
        ///////////////////////////////////////////////////////////////////////
        printf("%s", buf2);


       
        /////
        int bufsize = _countof(buf);
        if (buf[0] == '\n')
        {
            break;
        }

        int isendmsg=send(listensock,buf, bufsize, 0);
        //윈도우 받기 보내기 버퍼에 준비. 버퍼에 적으면 샌드 된거, 버퍼 사이즈가 있어서 넘칠 수 있다. 한번에 보낼 수 있는 크기 2바이트
        if (isendmsg == SOCKET_ERROR)
        {
            E_MSG("send");
            printf("서버 다운");
            break;
        }
      
    }
    closesocket(listensock);
    WSACleanup();
    return ;
}