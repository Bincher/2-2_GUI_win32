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

/*
WS_BORDER 윈도우테두리
WS_CHILD 자식 윈도우로 설정
WS_POPUP 팝업 윈도우로 설정
WS_VISIBLE 윈도우를 생성과 동시에 화면에 표시
WS_OVERLAPPEDWINDOW 일반 속성 모두 포함
*/
//0, 400, 1430, 480,
LRESULT CALLBACK WndProc(HWND hWnd, UINT mesg, WPARAM wParam, LPARAM lParam)
{
	static HWND hWnd2; //static은 계속 유지해야할때 사용
	static HWND hBtn1;
	static HWND hBtn2;
	static HWND hEdt1;
	static HWND hEdt2;

	/*
	*ES_AUTOHSCROLL 자동수평스크롤
	*ES_AUTOVSCROLL 자동수직스크롤
	*ES_MULTILINE 다중라인 지원
	*ES_NUMBER 숫자만 입력 설정
	*ES_READONLY 편집 불가능 설정
	*/

	switch (mesg)
	{
	case WM_CREATE:
		hBtn1 = CreateWindow("BUTTON", "click", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
			0, 0, 100, 100, hWnd, (HMENU)888, _hInstance, NULL);
		/*
		hBtn2 = CreateWindow("BUTTON", "click", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
			100, 0, 100, 100, hWnd, (HMENU)999, _hInstance, NULL);'
		*/
		//BUTTON은 클래스이름, BS_PUSHBUTTON은 버튼 윈도우 스타일 ES_PUSHBUTTON
		hEdt1 = CreateWindow("EDIT", "HELLO", WS_VISIBLE | WS_CHILD | WS_BORDER
			| ES_AUTOHSCROLL | ES_AUTOVSCROLL | ES_MULTILINE,
			100, 0, 200, 100, hWnd, (HMENU)999, _hInstance, NULL);
		hEdt2 = CreateWindow("EDIT", "", WS_VISIBLE | WS_CHILD 
			| ES_AUTOHSCROLL | ES_AUTOVSCROLL | ES_MULTILINE,
			0, 102, 302, 100, hWnd, (HMENU)777, _hInstance, NULL);
		hWnd2 = CreateWindow(
			"WND2",
			"World",
			WS_OVERLAPPEDWINDOW | WS_VISIBLE | WS_CHILD,
			0, 400, 1430, 480,
			hWnd, NULL,
			_hInstance,
			NULL
		);
		break;

	case WM_LBUTTONDOWN:
		SetWindowText(hWnd2, "Black");
		break;

	//1.메뉴항목 선택
	//2.컨트롤 윈도우에서 부모 윈도우에 알림 코드 보낼 때(wParam) - Notification
	//BN_CLICKED BN_DBLCLK BN_KILLFOUCS(키보드 포커스를 잃음)
	//EN_CHANGED EN_SETOCUSE(키보드 포커스를 얻음)
	//3.단축키 눌렸을 때
	case WM_COMMAND:
		int wNofifyCode = HIWORD(wParam);
		HWND hWndCtrl = (HWND)lParam;
		int id = LOWORD(wParam);
		if (id == 0)
			MessageBox(hWnd, "안녕하세요", "알림", MB_OK);
		/*
		else if (id == 999)
			MessageBox(hWnd, "홍길동입니다", "알림", MB_OK);
		*/
		else if (id == 888)
		{
			char szMsg[1024];
			GetWindowText(hEdt1, szMsg, 1024);
			SetWindowText(hEdt2, szMsg);
		}
		else if (id == 999)
		{
			int code;
			code = HIWORD(wParam);
			if (code == EN_CHANGE)
			{
				char szMsg[1024];
				GetWindowText(hEdt1, szMsg, 1024);
				SetWindowText(hEdt2, szMsg);
			}
		}
		break;
	}
	
	return DefWindowProc(hWnd, mesg, wParam, lParam); //기본적인 윈도우 메시지 처리(default)
}
LRESULT CALLBACK WndProc2(HWND hWnd, UINT mesg, WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, mesg, wParam, lParam);
}