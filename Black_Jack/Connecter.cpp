#include "Connecter.h"

bool Recv2(SOCKET sock)
{
    DWORD dwTransfer, flag = 0;
    Player tp;
    tp.m_wsaRecv_Buffer.buf = tp.m_szRecv_Buffer;
    tp.m_wsaRecv_Buffer.len = MAX_USER_BUFFER_SIZE;
    OVERLAPPED2* pOV = new OVERLAPPED2();
    pOV->dw_Flag = PACK_RECV;

    int iRet = WSARecv(sock,
        &tp.m_wsaRecv_Buffer, 1,
        &dwTransfer, &flag,
        (LPOVERLAPPED)pOV, NULL);
    if (iRet != -1)
    {
        int a = 999;
    }
    if (iRet == SOCKET_ERROR)
    {
        if (WSAGetLastError() != WSA_IO_PENDING)
        {
            int iError = WSAGetLastError();
            //E_MSG("Server::WSARecv");			
            return false;
        }
    }
    return true;
}
DWORD WINAPI RecvThread(LPVOID arg)
{
    SOCKET sock = (SOCKET)arg;
    char buffer[256] = { 0 };
    int iRecvByte = 0;
    while (1)
    {


        iRecvByte = recv(sock, &buffer[iRecvByte], PACKET_HEADER_SIZE - iRecvByte, 0);
        if (iRecvByte == 0)
        {
            //연결은 되었는데 보낸게 없다.  혹은?
            break;
        }
        if (iRecvByte == SOCKET_ERROR)
        {
            E_MSG("Recv3"); // 소켓 에러 발생 => 해당 소켓을 제거 해야 할까?
            break;
        }
        if (iRecvByte == PACKET_HEADER_SIZE)
        {
            Packet packet;
            ZeroMemory(&packet, sizeof(packet));
            memcpy(&packet.ph, buffer, PACKET_HEADER_SIZE);
            int iMsgByte = packet.ph.len - PACKET_HEADER_SIZE;
            iRecvByte = 0;
            do
            {
                int iByte = recv(sock, (char*)&packet.msg[iRecvByte], iMsgByte - iRecvByte, 0);
                if (iByte == SOCKET_ERROR)
                {
                    E_MSG("Recv4");
                    return 1;
                }
                iRecvByte += iByte;

            } while (iMsgByte > iRecvByte);
            //
            iRecvByte = 0;

           
        }
    }
    closesocket(sock);
    return 1;
}
bool Connecter::Init(int iPort, const char* address)
{
    WSADATA wsa;
    WSAStartup(MAKEWORD(2, 2),&wsa);
    SOCK = socket(AF_INET, SOCK_STREAM, 0);

    //unsigned long iMode = 0;    //0은 블록형 1은 논 블록형 소켓
    ////이걸 논블록형 으로 하면 
    //ioctlsocket(SOCK, FIONBIO, &iMode);

    SOCKADDR_IN sa;
    ZeroMemory(&sa, sizeof(sa));
    sa.sin_family = AF_INET;
    sa.sin_port = htons(iPort);
    sa.sin_addr.s_addr = inet_addr(address);//주소 지정 안하면 모든 주소 다받음

    int ref = connect(SOCK, (SOCKADDR*)&sa, sizeof(sa));
    if (ref == SOCKET_ERROR)
    {
             E_MSG("connect");
             MessageBox(g_hWnd, L"서버접속 실패", L"에러", MB_OK);

        //if (WSAGetLastError() != WSAEWOULDBLOCK)
        //{
        //    return 1;
        //}
    }
    //ref = Send_Packet(PACKET_ACCESS_RQ);
    if (ref == SOCKET_ERROR)
    {
            MessageBox(g_hWnd, L"서버접속 실패", L"에러", MB_OK);

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
    int iRecvByte = 0;
    //iRecvByte = recv(SOCK, &buf[iRecvByte], PACKET_HEADER_SIZE - iRecvByte, 0);
}

bool Connecter::Recv()
{

    //memcpy(&packet.ph, buf, PACKET_HEADER_SIZE);
   
    int iRecvByte = 0;
    while (1)
    {

        iRecvByte += recv(SOCK, &buf[iRecvByte], PACKET_HEADER_SIZE - iRecvByte, 0);
        if (iRecvByte == INVALID_SOCKET)
        {
            E_MSG("Recv_INVALID_SOCKET");
            
            break;

        }
        if (iRecvByte == SOCKET_ERROR)
        {
            E_MSG("Recv1"); // 소켓 에러 발생 => 해당 소켓을 제거 해야 할까?
            return false;
        }
        if (iRecvByte >= PACKET_HEADER_SIZE)
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
                    E_MSG("Recv2");
                    return false;
                }
                iRecvByte += iByte;

            } while (iMsgByte > iRecvByte);
            m_Packet_Pool.push_back(packet);
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
        //::Recv2(connecter->SOCK);

    }
    return 0;
}

void Connecter::CreateThread_Recv_Run()
{
  //  DWORD iThreadID_2;
  //   HANDLE hThreadRecv = CreateThread(0, 0,
  //       Recv2,
  //       (void*)this->SOCK,
  //       0,
  //       &iThreadID_2);
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
