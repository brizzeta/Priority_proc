#include "Priority_proc.h"

Priority_proc* Priority_proc::ptr = NULL;

Priority_proc::Priority_proc(void)
{
	ptr = this;
}

Priority_proc::~Priority_proc(void)
{
}

void Priority_proc::Cls_OnClose(HWND hwnd)
{
	EndDialog(hwnd, 0);
}

DWORD WINAPI Thread(LPVOID lp)
{
	DWORD Priority = GetPriorityClass(GetCurrentProcess());
	SetPriorityClass(GetCurrentProcess(), ABOVE_NORMAL_PRIORITY_CLASS);
	SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_ABOVE_NORMAL);
	HWND Progress = (HWND)lp;
	while (true) {
		static time_t t;
		static TCHAR str[100];
		t = time(NULL);	
		lstrcpy(str, _tctime(&t));	
		str[lstrlen(str) - 1] = '\0';
		SetWindowText(Progress, str);
		Sleep(1000);
	}
	SetPriorityClass(GetCurrentProcess(), Priority);
	return 0;
}

BOOL Priority_proc::Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam)
{
	hEdit = GetDlgItem(hwnd, IDC_EDIT1);
	hBut = GetDlgItem(hwnd, IDC_BUTTON1);
	hProgress = GetDlgItem(hwnd, IDC_PROGRESS1);
	SendMessage(hProgress, PBM_SETRANGE, 0, MAKELPARAM(0, 100)); 
	SendMessage(hProgress, PBM_SETSTEP, 0, 0); 
	SendMessage(hProgress, PBM_SETPOS, 0, 0); 
	SendMessage(hProgress, PBM_SETBARCOLOR, 0, LPARAM(RGB(0, 214, 120))); 
	CreateThread(NULL, 0, Thread, hEdit, 0, NULL);
	return TRUE;
}

void Priority_proc::Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
	float procent = 0;
	int question = 3;
	int score = 0;
	if (LOWORD(id) == IDC_BUTTON1) {
		LRESULT res = SendDlgItemMessage(hwnd, IDC_RADIO3, BM_GETCHECK, 0, 0);
		if (res == BST_CHECKED) {
			score++;
		}
		res = SendDlgItemMessage(hwnd, IDC_RADIO6, BM_GETCHECK, 0, 0);
		if (res == BST_CHECKED) {
			score++;
		}
		res = SendDlgItemMessage(hwnd, IDC_RADIO7, BM_GETCHECK, 0, 0);
		if (res == BST_CHECKED) {
			score++;
		}
		procent = (score * 100) / question;
		TCHAR str[20];
		SendMessage(hProgress, PBM_SETPOS, WPARAM(procent), 0);
	}
}

BOOL CALLBACK Priority_proc::DlgProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		HANDLE_MSG(hwnd, WM_CLOSE, ptr->Cls_OnClose);
		HANDLE_MSG(hwnd, WM_INITDIALOG, ptr->Cls_OnInitDialog);
		HANDLE_MSG(hwnd, WM_COMMAND, ptr->Cls_OnCommand);
	}
	return FALSE;
}