#include <windows.h> //윈도우 프로그래밍에 필요
#include <stdio.h>
#include <stdlib.h>
//WndProc : 메시지 처리 코딩
//WinMain : 윈도우 생성 코딩
//HINSTANCE : handle to an Instance (Program)

/*
typedef struct
{
	HWND hwnd; //윈도우 구분 아이디(Handle to a Window)
	UINT message; //이벤트 구분 아이디(unsigned int)
	WPARAM wParam; //상황정보
	LPARAM lParam;
	DWORD time; //이벤트 발생 시점 기록
	POINT pt; //마우스 위치 기록
}MSG;
*/

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
//리턴타입 함수호출방식지정 함수이름(윈도우 핸들, 이벤트 아이디, 부가정보1, 부가정보2)
//         (PASCAL, C)
//		   == _stdcall
//WPARAM, LPARAM(부가정보)는 4바이트
LRESULT CALLBACK WndProc2(HWND, UINT, WPARAM, LPARAM);
HWND _hWnd2; //설명 편하게 하려고 전역변수 사용

//int 파스칼호출방식지정 함수(방금 실행된 프로그램 ID, 이전에 실행된 프로그램 ID, 실행 시 넘겨지는 문자열, 윈도우 화면 출력 여부 결정하는 상수 값 넘어옴) 
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszArg, int nCmdShow)
{
	//윈도우 클래스 정의 -> 윈도우 클래스 등록 -> 윈도우 생성 -> 메시지 루프
	//속성 모음(값 설정) -> 설정을 운영체제에 알림 -> 등록 값을 이용해 윈도우 생성 -> 메시지 처리 반복
	
	//클래스 정의 
	HWND hWnd;
	MSG msg;
	WNDCLASS WndClass;
	WndClass.style = NULL;
	WndClass.lpfnWndProc = WndProc; //이벤트 처리 함수 이름, 변경가능
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hInstance = hInstance; //프로그램 ID 기록
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH); //화면 색
	WndClass.lpszMenuName = NULL;
	WndClass.lpszClassName = "Hello"; //변경가능 -> 정의 등록

	WndClass.lpfnWndProc = WndProc2;
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); //화면 색
	WndClass.lpszClassName = "WND2"; //변경가능 -> 정의 등록
	//클래스 등록
	if (!RegisterClass(&WndClass)) return NULL;
	//메모리를 따로 기록(주소만)

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
		"Hello", //윈도우 타이틀
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL, NULL, hInstance, NULL
	);

	//윈도우 타이틀 관련 함수
	ShowWindow(hWnd, nCmdShow); //생성된 윈도우를 실제로 출력
	UpdateWindow(hWnd); //윈도우 API : 이미 만들어진 윈도우에 뭔가 조작을 하는 함수
						//             첫 번째 인자는 hWnd, 필요함수 및 SW_SHOW 등(windows.h)
	
	ShowWindow(_hWnd2, nCmdShow); //변경할 윈도우 타이틀
	UpdateWindow(_hWnd2); //얻어올 윈도우 타이틀

	//메시지 루프
	while (GetMessage(&msg, NULL, 0, 0)) //GetMessage()가 false 될 때까지
	{                                    // == WM_QUIT일때, Application Queue에서 갖고옴
		TranslateMessage(&msg);
		DispatchMessage(&msg); //내부적으로 WndProc 호출
		//TranslateMessage : 단축키(ex.복붙) 처리
		//DispatchMessage : 이벤트가 발생한 윈도우의 윈도우 프로시저 호출
	}
	return msg.wParam;
	


	//메시지박스 윈도우 생성 및 출력
	//MessageBox(HWND hWnd, LPCSTR szMsg, LPCSTR szTitle, UINT type);
	//                     (출력할 메시지)(대화상자 윈도우 타이틀)
}

//윈도우 프로시저(이벤트가 발생할 때 마다 자동으로 호출)
//hwnd가 호출 -> WndProc 실행(WndClass.lpfnWndProc = WndProc;)
LRESULT CALLBACK WndProc(HWND hWnd, UINT mesg, WPARAM wParam, LPARAM lParam)
{
	//WM_RBUTTONDOWN, WM_LBUTTONUP ...
	switch (mesg)
	{
	case WM_LBUTTONDOWN: //처리 메시지=>case문만 변경
		//MessageBox(hWnd, "안녕하세요", "인사", MB_OK); //처리 내용 -> 프로그램 종료
		SetWindowText(_hWnd2, "Black"); 
		break;
	/*
	case WM_MOUSEMOVE: //마우스 움직임 이벤트
		//윈도우 화면에 글자 출력하기
		int x, y;
		char szPos[80];
		HDC hdc;
		x = HIWORD(lParam); //마우스 좌표
		y = LOWORD(lParam); //MSDN활용
		sprintf(szPos, "%03d %03d", x, y);
		hdc = GetDC(hWnd);
		TextOut(hdc, x, y, "hello", strlen(szPos));
		ReleaseDC(hWnd, hdc);
		
		//HDC GetDC(HWND, hWnd);
		//ReleaseDC(HWND hWnd, HDC hdc);
		
		break;
		*/
	case WM_DESTROY:
		PostQuitMessage(0);
		return FALSE;

	return FALSE;
	}

	return DefWindowProc(hWnd, mesg, wParam, lParam); //기본적인 윈도우 메시지 처리(default)
	//                   HWND hWnd, ...
}
LRESULT CALLBACK WndProc2(HWND hWnd, UINT mesg, WPARAM wParam, LPARAM lParam)
{
	//WM_RBUTTONDOWN, WM_LBUTTONUP ...
	switch (mesg)
	{
	case WM_LBUTTONDOWN: //처리 메시지=>case문만 변경
		MessageBox(hWnd, "안녕하세요", "인사", MB_OK); //처리 내용 -> 프로그램 종료
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return FALSE;
	}
	return DefWindowProc(hWnd, mesg, wParam, lParam); //기본적인 윈도우 메시지 처리(default)
	//                   HWND hWnd, ...
}