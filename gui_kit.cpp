#include <windows.h> //������ ���α׷��ֿ� �ʿ�
#include <stdio.h>
#include <stdlib.h>

#define WM_MYMOVE WM_USER + 1

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK WndProc2(HWND, UINT, WPARAM, LPARAM);
HINSTANCE _hInstance;
WNDPROC _fpOldBtnProc;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszArg, int nCmdShow)
{
	HWND hWnd;
	HWND _hWnd2;
	MSG msg;
	WNDCLASS WndClass, WndClass2;
	WndClass.style = NULL;
	WndClass.lpfnWndProc = WndProc; //�̺�Ʈ ó�� �Լ� �̸�, ���氡��
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hInstance = hInstance; //���α׷� ID ���
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); //ȭ�� ��
	WndClass.lpszMenuName = NULL;
	WndClass.lpszClassName = "Hello"; //���氡�� -> ���� ���

	WndClass2 = WndClass;
	WndClass.lpfnWndProc = WndProc2;
	WndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH); //ȭ�� ��
	WndClass.lpszClassName = "WND2"; //���氡�� -> ���� ���

	if (!RegisterClass(&WndClass)) return NULL;
	if (!RegisterClass(&WndClass2)) return NULL;

	_hInstance = hInstance;


	hWnd = CreateWindow( //���� ������ ����(11���� ����)
		"Hello", //�̸��� Hello�� Ŭ������ �̿��Ͽ� ������ ����
		"Hello", //������ Ÿ��Ʋ
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL, NULL, hInstance, NULL
	);
	_hWnd2 = CreateWindow( //���� ������ ����(11���� ����)
		"WND2", //�̸��� WND2�� Ŭ������ �̿��Ͽ� ������ ����
		"World", //������ Ÿ��Ʋ
		WS_OVERLAPPEDWINDOW,
		320, 0, 320, 240,
		hWnd, NULL, hInstance, NULL
	);
	
	ShowWindow(hWnd, nCmdShow); //������ �����츦 ������ ���
	UpdateWindow(hWnd);



	//�޽��� ����
	while (GetMessage(&msg, NULL, 0, 0)) //GetMessage()�� false �� ������
	{                                    // == WM_QUIT�϶�, Application Queue���� �����
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT mesg, WPARAM wParam, LPARAM lParam)
{
	static HWND hWnd2;

	switch (mesg)
	{
	case WM_CREATE:

		hWnd2 = CreateWindow("WND2", "�ڽ�������",
			WS_OVERLAPPEDWINDOW | WS_VISIBLE,
			320, 0, 320, 240, hWnd, NULL, _hInstance, NULL);
		break;

	case WM_MOUSEMOVE:
		/*
		int x, y;
		HDC hdc;
		x = LOWORD(lParam);
		y = HIWORD(lParam);
		hdc = GetDC(hWnd2);
		TextOut(hdc, x, y, "X", 1);
		ReleaseDC(hWnd2, hdc);
		*/
		/*
		int x, y;
		x = LOWORD(lParam);
		y = HIWORD(lParam);
		lParam = (x << 16) | y; //����
		*/
		SendMessage(hWnd2, 2000, wParam, lParam);
		//PostMessage(HWnd hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		return FALSE;
	}
	return DefWindowProc(hWnd, mesg, wParam, lParam); //�⺻���� ������ �޽��� ó��(default)
}
LRESULT CALLBACK WndProc2(HWND hWnd, UINT mesg, WPARAM wParam, LPARAM lParam)
{
	switch (mesg)
	{
	case 2000:
		int x, y;
		HDC hdc;
		x = LOWORD(lParam);
		y = HIWORD(lParam);
		hdc = GetDC(hWnd);
		TextOut(hdc, x, y, "X", 1);
		ReleaseDC(hWnd, hdc);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return FALSE;
	}
	
	return DefWindowProc(hWnd, mesg, wParam, lParam);
}
//==SetWindowLong()
