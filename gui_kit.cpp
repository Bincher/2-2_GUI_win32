#include <windows.h> //������ ���α׷��ֿ� �ʿ�

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
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.lpszMenuName = NULL;
	WndClass.lpszClassName = "Hello"; //���氡��

	//Ŭ���� ���
	if (!RegisterClass(&WndClass)) return NULL;
	//�޸𸮸� ���� ���(�ּҸ�)

	//������ ����
	hWnd = CreateWindow( //���� ������ ����(11���� ����)
		"Hello",
		"Hello",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL, NULL, hInstance, NULL
	);

	ShowWindow(hWnd, nCmdShow); //������ �����츦 ������ ���
	UpdateWindow(hWnd); //������ API : �̹� ������� �����쿡 ���� ������ �ϴ� �Լ�
						//             ù ��° ���ڴ� hWnd, �ʿ��Լ� �� SW_SHOW ��(windows.h)
	
	//�޽��� ����
	while (GetMessage(&msg, NULL, 0, 0)) //GetMessage()�� false �� ������
	{                                    // == WM_QUIT�϶�, Application Queue���� �����
		TranslateMessage(&msg);
		DispatchMessage(&msg); //���������� WndProc ȣ��
	}
	return msg.wParam;
}

//������ ���ν���(�̺�Ʈ�� �߻��� �� ���� �ڵ����� ȣ��)
LRESULT CALLBACK WndProc(HWND hWnd, UINT mesg, WPARAM wParam, LPARAM lParam)
{
	switch (mesg)
	{
	case WM_DESTROY: //ó�� �޽���
		PostQuitMessage(0); //ó�� ���� -> ���α׷� ����
	return FALSE;
	}
	return DefWindowProc(hWnd, mesg, wParam, lParam); //�⺻���� ������ �޽��� ó��(default)
	//                   HWND hWnd, ...
}