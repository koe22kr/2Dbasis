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

/////접속 관련//////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////
//#define PACKET_ACCESS_RQ 2001           -> 로그인 전 접속요청??
#define PACKET_ACCESS_ACK 2002          //NO DATA -> 서버 온 확인
#define PACKET_NEW_ACCOUNT_RQ 2003                 // msg 에 이름 적어서 보내면 이름 중복 확인후 UID 지급
#define PACKET_NEW_ACCOUNT_ACK 2004    //NO DATA 계정 생성 성공시 만 보내기.
#define PACKET_LOGIN_RQ 2005           //NO DATA
#define PACKET_LOGIN_ACK 2006   //1 바이트  flag 값 보내기. 1 == 성공   0 == 실패 //for 문으로 현재 접속중 유저 인포 보내야.
#define PACKET_JOIN_NEW_USER 2007      //USER_INFO           UID,NAME


///////////////////////////////////////////////////////////////////////////////////////////////////////////

/////인 게임///////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////
#define PACKET_GAME_READY 3001       //NO DATA>>>           // 해더의 UID 읽고, 데이터X
#define PACKET_SOME_BODY_READY 3002  //USER_INFO         //
#define PACKET_GAME_READY_CANCEL 3003 //NO DATA
#define PACKET_SOME_BODY_READY_CANCEL 3004 //USER_INFO
#define PACKET_ALL_PLAYER_READY 3005  //NO_DATA 
#define PACKET_GAME_START 3006        //NO_DATA
//////////////////////////////////////
#define PACKET_COMMAND_HIT 4001      //NO_DATA
#define PACKET_SOME_BODY_HIT 4003    //USER_INFO+CARD         //// 패킷 보내면
#define PACKET_BURST_OR_BLACK_JACK 4005   //  FLAG 1 == 블랙잭  0 == 버스트
#define PACKET_COMMAND_STAY 4002     //NO_DATA           //
#define PACKET_SOME_BODY_STAY 4004   //USER_INFO
#define PACKET_GAME_WIN 4005  //USER_INFO
#define PACKET_GAME_LOSE 4006  //USER_INFO

/////////////////////////////////////////////////////////////////////////////////////////////////////////
#define PACKET_UPDATE 8000  //로그인시 USER_INFO 보내기
#define PACKET_UPDATE_END 8001  //업데이트 완료시 보내기. 이거 받으면 접속

#define PACKET_ERROR_CODE 9000
enum ERROR_CODE //1바이트 안으로
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
//패킷 구조체 
struct Packet_Header //해더 사이즈는 6 .
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