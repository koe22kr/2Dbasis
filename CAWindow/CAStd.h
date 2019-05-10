#pragma once
#include <Windows.h>
#include <tchar.h>
#include <map>
#include <string>
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

struct CAInputMap //TInputActionMap; 이라고도 함.
{
    DWORD bWKey;
    DWORD bSKey;
    DWORD bAKey;
    DWORD bDKey;
    DWORD bLeftClick;
    DWORD bRightClick;
    DWORD bExit;
    DWORD bSpace;

};
extern CAInputMap g_ActionInput;
extern float g_fSeoundPerFrame;  //프레임당 sec
extern float g_fGameTimer;    //총시간


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
//getinstance I_~~~로 매크로화.