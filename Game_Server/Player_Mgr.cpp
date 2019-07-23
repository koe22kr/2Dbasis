#include "Player_Mgr.h"
#include "Packet_Pool.h"
void Player_Mgr::Add_User(Packet user_info_packet)
{
    //db�� �ִ��� Ȯ��. ��

    //�� ���� ������ ���� Ȯ��
    //�� �÷��̾� map �� ������ �� ���� ���� �� Ŭ�� ������ �϶�� ������
    
    //�÷��̾� map�� UID Ű������ �� ���� ����Ʈ ��? ���簡 ������ �̷� �����̸�.
    //������� �����ϸ� return true;

    //DB�� �߰� �ϰ� ����.

    //���� �ߺ�����? ����Ŭ�� ����? �ߺ����� ����
    if (Player_map.end() != Player_map.find(user_info_packet.ph.UID))
    {
        //�ߺ� ������.
        //Packet_Sender(int Protocol,msg?) �ϳ� ���� ���� msg�� ���� ���� �����.
    }
    else
    {
        Player_map[user_info_packet.ph.UID] = //������ ���̽����� UID�� �˻��ؼ� ������ ���� ���� ���� �Է�.
            
    }

    return;
}
void Player_Mgr::Del_User(Packet user_info_packet)
{
    // ���Ͽ���, Ȥ�� ���� ��Ŷ ������ DB�� ���� ���� ������ �� ������ ������
    
    
    // player �ʿ��� �����
    if (Player_map.end() != Player_map.find(user_info_packet.ph.UID))//�ߺ� ���� ����. ��� �ɰ� ���⵵ ��.
    {
        Player_map.erase(user_info_packet.ph.UID);
    }

}
void Player_Mgr::Del_User(int uid)
{
    // ���Ͽ���, Ȥ�� ���� ��Ŷ ������ DB�� ���� ���� ������ �� ������ ������


    // player �ʿ��� �����
    if (Player_map.end() != Player_map.find(uid))//�ߺ� ���� ����. ��� �ɰ� ���⵵ ��.
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
    //����ó�� + release �ؾ���
    
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
{//find User �ؼ� end()�� �ƴ϶�� Player[UID] �� target_user �� ����.
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
        // ���� ������ ũ��(1���� ��Ŷ���� ũ��)
        if (pPacket->ph.len <= target_player->m_dwByte_To_Read)
        {
            do {

                Packet newPacket;
                ZeroMemory(&newPacket, sizeof(newPacket));
                // UID �� �㰡 ��Ŷ���� MAP �� Ű��UID �����ְ� �װɷ� �޾Ƽ� ���� �ʿ�.
                memcpy(&newPacket, pPacket, pPacket->ph.len);
                //newPacket�� ��Ŷ Ǯ? �� ���� �ϰ�  pos�� �������ְ�..

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
