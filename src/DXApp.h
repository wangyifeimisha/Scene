// DXApp
// Andre Berthiaume, June 2016
// Note: DX 11 SDK https://www.microsoft.com/en-us/download/details.aspx?id=6812
// Note on weird stuff with swap chain (1s and 2s) https://msdn.microsoft.com/en-us/library/windows/desktop/jj863687(v=vs.85).aspx

#ifndef _DXApp
#define _DXApp

#include <d3d11.h>
#include "d3dUtil.h"
#include "Align16.h"
#include "GameTimer.h"
#include <string>

// New includes for demo
#include "Vect.h"
#include "Matrix.h"
#include "Camera.h"
#include "ShaderColor.h"
#include "ShaderColorLight.h"
#include "ShaderTexture.h"
#include "ShaderLightTexture.h"
#include "SkyBox.h"
#include "TerrainModel.h"

class Model;
class Texture;
class FlatPlane;
class GraphicObject_Color;
class ShaderTexture;
class ShaderLightTexture;
class GraphicObject_Texture;
class GraphicObject_ColorLight;
class GraphicObject_TextureLight;

class DXApp : public Align16
{
private:	
	// Main window handle
	HWND      mhMainWnd;

	Vect BackgroundColor;
	int SyncInterval = 1;  // 1 for sync to refresh rate, 0 for no sync

	// DX application elements
	ID3D11Device* md3dDevice;					// Connects to the graphics card
	ID3D11DeviceContext* md3dImmediateContext;	// Settings for the GPU to use
	IDXGISwapChain* mSwapChain;					// image buffers used for rendering
	ID3D11RenderTargetView* mRenderTargetView;	// Where to send rendring operations (typically: points to one of the swap buffers)
	ID3D11DepthStencilView* mpDepthStencilView; // Needed to force depth-buffer operations

	GameTimer mTimer;
	std::string mMainWndCaption;
	int mClientWidth;
	int mClientHeight;

	void InitDirect3D();
	void InitDemo();
	void UpdateScene();
	void DrawScene();
	void CalculateFrameStats();

	// Shader loading utility. SHould be moved elsewhere later...
	HRESULT CompileShaderFromFile(WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut);

	// Debug utility
	void ReportLiveDXObjects();

	// Demo specific additions
	Camera mCam;

	SkyBox* pSkyBox;
	Texture* mTexSkyBox;
	Matrix mWorldSkyBox;

	TerrainModel* pTerrainModel;
	Texture* mTexTerrain;
	Matrix mWorldTerrain;
	
	Model* pModelSailShip;
	Texture* mTexSailShip;
	Matrix mWorldSailShip;

	Model* pModelCruiseShip;
	Texture* mTexCruiseShip;
	Matrix mWorldCruiseShip;
	
	Model* pModelFountain;
	Texture* mTexFountain;
	Matrix mWorldFountain;

	Model* pModelPrison;
	Texture* mTexPrison;
	Matrix mWorldPrison;

	Model* pModelTent;
	Texture* mTexTent;
	Matrix mWorldTent;

	Model* pModelLamp1;
	Texture* mTexLamp1;
	Matrix mWorldLamp1;

	Model* pModelLamp2;
	Texture* mTexLamp2;
	Matrix mWorldLamp2;

	Model* pModelTavern;
	Texture* mTexTavern;
	Matrix mWorldTavern;

	Model* pModelPremadeCube;
	Texture* mTexPremade;
	Matrix mWorldPremadeCube;

	Model* pModelPremadeSphere;
	Matrix mWorldPremadeSphere;

	GraphicObject_TextureLight* pGOCruiseShip;
	GraphicObject_TextureLight* pGOSailShip;
	GraphicObject_TextureLight* pGOFountain;
	GraphicObject_TextureLight* pGOLamp1;
	GraphicObject_TextureLight* pGOLamp2;
	GraphicObject_TextureLight* pGOPrison;
	GraphicObject_TextureLight* pGOTavern;
	GraphicObject_TextureLight* pGOTent;
	GraphicObject_TextureLight* pGOPremadeCube;
	GraphicObject_TextureLight* pGOPremadeSphere;
	
	Vect pos2;

	ShaderColor*			pShaderCol;
	ShaderColorLight*		pShaderColLight;
	ShaderLightTexture*		pShaderLightTex;

	GraphicObject_Texture*		GraphTexObj;
	GraphicObject_ColorLight*	GraphColLightObj;
	GraphicObject_TextureLight*	GraphTexLightObj;
	

public:
	DXApp(HWND hwnd);
	virtual ~DXApp();
	
	void FrameTick();

	// overrides for handling mouse input.
	void OnMouseDown(WPARAM btnState, int xval, int yval);
	void OnMouseUp(WPARAM btnState, int xval, int yval);
	void OnMouseMove(WPARAM btnState, int xval, int yval);
	void OnMouseWheel(short delta);


};

#endif _DXApp