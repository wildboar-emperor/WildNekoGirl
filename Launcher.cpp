//#include "Launcher.h"
//#include "Game.h"
//#include "GraphicsDevice.h"
//// совпадение имени класса и переменной: GS = launcher; 
//
//extern LPDIRECT3DDEVICE9 device;
//Launcher::Launcher()
//{
//	//extern LPDIRECT3DDEVICE9 Game::gDevice;
//	//LPDIRECT3DDEVICE9 gDevice;
//	//button_launcher1 = new GameSprite(200, 200);
//	button_launcher1 = new GameSprite();
//	//button_launcher1->Initialize(gDevice->device, "GUI/run.png", 200, 100);
//	button_launcher1->Initialize(device, "GUI/run.png", 200, 100);
//	button_launcher1->velocity.x = 0;
//	button_launcher1->velocity.y = 0;
//
//	//button_launcher2 = new GameSprite(0, 102);
//	//button_launcher2->Initialize(gDevice->device, "GUI/options.png", 200, 100);
//	//button_launcher2->velocity.x = 0;
//	//button_launcher2->velocity.y = 0;
//
//	//button_launcher3 = new GameSprite(0, 204);
//	//button_launcher3->Initialize(gDevice->device, "GUI/exit.png", 200, 100);
//	//button_launcher3->velocity.y = 0;
//	//button_launcher3->velocity.x = 0;
//}
//
//
//Launcher::~Launcher()
//{
//}
//
//bool Launcher::Initialize(HWND hWnd)
//{
//	return true;
//}
//
//void Launcher::Update(float gameTime)
//{
//	// перенесено в switch case launcher
//	/*button_launcher1->Update(gameTime);
//	button_launcher2->Update(gameTime);
//	button_launcher3->Update(gameTime);*/
//}
//
//void Launcher::Draw(float gameTime)
//{
//	//gDevice->Clear(D3DCOLOR_XRGB(50, 50, 100));
//	//gDevice->Begin();
//
//	//if (button_launcher1 && button_launcher1->IsInitialized()) button_launcher1->Draw(gameTime);
//	//if (button_launcher2 && button_launcher2->IsInitialized()) button_launcher2->Draw(gameTime);
//	//if (button_launcher3 && button_launcher3->IsInitialized()) button_launcher3->Draw(gameTime);
//	//
//	//gDevice->End();
//	//gDevice->Present();
//}