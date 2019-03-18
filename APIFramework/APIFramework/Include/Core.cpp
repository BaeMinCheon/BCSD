#include "Core.h"

Core * Core::m_pInst = nullptr;
bool Core::m_isLooping = true;

Core::Core()
{
}

Core::~Core()
{
}

ATOM Core::MyRegisterClass()
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = Core::WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = m_hInst;
	wcex.hIcon = LoadIcon(m_hInst, MAKEINTRESOURCE(IDI_ICON1));
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_ICON1));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;  // MAKEINTRESOURCEW(IDC_WINAPI01);
	wcex.lpszClassName = CLASS_NAME;

	return RegisterClassExW(&wcex);
}

BOOL Core::Create()
{
	m_hWnd = CreateWindowW(CLASS_NAME, CLASS_NAME, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, m_hInst, nullptr);

	if (!m_hWnd)
		return FALSE;

	// 윈도우 크기 확인
	RECT rc = { 0, 0, WND_WIDTH, WND_HEIGHT };
	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);
	// 윈도우 크기 설정
	SetWindowPos(m_hWnd, HWND_TOPMOST, 100, 100, rc.right - rc.left, rc.bottom - rc.top, SWP_NOMOVE | SWP_NOZORDER);

	ShowWindow(m_hWnd, SW_SHOW);
	UpdateWindow(m_hWnd);

	return TRUE;
}

bool Core::Init(HINSTANCE hInst)
{
	m_hInst = hInst;
	MyRegisterClass();

	// 해상도
	m_rs.w = WND_WIDTH;
	m_rs.h = WND_HEIGHT;

	Create();

	return true;
}

int Core::Run()
{
	MSG msg;

	// 기본 메시지 루프
	while (m_isLooping)
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
		}
	}

	return (int)msg.wParam;
}

LRESULT Core::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);

		// TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...

		EndPaint(hWnd, &ps);
	}
	break;
	case WM_DESTROY:
		m_isLooping = false;
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
