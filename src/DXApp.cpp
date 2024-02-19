#include "DXApp.h"
#include <windows.h>
#include <sstream>
#include <assert.h>
#include "d3dUtil.h"

// needed to load shaders from file
#include <d3dcompiler.h>

#include "Model.h"
#include "ShaderColor.h"
#include "DirectXTex.h"
#include "Texture.h"
#include "FlatPlane.h"
#include "GraphicObject_Color.h"
#include "ShaderTexture.h"
#include "ShaderLightTexture.h"
#include "GraphicObject_Texture.h"
#include "GraphicObject_TextureLight.h"
#include "GraphicObject_ColorLight.h"

void DXApp::InitDemo()
{
	pShaderColLight = new ShaderColorLight(md3dDevice);
	pShaderLightTex = new ShaderLightTexture(md3dDevice);

	pShaderLightTex->SetDirectionalLightParameters(Vect(-1, -1, 1).getNorm(),
		.1f * Vect(1, 1, 1), .1f * Vect(1, 1, 1), .1 * Vect(1, 1, 1));

	pShaderLightTex->SetToContext(md3dImmediateContext);
	
	
	// ------------ Terrain & Skybox -------------
	pTerrainModel = new TerrainModel(md3dDevice, L"../Assets/Textures/HMtest.tga", 400, 50, -20, 15, 15);
	mTexTerrain = new Texture(md3dDevice, L"../Assets/Textures/grass1.tga", D3D11_FILTER_MIN_MAG_MIP_LINEAR, 4, true, 0);
	mWorldTerrain = Matrix(IDENTITY);

	pSkyBox = new SkyBox(md3dDevice, 400);
	mTexSkyBox = new Texture(md3dDevice, L"../Assets/Textures/skybox2.tga", D3D11_FILTER_MIN_MAG_MIP_POINT);
	mWorldSkyBox = Matrix(IDENTITY);

	mTexCruiseShip = new Texture(md3dDevice, L"../Assets/Textures/texture.tga", D3D11_FILTER_MIN_MAG_MIP_POINT);
	mTexSailShip = new Texture(md3dDevice, L"../Assets/Textures/texture.tga", D3D11_FILTER_MIN_MAG_MIP_POINT);
	mTexFountain = new Texture(md3dDevice, L"../Assets/Textures/stone.tga", D3D11_FILTER_MIN_MAG_MIP_POINT);
	mTexLamp1 = new Texture(md3dDevice, L"../Assets/Textures/stone.tga", D3D11_FILTER_MIN_MAG_MIP_POINT);
	//mTexLamp2 = new Texture(md3dDevice, L"../Assets/Textures/CrateFace.tga", D3D11_FILTER_MIN_MAG_MIP_POINT);
	mTexPrison = new Texture(md3dDevice, L"../Assets/Textures/brick.tga", D3D11_FILTER_MIN_MAG_MIP_POINT);
	mTexTavern = new Texture(md3dDevice, L"../Assets/Textures/texture.tga", D3D11_FILTER_MIN_MAG_MIP_POINT);
	mTexTent = new Texture(md3dDevice, L"../Assets/Textures/texture.tga", D3D11_FILTER_MIN_MAG_MIP_POINT);
	mTexPremade = new Texture(md3dDevice, L"../Assets/Textures/CrateFace.tga", D3D11_FILTER_MIN_MAG_MIP_POINT);

	// Flying light space frigate
	pModelCruiseShip = new Model(md3dDevice, "../Assets/Models/space_frigate.azul");
	pGOCruiseShip = new GraphicObject_TextureLight(pShaderLightTex, pModelCruiseShip);
	pGOCruiseShip->SetTexture(mTexCruiseShip, 0);
	pGOCruiseShip->SetMaterial(Colors::DarkGray, Colors::DarkGray, Colors::White, 0);
	mWorldCruiseShip = Matrix(SCALE, .15f, .15f, .15f) * Matrix(TRANS, 50 , 20 , 50);
	pGOCruiseShip->SetWorld(mWorldCruiseShip);

	// Sailship
	pModelSailShip = new Model(md3dDevice, "../Assets/Models/BoatModel.azul");
	pGOSailShip = new GraphicObject_TextureLight(pShaderLightTex, pModelSailShip);
	pGOSailShip->SetTexture(mTexSailShip, 0);
	pGOSailShip->SetTexture(mTexSailShip, 1);
	pGOSailShip->SetTexture(mTexPremade, 2);
	pGOSailShip->SetTexture(mTexPremade, 3);
	pGOSailShip->SetTexture(mTexPremade, 4);
	pGOSailShip->SetTexture(mTexPremade, 5);
	pGOSailShip->SetTexture(mTexPremade, 6);
	pGOSailShip->SetTexture(mTexPremade, 7);
	pGOSailShip->SetTexture(mTexPremade, 8);
	pGOSailShip->SetTexture(mTexPremade, 9);
	pGOSailShip->SetMaterial(Colors::White, Colors::White, Colors::White, 0);
	pGOSailShip->SetMaterial(Colors::White, Colors::White, Colors::White, 1);
	pGOSailShip->SetMaterial(Colors::White, Colors::White, Colors::White, 2);
	pGOSailShip->SetMaterial(Colors::White, Colors::White, Colors::White, 3);
	pGOSailShip->SetMaterial(Colors::White, Colors::White, Colors::White, 4);
	pGOSailShip->SetMaterial(Colors::White, Colors::White, Colors::White, 5);
	pGOSailShip->SetMaterial(Colors::White, Colors::White, Colors::White, 6);
	pGOSailShip->SetMaterial(Colors::White, Colors::White, Colors::White, 7);
	pGOSailShip->SetMaterial(Colors::White, Colors::White, Colors::White, 8);
	pGOSailShip->SetMaterial(Colors::White, Colors::White, Colors::White, 9);

	mWorldSailShip = Matrix(SCALE, .15f, .15f, .15f) * Matrix(ROT_X, -MATH_PI / 2) * Matrix(ROT_Y, MATH_PI / 4) * Matrix(TRANS, -15, -18, 10);
	pGOSailShip->SetWorld(mWorldSailShip);

	// Fountain
	pModelFountain = new Model(md3dDevice, "../Assets/Models/fountain.azul");
	pGOFountain = new GraphicObject_TextureLight(pShaderLightTex, pModelFountain);
	pGOFountain->SetTexture(mTexFountain, 0);
	pGOFountain->SetMaterial(Colors::LightYellow, Colors::White, Colors::White, 0);
	mWorldFountain = Matrix(SCALE, .03f, .03f, .03f) * Matrix(TRANS, 0, -19, -5);
	pGOFountain->SetWorld(mWorldFountain);

	// Lamp1
	pModelLamp1 = new Model(md3dDevice, "../Assets/Models/lamp1.azul");
	pGOLamp1 = new GraphicObject_TextureLight(pShaderLightTex, pModelLamp1);
	pGOLamp1->SetTexture(mTexLamp1, 0);
	pGOLamp1->SetMaterial(Colors::LightYellow, Colors::White, Colors::White, 0);
	mWorldLamp1 = Matrix(SCALE, .03f, .03f, .03f) * Matrix(TRANS, 17, -19, -13);
	pGOLamp1->SetWorld(mWorldLamp1);

	// Lamp2
	pModelLamp2 = new Model(md3dDevice, "../Assets/Models/lamp2.azul");
	pGOLamp2 = new GraphicObject_TextureLight(pShaderLightTex, pModelLamp2);
	pGOLamp2->SetTexture(mTexLamp1, 0);
	pGOLamp2->SetMaterial(Colors::LightYellow, Colors::White, Colors::White, 0);
	mWorldLamp2 = Matrix(SCALE, .03f, .03f, .03f) * Matrix(TRANS, -18, -19, 16);
	pGOLamp2->SetWorld(mWorldLamp2);

	// Prison
	pModelPrison = new Model(md3dDevice, "../Assets/Models/prison.azul");
	pGOPrison = new GraphicObject_TextureLight(pShaderLightTex, pModelPrison);
	pGOPrison->SetTexture(mTexPrison, 0);
	pGOPrison->SetMaterial(Colors::LightYellow, Colors::White, Colors::White, 0);
	mWorldPrison = Matrix(SCALE, .04f, .04f, .04f) * Matrix(TRANS, -3, -18.3, -30);
	pGOPrison->SetWorld(mWorldPrison);

	// Tavern
	pModelTavern = new Model(md3dDevice, "../Assets/Models/tavern.azul");
	pGOTavern = new GraphicObject_TextureLight(pShaderLightTex, pModelTavern);
	pGOTavern->SetTexture(mTexTavern, 0);
	pGOTavern->SetMaterial(Colors::White, Colors::White, Colors::White, 0);
	mWorldTavern = Matrix(SCALE, .04f, .04f, .04f) * Matrix(ROT_Y, MATH_PI) * Matrix(TRANS, 33, -18.3, -10);
	pGOTavern->SetWorld(mWorldTavern);

	// Tent
	pModelTent = new Model(md3dDevice, "../Assets/Models/tent.azul");
	pGOTent = new GraphicObject_TextureLight(pShaderLightTex, pModelTent);
	pGOTent->SetTexture(mTexTent, 0);
	pGOTent->SetMaterial(Colors::White, Colors::White, Colors::White, 0);
	mWorldTent = Matrix(SCALE, .04f, .04f, .04f) *Matrix(ROT_Y, MATH_PI/4) * Matrix(TRANS, 23, -18.3, 20);
	pGOTent->SetWorld(mWorldTent);
	
	// Premade sphere & cube
	pModelPremadeSphere = new Model(md3dDevice, Model::PreMadeModels::UnitSphere);
	pGOPremadeSphere = new GraphicObject_TextureLight(pShaderLightTex, pModelPremadeSphere);
	pGOPremadeSphere->SetTexture(mTexPremade, 0);
	pGOPremadeSphere->SetMaterial(Colors::White, Colors::White, Colors::White, 0);
	mWorldPremadeSphere = Matrix(SCALE, 2, 2, 2) * Matrix(TRANS, 20, -18, 20);
	pGOPremadeSphere->SetWorld(mWorldPremadeSphere);
	
	pModelPremadeCube = new Model(md3dDevice, Model::PreMadeModels::UnitBoxRepeatedTexture);
	pGOPremadeCube = new GraphicObject_TextureLight(pShaderLightTex, pModelPremadeCube);
	pGOPremadeCube->SetTexture(mTexPremade, 0);
	pGOPremadeCube->SetMaterial(Colors::White, Colors::White, Colors::White, 0);
	mWorldPremadeCube = Matrix(SCALE, 2, 2, 2) * Matrix(TRANS, 24, -18, 10);
	pGOPremadeCube->SetWorld(mWorldPremadeCube);


	// Initialize the projection matrix
	mCam.setPerspective( 3.14159 / 3 , mClientWidth / (float)mClientHeight, 1.0f, 1000.0f);
	mCam.setOrientAndPosition(Vect(0, 5, 0), Vect(0, -1, 0), Vect(-20, 13, 15));

	mTimer.Reset();
}

void DXApp::UpdateScene()
{
	mWorldCruiseShip *= Matrix(ROT_Y, -0.002);
	pGOCruiseShip->SetWorld(mWorldCruiseShip);
	pos2 = mWorldCruiseShip.get(MatrixRowType::ROW_3);

	float camSpeed = 0.08f;
	if (GetKeyState('W') & 0x08000)
	{
		mCam.TranslateFwdBack(camSpeed);
	}
	else if (GetKeyState('S') & 0x08000)
	{
		mCam.TranslateFwdBack(-camSpeed);
	}

	if (GetKeyState('A') & 0x08000)
	{
		mCam.TranslateLeftRight(-camSpeed);
	}
	else if (GetKeyState('D') & 0x08000)
	{
		mCam.TranslateLeftRight(camSpeed);
	}

	float rotSpeed = 0.008f;
	if (GetKeyState(VK_LEFT) & 0x08000)
	{
		mCam.TurnLeftRight(rotSpeed);
	}
	else if (GetKeyState(VK_RIGHT) & 0x08000)
	{
		mCam.TurnLeftRight(-rotSpeed);
	}

	if (GetKeyState(VK_UP) & 0x08000)
	{
		mCam.TiltUpDown(rotSpeed);
	}
	else if (GetKeyState(VK_DOWN) & 0x08000)
	{
		mCam.TiltUpDown(-rotSpeed);
	}

	mCam.updateCamera();
}

void DXApp::DrawScene()
{
	md3dImmediateContext->ClearRenderTargetView(mRenderTargetView, VasA(BackgroundColor));
	md3dImmediateContext->ClearDepthStencilView(mpDepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);
	//*/

	pShaderLightTex->SetToContext(md3dImmediateContext);
	pShaderLightTex->SendCamMatrices(mCam.getViewMatrix(), mCam.getProjMatrix());
	
	pShaderLightTex->SetSpotLightParameters(0, pos2, 3000, .5 * Vect(1, 0, 0),
		-pos2.getNorm(), 50,
		.2 * Vect(1, 1, 1), .9 * Vect(1, 1, 1), 1 * Vect(1, 1, 1, 150));
	
	pShaderLightTex->SetSpotLightParameters(1, Vect(37, 19, 9), 2000, .5 * Vect(1, 0, 0),
		-Vect(17, 19, 13).getNorm(), 50,
		Colors::LightGoldenrodYellow, .9 * Vect(1, 1, 1), 1 * Vect(1, 1, 1, 150));
	
	pShaderLightTex->SetSpotLightParameters(2, Vect(0, 19, 25), 1500, .5 * Vect(1, 0, 0),
		-Vect(5, 10, 5).getNorm(), 50,
		Colors::LightGoldenrodYellow, .9 * Vect(1, 1, 1), 1 * Vect(1, 1, 1, 150));
	
	pShaderLightTex->SetPointLightParameters(Vect(17, 1, 13), 1000, .2 * Vect(0, 1, 0),
		.1 * Vect(1, 1, 1), 2 * Vect(1, 1, 1), 1 * Vect(1, 1, 1));

	Vect eyepos;
	mCam.getPos(eyepos);
	pShaderLightTex->SendLightParameters(eyepos);
	

	// Plane/box with light
	pShaderLightTex->SendWorldAndMaterial(mWorldTerrain, Colors::White, Colors::White, Vect(.9, .9, .9, 100));
	pShaderLightTex->SetTextureResourceAndSampler(mTexTerrain);
	pShaderLightTex->SendFog(200, 25, Colors::Black);
	pTerrainModel->Render(md3dImmediateContext);

	pShaderLightTex->SendWorldAndMaterial(mWorldSkyBox, Colors::White, Colors::White, Vect(2, 2, 2, 100));
	pShaderLightTex->SetTextureResourceAndSampler(mTexSkyBox);
	pShaderLightTex->SendFog(2000, 2500, Colors::Black);
	pSkyBox->Render(md3dImmediateContext);

	pGOCruiseShip->SetToContext(md3dImmediateContext);
	pGOCruiseShip->SendLightParameters(eyepos);
	pGOCruiseShip->SendFogData(500, 200, Colors::Black);
	pGOCruiseShip->Render();

	pGOSailShip->SetToContext(md3dImmediateContext);
	pGOSailShip->SendLightParameters(eyepos);
	pGOSailShip->SendFogData(110, 500, Colors::Black);
	pGOSailShip->Render();

	pGOPrison->SetToContext(md3dImmediateContext);
	pGOPrison->SendLightParameters(eyepos);
	pGOPrison->SendFogData(1100, 2000, Colors::Black);
	pGOPrison->Render();
	
	pGOTavern->SetToContext(md3dImmediateContext);
	pGOTavern->SendLightParameters(eyepos);
	pGOTavern->SendFogData(1100, 2000, Colors::Black);
	pGOTavern->Render();

	pGOFountain->SetToContext(md3dImmediateContext);
	pGOFountain->SendLightParameters(eyepos);
	pGOFountain->SendFogData(1100, 2000, Colors::Black);
	pGOFountain->Render();
	
	pGOLamp1->SetToContext(md3dImmediateContext);
	pGOLamp1->SendLightParameters(eyepos);
	pGOLamp1->SendFogData(1100, 2000, Colors::Black);
	pGOLamp1->Render();

	pGOLamp2->SetToContext(md3dImmediateContext);
	pGOLamp2->SendLightParameters(eyepos);
	pGOLamp2->SendFogData(1100, 2000, Colors::Black);
	pGOLamp2->Render();
	
	pGOTent->SetToContext(md3dImmediateContext);
	pGOTent->SendLightParameters(eyepos);
	pGOTent->SendFogData(1100, 2000, Colors::Black);
	pGOTent->Render();

	pGOPremadeSphere->SetToContext(md3dImmediateContext);
	pGOPremadeSphere->SendLightParameters(eyepos);
	//pGOPremadeSphere->SendFogData(1100, 2000, Colors::Black);
	pGOPremadeSphere->Render();

	pGOPremadeCube->SetToContext(md3dImmediateContext);
	pGOPremadeCube->SendLightParameters(eyepos);
	//pGOPremadeCube->SendFogData(1100, 2000, Colors::Black);
	pGOPremadeCube->Render();

	// Switches the display to show the now-finished back-buffer
	mSwapChain->Present(SyncInterval, 0);
}


DXApp::DXApp(HWND hwnd)
{
	assert(hwnd);
	mhMainWnd = hwnd;

	BackgroundColor = Colors::MidnightBlue;

	md3dDevice = nullptr;
	md3dImmediateContext = nullptr;
	mSwapChain = nullptr;
	mRenderTargetView = nullptr;

	// Get window data through the window handle
	RECT rc;
	BOOL err = GetClientRect(mhMainWnd, &rc);  // Seriously MS: Redifining BOOL as int? Confusing much?
	assert(err);

	// get width/hight
	mClientWidth = rc.right - rc.left;
	mClientHeight = rc.bottom - rc.top;

	// Get window caption
	const int MAX_LABEL_LENGTH = 100; // probably overkill...
	CHAR str[MAX_LABEL_LENGTH];
	GetWindowText(mhMainWnd, str, MAX_LABEL_LENGTH);
	mMainWndCaption = str;

	// Initialize DX11
	this->InitDirect3D();

	// Demo initialization
	this->InitDemo();
}

DXApp::~DXApp()
{
	delete pShaderColLight;
	delete pShaderLightTex;

	delete pSkyBox;
	delete pTerrainModel;
	delete mTexSkyBox;
	delete mTexTerrain;
	
	delete pModelCruiseShip;
	delete pModelSailShip;
	delete pModelFountain;
	delete pModelLamp1;
	delete pModelLamp2;
	delete pModelPrison;
	delete pModelTavern;
	delete pModelTent;
	delete pModelPremadeCube;
	delete pModelPremadeSphere;

	delete pGOCruiseShip;
	delete pGOSailShip;
	delete pGOFountain;
	delete pGOLamp1;
	delete pGOLamp2;
	delete pGOPrison;
	delete pGOTavern;
	delete pGOTent;
	delete pGOPremadeCube;
	delete pGOPremadeSphere;

	delete mTexCruiseShip;
	delete mTexSailShip;
	delete mTexFountain;
	delete mTexLamp1;
	//delete mTexLamp2;
	delete mTexPrison;
	delete mTexTavern;
	delete mTexTent;
	delete mTexPremade;

	ReleaseAndDeleteCOMobject(mRenderTargetView);
	ReleaseAndDeleteCOMobject(mpDepthStencilView);
	ReleaseAndDeleteCOMobject(mSwapChain);
	ReleaseAndDeleteCOMobject(md3dImmediateContext);

	// Must be done BEFORE the device is released
	ReportLiveDXObjects();		// See http://masterkenth.com/directx-leak-debugging/

	ReleaseAndDeleteCOMobject(md3dDevice);
}

// See http://masterkenth.com/directx-leak-debugging/
void DXApp::ReportLiveDXObjects()
{
#ifdef _DEBUG
	HRESULT hr = S_OK;

	// Now we set up the Debug interface, to be queried on shutdown
	ID3D11Debug* debugDev;
	hr = md3dDevice->QueryInterface(__uuidof(ID3D11Debug), reinterpret_cast<void**>(&debugDev));

	debugDev->ReportLiveDeviceObjects(D3D11_RLDO_DETAIL);
	ReleaseAndDeleteCOMobject(debugDev);
#endif
}

void DXApp::InitDirect3D()
{
	HRESULT hr = S_OK;

	UINT createDeviceFlags = 0;
#ifdef _DEBUG
	createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	// This is a *greatly* simplified process to create a DX device and context:
	// We force the use of DX11 feature level since that's what CDM labs are limited to.
	// For real-life applications would need to test what's the best feature level and act accordingly
	hr = D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, createDeviceFlags, nullptr, 0, D3D11_SDK_VERSION, &md3dDevice, nullptr, &md3dImmediateContext);
	assert(SUCCEEDED(hr));

	// Now we obtain the associated DXGIfactory1 with our device 
	// Many steps...
	IDXGIDevice* dxgiDevice = nullptr;
	hr = md3dDevice->QueryInterface(__uuidof(IDXGIDevice), reinterpret_cast<void**>(&dxgiDevice));
	assert(SUCCEEDED(hr));

	IDXGIAdapter* adapter = nullptr;
	hr = dxgiDevice->GetAdapter(&adapter);
	assert(SUCCEEDED(hr));

	IDXGIFactory1* dxgiFactory1 = nullptr;
	hr = adapter->GetParent(__uuidof(IDXGIFactory1), reinterpret_cast<void**>(&dxgiFactory1));
	assert(SUCCEEDED(hr));
	// See also note on weird stuff with factories and swap chains (1s and 2s)
	// https://msdn.microsoft.com/en-us/library/windows/desktop/jj863687(v=vs.85).aspx

	// We are done with these now...
	ReleaseAndDeleteCOMobject(adapter);
	ReleaseAndDeleteCOMobject(dxgiDevice);

	// Controls MSAA option:
	// - 4x count level garanteed for all DX11 
	// - MUST be the same for depth buffer!
	// - We _need_ to work with the depth buffer because reasons... (see below)
	DXGI_SAMPLE_DESC sampDesc;
	sampDesc.Count = 1;
	sampDesc.Quality = static_cast<UINT>(D3D11_CENTER_MULTISAMPLE_PATTERN);  // MS: what's with the type mismtach?

	DXGI_MODE_DESC buffdesc;				// https://msdn.microsoft.com/en-us/library/windows/desktop/bb173064(v=vs.85).aspx
	ZeroMemory(&buffdesc, sizeof(buffdesc));
	buffdesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;

	// Next we create a swap chain. 
	// Useful thread: http://stackoverflow.com/questions/27270504/directx-creating-the-swapchain
	// Note that this is for a DirectX 11.0: in a real app, we should test the feature levels and act accordingly

	DXGI_SWAP_CHAIN_DESC sd;				// See MSDN: https://msdn.microsoft.com/en-us/library/windows/desktop/bb173075(v=vs.85).aspx
	ZeroMemory(&sd, sizeof(sd));
	sd.BufferCount = 2;						// Much confusion about this number... see http://www.gamedev.net/topic/633807-swap-chain-buffer-count/
	sd.BufferDesc = buffdesc;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.OutputWindow = mhMainWnd;
	sd.SampleDesc = sampDesc;
	sd.Windowed = TRUE;

	hr = dxgiFactory1->CreateSwapChain(md3dDevice, &sd, &mSwapChain);
	assert(SUCCEEDED(hr));
	ReleaseAndDeleteCOMobject(dxgiFactory1);

	// Create a render target view		https://msdn.microsoft.com/en-us/library/windows/desktop/ff476582(v=vs.85).aspx
	ID3D11Texture2D* pBackBuffer = nullptr;
	hr = mSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&pBackBuffer));
	assert(SUCCEEDED(hr));;

	hr = md3dDevice->CreateRenderTargetView(pBackBuffer, nullptr, &mRenderTargetView);
	ReleaseAndDeleteCOMobject(pBackBuffer);
	assert(SUCCEEDED(hr));

	/**********************************************************/

	// First we fix what it means for triangles to be front facing.
	// Requires setting a whole new rasterizer state
	//*
	D3D11_RASTERIZER_DESC rd;
	rd.FillMode = D3D11_FILL_SOLID;  // Also: D3D11_FILL_WIREFRAME
	rd.CullMode = D3D11_CULL_BACK;
	rd.FrontCounterClockwise = true; // true for RH forward facing
	rd.DepthBias = 0;
	rd.SlopeScaledDepthBias = 0.0f;
	rd.DepthBiasClamp = 0.0f;
	rd.DepthClipEnable = true;
	rd.ScissorEnable = false;
	rd.MultisampleEnable = true;  // Does not in fact turn on/off multisample: https://msdn.microsoft.com/en-us/library/windows/desktop/ff476198(v=vs.85).aspx
	rd.AntialiasedLineEnable = true;

	ID3D11RasterizerState* rs;
	md3dDevice->CreateRasterizerState(&rd, &rs);

	md3dImmediateContext->RSSetState(rs);
	ReleaseAndDeleteCOMobject(rs); // we can release this resource since we won't be changing it any further
	//*/

	// We must turn on the abilty to process depth during rendering.
	// Done through depth stencils (see https://msdn.microsoft.com/en-us/library/windows/desktop/bb205074(v=vs.85).aspx)
	// Below is a simplified version
	//*
	D3D11_TEXTURE2D_DESC descDepth;
	descDepth.Width = mClientWidth;
	descDepth.Height = mClientHeight;
	descDepth.MipLevels = 1;
	descDepth.ArraySize = 1;
	descDepth.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	descDepth.SampleDesc = sampDesc;
	descDepth.Usage = D3D11_USAGE_DEFAULT;
	descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	descDepth.CPUAccessFlags = 0;
	descDepth.MiscFlags = 0;

	ID3D11Texture2D* pDepthStencil;
	hr = md3dDevice->CreateTexture2D(&descDepth, NULL, &pDepthStencil);
	assert(SUCCEEDED(hr));

	// Create the depth stencil view
	D3D11_DEPTH_STENCIL_VIEW_DESC descDSV;
	ZeroMemory(&descDSV, sizeof(descDSV));
	descDSV.Format = descDepth.Format;
	descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2DMS;
	descDSV.Texture2D.MipSlice = 0;;

	hr = md3dDevice->CreateDepthStencilView(pDepthStencil, &descDSV, &mpDepthStencilView);
	assert(SUCCEEDED(hr));
	ReleaseAndDeleteCOMobject(pDepthStencil);
	//*/

	/**********************************************************/

	//md3dImmediateContext->OMSetRenderTargets(1, &mRenderTargetView, nullptr);  // to use without depth stencil
	md3dImmediateContext->OMSetRenderTargets(1, &mRenderTargetView, mpDepthStencilView);

	// Setup the viewport
	D3D11_VIEWPORT vp;
	vp.Width = (FLOAT)mClientWidth;
	vp.Height = (FLOAT)mClientHeight;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	md3dImmediateContext->RSSetViewports(1, &vp);
}

void DXApp::CalculateFrameStats()
{
	// Code computes the average frames per second, and also the 
	// average time it takes to render one frame.  These stats 
	// are appended to the window caption bar.

	static int frameCnt = 0;
	static float timeElapsed = 0.0f;

	frameCnt++;

	// Compute averages over one second period.
	if ((mTimer.TotalTime() - timeElapsed) >= 1.0f)
	{
		float fps = (float)frameCnt; // fps = frameCnt / 1
		float mspf = 1000.0f / fps;

		std::ostringstream outs;
		outs.precision(6);
		outs << mMainWndCaption << "    "
			<< "FPS: " << fps << "    "
			<< "Frame Time: " << mspf << " (ms)";
		SetWindowText(mhMainWnd, outs.str().c_str());

		// Reset for next average.
		frameCnt = 0;
		timeElapsed += 1.0f;
	}
}

void DXApp::FrameTick()
{
	mTimer.Tick();
	CalculateFrameStats();

	this->UpdateScene();
	this->DrawScene();
}

void DXApp::OnMouseDown(WPARAM btnState, int xval, int yval)
{
	UNREFERENCED_PARAMETER(btnState);
	UNREFERENCED_PARAMETER(xval);
	UNREFERENCED_PARAMETER(yval);
}

void DXApp::OnMouseUp(WPARAM btnState, int xval, int yval)
{
	UNREFERENCED_PARAMETER(btnState);
	UNREFERENCED_PARAMETER(xval);
	UNREFERENCED_PARAMETER(yval);
}

void DXApp::OnMouseMove(WPARAM btnState, int xval, int yval)
{
	UNREFERENCED_PARAMETER(btnState);
	UNREFERENCED_PARAMETER(xval);
	UNREFERENCED_PARAMETER(yval);
}

void  DXApp::OnMouseWheel(short delta)
{
	UNREFERENCED_PARAMETER(delta);
}


// Shader loading utility. Will be moved elsewhere later...
// Needs to be moved. Requires
HRESULT DXApp::CompileShaderFromFile(WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut)
{
	HRESULT hr = S_OK;

	DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#ifdef _DEBUG
	// Set the D3DCOMPILE_DEBUG flag to embed debug information in the shaders.
	// Setting this flag improves the shader debugging experience, but still allows 
	// the shaders to be optimized and to run exactly the way they will run in 
	// the release configuration of this program.
	dwShaderFlags |= D3DCOMPILE_DEBUG;

	// Disable optimizations to further improve shader debugging
	dwShaderFlags |= D3DCOMPILE_SKIP_OPTIMIZATION;
#endif

	ID3DBlob* pErrorBlob = nullptr;
	hr = D3DCompileFromFile(szFileName, nullptr, nullptr, szEntryPoint, szShaderModel, dwShaderFlags, 0, ppBlobOut, &pErrorBlob);
	if (FAILED(hr))
	{
		if (pErrorBlob)
		{
			OutputDebugStringA(reinterpret_cast<const char*>(pErrorBlob->GetBufferPointer()));
			pErrorBlob->Release();
		}
		return hr;
	}
	if (pErrorBlob) pErrorBlob->Release();

	return S_OK;
}