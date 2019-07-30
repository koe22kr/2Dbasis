#include "Connecter.h"

bool Connecter::Init(int iPort, const char* address)
{
    WSADATA wsa;
    WSAStartup(MAKEWORD(2, 2),&wsa);
    SOCK = socket(AF_INET, SOCK_STREAM, 0);

   // unsigned long iMode = 0;    //0�� ����� 1�� �� ����� ����
    //�̰� ������ ���� �ϸ� 
    //ioctlsocket(SOCK, FIONBIO, &iMode);

    SOCKADDR_IN sa;
    ZeroMemory(&sa, sizeof(sa));
    sa.sin_family = AF_INET;
    sa.sin_port = htons(iPort);
    sa.sin_addr.s_addr = inet_addr(address);//�ּ� ���� ���ϸ� ��� �ּ� �ٹ���

    int ref = connect(SOCK, (SOCKADDR*)&sa, sizeof(sa));
    if (ref == SOCKET_ERROR)
    {
             E_MSG("connect");
             MessageBox(g_hWnd, L"�������� ����", L"����", MB_OK);

        //if (WSAGetLastError() != WSAEWOULDBLOCK)
        //{
        //    return 1;
        //}
    }
    //ref = Send_Packet(PACKET_ACCESS_RQ);
    if (ref == SOCKET_ERROR)
    {
            MessageBox(g_hWnd, L"�������� ����", L"����", MB_OK);

        //if (WSAGetLastError() != WSAEWOULDBLOCK)
        //{
        //   // E_MSG("connecter_send");
        //}
    }
    return 1;
}


void Connecter::Send(WORD type, char* msg, WORD msg_len)
{
    Packet packet;
    memcpy(packet.msg, msg, msg_len);
    packet.ph.len = msg_len + PACKET_HEADER_SIZE;
    packet.ph.type = type;
    packet.ph.UID = m_iUID;
    
    int ret = send(SOCK, (char*)&packet, packet.ph.len, 0);
    if (ret == SOCKET_ERROR)
    {
        E_MSG("send");
    }

}

bool Connecter::Recv()
{

    //memcpy(&packet.ph, buf, PACKET_HEADER_SIZE);
   
    int iRecvByte = 0;
    while (1)
    {

        iRecvByte = recv(SOCK, &buf[iRecvByte], PACKET_HEADER_SIZE - iRecvByte, 0);
        if (iRecvByte == INVALID_SOCKET)
        {
            E_MSG("Recv_INVALID_SOCKET");
            return false;
        }
        if (iRecvByte == SOCKET_ERROR)
        {
            E_MSG("Recv"); // ���� ���� �߻� => �ش� ������ ���� �ؾ� �ұ�?
            return false;
        }
        if (iRecvByte == PACKET_HEADER_SIZE)
        {
            Packet packet;
            ZeroMemory(&packet, sizeof(packet));//
            memcpy(&packet.ph, buf, PACKET_HEADER_SIZE);
            int iMsgByte = packet.ph.len - PACKET_HEADER_SIZE;
            iRecvByte = 0;
            do
            {
                int iByte = recv(SOCK, (char*)&packet.msg[iRecvByte], iMsgByte - iRecvByte, 0);
                if (iByte == SOCKET_ERROR)
                {
                    E_MSG("Recv");
                    return false;
                }
                iRecvByte += iByte;

            } while (iMsgByte >= iRecvByte);
            //
            iRecvByte = 0;

        }
    }
    closesocket(SOCK);
    return 1;
}





unsigned int WINAPI Connecter::Handle_Runner(LPVOID prameter)
{
    Connecter* connecter = (Connecter*)prameter;
    //connecter->Init(10000,"192.168.0.61");
    while (true)
    {
        connecter->Recv();

    }
    return 0;
}

void Connecter::CreateThread_Recv_Run()
{
        m_hThread = (HANDLE)_beginthreadex(NULL, 0, Handle_Runner, (LPVOID)this, 0, &m_iID);
}

Connecter::Connecter()
{
    m_hThread = 0;
    m_iID = 0;

}


Connecter::~Connecter()
{
}
