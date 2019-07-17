
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <WinSock2.h>
#include <iostream>
#include "Sample.h"

#pragma comment(lib, "ws2_32")

Sample::Sample()
{
}


Sample::~Sample()
{
}


void main()
{
    WSADATA wd;
    WSAStartup(MAKEWORD(2, 2), &wd);
    SOCKET sock = socket(AF_INET,
        SOCK_DGRAM, 0);

    SOCKADDR_IN serverAddr;
    ZeroMemory(&serverAddr, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(9000);
    serverAddr.sin_addr.s_addr = inet_addr("192.168.0.8");

    SOCKADDR_IN peerAddr;
    int iRet = 0;
    char buf[256] = "±èÇü±â";

    SOCKADDR_IN clientAddr;
    int addlen = sizeof(clientAddr);
    iRet = sendto(sock, buf, strlen(buf), 0,
        (SOCKADDR*)&serverAddr,
        sizeof(serverAddr));
    while (1) {
        
        iRet = recvfrom(sock, buf, 256, 0,
            (SOCKADDR*)&peerAddr, &addlen);
        std::cout << buf << std::endl;
    }
    closesocket(sock);
    WSACleanup();
}