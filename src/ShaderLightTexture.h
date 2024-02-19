
#ifndef _ShaderLightTexture
#define _ShaderLightTexture

#include "ShaderBase.h"
#include "Matrix.h"
#include "Texture.h"

struct ID3D11Buffer;
struct ID3D11Device;

class ShaderLightTexture : public ShaderBase
{

public:
	ShaderLightTexture(const ShaderLightTexture&) = delete;				 // Copy constructor
	ShaderLightTexture(ShaderLightTexture&&) = default;                    // Move constructor
	ShaderLightTexture& operator=(const ShaderLightTexture&) & = default;  // Copy assignment operator
	ShaderLightTexture& operator=(ShaderLightTexture&&) & = default;       // Move assignment operator
	~ShaderLightTexture();		  							         // Destructor

	ShaderLightTexture(ID3D11Device* device);

	virtual void SetToContext(ID3D11DeviceContext* devcon) override;

	void SetDirectionalLightParameters(const Vect& dir, const Vect& amb = Vect(1, 1, 1), const Vect& dif = Vect(1, 1, 1), const Vect& sp = Vect(1, 1, 1));
	void SetPointLightParameters(const Vect& pos, float r, const Vect& att, const Vect& amb = Vect(1, 1, 1), const Vect& dif = Vect(1, 1, 1), const Vect& sp = Vect(1, 1, 1));
	void SetSpotLightParameters(int num, const Vect& pos, float r, const Vect& att, const Vect& dir, float spotExp, const Vect& amb = Vect(1, 1, 1), const Vect& dif = Vect(1, 1, 1), const Vect& sp = Vect(1, 1, 1));

	void SendCamMatrices(const Matrix& view, const Matrix& proj);
	void SendLightParameters(const Vect& eyepos);
	void SendWorldAndMaterial(const Matrix& world, const Vect& amb = Vect(.5f, .5f, .5f), const Vect& dif = Vect(.5f, .5f, .5f), const Vect& sp = Vect(.5f, .5f, .5f));
	void SendFog(float fogstart = 25.0f, float fogrange = 30.0f, const Vect& fogcolor = Vect(0,0,0));

	void SetTextureResourceAndSampler(Texture* tex);
private:
	struct Material
	{
		Vect Ambient;
		Vect Diffuse;
		Vect Specular;
	};

	struct PhongADS
	{
		Vect Ambient;
		Vect Diffuse;
		Vect Specular;
	};



	struct DirectionalLight
	{
		PhongADS Light;
		Vect Direction;
	};

	DirectionalLight DirLightData;

	struct PointLight
	{
		PhongADS Light;
		Vect Position;
		Vect Attenuation;
		float Range;
	};

	PointLight PointLightData;

	struct SpotLight
	{
		PhongADS Light;
		Vect Position;
		Vect Attenuation;
		Vect Direction;
		float SpotExp;
		float Range;
	};

	SpotLight SpotLightData[3];

	struct CamMatrices
	{
		Matrix View;
		Matrix Projection;
	};

	ID3D11Buffer* mpBufferCamMatrices;

	struct Data_WorldAndMaterial
	{
		Matrix World;
		Matrix WorlInv;
		Material Mat;
	};

	ID3D11Buffer* mpBuffWordAndMaterial;

	struct Data_LightParams
	{
		DirectionalLight DirLight;
		PointLight PntLight;
		SpotLight SptLight[3];
		Vect EyePosWorld;
	};

	ID3D11Buffer* mpBufferLightParams;

	struct FogData
	{
		float FogStart;
		float FogRange;
		Vect FogColor;
	};

	ID3D11Buffer* mpBufferFogData;
};

#endif _ShaderLightTexture

