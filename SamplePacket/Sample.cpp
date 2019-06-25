#include "Protocol.h"
#include <vector>
#include <list>
#include <algorithm>
using namespace std;

CRITICAL_SECTION cs;

struct User
{
    WORD User_Num;
    SOCKET sock;
    SOCKADDR_IN client_addr;
    char recv_buffer[256];
    char send_buffer[256];
    bool operator()(User* user) const
    {
        return (sock == user->sock);
    }
};
using user_list_ITOR = list<User*>::iterator;
list<User*> user_list;


template<typename T> class find_sock_anchor
{
public:
    bool operator() (T val) const
    {
        return (val->sock == anchor);
    }
    SOCKET anchor;
};

void AddUser(User* user)
{
    EnterCriticalSection(&cs);
    user_list.push_back(user);
    LeaveCriticalSection(&cs);
    printf("���� [%s][%d] = %d\n", inet_ntoa(user->client_addr.sin_addr),
        ntohs(user->client_addr.sin_port),
        user_list.size());
    
}
void Broadcast(PACKET packet)
{
    
    EnterCriticalSection(&cs);
    for (User* user :user_list)
    {
        
        int iSendByte = 0;
        do
        {
            int iPacketByte = send(user->sock, (char*)&packet, packet.ph.len - iSendByte, 0);    //��Ŷ�� .msg[iSendByte ���� ���ϴ��� Ȯ�� �ʿ���. üũ �ʿ�
            
            if (iPacketByte==SOCKET_ERROR)
            {
                closesocket(user->sock);
                continue;
            }
                iSendByte += iPacketByte;
        } while (packet.ph.len > iSendByte);
    }
    LeaveCriticalSection(&cs);
}
void Deluser(User* user)   //üũ���� �̳� 190625
{
    
    EnterCriticalSection(&cs);
    user_list_ITOR iter;
    find_sock_anchor<User*> anchor;
    anchor.anchor = user->sock;
    iter = find_if(user_list.begin(), user_list.end(), anchor);
    //iter = find_if(user_list.begin(), user_list.end(),user); //�̰� �������� ************************
    if (iter != user_list.end())
    {
       
        closesocket(user->sock);
        user_list.erase(iter);
        printf("���� [%s][%d] = %d\n", inet_ntoa(user->client_addr.sin_addr),
            ntohs(user->client_addr.sin_port),
            user_list.size());
    }

    LeaveCriticalSection(&cs);

}
DWORD WINAPI UserThread(LPVOID arg)
{
    User* user = (User*)arg;
    int iRecvByte = 0;
    while (1)
    {
     
                                     ///////////////////////////// �̺κ� �߿�! ���ú� ������ iRecvByte ��° ���� �д´�! ó������ ������ �ٽ� ������ ó������ �о����   
        iRecvByte = recv(user->sock, &user->recv_buffer[iRecvByte], PACKET_HEADER_SIZE - iRecvByte,0);
        if (iRecvByte == 0)
        {
            //������ �Ǿ��µ� ������ ����.  Ȥ��?
            break;
        }
        if (iRecvByte == SOCKET_ERROR)
        {
            E_MSG("Recv"); // ���� ���� �߻� => �ش� ������ ���� �ؾ� �ұ�?
            break;
        }
        if (iRecvByte == PACKET_HEADER_SIZE)
        {
            PACKET packet;
            ZeroMemory(&packet, sizeof(packet));
            memcpy(&packet.ph, &user->recv_buffer, PACKET_HEADER_SIZE);
            int iMsgByte = packet.ph.len - PACKET_HEADER_SIZE;
            iRecvByte = 0;
            do
            {
                int iByte = recv(user->sock, (char*)&packet.msg[iRecvByte], iMsgByte - iRecvByte, 0);
                if (iByte == SOCKET_ERROR)
                {
                    E_MSG("Recv");
                    break;
                }
                iRecvByte += iByte;

            } while (iMsgByte > iRecvByte);
            //
            iRecvByte = 0;
            //
            switch (packet.ph.type)
            {
                case PACKET_TYPE_CHAT:
                {
                    Broadcast(packet);
                }break;

            }

        }
    }
    Deluser(user);
    return 1;

}

void main()
{
    InitializeCriticalSection(&cs);
    
    WSADATA wsa;
    WSAStartup(MAKEWORD(2, 2), &wsa);
    SOCKET listensock = socket(AF_INET, SOCK_STREAM, 0);
    SOCKADDR_IN sa;
    ZeroMemory(&sa, sizeof(sa));
    sa.sin_family = AF_INET;
    sa.sin_addr.s_addr = htonl(INADDR_ANY);
    sa.sin_port = htons(10000);

    int ret = bind(listensock, (SOCKADDR*)&sa, sizeof(sa));
    if (ret == SOCKET_ERROR)
    {
        E_MSG("Bind");
        return;
    }
    ret = listen(listensock, SOMAXCONN);
    if (ret == SOCKET_ERROR)
    {
        E_MSG("Listen");
        return;
    }
    ////////
    printf("\nServer Online\n");

    int addrlen = sizeof(SOCKADDR_IN);
    while (1)
    {
        ////
        User* newuser = new User;
        ZeroMemory(newuser, sizeof(newuser));
        newuser->sock = accept(listensock, (SOCKADDR*)&newuser->client_addr, &addrlen);
        if (newuser->sock == INVALID_SOCKET)
        {
            E_MSG("Accept");
            delete newuser;
        }
        else
        {
            
            AddUser(newuser);
           
            DWORD iThreadID;
            HANDLE hThreadSend = CreateThread(0, 0, UserThread, (void*)newuser, 0, &iThreadID);
        }
        

    }
    closesocket(listensock);
    WSACleanup();

    DeleteCriticalSection(&cs);




}