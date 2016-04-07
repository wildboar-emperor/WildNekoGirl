#pragma once

//Texture and Sprites and other functions.
#include <d3dx9.h>
#include <string>

class GameSprite
{
public:
	//Attributes
	D3DXVECTOR3 velocity; // потом при объяевлении придется указывать велосити всем спрайтам (иначе не проинитятся)

	//Constructors and Destructor
	GameSprite();
	GameSprite(float x, float y); // позиция на экране
	~GameSprite();

	//Sprite Functions
	bool Initialize(LPDIRECT3DDEVICE9 device, std::string file, int width, int height);
	bool IsInitialized();
	virtual void Update(float gameTime);
	virtual void Draw(float gameTime);
private:
	//Pointers
	LPDIRECT3DTEXTURE9 tex;
	LPD3DXSPRITE sprite;

	//Attributes
	D3DXVECTOR3 position;
	D3DCOLOR color;
	bool initialized;
};

