//#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include "CAServerStd.h"
#include <conio.h>
void main()
{
    WSADATA wsa;
    WSAStartup(MAKEWORD(2, 2), &wsa);

    SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);  //protocol 0 ������ Ÿ�Կ� ���缭 �ڵ����� ����� tcp/udp  
    //SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); //�̰Ͱ� ����.              //datagrame udp[type]  
    
    
    //*************************
    unsigned long iMode = 1;    //0�� ����� 1�� �� ����� ����
    //�̰� ������ ���� �ϸ� 
    ioctlsocket(sock, FIONBIO, &iMode);

    //************************


    SOCKADDR_IN sa;
    ZeroMemory(&sa, sizeof(sa));
    sa.sin_family=AF_INET;
    sa.sin_port = htons(10000); //�� ���̱� ������,  host to network short
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
        //������ �ޱ� ������ ���ۿ� �غ�. ���ۿ� ������ ���� �Ȱ�, ���� ����� �־ ��ĥ �� �ִ�. �ѹ��� ���� �� �ִ� ũ�� 2����Ʈ
        if (isendmsg == SOCKET_ERROR)
        {
            E_MSG("send");
            printf("���� �ٿ�");
            break;
        }

        int irecvmsg = recv(sock, buf2, strlen(buf2), 0);
        if (sock == 0 )
        {
            printf("���� ���᳡");
            E_MSG("recv");
            break;
        }

        if( sock == SOCKET_ERROR)
        {
            if (WSAGetLastError() != WSAEWOULDBLOCK)
            {
                printf("���� �߻�");
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