#pragma once
#include "Card.h"
//#include "Deck.h"
#include "Connecter.h"
#include "CABitmapMgr.h"
#include "Chat.h"

class Black_Jack
{
public:
    Connecter* g_pConnecter;//��������

public:
    User m_User;
    map<int, Player> m_Player_list;
    CABitmapMgr m_BitmapMgr;
    Chat chat;

public:

    Black_Jack();
    ~Black_Jack();
    void Init();
    void Frame();
    void Render();
    void Release();
    void New_Account() {};
    void Login(char* buf) {};
    void Login(TCHAR* wbuf) {};

    
    //void Resetgame();
    //void Hit();
    //void Stay();
    //void Burst();
    //void Command();
    ////void Shuffle();
    //void Judgement();
    //void Ranking();


};

////�޴� ��Ŷ
//PACKET_NEW_ACCOUNT_ACK
//PACKET_JOIN_NEW_USER
//PACKET_LOGIN_ACK
//PACKET_UPDATE
//PACKET_UPDATE_END
//PACKET_USER_EXIT
//
//PACKET_SOME_BODY_READY
//PACKET_SOME_BODY_READY_CANCEL
//PACKET_ALL_PLAYER_READY
//PACKET_GAME_START
//
//
//PACKET_SOME_BODY_HIT
//PACKET_SOME_BODY_STAY
//PACKET_BURST_OR_BLACK_JACK
//PACKET_GAME_LOSE
//PACKET_GAME_WIN
//
//PACKET_ERROR_CODE
//
//
////���� ��Ŷ
//PACKET_NEW_ACCOUNT_RQ
//PACKET_LOGIN_RQ
//PACKET_USER_EXIT
//PACKET_GAME_READY
//PACKET_GAME_READY_CANCEL
//PACKET_COMMAND_HIT
//PACKET_COMMAND_STAY
//
//
////PACKET_ACCESS_RQ ������� �����.���Ͽ��� ó���ص� �����ҵ� ���� �ȵǸ� �߰��ϱ�