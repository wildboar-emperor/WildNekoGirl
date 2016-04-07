#pragma once

#include "GraphicsDevice.h"
#include "GameTime.h"
#include "GameSprite.h"
#include <math.h>
#include "Log.h"
//#include "Launcher.h"
//namespace Game
class Game
{
public:
	Game();
	~Game();
	// static enum eGameState{ launcher, menu, gameitself, opening, ending } GS; // static чтобы использ вне класса
	enum eGameState{ gs_launcher, gs_menu, gs_gameitself, gs_opening, gs_ending } GS = gs_launcher; // error LNK2001: unresolved external symbol "public: static enum Game::eGameState Game::GS" (?GS@Game@@2W4eGameState@1@A)
	enum eButtonsLauncher { bl_nothing, bl_run, bl_options, bl_autors, bl_exit } BL = bl_nothing;
	
	// это третий дескриптор окна (единый хз как передавать между модулями)
	// hWnd первым при созд окна определится в майн 
	//+хендл потом  в GraphicsDevice при инициализации directx
	HWND game_hwnd;

	bool GameInitialize(HWND hWnd);
	bool LoadStateResource(eGameState GS);
	//void Run(eGameState GS); // virtual - сделать тут пустышками а реализовать ТОЛЬКО в модулях ???
	void Run();
	void Update(float gameTime);
	void Draw(float gameTime);
	
	// перенес в WindowProc case WM_MOUSEMOVE
	//void CheckCursor(HWND game_hwnd); // или передать hWnd или ручками выпрямлять координаты
	
	void SetColor(int r, int g, int b);
	void PrintText(int x, int y, LPCWSTR text);
	void PrintInt(int a, int x, int y);
	
	//static GraphicsDevice *gDevice;
	GraphicsDevice *gDevice; // not static cannot used outside the class
	GameTime *gameTime;
	Log *log;

	
	POINT ptCursor;
	//текущие координаты курсора
	struct Point2D
	{
		float x, y;
		Point2D() {}
		Point2D(float x, float y) : x(x), y(y) {}
	};

	//  прямоугольник для кнопок
	struct Rect2D
	{
		float l, t, r, b;
		Rect2D() {}
		Rect2D(float l, float t, float r, float b) : l(l), t(t), r(r), b(b) {}
	};
	bool PointInRect(Point2D &p, Rect2D &r);

	//friend class Launcher;
	Rect2D Rect1{ 0,   0, 200, 100 };
	Rect2D Rect2{ 0, 102, 200, 100 };
	Rect2D Rect3{ 0, 204, 200, 100 };

private:
	//Launcher *l;
	bool running;
	bool paused;

	/*GraphicsDevice *gDevice;
	GameTime *gameTime;*/
	
	//GS *game_state;
	
	//GameSprite *button_active_now;

	GameSprite *button_run; // создать обертку над спрайтами -некую GameButton с пустышками для иницииализации
	GameSprite *button_launcher1;
	GameSprite *button_launcher1a; // a - active
	GameSprite *button_launcher1s; // s - selected
									
	GameSprite *button_setup;
	GameSprite *button_launcher2;
	GameSprite *button_launcher2a;
	GameSprite *button_launcher2s;

	GameSprite *button_exit;
	GameSprite *button_launcher3;
	GameSprite *button_launcher3a;
	GameSprite *button_launcher3s;

	GameSprite *logo1;
	GameSprite *cat1;
	GameSprite *cat2;
		

	
	//GameSprite *player;
	//GameSprite *player2;

};

