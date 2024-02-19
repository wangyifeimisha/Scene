#include "GraphicObject_Texture.h"
#include "Model.h"
#include "ShaderTexture.h"
#include <assert.h>

GraphicObject_Texture::GraphicObject_Texture(ShaderTexture* shader, Model* mod)
{
	SetModel(mod);
	pShader = shader;
	World = Matrix(IDENTITY);

	int n = mod->GetMeshCount();
	MeshTex = new Texture*[n];
}

GraphicObject_Texture::~GraphicObject_Texture()
{
	delete[] MeshTex;
}

void GraphicObject_Texture::SetTexture(Texture* tex)
{
	pTex = tex;
}

void GraphicObject_Texture::SetTexture(Texture* tex, int meshNum)
{
	assert(pModel->ValidMeshNum(meshNum));
	MeshTex[meshNum] = tex;
}

void GraphicObject_Texture::SetWorld(const Matrix& m)
{
	World = m;
}

void GraphicObject_Texture::Render()
{
	pShader->SendWorld(World);
	pModel->SetToContext(pShader->GetContext());

	for (int i = 0; i < pModel->GetMeshCount(); i++)
	{
		pShader->SetTextureResourceAndSampler(MeshTex[i]);
		pModel->RenderMesh(pShader->GetContext(), i);
	}
	
}