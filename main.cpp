// 8 ������ 2016 
#include <Windows.h> 
#include "GraphicsDevice.h"
#include "Game.h"
//#include "Launcher.h"
Game *game;

// ���������
bool GenerateWindow(HINSTANCE hInstance, int nCmdShow, LPCWSTR className, LPCWSTR windowTitle, int width, int height, HWND& hWnd);
bool GenerateWindow(HINSTANCE hInstance, int nCmdShow, LPCWSTR className, LPCWSTR windowTitle, int x, int y, int width, int height, HWND& hWnd); 
LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);

// ����������

//HWND main_hWnd = NULL; // ? ��� ��� - ������� ����� �� GraphicsDevice
HWND hWnd = NULL;
HINSTANCE hInstance = NULL;
WNDCLASSEX wc;
//POINT ptCursor;
bool l_pressed = false;
bool r_pressed = false;
//extern enum eGameState GS; // ������� ��� ������� ��� ������������ ���������� ������
//extern enum eGameState; // ������� ��� ������� ��� ������������ ���������� ������

int width = GetSystemMetrics(SM_CXSCREEN);	// ������ ������ �� ���������
int height = GetSystemMetrics(SM_CYSCREEN);
int ScreenWidth;		// ������ ������ � ����������� �� ������ - ���������� � �������� ����
int ScreenHeight;
int pos_x = width / 2 - width / 6;
int pos_y = height / 2 - height / 4;




// �������e ����
bool GenerateWindow(HINSTANCE hInstance, int nCmdShow, LPCWSTR className, LPCWSTR windowTitle, int width, int height, HWND &hWnd)
{
	return GenerateWindow(hInstance, nCmdShow, className, windowTitle, (GetSystemMetrics(SM_CXSCREEN) - width) / 2, (GetSystemMetrics(SM_CYSCREEN) - height) / 2, width, height, hWnd);
}

bool GenerateWindow(HINSTANCE hInstance, int nCmdShow, LPCWSTR className, LPCWSTR windowTitle, int x, int y, int width, int height, HWND &hWnd)
{
	if (hInstance == NULL)
		hInstance = (HINSTANCE)GetModuleHandle(NULL);
	
	DWORD        dwExStyle;        // Window Extended Style
	DWORD        dwStyle;        // Window Style
	ZeroMemory(&wc, sizeof(WNDCLASSEX));
	// ��������� ������ ����
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_DBLCLKS | CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WindowProc;    //��������� �� ������� ��������� ��������� - ����� �������� 
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(hInstance, L"w");
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.lpszMenuName = 0;
	wc.lpszClassName = className;
	wc.hIconSm = LoadIcon(hInstance, L"w");

	// ����������� ������ ����
	if (!RegisterClassEx(&wc)) return(0);

	//if (fullscreen)                            // ���� ������������� �����
	//{
	//	dwExStyle = WS_EX_APPWINDOW;    // Window Extended Style
	//	//dwStyle=WS_POPUP;             // Windows Style
	//	ShowCursor(FALSE);            // Hide Mouse
	//	ScreenWidth = width;
	//	ScreenHeight = height;
	//}
	//else
	//{
	//	dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;    // Window Extended Style
	//	//dwStyle=WS_OVERLAPPEDWINDOW;            // Windows Style
	//	ScreenWidth = width / 3;
	//	ScreenHeight = height / 2;
	//}

	// �������� ����
	//hWnd = CreateWindowExW(NULL,
	//	className,             // ��� ������
	//	windowTitle, //�������� ����
	//	//dwStyle
	//	WS_POPUP | WS_CLIPCHILDREN | WS_VISIBLE | WS_CLIPSIBLINGS,
	//	pos_x, pos_y,    // ��������� ������� x,y
	//	ScreenWidth,	// ������ ����
	//	ScreenHeight,	// ������ ����
	//	0,              // ���������� ������������� ����
	//	0,              // ���������� ����
	//	hInstance,      // ��������� ����� ����������
	//	0);          // �������������� �������� - creation parms
	//	
	hWnd = CreateWindowEx(NULL, className, windowTitle, WS_OVERLAPPED | WS_SYSMENU | WS_MINIMIZEBOX, x, y, width, height, NULL, NULL, hInstance, NULL);

	ShowWindow(hWnd, SW_SHOWDEFAULT);// ����� �����������! - �������� ������, ���� ��������� nCmdShow ��-�� ���������� �� ��� �� ��� �� ��� �� ���
	//UpdateWindow(hwnd);
	
	return true;
}


// ���������� �������
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_KEYDOWN:
		{
			if (wParam == VK_ESCAPE)
			{ 
				PostQuitMessage(0);
			}
			/*if (wParam == VK_F1)
			{
				Game::GS::launcher;
			}
			if (wParam == VK_F2)
			{
				Game::GS::menu;
			}
			if (wParam == VK_F3)
			{
				Game::GS::gameitself;
			}*/

		}break;

		case WM_CLOSE:
		{
			PostQuitMessage(0);        // ����� �� ���������
			return 0;
		} break;

		case WM_DESTROY:
		{
			PostQuitMessage(0);
			return 0;
		} break;
		case WM_MOUSEMOVE:
		{
			GetCursorPos(&game->ptCursor);
			ScreenToClient(hWnd, &game->ptCursor); // �������� ���������� ������� game_hwnd
			Game::Point2D Cursor(1.0f*game->ptCursor.x, 1.0f*game->ptCursor.y);
			game->BL = Game::bl_nothing; // ����� ��������� ����� ����������
			if (game->PointInRect(Cursor, game->Rect1))
			{
				game->BL = game->bl_run;
			}
			
			if (game->PointInRect(Cursor, game->Rect2))
			{
				game->BL = game->bl_options;
			}
			if (game->PointInRect(Cursor, game->Rect3))
			{
				game->BL = game->bl_exit;
			}
			
			return  0;//return game->BL;
			
		}
		case WM_LBUTTONDOWN:
			l_pressed = true;
			switch (game->BL)
			{
			//case bl_run:
			//	Cleanup();
			//	MakeWindow2(hInstance, SW_SHOWDEFAULT); // SW_NORMAL nCmdShow
			//	GS = gs_intro;
			//	return 0;
			//case bl_options:
			//	//GS = gs_options;
			//	MakeWindow3(hInstance, SW_SHOWDEFAULT);

			case 4:
				PostQuitMessage(0);
			}
			return 0;
		case WM_LBUTTONUP:
			l_pressed = false;
			return 0;
	}// ����� switch
	return DefWindowProc(hWnd, message, wParam, lParam); // ��������� ���������
}

// WinMain
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//HWND hWnd;
	//if (GenerateWindow(hInstance, nCmdShow, L"KeyboardInput", L"Keyboard Input", 1280, 720, hWnd))
	if (GenerateWindow(hInstance, nCmdShow, L"KeyboardInput", L"WildNekoGirl", 768, 800, hWnd))
	{
		//extern Game::eGameState GS; // error LNK2001: unresolved external symbol "enum Game::eGameState GS"
		MSG    msg;
		memset(&msg, 0, sizeof(msg));

		game = new Game();
		game->GameInitialize(hWnd);

		while (msg.message != WM_QUIT)
		{
			if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			else
			{
				game->Run();
			}
		}
		delete game;
		return msg.wParam;
	}
	return 0;
}