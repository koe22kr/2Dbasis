#pragma once
#include "Server_std.h"


#define PACKET_MAX_DATA_SIZE 2046
#define PACKET_HEADER_SIZE 6
#define MAX_USER_BUFFER_SIZE PACKET_MAX_DATA_SIZE + PACKET_HEADER_SIZE
#define MAX_STREAM_SIZE (MAX_USER_BUFFER_SIZE) * 10

#define MAX_NAME_SIZE 10

#define PACK_RECV 101
#define PACK_SEND 102
#define PACK_END 103
#define PACK_ERROR 104

/////���� ����//////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////
//#define PACKET_ACCESS_RQ 2001           -> �α��� �� ���ӿ�û??
#define PACKET_ACCESS_ACK 2002          //NO DATA -> ���� �� Ȯ��
#define PACKET_NEW_ACCOUNT_RQ 2003                 // msg �� �̸� ��� ������ �̸� �ߺ� Ȯ���� UID ����
#define PACKET_NEW_ACCOUNT_ACK 2004    //NO DATA ���� ���� ������ �� ������.
#define PACKET_LOGIN_RQ 2005           //NO DATA
#define PACKET_LOGIN_ACK 2006   //1 ����Ʈ  flag �� ������. 1 == ����   0 == ���� //for ������ ���� ������ ���� ���� ������.
#define PACKET_JOIN_NEW_USER 2007      //USER_INFO           UID,NAME


///////////////////////////////////////////////////////////////////////////////////////////////////////////

/////�� ����///////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////
#define PACKET_GAME_READY 3001       //NO DATA>>>           // �ش��� UID �а�, ������X
#define PACKET_SOME_BODY_READY 3002  //USER_INFO         //
#define PACKET_GAME_READY_CANCEL 3003 //NO DATA
#define PACKET_SOME_BODY_READY_CANCEL 3004 //USER_INFO
#define PACKET_ALL_PLAYER_READY 3005  //NO_DATA 
#define PACKET_GAME_START 3006        //NO_DATA
//////////////////////////////////////
#define PACKET_COMMAND_HIT 4001      //NO_DATA
#define PACKET_SOME_BODY_HIT 4003    //USER_INFO+CARD         //// ��Ŷ ������
#define PACKET_BURST_OR_BLACK_JACK 4005   //  FLAG 1 == ����  0 == ����Ʈ
#define PACKET_COMMAND_STAY 4002     //NO_DATA           //
#define PACKET_SOME_BODY_STAY 4004   //USER_INFO
#define PACKET_GAME_WIN 4005  //USER_INFO
#define PACKET_GAME_LOSE 4006  //USER_INFO

/////////////////////////////////////////////////////////////////////////////////////////////////////////
#define PACKET_UPDATE 8000  //�α��ν� USER_INFO ������
#define PACKET_UPDATE_END 8001  //������Ʈ �Ϸ�� ������. �̰� ������ ����

#define PACKET_ERROR_CODE 9000
enum ERROR_CODE //1����Ʈ ������
{
    HIT_FAIL=101
};



#define PACKET_EXIT 9999                        //

#define PACKET_CHAT_MSG 1001
#define PACKET_CHAT_JOIN_RQ 1002
#define PACKET_CHAT_JOIN_ACK 1003
#define PACKET_CHAT_EXIT 9999

#pragma pack(push,1)
////////////////////
//��Ŷ ����ü 
struct Packet_Header //�ش� ������� 6 .
{
    WORD len;
    WORD type;
    WORD UID;
};

struct Packet // PH= 6   + 10, 12, 15
{
    Packet_Header ph;
    char msg[PACKET_MAX_DATA_SIZE];
};

struct sPacket
{
    SOCKET user_sock;
    Packet real_packet;
};
//
//struct bPacket
//{
//    Packet real_packet;
//};
#define MSG_USER_NAME_SIZE 10
struct User_Name  //10
{
    char name[MAX_NAME_SIZE] = { 0 };
};
#define MSG_USER_INFO_SIZE 12
struct  User_Info  //12
{
    char name[MAX_NAME_SIZE];
    WORD UID;
};


struct Card_info
{
    byte m_Card_type;
    byte m_Card_num;
    byte m_Card_Score;
};

#define MSG_USER_CARD_SIZE 15
struct User_Card_Info  //15
{
    WORD UID;        //2
    char name[MAX_NAME_SIZE];  //10
    Card_info hit_card;             //3
};










//
//
//struct Card_List
//{
//    WORD card_count;
//    Card card[256];
//};
//
//










////////////////////
#pragma pack(pop)