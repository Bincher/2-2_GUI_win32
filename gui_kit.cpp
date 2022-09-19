#include <windows.h> //윈도우 프로그래밍에 필요
#include <stdio.h>
#include <stdlib.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK BtnProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE _hInstance;
WNDPROC _fpOldBtnProc;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszArg, int nCmdShow)
{
	HWND hWnd;
	HWND _hWnd2;
	MSG msg;
	WNDCLASS WndClass, WndClass2;
	WndClass.style = NULL;
	WndClass.lpfnWndProc = WndProc; //이벤트 처리 함수 이름, 변경가능
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hInstance = hInstance; //프로그램 ID 기록
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); //화면 색
	WndClass.lpszMenuName = NULL;
	WndClass.lpszClassName = "Hello"; //변경가능 -> 정의 등록


	if (!RegisterClass(&WndClass)) return NULL;

	_hInstance = hInstance;


	hWnd = CreateWindow( //실제 윈도우 생성(11개의 인자)
		"Hello", //이름이 Hello인 클래스를 이용하여 윈도우 생성
		"Hello", //윈도우 타이틀
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL, NULL, hInstance, NULL
	);

	ShowWindow(hWnd, nCmdShow); //생성된 윈도우를 실제로 출력
	UpdateWindow(hWnd);

	//메시지 루프
	while (GetMessage(&msg, NULL, 0, 0)) //GetMessage()가 false 될 때까지
	{                                    // == WM_QUIT일때, Application Queue에서 갖고옴
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT mesg, WPARAM wParam, LPARAM lParam)
{
	static HWND hBtn;

	switch (mesg)
	{
	case WM_CREATE:

		hBtn = CreateWindow("BUTTON", "click", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
			0, 0, 100, 100, hWnd, (HMENU)888, _hInstance, NULL);

		_fpOldBtnProc = (WNDPROC)GetWindowLongPtr(hBtn, GWLP_WNDPROC);
	
		SetWindowLongPtr(hBtn, GWLP_WNDPROC, (LONG_PTR)BtnProc);

		break;


	case WM_MOUSEMOVE:
		HDC hdc;
		char szPos[32];
		sprintf(szPos, "%03d %03d", LOWORD(lParam), HIWORD(lParam));
		hdc = GetDC(hWnd);
		TextOut(hdc, 102, 0, szPos, strlen(szPos));
		ReleaseDC(hWnd, hdc);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		return FALSE;
	}
	return DefWindowProc(hWnd, mesg, wParam, lParam); //기본적인 윈도우 메시지 처리(default)
}
LRESULT CALLBACK BtnProc(HWND hWnd, UINT mesg, WPARAM wParam, LPARAM lParam)
{
	switch (mesg)
	{
	case WM_MOUSEMOVE:
		HDC hdc;
		HWND hParent;
		hParent = GetParent(hWnd);
		static char szPos[32];
		sprintf(szPos, "%03d %03d", LOWORD(lParam), HIWORD(lParam));
		hdc = GetDC(hParent);
		TextOut(hdc, 102, 32, szPos, strlen(szPos));
		ReleaseDC(hParent, hdc);
		break;
	}
	return CallWindowProc(_fpOldBtnProc, hWnd, mesg, wParam, lParam);
}
//==SetWindowLong()
