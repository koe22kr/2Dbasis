#pragma once
#include "Protocol.h"

struct Access_User :public Singleton<Access_User>
{
    friend Singleton<Access_User>;
    SOCKET			Sock;
    SOCKADDR_IN		Client_Addr;
};
class Access_User_Mgr : public Singleton<Access_User_Mgr>
{
    friend Singleton<Access_User_Mgr>;
     Access_User
public:
    Access_User_Mgr();
    ~Access_User_Mgr();

private:

};

Access_User_Mgr::Access_User_Mgr()
{
}

Access_User_Mgr::~Access_User_Mgr()
{
}