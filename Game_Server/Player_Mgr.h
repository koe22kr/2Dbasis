#pragma once
#include "Player.h"
#include "Object_Pool.h"



class Player_Mgr :public Singleton<Player_Mgr>
{
    friend Singleton<Player_Mgr>;
public:
    map<int, Player*> Player_map;//플레이어 = > 이름, 소지 카드 정보 


public:
   // void Add_Access_user(Player* pAccess_user);
   // void Del_Access_user(Player* pAccess_user);

    bool Add_User(Packet2 packet2,TCHAR* name,int uid); //ret
    void Del_User(Packet2 user_info_packet);
    void Del_User(int uid);
    bool Frame();//while (1)recv();
    bool Recv(Player*  target_player);
    void Packet_Cutting(Player* target_player, DWORD dwByte);
    void Update_Player(int UID,WCHAR* NAME);//이름바꾸기
    bool Dispatch(Player* pPlayer,DWORD dwTransfer, OVERLAPPED2* ov);
public:
    Player_Mgr();
    virtual ~Player_Mgr();
};
#define I_PLAYER_MGR Player_Mgr::GetInstance()


//
//#pragma once
//#include "User.h"
//
//class User_Mgr
//{
//    map<int, User> Player;//플레이어 = > 이름, 소지 카드 정보
//
//
//public:
//    void Add_User();
//    void Del_User();
//    void Dispatch();
//    void Packet_Cutting(User target_user, char* pBuffer, DWORD dwByte);
//
//public:
//
//    User_Mgr();
//    virtual ~User_Mgr();
//};
