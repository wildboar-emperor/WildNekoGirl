#include "GraphicsDevice.h"


GraphicsDevice::GraphicsDevice()
{
	main_hWnd = (HWND)GetModuleHandle(NULL);
}


GraphicsDevice::~GraphicsDevice()
{
	//SAFE_RELEASE(device);
	//SAFE_RELEASE(direct3d);
	//if (fullscreen)
	//{
	//	ChangeDisplaySettings(NULL, 0);
	//	ShowCursor(TRUE);
	//}



	//if (main_hWnd && !DestroyWindow(main_hWnd))    // Разрушить Окно
	//{
	//	MessageBox(NULL, L"Не удалось освободить hWnd", L"Ошибка Освобождения Ресурсов", MB_OK | MB_ICONINFORMATION);
	//	main_hWnd = 0;
	//}
	//DestroyIcon(wc.hIcon);
	//DestroyIcon(wc.hIconSm);
	//UnregisterClass(L"class1", wc.hInstance); // Разрегистровать класс

	if (device)
	{
		device->Release();
		device = 0;
	}

	if (direct3d)
	{
		direct3d->Release();
		direct3d = 0;
	}
}


bool GraphicsDevice::Initialize(HWND main_hWnd, bool fullscreen)
{
	HRESULT hr = 0;
	UINT vsync = 0;				// хранит значение d3dpp.PresentationInterval
	
	fullscreen = false;

		//Create Direct 3D Pointer
	direct3d = Direct3DCreate9(D3D_SDK_VERSION);
	if (!direct3d)
	{
		if (direct3d != NULL)direct3d->Release();
		::MessageBox(0, L"Direct3DCreate9(D3D_SDK_VERSION) - Failed", 0, 0);
		return false;
	}

	D3DDISPLAYMODE Display;
	if (FAILED(direct3d->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &Display)))
	{
		::MessageBox(0, L"GetAdapterDisplayMode - Failed", 0, 0);
		return false;
	}

	D3DCAPS9 caps;
	if (FAILED(direct3d->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &caps)))
	{
		if (direct3d != NULL)direct3d->Release();
		::MessageBox(0, L"GetDeviceCaps() - Failed", 0, 0);
		return false;
	}

	int vp = 0;
	if (caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
		vp = D3DCREATE_HARDWARE_VERTEXPROCESSING;
	else
		vp = D3DCREATE_SOFTWARE_VERTEXPROCESSING; // D3DCREATE_MIXED_VERTEXPROCESSING = Uses both hardware and software for 3D calculations

	if (VsyncSwitcher)
	{
		vsync = D3DPRESENT_INTERVAL_DEFAULT;    // переключатель  вкл. vsync
	}
	else
	{
		vsync = D3DPRESENT_INTERVAL_IMMEDIATE;    // переключатель  выкл. vsync
	}

	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp)); // memset(&d3dpp, 0, sizeof(D3DPRESENT_PARAMETERS));
	//d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD; //fastest
	d3dpp.hDeviceWindow = main_hWnd; //use the window we set up
	d3dpp.Windowed = !fullscreen;    // Boolean determines if we are running fullscreen or Windowed mode
	d3dpp.BackBufferFormat = Display.Format;
	d3dpp.EnableAutoDepthStencil = true;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8; // быстрее, чем D3DFMT_D16 на 0-20%
	
	d3dpp.BackBufferCount = 1;
	d3dpp.PresentationInterval = vsync;     // переключатель vsync
	if (fullscreen)
	{
		d3dpp.FullScreen_RefreshRateInHz = Display.RefreshRate;
		d3dpp.SwapEffect = D3DSWAPEFFECT_FLIP;
		d3dpp.BackBufferWidth = Display.Width;
		d3dpp.BackBufferHeight = Display.Height;
		
	}
	else
	{
		d3dpp.FullScreen_RefreshRateInHz = 0;
		d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	}
	
	hr = direct3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, main_hWnd, vp, &d3dpp, &device);
	if (FAILED(hr))
	{
		::MessageBox(0, L"CreateDevice() with 24 - FAILED", 0, 0);
		// попытаться ещё раз, используя 16-битный буфер глубины
		d3dpp.AutoDepthStencilFormat = D3DFMT_D16;

		hr = direct3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, main_hWnd, vp, &d3dpp, &device);

		if (FAILED(hr))
		{
			direct3d->Release();
			::MessageBox(0, L"CreateDevice() with 16 - FAILED", 0, 0);
			return false;
		}
	}
	

	// Создание текста
	D3DXCreateFont(device, 18, 0, NULL, 1, FALSE, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE,
		L"Courier new", &pFont);
	// Свет
	device->SetRenderState(D3DRS_LIGHTING, TRUE);
	device->SetRenderState(D3DRS_AMBIENT, D3DCOLOR_COLORVALUE(0.2f, 0.2f, 0.2f, 1.0f));
	D3DLIGHT9 light0; 	ZeroMemory(&light0, sizeof(D3DLIGHT9));
	light0.Type = D3DLIGHT_DIRECTIONAL;
	light0.Direction = D3DXVECTOR3(0.5f, -0.8f, 0.7f);
	light0.Diffuse.r = 1.0f;
	light0.Diffuse.g = 1.0f;
	light0.Diffuse.b = 1.0f;
	light0.Diffuse.a = 1.0f;
	device->SetLight(0, &light0);
	device->LightEnable(0, true);

	// Материал
	D3DMATERIAL9 mtrl;
	ZeroMemory(&mtrl, sizeof(D3DMATERIAL9));
	mtrl.Diffuse.r = 1.0f;
	mtrl.Diffuse.g = 1.0f;
	mtrl.Diffuse.b = 1.0f;
	mtrl.Diffuse.a = 1.0f;
	mtrl.Ambient.r = 1.0f;
	mtrl.Ambient.g = 1.0f;
	mtrl.Ambient.b = 1.0f;
	mtrl.Ambient.a = 1.0f;
	device->SetMaterial(&mtrl);

	device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);// Отключаем отсечение
	device->SetRenderState(D3DRS_AMBIENT, 0xffffffff);    // Окружающие освещенние
	device->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);    // Включаем Z буфер
	device->SetRenderState(D3DRS_LIGHTING, FALSE);			// освещение выкл., перед включением - настройте материалы!
	device->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
	device->SetRenderState(D3DRS_ALPHAREF, 0x01);
	device->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATEREQUAL);

	device->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	device->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	device->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);

	return true;
}

//HRESULT InitFont()
//{
//	HRESULT hr;
//	if (FAILED(hr = D3DXCreateFont(device, 18, 0, NULL, 1, FALSE, DEFAULT_CHARSET,
//		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE,
//		L"Courier new", &pFont)))
//	{
//		MessageBox(NULL, L"Failed to create font", L"Error", MB_OK);
//		return E_FAIL;
//	}
//	return S_OK;
//}

//void GraphicsDevice::InitFont(ID3DXFont* pFont)
//{
//	D3DXCreateFont(device, 18, 0, NULL, 1, FALSE, DEFAULT_CHARSET,
//		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE,
//		L"Courier new", &pFont);
//}

void GraphicsDevice::Clear(D3DCOLOR color)
{
	//2nd param 'NULL' clears the entire back buffer.
	device->Clear(0, NULL, D3DCLEAR_TARGET, color, 1.0f, 0);
	//device->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);     // очистка экрана
	//device ->Clear( 0, NULL, D3DCLEAR_ZBUFFER,D3DCOLOR_XRGB(30,30,50), 1.0f, 0 ); // прикол)

}

void GraphicsDevice::Begin()
{
	device->BeginScene();
}

void GraphicsDevice::End()
{
	device->EndScene();
}

void GraphicsDevice::Present()
{
	//Present our scene to the window.
	device->Present(NULL, NULL, NULL, NULL);
}