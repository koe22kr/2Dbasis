#pragma once
#include "Server_std.h"


#define PACKET_MAX_DATA_SIZE 2048
#define PACKET_HEADER_SIZE 4
#define MAX_USER_BUFFER_SIZE PACKET_MAX_DATA_SIZE + PACKET_HEADER_SIZE
#define MAX_STREAM_SIZE (MAX_USER_BUFFER_SIZE) * 10

#define PACK_RECV 101
#define PACK_SEND 102
#define PACK_END 103
#define PACK_ERROR 104

/////���� ����//////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////
//#define PACKET_ACCESS_RQ 2001           -> �α��� �� ���ӿ�û??
#define PACKET_ACCESS_ACK 2002                    // ä�ü��� ��Ʈ ��ȣ ��������� ������ ���� int ���� UID�� ����Ͽ� �����ֱ�.    -> ���� �� Ȯ��

#define PACKET_NEW_ACCOUNT_RQ 2003                 // msg �� �̸� ��� ������ �̸� �ߺ� Ȯ���� UID ����
#define PACKET_NEW_ACCOUNT_ACK 2004

#define PACKET_LOGIN_RQ 2005
#define PACKET_LOGIN_ACK 2006
#define PACKET_JOIN_NEW_USER 2007
///////////////////////////////////////////////////////////////////////////////////////////////////////////

/////�� ����///////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////
#define PACKET_GAME_READY 3001       //>>>           // �ش��� UID �а�, ������X
#define PACKET_SOME_BODY_READY 3002                     //

#define PACKET_GAME_READY_CANCEL 3003
#define PACKET_SOME_BODY_READY_CANCEL 3004

#define PACKET_ALL_PLAYER_READY 3005
#define PACKET_GAME_START 3006             //<<<<<           // ������ X
//////////////////////////////////////
#define PACKET_COMMAND_HIT 4001   
#define PACKET_SOME_BODY_HIT 4003                      //// ��Ŷ ������   
#define PACKET_COMMAND_STAY 4002                //
#define PACKET_SOME_BODY_STAY 4004
/////////////////////////////////////////////////////////////////////////////////////////////////////////
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
struct Packet //��Ŷ ������� 2046 + 6 .
{
    Packet_Header ph;
    char msg[2046];
};

struct Update
{
    Card hit_card

};



struct Card_List
{
    WORD card_count;
    Card card[256];
};












////////////////////
#pragma pack(pop)