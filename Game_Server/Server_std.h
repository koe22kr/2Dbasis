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


    std::string* IpMsgBuf;    //메모리 할당해주고 그것을 포인터로 받아서 에러 STR사용
    FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, NULL, WSAGetLastError()/*code*/,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        (char*)&IpMsgBuf, 0, NULL);
    MessageBoxA(NULL, (char*)IpMsgBuf, msg_title, MB_OK);


    //내부에서 만든 힙 메모리 할당 제거 delete로 하면 안됨
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
