#include <windows.h> //������ ���α׷��ֿ� �ʿ�
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
	//Ŭ���� ���
	if (!RegisterClass(&WndClass)) return NULL;
	if (!RegisterClass(&WndClass2)) return NULL;
	//�޸𸮸� ���� ���(�ּҸ�)
	_hInstance = hInstance;

	//������ ����
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

	//�����츦 �ѹ� �� ���� == �Ȱ��� �ڵ带 �ѹ� ��
	_hWnd2 = CreateWindow( //���� ������ ����(11���� ����)
		"WND2", //�̸��� WND2�� Ŭ������ �̿��Ͽ� ������ ����
		"World", //������ Ÿ��Ʋ
		WS_OVERLAPPEDWINDOW,
		320, 0, 320, 240,
		hWnd, NULL, hInstance, NULL
	);


	ShowWindow(hWnd, nCmdShow); //������ �����츦 ������ ���
	UpdateWindow(hWnd);

	ShowWindow(_hWnd2, nCmdShow); //������ ������ Ÿ��Ʋ
	UpdateWindow(_hWnd2); //���� ������ Ÿ��Ʋ

	//�޽��� ����
	while (GetMessage(&msg, NULL, 0, 0)) //GetMessage()�� false �� ������
	{                                    // == WM_QUIT�϶�, Application Queue���� �����
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}

/*
WS_BORDER �������׵θ�
WS_CHILD �ڽ� ������� ����
WS_POPUP �˾� ������� ����
WS_VISIBLE �����츦 ������ ���ÿ� ȭ�鿡 ǥ��
WS_OVERLAPPEDWINDOW �Ϲ� �Ӽ� ��� ����
*/

LRESULT CALLBACK WndProc(HWND hWnd, UINT mesg, WPARAM wParam, LPARAM lParam)
{
	//WndProc�� �̺�Ʈ�� �߻��� �� ���� ȣ��Ǵ� �Լ�
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
	return DefWindowProc(hWnd, mesg, wParam, lParam); //�⺻���� ������ �޽��� ó��(default)
}
LRESULT CALLBACK WndProc2(HWND hWnd, UINT mesg, WPARAM wParam, LPARAM lParam)
{
	switch (mesg)
	{
	case WM_DESTROY:
		MessageBox(hWnd, "���׾�?", "", MB_OK);
		return FALSE;
	}
	return DefWindowProc(hWnd, mesg, wParam, lParam); //�⺻���� ������ �޽��� ó��(default)
	//                   HWND hWnd, ...
}