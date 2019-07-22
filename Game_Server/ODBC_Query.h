#pragma once
#include <tchar.h>
#include <windows.h>
#include <sql.h>
#include <sqlext.h>

#include <vector>
#include <map>
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
    
public:
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
    void	Check();
    
    SQLRETURN GetResultInfo();
public:
    ODBC_Query();
    ~ODBC_Query();
};

#define I_ODBC ODBC_Query::GetInstance()