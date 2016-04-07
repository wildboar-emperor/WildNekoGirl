#include "Game.h"

D3DXCOLOR TextColor;
//ID3DXFont* pFont;
RECT		rc; // для курсора
RECT text_rc = { 1, 1, 0, 0 };

Game::Game()
{
	running = true;
	
	
}


Game::~Game()
{

	if (gDevice) { delete gDevice; gDevice = 0; }
	if (gameTime) { delete gameTime; gameTime = 0; }
	running = false;
}
//bool Game::LoadStateResource(eGameState GS)
//{
//	// замысел проинитить в зависимости от GS
//	// GS.Initialize();
//	//l = new Launcher();
//	
//	return true;
//}

// проверка на пересечение Point2D с Rect2D
bool Game::PointInRect(Point2D &p, Rect2D &r)
{
	return ((p.x >= r.l) && (p.y >= r.t) && (p.x <= r.r) && (p.y <= r.b));
}

bool Game::GameInitialize(HWND hWnd)
{
	/*
	1) инитить все сразу + switch(GS)
	2) когда-нибудь разделить без switch
	*/
	// hWnd = NULL; // эта строчка уронит прогу :) тк hWnd в создании устройства
	GS = gs_launcher;
	gDevice = new GraphicsDevice();
	game_hwnd = hWnd;
	//gDevice->InitFont(ID3DXFont *pFont);
	if (!gDevice->Initialize(hWnd, true))
	{
		return false;
	}

	gameTime = new GameTime();
	if (!gameTime->Initialize())
	{
		return false;
	}

	// спрайты
	// velocity для обновления (если в функции обновленя без велосити то не прорендится)
	

	// Game::Initialize(GS)
	//Launcher *l = new Launcher(); // error C2512: 'Launcher' : no appropriate default constructor available
	//l->Initialize(hWnd);
	//Launcher *l;// = new Launcher(); // error C2512: 'Launcher' : no appropriate default constructor available
	//Initialize()
	log = new Log();

	button_run = new GameSprite(0, 0);
	button_run->Initialize(gDevice->device, "GUI/none.png", 200, 100);
	button_run->velocity.x = 0; button_run->velocity.y = 0;
			
	button_launcher1 = new GameSprite(0, 0);
	button_launcher1->Initialize(gDevice->device, "GUI/run.png", 200, 100);
	button_launcher1->velocity.x = 0;
	button_launcher1->velocity.y = 0;
	log->trace("run.png - loaded\n"); 
	log->trace("в логе\n не получается сохранить предыдущий текст\n");
	button_launcher1s = new GameSprite(0, 0);
	button_launcher1s->Initialize(gDevice->device, "GUI/run_s.png", 200, 100);
	button_launcher1s->velocity.x = 0;
	button_launcher1s->velocity.y = 0;
	log->trace("run_s.png - loaded\n");
	log->trace("в логе\n не получается сохранить предыдущий текст\n");
	
	button_setup = new GameSprite(0, 102);
	button_setup->Initialize(gDevice->device, "GUI/none.png", 200, 100);
	button_setup->velocity.x = 0;
	button_setup->velocity.y = 0;
	button_launcher2 = new GameSprite(0, 102);
	button_launcher2->Initialize(gDevice->device, "GUI/options.png", 200, 100);
	button_launcher2->velocity.x = 0;
	button_launcher2->velocity.y = 0;
	log->trace("options.png - loaded\n"); 
	button_launcher2s = new GameSprite(0, 102);
	button_launcher2s->Initialize(gDevice->device, "GUI/options_s.png", 200, 100);
	button_launcher2s->velocity.x = 0;
	button_launcher2s->velocity.y = 0;
	log->trace("options_s.png - loaded\n");
	
	button_exit = new GameSprite(0, 204);
	button_exit->Initialize(gDevice->device, "GUI/none.png", 200, 100);
	button_exit->velocity.x = 0; button_exit->velocity.y = 0;
	button_launcher3 = new GameSprite(0, 204);
	button_launcher3->Initialize(gDevice->device, "GUI/exit.png", 200, 100);
	button_launcher3->velocity.y = 0;
	button_launcher3->velocity.x = 0;
	log->trace("exit.png - loaded\n");
	button_launcher3s = new GameSprite(0, 204);
	button_launcher3s->Initialize(gDevice->device, "GUI/exit_s.png", 200, 100);
	button_launcher3s->velocity.y = 0;
	button_launcher3s->velocity.x = 0;
	log->trace("exit_s.png - loaded\n");

	logo1 = new GameSprite(330, 220);
	logo1->Initialize(gDevice->device, "GUI/logo1.png", 100, 100);
	logo1->velocity.x = sin(100);
	logo1->velocity.y = cos(10);

	//cat1 = new GameSprite(50, 0);
	//if (!cat1->Initialize(gDevice->device, "long cat white.png", 238, 534))
	//{
	//	return false;
	//}
	//cat1->velocity.x = 10;
	//cat1->velocity.y = 0;


	//cat2 = new GameSprite(350, 0);
	//if (!cat2->Initialize(gDevice->device, "long cat black.png", 247, 538))
	//{
	//	return false;
	//}
	//cat2->velocity.x = -10;
	//cat2->velocity.y = 0;


	return true;
}

//перенес в WindowProc case WM_MOUSEMOVE
//void Game::CheckCursor(HWND game_hwnd)
//{
//	GetCursorPos(&ptCursor);
//	ScreenToClient(game_hwnd, &ptCursor);
//	Point2D Cursor(1.0f*ptCursor.x, 1.0f*ptCursor.y);
//
	// ! проблема "не тот хендл"
	//GetForegroundWindow()
	//ScreenToClient(hWnd, &ptCursor); // ! так хендл окна не передается и координаты- !
	//hWnd = (HWND)GetModuleHandle(NULL);
	
	/*BL = bl_nothing;
	if (PointInRect(Cursor, Rect1))
		button_launcher1->Update(gameTime);
	else
		button_launcher1s->Update(gameTime);*/
//------------- так работает только с одной кнопкой и падает на второй----------
	//if (PointInRect(Cursor, Rect1))
	//	button_run = button_launcher1;
	//else
	//	button_run = button_launcher1s;
	/*if (PointInRect(Cursor, Rect2))
		button_setup = button_launcher2;
	else
		button_setup = button_launcher2s;
	if (PointInRect(Cursor, Rect3))
		button_exit = button_launcher3;
	else
		button_exit = button_launcher3s;
//-----------------------------------------
*/

	//switch (PointInRect)
	//{
	//case Rect1:
	//	break;
	//}
	//
	
	/*if (PointInRect(Cursor, Rect1)) { BL = bl_run; }
	if (PointInRect(Cursor, Rect2)) { BL = bl_options; }
	if (PointInRect(Cursor, Rect3)) { BL = bl_exit; }*/

	//if (GS == gs_launcher)
	//{
	//	// из инит позиция + размер - объявил в .h
	//	if (PointInRect(Cursor, Rect1)) { BL = bl_run; }
	//	if (PointInRect(Cursor, Rect2)) { BL = bl_options; }
	//	if (PointInRect(Cursor, Rect3)) { BL = bl_exit; }
	//	//if (PointInRect(Cursor, Rect3)) { BL = bl_autors; }
	//	//if (PointInRect(Cursor, Rect4)) { BL = bl_exit; }
	//}
//}

//void Game::Run(eGameState)
void Game::Run()
{
	//Get game time then update + draw
	gameTime->Update();
	
	Update(gameTime->elapsedTime);
	Draw(gameTime->elapsedTime);
}


void Game::Update(float gameTime)
{
	switch (GS)
	{
	case gs_launcher:
		
		//CheckCursor(game_hwnd); //перенес в WindowProc case WM_MOUSEMOVE

		//button_run->Update(gameTime);
		//button_setup->Update(gameTime);
		//button_exit->Update(gameTime);
		/*button_launcher2->Update(gameTime);
		button_launcher2s->Update(gameTime);*/


		break;
	
	case gs_menu:
	//Update our sprites and other game logic
		if (cat1) cat1->Update(gameTime);
		break;
	//if (cat2) cat2->Update(gameTime);
//	if (player2) player2->Update(gameTime);
	default: break;
	}
}



void Game::SetColor(int r, int g, int b)
{
	TextColor = D3DCOLOR_XRGB(r, g, b);
}

void Game::PrintText(int x, int y, LPCWSTR text)
{
	SetRect(&rc, x, y, 0, 0);
	gDevice->pFont->DrawText(NULL, text, -1, &rc, DT_NOCLIP, TextColor);
}
void Game::PrintInt(int a, int x, int y)
{
	TCHAR textint[33];
	_itow(a, textint, 10);
	SetRect(&rc, x, y, 0, 0);
	gDevice->pFont->DrawText(NULL, textint, -1, &rc, DT_NOCLIP, TextColor);
}

void Game::Draw(float gameTime)
{
	SetColor(250, 255, 50);
		//Simple RGB value for the background so use XRGB instead of ARGB.
		gDevice->Clear(D3DCOLOR_XRGB(50, 50, 100));
		gDevice->Begin();
		switch (GS)
		{
		case gs_launcher:
			
			
			gDevice->pFont->DrawTextW(NULL, L"23", -1, &text_rc, DT_NOCLIP, TextColor);
			// Работает но показывает общие координаты, а не отсчет от стартовой окна программы
			PrintInt(ptCursor.x, 210, 50);
			PrintInt(ptCursor.y, 210, 65);
			PrintText(210, 70, L"Selected Screen Size: "); 
			//PrintText(260, 70, (LPCWSTR)&BL);
			
			//gDevice->pFont->DrawText(NULL, L"выбран размер:", -1, &text_rc, DT_NOCLIP, TextColor);

			/*button_launcher1->Draw(gameTime);
			button_launcher1s->Draw(gameTime);*/
			
			//CheckCursor(game_hwnd);	//выключено - все в WindowProc case WM_MOUSEMOVE
			/*
			button_run->Draw(gameTime);
			*/
			//button_setup->Draw(gameTime);
			//button_exit->Draw(gameTime);
			/*button_launcher2->Draw(gameTime);
			button_launcher3->Draw(gameTime);*/

			// switch не получилось.....................
			//switch (BL)
			//{
			//case bl_run:
			//	button_launcher1s->Draw(gameTime);
			//	else // illegal else without matching if
			//	button_launcher1->Draw(gameTime);
			//break;
			//}

			if (BL == bl_run)
				button_launcher1s->Draw(gameTime);
			else 
				button_launcher1->Draw(gameTime);
			if (BL == bl_options)
				button_launcher2s->Draw(gameTime);
			else
				button_launcher2->Draw(gameTime);
			if (BL == bl_exit)
				button_launcher3s->Draw(gameTime);
			else
				button_launcher3->Draw(gameTime);
			
			
			/*
			logo1->Draw(gameTime);
			*/
			break;
		case gs_menu:
			if (cat1 && cat1->IsInitialized()) cat1->Draw(gameTime);
			//if (cat2 && cat2->IsInitialized()) cat2->Draw(gameTime);
			//if (player2 && player2->IsInitialized()) player2->Draw(gameTime);
			break;
		default: break;
		}
		gDevice->End();
		gDevice->Present();	
}