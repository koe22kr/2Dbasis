#include "ODBC_Query.h"
#include "Player_Mgr.h"

#ifdef USE_OLD


void ODBC_Query::Stproc_New(TCHAR* name)
{
    _tcscpy(param2, name);
    SQLExecute(m_hStmt_New);
    SQLFetch(m_hStmt_New);
    int a = 999;
}
void ODBC_Query::Stproc_Login(TCHAR* name)
{

}

void ODBC_Query::Modify(User* user_data)
{
    TCHAR sql[MAX_PATH] = { 0 };
    wsprintf(sql, L"Update acc set user_name='%s' where UID=%d", user_data->Name, user_data->UID);

    Exec(sql);
    Update(user_data->UID);
}


void ODBC_Query::Delete(User* user_data)
{
    TCHAR sql[MAX_PATH] = { 0 };
    swprintf(sql, L"Delete from acc where UID=%d", user_data->UID);

    Exec(sql);
    Update(user_data->UID);
}

void ODBC_Query::Delete(int UID)
{
    TCHAR sql[MAX_PATH] = { 0 };
    swprintf(sql, L"Delete from acc where UID=%d", UID);

    Exec(sql);
    Update(UID);
}

void ODBC_Query::Update(int User_UID)//이름바꾸기
{
  
    TCHAR sql[MAX_PATH] = { 0, };
    wsprintf(sql, L"select user_name from acc where UID=%d", User_UID);

    Exec(sql);

      //TCHAR sql[MAX_PATH] = L"select UID from acc";
    //int Uid;
    //SQLLEN Uid_Len;
    WCHAR Name[21] = { 0 };
    SQLLEN Name_Len;
   //SQLRETURN ret = SQLBindCol(m_hStmt, 1, SQL_C_LONG, &Uid, 0, &Uid_Len);
   SQLRETURN ret = SQLBindCol(m_hStmt, 2, SQL_WCHAR, Name, sizeof(Name), &Name_Len);
    //ret = SQLPrepare(g_odbc.m_hStmt,sql, _tcslen(sql));
    
        ret = SQLFetch(m_hStmt);
        if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO)
        {
            Check();
        }
        
        I_PLAYER_MGR.Update_Player(User_UID, Name);
        //User update_user;
        //update_user.Name = Name;
        //update_user.UID = Uid;
        
        SQLCloseCursor(m_hStmt);

}
//void ODBC_Query::Update_All() 쓸모 없을듯.
//{
//    TCHAR sql[MAX_PATH] = L"select UID from acc";
//    int Uid;
//    SQLLEN Uid_Len;
//    WCHAR Name[21] = { 0 };
//    SQLLEN Name_Len;
//   SQLRETURN ret = SQLBindCol(m_hStmt, 1, SQL_C_LONG, &Uid, 0, &Uid_Len);
//   SQLRETURN ret = SQLBindCol(m_hStmt, 2, SQL_WCHAR, Name, sizeof(Name), &Name_Len);
//    //ret = SQLPrepare(g_odbc.m_hStmt,sql, _tcslen(sql));
//    if (SQLExecDirect(m_hStmt, sql, SQL_NTS) != SQL_SUCCESS)
//    {
//        Check();
//        return;
//    }
//    
//    while (1)
//    {
//        SQLRETURN ret = SQLFetch(m_hStmt);
//        if (ret == SQL_NO_DATA)
//        {
//            break;
//        }
//        else if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO)
//        {
//            Check();
//            break;
//        }
//        
//        유저 map 을 알아야 거기에 푸쉬를...
//    }
//    SQLCloseCursor(m_hStmt);
//}
#endif // USE_OLD

int ODBC_Query::New(char* newname)
{
    param1 = 0;
    _wcsset(param2, 0);
    TCHAR sql[MAX_PATH] = { 0 };
    TCHAR name[20] = { 0 };
    mbstowcs(name, newname, strlen(newname));
    SQLLEN Name_Len;
    SQLRETURN ret;
    wsprintf(sql, L"SELECT * FROM USERLIST WHERE NAME =N'%s' ", name);
    ret = SQLBindCol(m_hStmt, 1, SQL_INTEGER, &param1, 0, 0);
    if (ret != SQL_SUCCESS)
    {
        Check();
    }
    ret = SQLBindCol(m_hStmt, 2, SQL_UNICODE, param2, sizeof(param2), &Name_Len);
    if (ret != SQL_SUCCESS)
    {
        Check();
    }
    Exec(sql);
    SQLFetch(m_hStmt);
    SQLCloseCursor(m_hStmt);

    if (param1 == 0)// 없음
    {


        wsprintf(sql, L"INSERT INTO USERLIST(NAME) VALUES(N'%s')", name);


        Exec(sql);
        SQLFetch(m_hStmt);
        SQLCloseCursor(m_hStmt);


        wsprintf(sql, L"SELECT * FROM USERLIST WHERE NAME = N'%s'", name);
        Exec(sql);
        SQLFetch(m_hStmt);
        SQLCloseCursor(m_hStmt);
        return param1;
    }








    return 0;
}

User_Info ODBC_Query::Login(char* login_name)
{
    param1 = 0;
    _wcsset(param2, 0);
    TCHAR sql[MAX_PATH] = { 0 };
    TCHAR name[20] = { 0 };
    mbstowcs(name, login_name, strlen(login_name));
    SQLLEN Name_Len;
    SQLRETURN ret;
    wsprintf(sql, L"SELECT * FROM USERLIST WHERE NAME =N'%s' ", name);
    ret = SQLBindCol(m_hStmt, 1, SQL_INTEGER, &param1, 0, 0);
    if (ret != SQL_SUCCESS)
    {
        Check();
    }
    ret = SQLBindCol(m_hStmt, 2, SQL_UNICODE, param2, sizeof(param2), &Name_Len);
    if (ret != SQL_SUCCESS)
    {
        Check();
    }
    Exec(sql);
    SQLFetch(m_hStmt);
    SQLCloseCursor(m_hStmt);
    
    User_Info temp;
    wcstombs(temp.name, param2, sizeof(temp.name));
    temp.UID = param1;
    return temp;
}

bool ODBC_Query::Exec(const TCHAR* sql)
{
    SQLRETURN ret = SQLExecDirect(m_hStmt, (SQLTCHAR*)sql, SQL_NTS);
    if (ret != SQL_SUCCESS)
    {
        Check();
        return false;
    }

    /*
    SQLRETURN ret = SQLBindParameter(g_odbc.m_hStmt, 1, SQL_PARAM_INPUT, SQL_C_WCHAR, SQL_UNICODE, _tcslen(szSelectName), 0, szSelectName, 0, &namelen);

    TCHAR sql[MAX_PATH] = { 0, };
    wsprintf(sql, L"select name, price, korean from tblCigar where name= ?");*/

    return true;
}

void ODBC_Query::Check()
{//이거 부터 보기.
    SQLTCHAR szSQLState[SQL_SQLSTATE_SIZE + 1];
    SQLTCHAR errorBuffer[SQL_MAX_MESSAGE_LENGTH + 1];
    SQLINTEGER iSQLCode;
    SQLSMALLINT length;
    SQLError(this->m_hEnv, this->m_hDbc,
        this->m_hStmt,
        szSQLState,
        &iSQLCode,
        errorBuffer,
        sizeof(errorBuffer),
        &length);
    MessageBox(NULL, errorBuffer, szSQLState, MB_OK);
}
void ODBC_Query::Check2(SQLHSTMT& nowStmt)
{//이거 부터 보기.
    SQLTCHAR szSQLState[SQL_SQLSTATE_SIZE + 1];
    SQLTCHAR errorBuffer[SQL_MAX_MESSAGE_LENGTH + 1];
    SQLINTEGER iSQLCode;
    SQLSMALLINT length;
    SQLError(this->m_hEnv, this->m_hDbc,
        nowStmt,
        szSQLState,
        &iSQLCode,
        errorBuffer,
        sizeof(errorBuffer),
        &length);
    MessageBox(NULL, errorBuffer, szSQLState, MB_OK);
}
bool ODBC_Query::Connect(const TCHAR* loadDB) // FileDsn 으로 연결
{
    SQLRETURN ret;

    TCHAR Dir[MAX_PATH] = { 0, };
    GetCurrentDirectory(MAX_PATH, Dir);

    TCHAR InCon[256] = { 0, };
    _stprintf(InCon, _T("DRIVER={Microsoft Access Driver (*.mdb, *.accdb)};DBQ=%s\\%s"), Dir, loadDB);
    SQLSMALLINT cbOutLen;

    
    wsprintf(InCon, _T("FileDsn=%s"), loadDB);
    ret = SQLDriverConnect(m_hDbc, NULL, InCon, _countof(InCon), NULL, 0, &cbOutLen, SQL_DRIVER_NOPROMPT);
    if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO)
    {
        Check();
        return false;
    }
    if (SQLAllocHandle(SQL_HANDLE_STMT, m_hDbc, &m_hStmt) != SQL_SUCCESS)
    {
        Check();
        return false;
    }	
    return true;

    
}
bool ODBC_Query::Connect(const TCHAR* DB_NAME, const TCHAR* UID, const TCHAR* PW)
{
    SQLRETURN ret;
    ret = SQLConnect(m_hDbc,
        (SQLTCHAR*)DB_NAME, SQL_NTS,
        (SQLTCHAR*)UID, SQL_NTS,
        (SQLTCHAR*)PW, SQL_NTS);
    if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO)
    {
        Check();
        return false;
    }
    if (SQLAllocHandle(SQL_HANDLE_STMT, m_hDbc, &m_hStmt) != SQL_SUCCESS)
    {
        Check();
        return false;
    }
    if (SQLAllocHandle(SQL_HANDLE_STMT, m_hDbc, &m_hStmt_New) != SQL_SUCCESS)
    {
        Check();
        return false;
    }
    if (SQLAllocHandle(SQL_HANDLE_STMT, m_hDbc, &m_hStmt_Login) != SQL_SUCCESS)
    {
        Check();
        return false;
    }
  //PREPARE
//
//param1 = 0;
//ZeroMemory(param2, sizeof(param2));
//param3 = 0;
////
//SQLINTEGER LEN = SQL_NTS;
//TCHAR sql[MAX_PATH] = _T("{?=CALL Create_Account(?,?)}");
//SQLBindParameter(m_hStmt_New, 1, SQL_PARAM_OUTPUT, SQL_C_SHORT, SQL_INTEGER, 0, 0, &param1, 0, 0);
//if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO)
//{
//    Check2(m_hStmt_New);
//}
//SQLBindParameter(m_hStmt_New, 2, SQL_PARAM_INPUT, SQL_C_TCHAR, SQL_CHAR, sizeof(param2), 0, param2, 0, &namelen);
//if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO)
//{
//    Check2(m_hStmt_New);
//}
//SQLBindParameter(m_hStmt_New, 3, SQL_PARAM_OUTPUT, SQL_C_SHORT, SQL_INTEGER, 0, 0, &param3, 0, 0);
//if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO)
//{
//    Check2(m_hStmt_New);
//}
//SQLPrepare(m_hStmt_New, sql, SQL_NTS);
//if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO)
//{
//    Check2(m_hStmt_New);
//}
////
//TCHAR sql2[MAX_PATH] = _T("{?=Call Login(?,?)}");
//SQLBindParameter(m_hStmt_Login, 1, SQL_PARAM_OUTPUT, SQL_C_SHORT, SQL_INTEGER, 0, 0, &param1, 0, 0);
//if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO)
//{
//    Check2(m_hStmt_Login);
//}
//SQLBindParameter(m_hStmt_Login, 2, SQL_PARAM_INPUT, SQL_C_TCHAR, SQL_CHAR, sizeof(param2), 0, param2, 0, &namelen);
//if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO)
//{
//    Check2(m_hStmt_Login);
//}
//SQLBindParameter(m_hStmt_Login, 3, SQL_PARAM_OUTPUT, SQL_C_SHORT, SQL_INTEGER, 0, 0, &param3, 0, 0);
//if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO)
//{
//    Check2(m_hStmt_Login);
//}
//SQLPrepare(m_hStmt_Login, sql, SQL_NTS);
//if (ret != SQL_SUCCESS && ret != SQL_NEED_DATA)
//{
//    Check2(m_hStmt_Login);
//}
//
//
//wcscpy(param2, L"ASDF");
//ret =SQLExecute(m_hStmt_New);
//if (ret != SQL_SUCCESS && ret != SQL_NEED_DATA)
//{
//    Check2(m_hStmt_New);
//}
//ret =SQLFetch(m_hStmt_New);
//if (ret != SQL_SUCCESS && ret != SQL_NEED_DATA)
//{
//    Check2(m_hStmt_New);
//}
//ret = SQLGetData(m_hStmt_New, 3, SQL_INTEGER, &param3, 0, 0);
//if (ret != SQL_SUCCESS && ret != SQL_NEED_DATA)
//{
//    Check2(m_hStmt_New);
//}
////~~~~
//int a = 999;
    return true;

}

bool ODBC_Query::Init()
{
    if (SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &m_hEnv) != SQL_SUCCESS)
    {
        Check();
        return false;
    }
    if (SQLSetEnvAttr(m_hEnv, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, SQL_IS_INTEGER) != SQL_SUCCESS)
    {
        Check();
        return false;
    }
    // 연결 핸들 -> 할당 -> 해제	
    if (SQLAllocHandle(SQL_HANDLE_DBC, m_hEnv, &m_hDbc) != SQL_SUCCESS)
    {
        Check();
        return false;
    }
   // if (Connect(DB_Name));
    Connect(L"USERLIST", L"sa", L"kgca!@ 34");
    return true;
}

bool ODBC_Query::Release()
{
    SQLFreeHandle(SQL_HANDLE_STMT, m_hStmt);
    SQLDisconnect(m_hDbc);
    SQLFreeHandle(SQL_HANDLE_DBC, m_hDbc);
    SQLFreeHandle(SQL_HANDLE_ENV, m_hEnv);
    return true;

}

ODBC_Query::ODBC_Query()
{

}


ODBC_Query::~ODBC_Query()
{

}
