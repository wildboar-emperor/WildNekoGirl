#pragma once
#include "Game.h"

//--------------------------------------------------------------------------------
// НЕ РАБОТАЕТ!!!  на классы разделить не получилось все в основной части + switch
//--------------------------------------------------------------------------------

// название файла и название класса может быть разным
//class Launcher: public Game 	//error C2504 : 'Game' : base class undefined
//extern LPDIRECT3DDEVICE9 Game::gDevice;
//extern LPDIRECT3DDEVICE9 device;
class Launcher
{
public:
	Launcher();
	~Launcher();

	bool Initialize(HWND hWnd);
	void Run();
	void Update(float gameTime);
	void Draw(float gameTime);
	friend class Game;
	//LPDIRECT3DDEVICE9 gDevice;
	//LPDIRECT3DDEVICE9 device;
	//GameSprite *button_launcher1;
	//GameSprite *button_launcher1a; // a - active
	//GameSprite *button_launcher1s; // s - selected

	//GameSprite *button_launcher2;
	//GameSprite *button_launcher2a;
	//GameSprite *button_launcher2s;

	//GameSprite *button_launcher3;
	//GameSprite *button_launcher3a;
	//GameSprite *button_launcher3s;
private:
	
	
	// тут были спрайты - перенес в public
	
};

