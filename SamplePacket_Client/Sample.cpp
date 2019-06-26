#include "Protocol.h"
#include <vector>
#include <list>
#include <algorithm>
using namespace std;

CRITICAL_SECTION cs;
//////////////////////////
//#define _WINSOCK_DEPRECATED_NO_WARNINGS

DWORD WINAPI RecvThread(LPVOID arg)
{
    SOCKET* sock = (SOCKET*)arg;
    char buffer[256] = { 0 };
    int iRecvByte = 0;
    while (1)
    {



        iRecvByte = recv(*sock, &buffer[iRecvByte], PACKET_HEADER_SIZE - iRecvByte, 0);
        if (iRecvByte == 0)
        {
            //연결은 되었는데 보낸게 없다.  혹은?
            break;
        }
        if (iRecvByte == SOCKET_ERROR)
        {
            E_MSG("Recv"); // 소켓 에러 발생 => 해당 소켓을 제거 해야 할까?
            break;
        }
        if (iRecvByte == PACKET_HEADER_SIZE)
        {
            PACKET packet;
            ZeroMemory(&packet, sizeof(packet));
            memcpy(&packet.ph, buffer, PACKET_HEADER_SIZE);
            int iMsgByte = packet.ph.len - PACKET_HEADER_SIZE;
            iRecvByte = 0;
            do
            {
                int iByte = recv(*sock, (char*)&packet.msg[iRecvByte], iMsgByte - iRecvByte, 0);
                if (iByte == SOCKET_ERROR)
                {
                    E_MSG("Recv");
                    return 1;
                }
                iRecvByte += iByte;

            } while (iMsgByte > iRecvByte);
            //
            iRecvByte = 0;

            switch (packet.ph.type)
            {
            case PACKET_TYPE_CHAT:
            {
                printf("%s\n", packet.msg);
            }break;
            case 1001:
            {
                char name[20] = { "김형기" };
                USER_BASE base;
                ZeroMemory(&base, sizeof(base));
                base.iIndex = 61;
                strcpy(base.szName, name);
                //PACKET_CHAR_NAME_CS_ACK
                PACKET sendpacket;
                ZeroMemory(&sendpacket, sizeof(base) + PACKET_HEADER_SIZE);
                sendpacket.ph.len = PACKET_HEADER_SIZE + sizeof(base);
                sendpacket.ph.type = 1002;
                memcpy(sendpacket.msg, &base, sendpacket.ph.len);

                do
                {
                    int iSendByte = send(*sock, (char*)&sendpacket, sendpacket.ph.len, 0);
                    if (iSendByte == SOCKET_ERROR)
                    {
                        E_MSG("send");
                        printf("서버 다운");
                        // closesocket(*sock);
                        return 1;
                    }
                    iMsgByte += iSendByte;
                } while (sendpacket.ph.len > iMsgByte);
            }
            // }

            }
        }
    }
    closesocket(*sock);
    return 1;
}
DWORD WINAPI SendThread(LPVOID arg)
{
    SOCKET* sock = (SOCKET*)arg;
    char buffer[256] = { 0 };
    while (1)
    {
        int iMsgByte = 0;
        fgets(buffer, sizeof(buffer), stdin);
        int iBuffersize = strlen(buffer);
        if (buffer[0] == '\n')
        {
            break;
        }
        
        PACKET sendpacket;
        USER_CHAT_MSG msg;
        char name[20] = "김형기";
        strcpy(msg.szName, name);
        memcpy(msg.msg, buffer,iBuffersize);
        ZeroMemory(&sendpacket, sizeof(sendpacket));
        sendpacket.ph.len = PACKET_HEADER_SIZE + iBuffersize + sizeof(msg.szName);
        sendpacket.ph.type = PACKET_TYPE_CHAT;

        memcpy(sendpacket.msg, &msg, sendpacket.ph.len);
        do
        {
            int iSendByte = send(*sock, (char*)&sendpacket, sendpacket.ph.len, 0);
            if (iSendByte == SOCKET_ERROR)
            {
                E_MSG("send");
                printf("서버 다운");
               // closesocket(*sock);
                return 1;
            }
            iMsgByte += iSendByte;
        } while (iBuffersize > iMsgByte);
    }
    closesocket(*sock);
    return 1;
    LeaveCriticalSection(&cs);
    Sleep(1);
}


void main()
{
    
    InitializeCriticalSection(&cs);
    WSADATA wsa;
    WSAStartup(MAKEWORD(2, 2), &wsa);
    SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);  //protocol 0 넣으면 타입에 맞춰서 자동으로 잡아줌 tcp/udp  
    //SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); //이것과 같다.              //datagrame udp[type]  

    //*************************
    unsigned long iMode = 0;    //0은 블록형 1은 논 블록형 소켓
    //이걸 논블록형 으로 하면 
    ioctlsocket(sock, FIONBIO, &iMode);

    //************************


    SOCKADDR_IN sa;
    ZeroMemory(&sa, sizeof(sa));
    sa.sin_family = AF_INET;
    sa.sin_port = htons(10000); //숏 형이기 때문에,  host to network short
    sa.sin_addr.s_addr = inet_addr("192.168.0.8");

    

    int ref = connect(sock, (SOCKADDR*)&sa, sizeof(sa));
    if (ref == SOCKET_ERROR)
    {
        if (WSAGetLastError() != WSAEWOULDBLOCK)
        {
            //E_MSG("connect");
            E_MSG("connect");
            return;
        }

    }
    ////스레드로 아래를 수정하면서 가자.
    DWORD iThreadID_1;
    HANDLE hThreadSend = CreateThread(0, 0,
        SendThread,
        (void*)&sock,
        0,
        &iThreadID_1);

    DWORD iThreadID_2;
    HANDLE hThreadRecv = CreateThread(0, 0,
        RecvThread,
        (void*)&sock,
        0,
        &iThreadID_2);

    //////
    WaitForSingleObject(hThreadSend, INFINITE);
    WaitForSingleObject(hThreadRecv, INFINITE);

    CloseHandle(hThreadSend);
    CloseHandle(hThreadRecv);
    WSACleanup();
   ////////

   //char buf[256] = { 0 };
   //
   //while (1)
   //{
   //
   //    char buf2[256] = { 0 };
   //
   //
   //    ////
   //    if (_kbhit() == 1)
   //    {
   //        int iValue = _getch();
   //        if (strlen(buf) == 0 && iValue == '\r')
   //        {
   //            break;
   //        }
   //    }
   //    fgets(buf, sizeof(buf), stdin);
   //
   //    //
   //    int bufsize = _countof(buf);
   //    if (buf[0] == '\n')
   //    {
   //        break;
   //    }
   //    int isendmsg = send(sock, buf, bufsize, 0);
   //    //윈도우 받기 보내기 버퍼에 준비. 버퍼에 적으면 샌드 된거, 버퍼 사이즈가 있어서 넘칠 수 있다. 한번에 보낼 수 있는 크기 2바이트
   //    if (isendmsg == SOCKET_ERROR)
   //    {
   //        E_MSG("send");
   //        printf("서버 다운");
   //        break;
   //    }
   //
   //    int irecvmsg = recv(sock, buf2, strlen(buf2), 0);
   //    if (sock == 0)
   //    {
   //        printf("정상 연결끝");
   //        E_MSG("recv");
   //        break;
   //    }
   //
   //    if (sock == SOCKET_ERROR)
   //    {
   //        if (WSAGetLastError() != WSAEWOULDBLOCK)
   //        {
   //            printf("에러 발생");
   //            E_MSG("recv");
   //            break;
   //        }
   //
   //    }
   //    printf("%s", buf2);
   //
   //
   //
   //
   //}
   //closesocket(sock);
   //WSACleanup();
   return;
}
////////////////////////////