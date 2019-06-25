//#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include "CAServerStd.h"
#include <conio.h>
void main()
{
    WSADATA wsa;
    WSAStartup(MAKEWORD(2, 2), &wsa);

    SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);  //protocol 0 넣으면 타입에 맞춰서 자동으로 잡아줌 tcp/udp  
    //SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); //이것과 같다.              //datagrame udp[type]  
    
    
    //*************************
    unsigned long iMode = 1;    //0은 블록형 1은 논 블록형 소켓
    //이걸 논블록형 으로 하면 
    ioctlsocket(sock, FIONBIO, &iMode);

    //************************


    SOCKADDR_IN sa;
    ZeroMemory(&sa, sizeof(sa));
    sa.sin_family=AF_INET;
    sa.sin_port = htons(10000); //숏 형이기 때문에,  host to network short
    sa.sin_addr.s_addr = inet_addr("192.168.0.8");
    
//    1 > d:\dir\2dbasis\clientsocket\sample.cpp(16) : error C4996 : 'inet_addr' : Use inet_pton() or InetPton() instead or define _WINSOCK_DEPRECATED_NO_WARNINGS to disable deprecated API warnings
    
    int ref = connect(sock, (SOCKADDR*)&sa, sizeof(sa));
    if(ref==SOCKET_ERROR)
    {
        if (WSAGetLastError() != WSAEWOULDBLOCK)
        {
            //E_MSG("connect");
            E_MSG("connect");
            return;
        }
        
    }
    char buf[256] = { 0 };
    
    while (1)
    {
        
        char buf2[256] = { 0 };


        ////
        if (_kbhit() == 1)
        {
            int iValue = _getch();
            if (strlen(buf) == 0 && iValue == '\r')
            {
                break;
            }
        }
        fgets(buf, sizeof(buf), stdin);

        //
        int bufsize = _countof(buf);
        if (buf[0] == '\n')
        {
            break;
        }
        int isendmsg = send(sock, buf, bufsize, 0);
        //윈도우 받기 보내기 버퍼에 준비. 버퍼에 적으면 샌드 된거, 버퍼 사이즈가 있어서 넘칠 수 있다. 한번에 보낼 수 있는 크기 2바이트
        if (isendmsg == SOCKET_ERROR)
        {
            E_MSG("send");
            printf("서버 다운");
            break;
        }

        int irecvmsg = recv(sock, buf2, strlen(buf2), 0);
        if (sock == 0 )
        {
            printf("정상 연결끝");
            E_MSG("recv");
            break;
        }

        if( sock == SOCKET_ERROR)
        {
            if (WSAGetLastError() != WSAEWOULDBLOCK)
            {
                printf("에러 발생");
                E_MSG("recv");
                break;
            }
            
        }
        printf("%s", buf2);


        
       
    }
    closesocket(sock);
    WSACleanup();
    return ;
}