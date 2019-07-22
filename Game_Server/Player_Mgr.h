#pragma once
#include "Player.h"
#include "Object_Pool.h"

struct OVERLAPPED2 :public Object_Pool<OVERLAPPED2>
{
    OVERLAPPED ov;
    DWORD dw_Flag;
};

class Player_Mgr :public Singleton<Player_Mgr>
{
    friend Singleton<Player_Mgr>;
    map<SOCKET*,Player*> Access_User;
    map<int, Player*> Player_map;//�÷��̾� = > �̸�, ���� ī�� ���� 


public:
    void Add_Access_user(Player* pAccess_user);
    void Del_Access_user(Player* pAccess_user);

    void Add_User(Packet user_info_packet);     //������û-> ���� ����   //DB �κ� �߰� �ؾ���
    void Del_User(Packet user_info_packet);
    bool Frame();//while (1)recv();
    bool Recv(Player  target_player);
    void Packet_Cutting(Player target_player, char* pBuffer, DWORD dwByte);
    void Update_Player(int UID,WCHAR* NAME);//�̸��ٲٱ�
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
//    map<int, User> Player;//�÷��̾� = > �̸�, ���� ī�� ����
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
