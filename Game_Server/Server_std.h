#pragma once
#include <WinSock2.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <map>
#include <vector>
#include <list>

#pragma comment (lib, "ws2_32.lib")
using namespace std;

//int code = WSAGetLastError();
void E_MSG(const char* msg_title)
{


    std::string* IpMsgBuf;    //�޸� �Ҵ����ְ� �װ��� �����ͷ� �޾Ƽ� ���� STR���
    FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, NULL, WSAGetLastError()/*code*/,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        (char*)&IpMsgBuf, 0, NULL);
    MessageBoxA(NULL, (char*)IpMsgBuf, msg_title, MB_OK);


    //���ο��� ���� �� �޸� �Ҵ� ���� delete�� �ϸ� �ȵ�
    LocalFree(IpMsgBuf);
    return;
}

template <class T> class Singleton
{
public:
    static T& GetInstance()
    {
        static T Instance;
        return Instance;
    }
};
