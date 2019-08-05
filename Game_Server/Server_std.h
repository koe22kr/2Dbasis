#pragma once
#include <random>

#include <WinSock2.h>
#include <sql.h>
#include <sqlext.h>
#include <stdio.h>
//#include <Windows.h>//
#include <string>
#include <iostream>
#include <map>
#include <vector>
#include <list>
#include <queue>
#pragma comment (lib, "ws2_32.lib")
using namespace std;

extern bool g_start_flag;
//int code = WSAGetLastError();
static void E_MSG(const char* msg_title)
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


class WINT
{
public:
    int x = 0;
    int y = 0;
    WINT() {};
    WINT(int a, int b) :x(a), y(b) {};
    WINT(const WINT& wint) :x(wint.x), y(wint.y) {};
    WINT(int& a, int&b) : x(a), y(b) {};
    ~WINT() {};
    WINT operator +(WINT& wint) { return WINT(x + wint.x, y + wint.y); };
    WINT operator +(POINT& point) { return WINT(x + point.x, y + point.y); };
    WINT& operator =(WINT& src_wint)
    {
        //x = y = x = y;
        if (this == &src_wint)
        {
            return *this;
        }
        this->x = src_wint.x;
        this->y = src_wint.y;

        return *this;
    }

};
//����ī�带 �޸� ī���.����;