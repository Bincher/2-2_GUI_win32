#include <windows.h> //윈도우 프로그래밍에 필요

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
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.lpszMenuName = NULL;
	WndClass.lpszClassName = "Hello"; //변경가능

	//클래스 등록
	if (!RegisterClass(&WndClass)) return NULL;
	//메모리를 따로 기록(주소만)

	//윈도우 생성
	hWnd = CreateWindow( //실제 윈도우 생성(11개의 인자)
		"Hello",
		"Hello",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL, NULL, hInstance, NULL
	);

	ShowWindow(hWnd, nCmdShow); //생성된 윈도우를 실제로 출력
	UpdateWindow(hWnd); //윈도우 API : 이미 만들어진 윈도우에 뭔가 조작을 하는 함수
						//             첫 번째 인자는 hWnd, 필요함수 및 SW_SHOW 등(windows.h)
	
	//메시지 루프
	while (GetMessage(&msg, NULL, 0, 0)) //GetMessage()가 false 될 때까지
	{                                    // == WM_QUIT일때, Application Queue에서 갖고옴
		TranslateMessage(&msg);
		DispatchMessage(&msg); //내부적으로 WndProc 호출
	}
	return msg.wParam;
}

//윈도우 프로시저(이벤트가 발생할 때 마다 자동으로 호출)
LRESULT CALLBACK WndProc(HWND hWnd, UINT mesg, WPARAM wParam, LPARAM lParam)
{
	switch (mesg)
	{
	case WM_DESTROY: //처리 메시지
		PostQuitMessage(0); //처리 내용 -> 프로그램 종료
	return FALSE;
	}
	return DefWindowProc(hWnd, mesg, wParam, lParam); //기본적인 윈도우 메시지 처리(default)
	//                   HWND hWnd, ...
}