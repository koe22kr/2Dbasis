#pragma once
#include <tchar.h>
//#include <windows.h>

#include "User.h"

class ODBC_Query :public Singleton<ODBC_Query>
{
    friend Singleton<ODBC_Query>;
    //HWND g_hDlg;
    //HWND g_hList;
    //HWND g_hName;
    //HWND g_hPrice;
    //HWND g_hKor;
    //TOdbcQuery  g_odbc;

   // struct ColDescription
   // {
   //     SQLUSMALLINT       icol;
   //     SQLWCHAR		   szColName[80];
   //     SQLSMALLINT        cchColNameMax;
   //     SQLSMALLINT        pcchColName;
   //     SQLSMALLINT        pfSqlType;
   //     SQLULEN            pcbColDef;
   //     SQLSMALLINT        pibScale;
   //     SQLSMALLINT        pfNullable;
   // };
    TCHAR DB_Name[MAX_PATH] = L"Account_DB.accdb.dsn";
public:
    SQLHENV		m_hEnv;
    SQLHDBC		m_hDbc;
    SQLHSTMT	m_hStmt;
    SQLHSTMT m_hStmt_New;
    SQLHSTMT m_hStmt_Login;
    int      param1;  //
    TCHAR    param2[20];//
    int      param3;//사용시 사전에 초기화
    SQLLEN namelen;

public:
    void Stproc_New(TCHAR* name);
    void Stproc_Login(TCHAR* name);
    void New(User* user_data);
    void Modify(User* user_data);
    void Delete(User* user_data);
    void Delete(int UID);
    

    void Update(int User_UID);
    //void Update_All();
    bool	Exec(const TCHAR* sql);


public:
    bool	Init();
    bool	Release();
    bool	Connect(const TCHAR* loadDB);
    bool Connect(const TCHAR* DB_NAME, const TCHAR* UID, const TCHAR* PW);
    void	Check();
    
    SQLRETURN GetResultInfo();
public:
    ODBC_Query();
    ~ODBC_Query();
};

#define I_ODBC ODBC_Query::GetInstance()