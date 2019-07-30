#pragma once
#include "Player.h"
#include <process.h>
class Connecter :public Singleton<Connecter>
{
    friend Singleton<Connecter>;
public:
    HINSTANCE m_hpInstance; //생성자필

public:
    int m_iPort=10000;
    int m_iUID = 0;
    TCHAR m_szName[20] = { 0 };
    SOCKET SOCK;
    list<Packet> m_Packet_Pool; //싱글턴 받기

    char buf[PACKET_MAX_DATA_SIZE] = { 0 };

    void Send(WORD type, char* msg = nullptr, WORD msg_len = 0);
    bool Recv();
    bool Init(int iPort, const char* address);

    

    HANDLE m_hThread;
    unsigned int m_iID;
public:
    void CreateThread_Recv_Run();
    static unsigned int WINAPI Handle_Runner(LPVOID prameter);


public:
    Connecter();
    ~Connecter();
};
#define I_CONNECTER Connecter::GetInstance()
