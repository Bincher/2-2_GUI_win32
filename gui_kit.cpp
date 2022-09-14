#include <windows.h> //윈도우 프로그래밍에 필요
#include <stdio.h>
#include <stdlib.h>
/*
#define SW1 1
#define SW2 2
#define SW3 4
#define SW4 8

main()
{
	int sw = 0;
	sw = SW1;
	sw = sw | SW2;
	sw = sw | SW3;

	if (sw & SW2)
		printf("ON");
}
*/
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK WndProc2(HWND, UINT, WPARAM, LPARAM);

HINSTANCE _hInstance;

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
	WndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH); //화면 색
	WndClass.lpszClassName = "WND2"; //변경가능 -> 정의 등록
	//클래스 등록
	if (!RegisterClass(&WndClass)) return NULL;
	if (!RegisterClass(&WndClass2)) return NULL;
	//메모리를 따로 기록(주소만)
	_hInstance = hInstance;

	//윈도우 생성
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

	//윈도우를 한번 더 생성 == 똑같은 코드를 한번 더
	_hWnd2 = CreateWindow( //실제 윈도우 생성(11개의 인자)
		"WND2", //이름이 WND2인 클래스를 이용하여 윈도우 생성
		"World", //윈도우 타이틀
		WS_OVERLAPPEDWINDOW,
		320, 0, 320, 240,
		hWnd, NULL, hInstance, NULL
	);


	ShowWindow(hWnd, nCmdShow); //생성된 윈도우를 실제로 출력
	UpdateWindow(hWnd);

	ShowWindow(_hWnd2, nCmdShow); //변경할 윈도우 타이틀
	UpdateWindow(_hWnd2); //얻어올 윈도우 타이틀

	//메시지 루프
	while (GetMessage(&msg, NULL, 0, 0)) //GetMessage()가 false 될 때까지
	{                                    // == WM_QUIT일때, Application Queue에서 갖고옴
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}

/*
WS_BORDER 윈도우테두리
WS_CHILD 자식 윈도우로 설정
WS_POPUP 팝업 윈도우로 설정
WS_VISIBLE 윈도우를 생성과 동시에 화면에 표시
WS_OVERLAPPEDWINDOW 일반 속성 모두 포함
*/

LRESULT CALLBACK WndProc(HWND hWnd, UINT mesg, WPARAM wParam, LPARAM lParam)
{
	//WndProc도 이벤트가 발생할 때 마다 호출되는 함수
	static HWND hWnd2;
	//DWORD style;
	//style = WS_OVERLAPPEDWINDOW | WS_VISIBLE;	
	//WM_RBUTTONDOWN, WM_LBUTTONUP ...
	switch (mesg)
	{
	case WM_CREATE:
		hWnd2 = CreateWindow(
			"WND2",
			"World",
			WS_OVERLAPPEDWINDOW | WS_VISIBLE | WS_CHILD,
			320, 0, 320, 240,
			hWnd, NULL,
			_hInstance,
			NULL
		);
		break;
	case WM_LBUTTONDOWN:
		SetWindowText(hWnd2, "Black");
		break;
	}
	return DefWindowProc(hWnd, mesg, wParam, lParam); //기본적인 윈도우 메시지 처리(default)
}
LRESULT CALLBACK WndProc2(HWND hWnd, UINT mesg, WPARAM wParam, LPARAM lParam)
{
	switch (mesg)
	{
	case WM_DESTROY:
		MessageBox(hWnd, "나죽어?", "", MB_OK);
		return FALSE;
	}
	return DefWindowProc(hWnd, mesg, wParam, lParam); //기본적인 윈도우 메시지 처리(default)
	//                   HWND hWnd, ...
}