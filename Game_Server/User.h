#include "Protocol.h"
#pragma once

class User
{
public:
    bool			bCan_Chatting;
    bool			bBe_Connected;
    
    DWORD			m_dwStart_Pos;
    DWORD			m_dwWrite_Pos;
    DWORD			m_dwByte_To_Read;

    OVERLAPPED m_ovRecv_OV;
    int        i_Flag;
    OVERLAPPED m_ovDummy_OV;

    string	    	Name;
    SOCKET			Sock;
    SOCKADDR_IN		Client_Addr;

    int				m_iRecvByte;
    char			m_szRecvBuffer[MAX_USER_BUFFER_SIZE];
    char			m_szPackStream[MAX_STREAM_SIZE];
public:
    User();
    virtual ~User();
};

