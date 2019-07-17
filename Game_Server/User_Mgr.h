#pragma once
#include "User.h"

class User_Mgr
{
    map<int, User> Player;//플레이어 = > 이름, 소지 카드 정보

   
public:
    void Add_User();
    void Del_User();
    void Dispatch();
    void Packet_Cutting(User target_user, char* pBuffer, DWORD dwByte);

public:

    User_Mgr();
    virtual ~User_Mgr();
};
