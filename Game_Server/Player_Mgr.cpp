#include "Player_Mgr.h"
#include "Packet_Pool.h"
void Player_Mgr::Add_User(Packet user_info_packet)
{
    //db에 있는지 확인. 후

    //현 게임 참가중 인지 확인
    //현 플레이어 map 에 있으면 그 유저 끊고 현 클라에 제접속 하라고 던지기
    
    //플레이어 map에 UID 키값으로 그 유저 포인트 값? 복사가 나을듯 이런 게임이면.
    //여기까지 성공하면 return true;

    //DB는 추가 하고 나서.

    //게임 중복참가? 유령클라 방지? 중복접속 방지
    if (Player_map.end() != Player_map.find(user_info_packet.ph.UID))
    {
        //중복 참가시.
        //Packet_Sender(int Protocol,msg?) 하나 만들어서 쓰자 msg는 쓸지 말지 고민후.
    }
    else
    {
        Player_map[user_info_packet.ph.UID] = //데이터 베이스에서 UID로 검색해서 가져온 유저 정보 복사 입력.
            
    }

    return;
}
void Player_Mgr::Del_User(Packet user_info_packet)
{
    // 소켓에러, 혹은 종료 패킷 받으면 DB에 유저 정보 갱신할 것 있으면 갱신후
    
    
    // player 맵에서 지우기
    if (Player_map.end() != Player_map.find(user_info_packet.ph.UID))//중복 삭제 방지. 없어도 될거 같기도 함.
    {
        Player_map.erase(user_info_packet.ph.UID);
    }

}
void Player_Mgr::Del_User(int uid)
{
    // 소켓에러, 혹은 종료 패킷 받으면 DB에 유저 정보 갱신할 것 있으면 갱신후


    // player 맵에서 지우기
    if (Player_map.end() != Player_map.find(uid))//중복 삭제 방지. 없어도 될거 같기도 함.
    {
        Player_map.erase(uid);
    }

}

bool Player_Mgr::Dispatch(Player* pPlayer,DWORD dwTransfer, OVERLAPPED2* ov)
{
    if (ov->dw_Flag == PACK_RECV)
    {
        delete ov;
        Packet_Cutting(pPlayer, dwTransfer);
        Recv(pPlayer);
    }

}

bool Player_Mgr::Recv(Player*  target_player)
{
    DWORD dwTransfer, flag = 0;

    target_player->m_wsaRecv_Buffer.buf = target_player->m_szRecv_Buffer;
    target_player->m_wsaRecv_Buffer.len = MAX_USER_BUFFER_SIZE;
    OVERLAPPED2* pOV = new OVERLAPPED2();
    pOV->dw_Flag = PACK_RECV;

    int iRet = WSARecv(target_player->Sock,
        &target_player->m_wsaRecv_Buffer, 1,
        &dwTransfer, &flag,
        (LPOVERLAPPED)pOV, NULL);
    if (iRet == SOCKET_ERROR)
    {
        if (WSAGetLastError() != WSA_IO_PENDING)
        {
            int iError = WSAGetLastError();
            //E_MSG("Server::WSARecv");			
            return false;
        }
    }
    return true;
}

bool Player_Mgr::Frame()
{
    while (true)
    {
        if (Recv())
        {
            break;
        }
    }
    //오류처리 + release 해야할
    
}

void Player_Mgr::Update_Player(int UID, WCHAR* NAME)
{
    auto iter = Player_map.find(UID);
    if (Player_map.end() !=  iter)
    {
        iter->second->Name = NAME;
    }
}

void Player_Mgr::Packet_Cutting(Player* target_player, DWORD dwByte)
{//find User 해서 end()가 아니라면 Player[UID] 를 target_user 로 던지.
    if (target_player->m_dwWrite_Pos + dwByte >= MAX_STREAM_SIZE)
    {
        char strTemp[] = { 0, };
        memcpy(target_player->m_szPack_Stream,
            &target_player->m_szPack_Stream[target_player->m_dwWrite_Pos],
            MAX_STREAM_SIZE - target_player->m_dwWrite_Pos);
        target_player->m_dwStart_Pos = 0;
        target_player->m_dwWrite_Pos = target_player->m_dwByte_To_Read;
    }
    memcpy(&target_player->m_szPack_Stream[target_player->m_dwWrite_Pos], target_player->m_szRecv_Buffer, dwByte);
    target_player->m_dwWrite_Pos += dwByte;
    target_player->m_dwByte_To_Read += dwByte;

    if (target_player->m_dwByte_To_Read >= PACKET_HEADER_SIZE)
    {
        Packet* pPacket =
            (Packet*)&target_player->m_szPack_Stream[target_player->m_dwStart_Pos];
        // 받은 데이터 크기(1개의 패킷보다 크면)
        if (pPacket->ph.len <= target_player->m_dwByte_To_Read)
        {
            do {

                Packet newPacket;
                ZeroMemory(&newPacket, sizeof(newPacket));
                // UID 는 허가 패킷에서 MAP 의 키값UID 던져주고 그걸로 받아서 유저 맵에.
                memcpy(&newPacket, pPacket, pPacket->ph.len);
                //newPacket을 패킷 풀? 에 투입 하고  pos들 수정해주고..

                I_Packet_Pool.Push(newPacket);
                target_player->m_dwByte_To_Read -= newPacket.ph.len;
                target_player->m_dwStart_Pos += newPacket.ph.len;
                if (target_player->m_dwByte_To_Read < PACKET_HEADER_SIZE)
                {
                    break;
                }
                pPacket = (Packet*)&target_player->m_szPack_Stream[target_player->m_dwStart_Pos];
            } while (pPacket->ph.len <= target_player->m_dwByte_To_Read);
        }
    }

}
//
//void Player_Mgr::Add_Access_user(Player* access_user)
//{
//    Access_User[&access_user->Sock] = access_user;
//}
//
//void Player_Mgr::Del_Access_user(Player* access_user)
//{
//    Access_User.erase(&access_user->Sock);
//}

Player_Mgr::Player_Mgr()
{
}


Player_Mgr::~Player_Mgr()
{
}
