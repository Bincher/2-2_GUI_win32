#include <windows.h> //윈도우 프로그래밍에 필요
#include <stdio.h>
#include <stdlib.h>

#define WM_MYMOVE WM_USER + 1

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK WndProc2(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK BtnProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE _hInstance;
WNDPROC _fpOldBtnProc;

static HWND hEdt1;
static HWND hWnd1;
static HWND hWnd2;
static HWND hStc;
static HWND hBtn1;
static HWND hBtn2;
static HWND hBtn3;
static HWND hBtn4;
static HWND hEdt2;


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

	WndClass2 = WndClass;
	WndClass.lpfnWndProc = WndProc2;
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); //화면 색
	WndClass.lpszClassName = "WND2"; //변경가능 -> 정의 등록

	if (!RegisterClass(&WndClass)) return NULL;
	if (!RegisterClass(&WndClass2)) return NULL;

	_hInstance = hInstance;


	hWnd = CreateWindow( //실제 윈도우 생성(11개의 인자)
		"Hello", //이름이 Hello인 클래스를 이용하여 윈도우 생성
		"부모윈도우: 컴퓨터공학과 2학년 김성빈 20190207", //윈도우 타이틀
		WS_OVERLAPPEDWINDOW,
		0,
		0,
		500,
		300,
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
	switch (mesg)
	{
	case WM_CREATE:
		hWnd2 = CreateWindow(
			"WND2",
			"자식윈도우",
			WS_OVERLAPPEDWINDOW | WS_VISIBLE,
			0, 300, 500, 200,
			hWnd, NULL,
			_hInstance,
			NULL
		);
		hEdt1 = CreateWindow("EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER
			| ES_AUTOHSCROLL | ES_AUTOVSCROLL | ES_MULTILINE,
			0, 0, 250, 250, hWnd, NULL, _hInstance, NULL);
		hStc = CreateWindow(
			"Static",
			"",
			WS_OVERLAPPEDWINDOW | WS_VISIBLE| WS_CHILD,
			250, 0, 270, 270,
			hWnd, NULL,
			_hInstance,
			NULL
		);
		SetWindowLong(hStc, GWL_STYLE, 0);
		ShowWindow(hStc, SW_SHOW);
		break;

		
	case WM_DESTROY:
		PostQuitMessage(0);
		return FALSE;
	}
	return DefWindowProc(hWnd, mesg, wParam, lParam); //기본적인 윈도우 메시지 처리(default)
}
LRESULT CALLBACK WndProc2(HWND hWnd, UINT mesg, WPARAM wParam, LPARAM lParam)
{
	switch (mesg)
	{
	case WM_CREATE:
		hBtn1 = CreateWindow("BUTTON", "이름은", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
			0, 0, 100, 60, hWnd, (HMENU)777, _hInstance, NULL);
		hBtn2 = CreateWindow("BUTTON", "학번은", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
			100, 0, 100, 60, hWnd, (HMENU)888, _hInstance, NULL);
		hBtn3 = CreateWindow("BUTTON", "지움", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
			200, 0, 100, 60, hWnd, (HMENU)999, _hInstance, NULL);
		hBtn4 = CreateWindow("BUTTON", "", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
			300, 0, 270, 270, hWnd, (HMENU)111, _hInstance, NULL);
		hEdt2 = CreateWindow("EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER
			| ES_AUTOHSCROLL | ES_AUTOVSCROLL | ES_MULTILINE,
			0, 60, 300, 100, hWnd, (HMENU)666, _hInstance, NULL);

		_fpOldBtnProc = (WNDPROC)GetWindowLongPtr(hBtn4, GWLP_WNDPROC);
		SetWindowLongPtr(hBtn4, GWLP_WNDPROC, (LONG_PTR)BtnProc);
		break;


	case WM_DESTROY:
		PostQuitMessage(0);
		return FALSE;
		break;

	case WM_COMMAND:
		int wNofifyCode = HIWORD(wParam);
		HWND hWndCtrl = (HWND)lParam;
		int id = LOWORD(wParam);
		if (id == 777)
		{
			SetWindowText(hEdt1, "김성빈");
		}
		else if (id == 888)
		{

			SetWindowText(hEdt1, "20190207");
		}
		else if (id == 999)
		{
			SetWindowText(hEdt1, "");
		}
		else if (id == 111)
		{

		}
		else if (id == 666)
		{
			char szMsg[1024];
			GetWindowText(hEdt2, szMsg, 1024);
			SetWindowText(hEdt1, szMsg);
		}

	
	}

	return DefWindowProc(hWnd, mesg, wParam, lParam);
}

LRESULT CALLBACK BtnProc(HWND hWnd, UINT mesg, WPARAM wParam, LPARAM lParam)
{
	switch (mesg)
	{
	case WM_MOUSEMOVE:
		int x, y;
		HDC hdc;
		x = LOWORD(lParam);
		y = HIWORD(lParam);
		hdc = GetDC(hStc);
		SetPixel(hdc, x, y, RGB(0, 0, 255));
		ReleaseDC(hStc, hdc);
		break;
		//SendMessage(hWnd, 2000, wParam, lParam);
		break;
	}
	return CallWindowProc(_fpOldBtnProc, hWnd, mesg, wParam, lParam);
}
//==SetWindowLong()