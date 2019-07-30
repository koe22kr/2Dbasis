#include "Server_Obj.h"



Server_Obj::Server_Obj()
{
    InitializeCriticalSection(&m_cs);
}


Server_Obj::~Server_Obj()
{
    DeleteCriticalSection(&m_cs);
}
