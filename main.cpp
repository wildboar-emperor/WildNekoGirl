// 8 января 2016 
#include <Windows.h> 
#include "GraphicsDevice.h"
#include "Game.h"
//#include "Launcher.h"
Game *game;

// прототипы
bool GenerateWindow(HINSTANCE hInstance, int nCmdShow, LPCWSTR className, LPCWSTR windowTitle, int width, int height, HWND& hWnd);
bool GenerateWindow(HINSTANCE hInstance, int nCmdShow, LPCWSTR className, LPCWSTR windowTitle, int x, int y, int width, int height, HWND& hWnd); 
LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);

// глобальные

//HWND main_hWnd = NULL; // ? как тут - указать хендл из GraphicsDevice
HWND hWnd = NULL;
HINSTANCE hInstance = NULL;
WNDCLASSEX wc;
//POINT ptCursor;
bool l_pressed = false;
bool r_pressed = false;
//extern enum eGameState GS; // замысел был указать тут использовать переменную оттуда
//extern enum eGameState; // замысел был указать тут использовать переменную оттуда

int width = GetSystemMetrics(SM_CXSCREEN);	// размер экрана по умолчанию
int height = GetSystemMetrics(SM_CYSCREEN);
int ScreenWidth;		// размер экрана в зависимости от режима - уточняется в создании окна
int ScreenHeight;
int pos_x = width / 2 - width / 6;
int pos_y = height / 2 - height / 4;




// Созданиe окна
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
	// структура класса окна
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_DBLCLKS | CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WindowProc;    //указатель на функцию обработки сообщений - нужен прототип 
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(hInstance, L"w");
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.lpszMenuName = 0;
	wc.lpszClassName = className;
	wc.hIconSm = LoadIcon(hInstance, L"w");

	// Регистрация класса окна
	if (!RegisterClassEx(&wc)) return(0);

	//if (fullscreen)                            // Если полноэкранный режим
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

	// Создание окна
	//hWnd = CreateWindowExW(NULL,
	//	className,             // имя класса
	//	windowTitle, //заглавие окна
	//	//dwStyle
	//	WS_POPUP | WS_CLIPCHILDREN | WS_VISIBLE | WS_CLIPSIBLINGS,
	//	pos_x, pos_y,    // начальная позиция x,y
	//	ScreenWidth,	// ширина окна
	//	ScreenHeight,	// высота окна
	//	0,              // дескриптор родительского окна
	//	0,              // дескриптор меню
	//	hInstance,      // экземпляр этого приложения
	//	0);          // дополнительный параметр - creation parms
	//	
	hWnd = CreateWindowEx(NULL, className, windowTitle, WS_OVERLAPPED | WS_SYSMENU | WS_MINIMIZEBOX, x, y, width, height, NULL, NULL, hInstance, NULL);

	ShowWindow(hWnd, SW_SHOWDEFAULT);// здесь недоработка! - возможна ошибка, если поставить nCmdShow из-за объявления не тут не там хз где хз как
	//UpdateWindow(hwnd);
	
	return true;
}


// Обработчик событий
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
			PostQuitMessage(0);        // выход из программы
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
			ScreenToClient(hWnd, &game->ptCursor); // сдвинуть координаты курсора game_hwnd
			Game::Point2D Cursor(1.0f*game->ptCursor.x, 1.0f*game->ptCursor.y);
			game->BL = Game::bl_nothing; // сброс состояния чтобы обновилось
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
	}// конец switch
	return DefWindowProc(hWnd, message, wParam, lParam); // остальные сообщения
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