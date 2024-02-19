#include "TerrainModel.h"
#include "Model.h"
#include "d3dUtil.h"
#include "DirectXTex.h"
#include <assert.h>


TerrainModel::TerrainModel(ID3D11Device* dev, LPCWSTR heightmapFile, float len, float maxheight, float ytrans, int RepeatU, int RepeatV)
{
	DirectX::ScratchImage scrtTex;
	HRESULT hr = LoadFromTGAFile(heightmapFile, nullptr, scrtTex);
	assert(SUCCEEDED(hr));

	const DirectX::Image* hgtmap = scrtTex.GetImage(0, 0, 0);
	assert(hgtmap->height == hgtmap->width);

	size_t side = hgtmap->height;	// the image should be square
	size_t pixel_width = 4;			// 4 bytes RGBA per pixel
	//uint8_t h_val = hgtmap->pixels[ pixel_width * (5 * side + 3) ]; // the 'R' byte of the pixel at (3,5)

	uint8_t h_val; // out of 255

	// ** much work to add below **
	int nverts = side * side;
	StandardVertex* pVerts = new StandardVertex[nverts];

	int ntri = (side - 1) * (side - 1) * 2;
	TriangleByIndex* pTriList = new TriangleByIndex[ntri];

	float step = 1.0f / (side - 1);
	float uStep = step * RepeatU;
	float vStep = step * RepeatV;
	float x = 0.5f;
	float z = 0.5f;
	int index = 0;
	float u = 0;
	float v = 0;

	// construct vertices
	for (int i = 0; i < side; i++)
	{
		for (int j = 0; j < side; j++)
		{
			h_val = hgtmap->pixels[TexelIndex(side, j, i)];
			pVerts[index].set(x * len, ytrans + h_val / 255.0f * maxheight, z * len, u, v);
			x -= step;
			u += uStep;
			index++;
		}
		x = 0.5f;
		u = 0;
		z -= step;
		v += vStep;
	}

	index = 0;

	// triangles
	int t = 0;
	for (int i = 0; i < side - 1; i++)
	{
		for (int j = 0; j < side - 1; j++)
		{
			pTriList[index].set(t, t + side, t + 1);
			index++;
			pTriList[index].set(t + 1, t + side, t + side + 1);
			index++;
			t++;
		}
		t++;
	}

	pModTerrain = new Model(dev, pVerts, nverts, pTriList, ntri);
	delete[] pVerts;
	delete[] pTriList;
}

int TerrainModel::TexelIndex(int side, int i, int j) const
{
	return 4 * (j * side + i);
}
TerrainModel::~TerrainModel()
{
	delete pModTerrain;
}

void TerrainModel::Render(ID3D11DeviceContext* context)
{
	pModTerrain->SetToContext(context);
	pModTerrain->Render(context);
}