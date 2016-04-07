#pragma once

#include <d3d9.h>
#include "d3dx9.h"

#pragma comment (lib, "d3d9.lib")
#pragma comment (lib, "d3dx9.lib")


//#define SAFE_DELETE(p)       { if(p) { delete (p);     (p)=NULL; } }
//#define SAFE_DELETE_ARRAY(p) { if(p) { delete[] (p);   (p)=NULL; } }
//#define SAFE_RELEASE(p)      { if(p) { (p)->Release(); (p)=NULL; } }


class GraphicsDevice
{
public:
	GraphicsDevice();
	~GraphicsDevice();

	HWND main_hWnd = NULL;
	bool Initialize(HWND main_hWnd, bool fullscreen);	//	fullscreen or Windowed mode
	void Clear(D3DCOLOR color);
	//void InitFont(ID3DXFont* pFont); //ID3DXFont* pFont
	void Begin();
	void End();
	void Present();

	//Public Pointers
	//static LPDIRECT3DDEVICE9 device;	// IDirect3DDevice9	*pDevice = NULL;
	LPDIRECT3DDEVICE9 device;
	ID3DXFont* pFont;
	bool VsyncSwitcher = true;	// переключатель vsync Ц (выкл. Vsync)
private:
	//Private Pointers
	LPDIRECT3D9 direct3d;	// IDirect3D9 *pD3D = NULL;

};

