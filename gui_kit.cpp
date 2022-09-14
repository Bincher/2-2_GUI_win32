#include <windows.h> //������ ���α׷��ֿ� �ʿ�
#include <stdio.h>
#include <stdlib.h>


LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HWND _hWnd2;
LRESULT CALLBACK WndProc2(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszArg, int nCmdShow)
{
	HWND hWnd;
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
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
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

LRESULT CALLBACK WndProc(HWND hWnd, UINT mesg, WPARAM wParam, LPARAM lParam)
{
	//WM_RBUTTONDOWN, WM_LBUTTONUP ...
	switch (mesg)
	{
	case WM_LBUTTONDOWN:
		SetWindowText(_hWnd2, "Black");
		break;
	case WM_DESTROY:
		/*
		MessageBox(hWnd, "���׳�", "", MB_OK);
		DestroyWindow(_hWnd2);
		PostQuitMessage(0);
		return FALSE;
		*/
		PostQuitMessage(0);
		return FALSE;
	}
	return DefWindowProc(hWnd, mesg, wParam, lParam); //�⺻���� ������ �޽��� ó��(default)
}
LRESULT CALLBACK WndProc2(HWND hWnd, UINT mesg, WPARAM wParam, LPARAM lParam)
{
	//WM_RBUTTONDOWN, WM_LBUTTONUP ...
	switch (mesg)
	{
	case WM_LBUTTONDOWN:
		MessageBox(_hWnd2, "����������", "�λ�", MB_OK);
		break;
	case WM_DESTROY:
		
		PostQuitMessage(0);
		return FALSE;
	}
	return DefWindowProc(hWnd, mesg, wParam, lParam); //�⺻���� ������ �޽��� ó��(default)
	//                   HWND hWnd, ...
}