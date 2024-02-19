#ifndef _ShaderTexture
#define _ShaderTexture

#include "ShaderBase.h"
#include "Matrix.h"
#include "Texture.h"

struct ID3D11Buffer;
struct ID3D11Device;

class ShaderTexture : public ShaderBase
{
public:
	ShaderTexture(ID3D11Device* device);

	virtual void SetToContext(ID3D11DeviceContext* devcon) override;

	void SetTextureResourceAndSampler(Texture* tex);
	void SendCamMatrices(const Matrix& view, const Matrix& proj);
	void SendWorld(const Matrix& world);

	~ShaderTexture();

private:
	// add your own material
	ID3D11Buffer* mpcbViewProj;
	struct ViewProjData
	{
		Matrix mView;
		Matrix mProj;
	};

	ID3D11Buffer* mpcbWorld;
	struct WorldData
	{
		Matrix World;
	};
};

#endif _ShaderTexture