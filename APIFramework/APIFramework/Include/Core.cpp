#include "Core.h"
#include "Core\Timer.h"
#include "Scene\SceneManager.h"

Core * Core::m_pInst = nullptr;
bool Core::m_isLooping = true;

Core::Core()
{
	// �޸� ���� üũ
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//_CrtSetBreakAlloc();
}

Core::~Core()
{
	DESTROY_SINGLE(SceneManager);
	DESTROY_SINGLE(Timer);
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

	// ������ ũ�� Ȯ��
	RECT rc = { 0, 0, WND_WIDTH, WND_HEIGHT };
	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);
	// ������ ũ�� ����
	SetWindowPos(m_hWnd, HWND_TOPMOST, 100, 100, rc.right - rc.left, rc.bottom - rc.top, SWP_NOMOVE | SWP_NOZORDER);

	ShowWindow(m_hWnd, SW_SHOW);
	UpdateWindow(m_hWnd);

	return TRUE;
}

void Core::Logic()
{
	GET_SINGLE(Timer)->Update();

	float deltaTime = GET_SINGLE(Timer)->GetDeltaTime();

	Input(deltaTime);
	Update(deltaTime);
	LateUpdate(deltaTime);
	Collision(deltaTime);
	Render(deltaTime);
}

void Core::Input(float deltaTime)
{
	GET_SINGLE(SceneManager)->Input(deltaTime);
}

int Core::Update(float deltaTime)
{
	GET_SINGLE(SceneManager)->Update(deltaTime);
	return 0;
}

int Core::LateUpdate(float deltaTime)
{
	GET_SINGLE(SceneManager)->LateUpdate(deltaTime);
	return 0;
}

void Core::Collision(float deltaTime)
{
	GET_SINGLE(SceneManager)->Collision(deltaTime);
}

void Core::Render(float deltaTime)
{
	GET_SINGLE(SceneManager)->Render(m_hDC, deltaTime);
}

bool Core::Init(HINSTANCE hInst)
{
	m_hInst = hInst;
	MyRegisterClass();

	// �ػ�
	m_rs.w = WND_WIDTH;
	m_rs.h = WND_HEIGHT;

	// HWND
	Create();

	// HDC
	m_hDC = GetDC(m_hWnd);

	// Timer �ʱ�ȭ
	if (!GET_SINGLE(Timer)->Init())
		return false;

	// SceneManager �ʱ�ȭ
	if (!GET_SINGLE(SceneManager)->Init())
		return false;

	return true;
}

int Core::Run()
{
	MSG msg;

	// �⺻ �޽��� ����
	while (m_isLooping)
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			Logic();
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

		// TODO: ���⿡ hdc�� ����ϴ� �׸��� �ڵ带 �߰��մϴ�...

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
