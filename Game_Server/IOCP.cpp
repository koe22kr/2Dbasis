#include "IOCP.h"
#include "User.h"
DWORD WINAPI Worker_Thread(LPVOID param)
{

    IOCP* pIOCP = (IOCP*)param;
    HANDLE hIOCP = pIOCP->m_hIOCP;
    
    BOOL bReturn;
    DWORD dwTransfer;
    ULONG_PTR uKeyValue;
    OVERLAPPED* ov;

    while (1)
    {
        bReturn = ::GetQueuedCompletionStatus(hIOCP,
            &dwTransfer,
            &uKeyValue,
            (LPOVERLAPPED*)&ov, INFINITE);


        User* pUser = (User*)uKeyValue;
        ov = &pUser->m_ovRecv_OV;
        //if (ov != nullptr && pUser->i_Flag == PACK_END)
        //{
        //    I_UserMgr.DelUser(pUser);
        //    continue;
        //}
        if (bReturn == TRUE && dwTransfer != 0)
        {
            if (pUser->Dispatch(dwTransfer, ov) == false)  // 분배 부분만 수정하기.
            {
                pUser->i_Flag = PACK_END;
                PostQueuedCompletionStatus(hIOCP, 0, uKeyValue, (LPOVERLAPPED)ov);
            }
        }
        else
        {
            pUser->i_Flag = PACK_END;
            PostQueuedCompletionStatus(hIOCP, 0, uKeyValue, (LPOVERLAPPED)ov);
        }
       
    }
    return 1;
}

void IOCP::SetSocketBind(SOCKET sock, ULONG_PTR key)
{
    ::CreateIoCompletionPort((HANDLE)sock,
        m_hIOCP,
        key,
        0);
}

bool IOCP::Init()
{
    return true;
}
bool IOCP::Run()
{
    return true;
}

IOCP::IOCP()
{
}


IOCP::~IOCP()
{
}
