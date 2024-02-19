#include "GraphicObject_TextureLight.h"
#include "Model.h"
#include "ShaderLightTexture.h"
#include <assert.h>

GraphicObject_TextureLight::GraphicObject_TextureLight(ShaderLightTexture* shader, Model* mod)
{
	SetModel(mod);
	pShader = shader;
	World = Matrix(IDENTITY);

	int n = mod->GetMeshCount();
	MeshMaterial = new Material[n];
	MeshTex = new Texture * [n];
	for (int i = 0; i < n; i++)
	{
		MeshMaterial[i].Ambient = Vect(0, 0, 0);
		MeshMaterial[i].Diffuse = Vect(0, 0, 0);
		MeshMaterial[i].Specular = Vect(0, 0, 0);
	}
}

GraphicObject_TextureLight::~GraphicObject_TextureLight()
{
	delete[] MeshMaterial;
	delete[] MeshTex;
}

void GraphicObject_TextureLight::SetTexture(Texture* tex)
{
	pTex = tex;
}

void GraphicObject_TextureLight::SetMaterial(const Vect& amb, const Vect& dif, const Vect& sp)
{
	mMaterial.Ambient = amb;
	mMaterial.Diffuse = dif;
	mMaterial.Specular = sp;
}

void GraphicObject_TextureLight::SetMaterial(const Vect& amb, const Vect& dif, const Vect& sp, int num)
{
	assert(pModel->ValidMeshNum(num));
	MeshMaterial[num].Ambient = amb;
	MeshMaterial[num].Diffuse = dif;
	MeshMaterial[num].Specular = sp;
}

void GraphicObject_TextureLight::SetTexture(Texture* tex, int meshNum)
{
	assert(pModel->ValidMeshNum(meshNum));
	MeshTex[meshNum] = tex;
}

void GraphicObject_TextureLight::SetWorld(const Matrix& m)
{
	World = m;
}

void GraphicObject_TextureLight::Render()
{
	pModel->SetToContext(pShader->GetContext());
	for (int i = 0; i < pModel->GetMeshCount(); i++)
	{
		pShader->SetTextureResourceAndSampler(MeshTex[i]);
		pShader->SendWorldAndMaterial(World, MeshMaterial[i].Ambient, MeshMaterial[i].Diffuse, MeshMaterial[i].Specular);
		pModel->RenderMesh(pShader->GetContext(), i);
	}

}


void GraphicObject_TextureLight::SetDirectionalLightParameters(const Vect& dir, const Vect& amb, const Vect& dif, const Vect& sp)
{
	pShader->SetDirectionalLightParameters(dir, amb, dif, sp);
}
void GraphicObject_TextureLight::SetPointLightParameters(const Vect& pos, float r, const Vect& att, const Vect& amb, const Vect& dif, const Vect& sp, int count)
{
	pShader->SetPointLightParameters(pos, r, att, amb, dif, sp);
}
void GraphicObject_TextureLight::SetSpotLightParameters(int num, const Vect& pos, float r, const Vect& att, const Vect& dir, float spotExp, const Vect& amb, const Vect& dif, const Vect& sp, int count)
{
	pShader->SetSpotLightParameters(num, pos, r, att, dir, spotExp, amb, dif, sp);
}

void GraphicObject_TextureLight::SendCamMatrices(const Matrix& view, const Matrix& proj)
{
	pShader->SendCamMatrices(view, proj);
}
void GraphicObject_TextureLight::SendLightParameters(const Vect& eyepos)
{
	pShader->SendLightParameters(eyepos);
}
void GraphicObject_TextureLight::SendWorldAndMaterial(const Matrix& world, const Vect& amb, const Vect& dif, const Vect& sp)
{
	pShader->SendWorldAndMaterial(world, amb, dif, sp);

	for (int i = 0; i < pModel->GetMeshCount(); i++)
	{
		MeshMaterial[i].Ambient = amb;
		MeshMaterial[i].Diffuse = dif;
		MeshMaterial[i].Specular = sp;

	}
}

void GraphicObject_TextureLight::SendFogData(float start, float range, Vect c)
{
	pShader->SendFog(start, range, c);
}


void GraphicObject_TextureLight::SetToContext(ID3D11DeviceContext* devcon)
{
	pShader->SetToContext(devcon);
}