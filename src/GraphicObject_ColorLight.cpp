#include "GraphicObject_ColorLight.h"
#include "Model.h"
#include "ShaderColorLight.h"
#include <assert.h>

GraphicObject_ColorLight::GraphicObject_ColorLight(ShaderColorLight* shader, Model* mod)
{
	SetModel(mod);
	pShader = shader;
	World = Matrix(IDENTITY);

	int n = mod->GetMeshCount();
	MeshMaterial = new Material[n];
	for (int i = 0; i < n; i++)
	{
		MeshMaterial[i].Ambient = Vect(0, 0, 0);
		MeshMaterial[i].Diffuse = Vect(0, 0, 0);
		MeshMaterial[i].Specular = Vect(0, 0, 0);
	}
}

GraphicObject_ColorLight::~GraphicObject_ColorLight()
{
	delete[] MeshMaterial;
}

void GraphicObject_ColorLight::SetMaterial(const Vect& amb, const Vect& dif, const Vect& sp)
{
	mMaterial.Ambient = amb;
	mMaterial.Diffuse = dif;
	mMaterial.Specular = sp;
}

void GraphicObject_ColorLight::SetMaterial(const Vect& amb, const Vect& dif, const Vect& sp, int num)
{
	assert(pModel->ValidMeshNum(num));
	MeshMaterial[num].Ambient = amb;
	MeshMaterial[num].Diffuse = dif;
	MeshMaterial[num].Specular = sp;
}

void GraphicObject_ColorLight::SetWorld(const Matrix& m)
{
	World = m;
}

void GraphicObject_ColorLight::Render()
{
	pModel->SetToContext(pShader->GetContext());
	
	for (int i = 0; i < pModel->GetMeshCount(); i++)
	{
		pShader->SendWorldAndMaterial(World, MeshMaterial[i].Ambient, MeshMaterial[i].Diffuse, MeshMaterial[i].Specular);
		pModel->RenderMesh(pShader->GetContext(), i);
	}
	
}