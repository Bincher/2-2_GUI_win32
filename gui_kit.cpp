#include <windows.h> //������ ���α׷��ֿ� �ʿ�
#include <stdio.h>
#include <stdlib.h>
//WndProc : �޽��� ó�� �ڵ�
//WinMain : ������ ���� �ڵ�
//HINSTANCE : handle to an Instance (Program)

/*
typedef struct
{
	HWND hwnd; //������ ���� ���̵�(Handle to a Window)
	UINT message; //�̺�Ʈ ���� ���̵�(unsigned int)
	WPARAM wParam; //��Ȳ����
	LPARAM lParam;
	DWORD time; //�̺�Ʈ �߻� ���� ���
	POINT pt; //���콺 ��ġ ���
}MSG;
*/

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
//����Ÿ�� �Լ�ȣ�������� �Լ��̸�(������ �ڵ�, �̺�Ʈ ���̵�, �ΰ�����1, �ΰ�����2)
//         (PASCAL, C)
//		   == _stdcall
//WPARAM, LPARAM(�ΰ�����)�� 4����Ʈ
LRESULT CALLBACK WndProc2(HWND, UINT, WPARAM, LPARAM);
HWND _hWnd2; //���� ���ϰ� �Ϸ��� �������� ���

//int �Ľ�Įȣ�������� �Լ�(��� ����� ���α׷� ID, ������ ����� ���α׷� ID, ���� �� �Ѱ����� ���ڿ�, ������ ȭ�� ��� ���� �����ϴ� ��� �� �Ѿ��) 
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszArg, int nCmdShow)
{
	//������ Ŭ���� ���� -> ������ Ŭ���� ��� -> ������ ���� -> �޽��� ����
	//�Ӽ� ����(�� ����) -> ������ �ü���� �˸� -> ��� ���� �̿��� ������ ���� -> �޽��� ó�� �ݺ�
	
	//Ŭ���� ���� 
	HWND hWnd;
	MSG msg;
	WNDCLASS WndClass;
	WndClass.style = NULL;
	WndClass.lpfnWndProc = WndProc; //�̺�Ʈ ó�� �Լ� �̸�, ���氡��
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hInstance = hInstance; //���α׷� ID ���
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH); //ȭ�� ��
	WndClass.lpszMenuName = NULL;
	WndClass.lpszClassName = "Hello"; //���氡�� -> ���� ���

	WndClass.lpfnWndProc = WndProc2;
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); //ȭ�� ��
	WndClass.lpszClassName = "WND2"; //���氡�� -> ���� ���
	//Ŭ���� ���
	if (!RegisterClass(&WndClass)) return NULL;
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
		"Hello", //������ Ÿ��Ʋ
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL, NULL, hInstance, NULL
	);

	//������ Ÿ��Ʋ ���� �Լ�
	ShowWindow(hWnd, nCmdShow); //������ �����츦 ������ ���
	UpdateWindow(hWnd); //������ API : �̹� ������� �����쿡 ���� ������ �ϴ� �Լ�
						//             ù ��° ���ڴ� hWnd, �ʿ��Լ� �� SW_SHOW ��(windows.h)
	
	ShowWindow(_hWnd2, nCmdShow); //������ ������ Ÿ��Ʋ
	UpdateWindow(_hWnd2); //���� ������ Ÿ��Ʋ

	//�޽��� ����
	while (GetMessage(&msg, NULL, 0, 0)) //GetMessage()�� false �� ������
	{                                    // == WM_QUIT�϶�, Application Queue���� �����
		TranslateMessage(&msg);
		DispatchMessage(&msg); //���������� WndProc ȣ��
		//TranslateMessage : ����Ű(ex.����) ó��
		//DispatchMessage : �̺�Ʈ�� �߻��� �������� ������ ���ν��� ȣ��
	}
	return msg.wParam;
	


	//�޽����ڽ� ������ ���� �� ���
	//MessageBox(HWND hWnd, LPCSTR szMsg, LPCSTR szTitle, UINT type);
	//                     (����� �޽���)(��ȭ���� ������ Ÿ��Ʋ)
}

//������ ���ν���(�̺�Ʈ�� �߻��� �� ���� �ڵ����� ȣ��)
//hwnd�� ȣ�� -> WndProc ����(WndClass.lpfnWndProc = WndProc;)
LRESULT CALLBACK WndProc(HWND hWnd, UINT mesg, WPARAM wParam, LPARAM lParam)
{
	//WM_RBUTTONDOWN, WM_LBUTTONUP ...
	switch (mesg)
	{
	case WM_LBUTTONDOWN: //ó�� �޽���=>case���� ����
		//MessageBox(hWnd, "�ȳ��ϼ���", "�λ�", MB_OK); //ó�� ���� -> ���α׷� ����
		SetWindowText(_hWnd2, "Black"); 
		break;
	/*
	case WM_MOUSEMOVE: //���콺 ������ �̺�Ʈ
		//������ ȭ�鿡 ���� ����ϱ�
		int x, y;
		char szPos[80];
		HDC hdc;
		x = HIWORD(lParam); //���콺 ��ǥ
		y = LOWORD(lParam); //MSDNȰ��
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

	return DefWindowProc(hWnd, mesg, wParam, lParam); //�⺻���� ������ �޽��� ó��(default)
	//                   HWND hWnd, ...
}
LRESULT CALLBACK WndProc2(HWND hWnd, UINT mesg, WPARAM wParam, LPARAM lParam)
{
	//WM_RBUTTONDOWN, WM_LBUTTONUP ...
	switch (mesg)
	{
	case WM_LBUTTONDOWN: //ó�� �޽���=>case���� ����
		MessageBox(hWnd, "�ȳ��ϼ���", "�λ�", MB_OK); //ó�� ���� -> ���α׷� ����
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return FALSE;
	}
	return DefWindowProc(hWnd, mesg, wParam, lParam); //�⺻���� ������ �޽��� ó��(default)
	//                   HWND hWnd, ...
}