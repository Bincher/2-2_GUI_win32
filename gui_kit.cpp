#include <Windows.h>
using namespace std;
/*
HWND hWnd = CreateWindow(...);

ShowWindow(Hwnd, int);
MoveWindow(Hwnd, int, int, int, int);
WndProc(HWND, UINT, WPARAM, LPARAM);
SendMessage(HWND, WPARAM, LPARAM);

LRESULT WndProc(HWND, hWnd, UINT msg, WPARAM wParam, LPARAM, lParam)
{
	static HWND hBtn;
	switch (msg)
	{
	case WM_CREATE:
		hBtn = CreateWindow("button", "click",
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			0, 0, 100, 100,
			hWnd, 
			GetWindowLong(hWnd, GWL_HINSTANCE), (MENU)999, 0);
		break;

	case WM_MOUSEMOVE:
		HDC hdc;
		char szPos;
		sprintf(szPos, "%03d %03d", LOWORD(lParam), HIWORD(lParam));
		hdc = GetDC(hWnd);
		TextOut(hdc, 0, 0, szPos);
		ReleaseDC(hWnd, hdc);
		break;
	}
}
*/

/*

class CCmdTarget; // WM_COMMAND 처리

class CWnd : public CCmdTarget
{
public:
	CWnd();
	~CWnd();

	//윈도우  핸들
	HWND m_hWnd;

	// 함수
	void ShowWindow(int);
	void MoveWindow(int, int, int, int, BOOL);
	LRESULT WndProc(UINT, WPARAM, LPARAM);

	// 이벤트 핸들러
	// 또 다른 종류의 함수
	void onCreate(...); // WM_CREATE
	void OnMouseMove(...); // WM_MOUSEMOVE
	void OnLButtonDown(...); // WM_LBUTTONDOWN
};
*/