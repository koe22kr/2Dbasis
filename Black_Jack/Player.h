#pragma once
#include "User.h"
#include "CABitmapMgr.h"
class Player :public User, public Singleton<Player>
{
    friend class Singleton<Player>;
public:
    //map<int, Player> Player_map;
    const TCHAR* Card_Bitmap_File_Name = L"card.bmp";
    CABitmap* Bitmap;
    map<int, wstring> m_Key_Map;  //int = 1~52; 패킷 num-> key;
    map<wstring, RECT> m_Rect_Map;//key ->rect;
    bool m_bBe_Ready;
    bool m_bTurn_End_Flag;
    
    int m_My_Num=0; //플레이어 자신 = 0번 이후 보내지는 순서..
    vector<CABitmapObject> Card_obj_list;
    CABitmapMgr Card_Bit_Mgr;
    POINT m_Default_Render_Pos[2] = { {400,400} , {0,0} }; //임시로.. 5개 배열화 할예정
    int m_iScore;
    int m_iAce_Counter;
    vector<Card> Card_List;
public:
    bool Take_Card(Card hit_card,bool my=false, POINT pos= { 300,500 });//get_score도 내부에서 함
    void  Set_Score();
    void Reset_Score();
    void Rect_Map_Init();
    //void Burst();
    //void Black_Jack();
    bool Render();
    void Set();
public:

   /* DWORD			m_dwStart_Pos;
    DWORD			m_dwWrite_Pos;
    DWORD			m_dwByte_To_Read;*/

    //OVERLAPPED m_ovRecv_OV;
    //int        i_Flag;
    //OVERLAPPED m_ovDummy_OV;

    SOCKET			Sock;
    SOCKADDR_IN		Client_Addr;

    WSABUF			m_wsaRecv_Buffer;
    WSABUF			m_wsaSend_Buffer;

    int				m_iRecv_Byte;
    char			m_szRecv_Buffer[MAX_USER_BUFFER_SIZE];
    char			m_szPack_Stream[MAX_STREAM_SIZE];
public:
    Player();
    virtual ~Player();
};

#define I_PLAYER Player::GetInstance()


//