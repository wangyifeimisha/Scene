#include "ShaderTexture.h"
#include "d3dUtil.h"
#include <d3d11.h>
#include <assert.h>


ShaderTexture::ShaderTexture(ID3D11Device* device)
	: ShaderBase(device, L"../Assets/Shaders/Texture.hlsl")
{
	// Define the input layout
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 16, D3D11_INPUT_PER_VERTEX_DATA, 0}
	};
	UINT numElements = ARRAYSIZE(layout);
	this->CreateInputLayout(layout, numElements);

	HRESULT hr;

	// View Projection buffer
	D3D11_BUFFER_DESC bd;
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(ViewProjData);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;
	bd.StructureByteStride = 0;
	hr = this->GetDevice()->CreateBuffer(&bd, nullptr, &mpcbViewProj);
	assert(SUCCEEDED(hr));

	// Color buffer
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(WorldData);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;
	bd.StructureByteStride = 0;
	hr = this->GetDevice()->CreateBuffer(&bd, nullptr, &mpcbWorld);
	assert(SUCCEEDED(hr));

}

ShaderTexture::~ShaderTexture()
{
	ReleaseAndDeleteCOMobject(mpcbWorld);
	ReleaseAndDeleteCOMobject(mpcbViewProj);
}

void ShaderTexture::SetTextureResourceAndSampler(Texture* tex)
{
	tex->SetToContext(this->GetContext());
}

void ShaderTexture::SendCamMatrices(const Matrix& view, const Matrix& proj)
{
	ViewProjData mCamMatrices;
	mCamMatrices.mView = view;
	mCamMatrices.mProj = proj;

	this->GetContext()->UpdateSubresource(mpcbViewProj, 0, nullptr, &mCamMatrices, 0, 0);
}

void ShaderTexture::SendWorld(const Matrix& world)
{
	WorldData wd;
	wd.World = world;

	this->GetContext()->UpdateSubresource(mpcbWorld, 0, nullptr, &wd, 0, 0);
}

void ShaderTexture::SetToContext(ID3D11DeviceContext* devcon)
{
	ShaderBase::SetContext(devcon);
	ShaderBase::SetToContext_VS_PS_InputLayout();

	devcon->VSSetConstantBuffers(0, 1, &mpcbViewProj);
	devcon->VSSetConstantBuffers(1, 1, &mpcbWorld);
}
