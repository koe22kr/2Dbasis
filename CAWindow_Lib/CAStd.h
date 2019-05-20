#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <tchar.h>
#include <map>
#include <vector>
#include <string>
#include <assert.h>

#pragma comment( lib, "msimg32") //msing32.lib
#pragma comment (lib, "CAWindow_Lib.lib") //�̳��� �������̴�. ������Ʈ���� std�ҷ����� TCorelib �� �����ϴ� ������

using namespace std;

//#define Fir
#ifdef Fir
#define WINMAIN int APIENTRY  wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow){
#define WINRUN_DEFAULT Sample test_window; test_window.InitWindow(hInstance,0,0,800,600); test_window.Run();}
#define WINRUN(x,y,width,height) Sample test_window; test_window.InitWindow(hInstance,x,y,width,height); test_window.Run();}
#else

#define WINRUN_DEFAULT int APIENTRY  wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow){Sample test_window; test_window.InitWindow(hInstance,0,0,800,600); test_window.Run();}
#define WINRUN(x,y,width,height) int APIENTRY  wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow){Sample test_window; test_window.InitWindow(hInstance,x,y,width,height); test_window.Run();}
#endif 

extern HWND g_hWnd;
extern HINSTANCE g_hInstance;
//extern CAInputMap g_ActionInput;
extern float g_fSecondPerFrame;  //�����Ӵ� sec
extern float g_fGameTimer;    //�ѽð�
extern HDC g_hOffScreenDC;
extern HDC g_hScreenDC;

//struct CAInputMap //TInputActionMap; �̶�� ��.
//{
//    DWORD bWKey;
//    DWORD bSKey;
//    DWORD bAKey;
//    DWORD bDKey;
//    DWORD bLeftClick;
//    DWORD bRightClick;
//    DWORD bExit;
//    DWORD bSpace;
//
//};

//typedef basic_string<TCHAR> T_STR;
//typedef basic_string<WCHAR> W_STR;
//typedef basic_string<char> C_STR;
using T_STR = basic_string<TCHAR>;
using W_STR = basic_string<WCHAR>;
using C_STR = basic_string<char>;
        
template<class T>
class CASingleton
{
public:
    static T& GetInstance()
    {
        static T singleton;
        return singleton;
    }
};
//getinstance I_~~~�� ��ũ��ȭ.