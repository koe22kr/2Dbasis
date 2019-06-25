//#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include "CAServerStd.h"

void main()
{
    WSADATA wsa;
    WSAStartup(MAKEWORD(2, 2), &wsa);
    SOCKET listensock = socket(AF_INET, SOCK_STREAM, 0);  //protocol 0 ������ Ÿ�Կ� ���缭 �ڵ����� ����� tcp/udp  
    //SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); //�̰Ͱ� ����.              //datagrame udp[type]  
    SOCKADDR_IN sa;
    ZeroMemory(&sa, sizeof(sa));
    sa.sin_family=AF_INET;
    sa.sin_port = htons(10000); //�� ���̱� ������,  host to network short
    sa.sin_addr.s_addr = htonl(INADDR_ANY);
    
    int ref = bind(listensock, (SOCKADDR*)&sa, sizeof(sa));
    if(ref==SOCKET_ERROR)
    {
        E_MSG("bind");
        return;
      
    }
    ref = listen(listensock, SOMAXCONN); //somaxconn �� ���� �ִ� ��ġ ��ûŭ �������� ����.
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
        printf("\n���� ���� :D");

        char buf[256] = { 0 };
        char buf2[256] = { 0 };

        SOCKET clientsock = accept(listensock, (SOCKADDR*)&clientaddr, &addlen);
        if (clientsock == INVALID_SOCKET)
        {
            E_MSG("accept");
            break;
        }
        printf("����[%s][%d]", inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port));


        int recvbyte = recv(clientsock, buf2, strlen(buf2), 0);
        if (recvbyte == 0)
        {
            
            printf("���� ����[%s][%d]",
                inet_ntoa(clientaddr.sin_addr),
                ntohs(clientaddr.sin_port));
            E_MSG("recv");
            break;
        }
        if ( recvbyte == SOCKET_ERROR)
        {
            
            printf("���� ����[%s][%d]",
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
        //������ �ޱ� ������ ���ۿ� �غ�. ���ۿ� ������ ���� �Ȱ�, ���� ����� �־ ��ĥ �� �ִ�. �ѹ��� ���� �� �ִ� ũ�� 2����Ʈ
        if (isendmsg == SOCKET_ERROR)
        {
            E_MSG("send");
            printf("���� �ٿ�");
            break;
        }
      
    }
    closesocket(listensock);
    WSACleanup();
    return ;
}