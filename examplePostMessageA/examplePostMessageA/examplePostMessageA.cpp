// examplePostMessageA.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <windows.h>
#include <iostream>
HINSTANCE hInst;
DWORD DLLFunc;

__declspec(naked) BOOL WINAPI __stdcall manualPostMessageA(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
	hInst = LoadLibrary(_T("user32.dll"));
	DLLFunc = (DWORD)GetProcAddress(hInst, "PostMessageA") + 5;
	__asm
	{
		mov  edi, edi
		push ebp
			mov  ebp, esp
			jmp[DLLFunc]
	}
}

int main()
{
	HWND hWnd;
	hWnd = ::FindWindow(_T("Notepad"), NULL);
	hWnd = ::FindWindowEx(hWnd, 0, _T("Edit"), 0);
	std::cout << "ID" << hWnd;
	manualPostMessageA(hWnd, WM_KEYDOWN, (0x54), (0x00020001));

	return 0;
}

