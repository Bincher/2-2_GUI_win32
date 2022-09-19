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

/*
WS_BORDER �������׵θ�
WS_CHILD �ڽ� ������� ����
WS_POPUP �˾� ������� ����
WS_VISIBLE �����츦 ������ ���ÿ� ȭ�鿡 ǥ��
WS_OVERLAPPEDWINDOW �Ϲ� �Ӽ� ��� ����
*/
//0, 400, 1430, 480,
LRESULT CALLBACK WndProc(HWND hWnd, UINT mesg, WPARAM wParam, LPARAM lParam)
{
	static HWND hWnd2; //static�� ��� �����ؾ��Ҷ� ���
	static HWND hBtn1;
	static HWND hBtn2;
	static HWND hEdt1;
	static HWND hEdt2;

	/*
	*ES_AUTOHSCROLL �ڵ�����ũ��
	*ES_AUTOVSCROLL �ڵ�������ũ��
	*ES_MULTILINE ���߶��� ����
	*ES_NUMBER ���ڸ� �Է� ����
	*ES_READONLY ���� �Ұ��� ����
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
		//BUTTON�� Ŭ�����̸�, BS_PUSHBUTTON�� ��ư ������ ��Ÿ�� ES_PUSHBUTTON
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

	//1.�޴��׸� ����
	//2.��Ʈ�� �����쿡�� �θ� �����쿡 �˸� �ڵ� ���� ��(wParam) - Notification
	//BN_CLICKED BN_DBLCLK BN_KILLFOUCS(Ű���� ��Ŀ���� ����)
	//EN_CHANGED EN_SETOCUSE(Ű���� ��Ŀ���� ����)
	//3.����Ű ������ ��
	case WM_COMMAND:
		int wNofifyCode = HIWORD(wParam);
		HWND hWndCtrl = (HWND)lParam;
		int id = LOWORD(wParam);
		if (id == 0)
			MessageBox(hWnd, "�ȳ��ϼ���", "�˸�", MB_OK);
		/*
		else if (id == 999)
			MessageBox(hWnd, "ȫ�浿�Դϴ�", "�˸�", MB_OK);
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
	
	return DefWindowProc(hWnd, mesg, wParam, lParam); //�⺻���� ������ �޽��� ó��(default)
}
LRESULT CALLBACK WndProc2(HWND hWnd, UINT mesg, WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, mesg, wParam, lParam);
}