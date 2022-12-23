#pragma once
#include <windows.h>
#include <windowsX.h>
#include <ctime>
#include <tchar.h>
#include <commctrl.h>
#include "resource.h"

class Priority_proc
{
public:
	Priority_proc(void);
public:
	~Priority_proc(void);
	static BOOL CALLBACK DlgProc(HWND hWnd, UINT mes, WPARAM wp, LPARAM lp);
	static Priority_proc* ptr;
	HWND hEdit, hBut, hProgress;
	void Cls_OnClose(HWND hwnd);
	BOOL Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam);
	void Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify);
};