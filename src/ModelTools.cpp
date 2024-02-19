#include "ModelTools.h"
//#include "Enum.h"
//#include <math.h>
#include "Matrix.h"
#include <assert.h>
#include "Model.h"
#include "d3dUtil.h"


/// Creates the unit box centered at the origin
void ModelTools::CreateUnitBox(StandardVertex *&pVerts, int& nverts, TriangleByIndex *&pTriList, int& ntri)
{
	nverts = 8;
	pVerts = new StandardVertex[nverts];
	ntri = 12;
	pTriList = new TriangleByIndex[ntri];

	pVerts[0].set(-0.5f, -0.5f, -0.5f, Colors::Black);
	pVerts[1].set(-0.5f, +0.5f, -0.5f, Colors::Lime);
	pVerts[2].set(+0.5f, +0.5f, -0.5f, Colors::Yellow);
	pVerts[3].set(+0.5f, -0.5f, -0.5f, Colors::Red );
	pVerts[4].set(-0.5f, -0.5f, +0.5f, Colors::Blue);
	pVerts[5].set(-0.5f, +0.5f, +0.5f, Colors::Cyan);
	pVerts[6].set(+0.5f, +0.5f, +0.5f, Colors::White);
	pVerts[7].set(+0.5f, -0.5f, +0.5f, Colors::Magenta);

	// back face
	pTriList[0].set(0, 1, 2);
	pTriList[1].set(0, 2, 3);

	// front face
	pTriList[2].set(4, 6, 5);
	pTriList[3].set(4, 7, 6);

	// left face
	pTriList[4].set(4, 5, 1);
	pTriList[5].set(4, 1, 0);

	// right face
	pTriList[6].set(3, 2, 6);
	pTriList[7].set(3, 6, 7);

	// top face
	pTriList[8].set(1, 5, 6);
	pTriList[9].set(1, 6, 2);

	// bottom face
	pTriList[10].set(4, 0, 3);
	pTriList[11].set(4, 3, 7);
}

void ModelTools::CreateUnitBoxRepTexture(StandardVertex *&pVerts, int& nverts, TriangleByIndex *&pTriList, int& ntri)
{
	nverts = 24;
	pVerts = new StandardVertex[nverts];
	ntri = 12;
	pTriList = new TriangleByIndex[ntri];



	// Setting up faces
	// Forward
	int vind = 0;
	int tind = 0;
	pVerts[vind].set(0.5f, 0.5f, 0.5f, 1, 0, 0, 0, 1 );
	pVerts[vind + 1].set(-0.5f, 0.5f, 0.5f, 0, 0, 0, 0, 1);
	pVerts[vind + 2].set(-0.5f, -0.5f, 0.5f, 0, 1, 0, 0, 1);
	pVerts[vind + 3].set(0.5f, -0.5f, 0.5f, 1, 1, 0, 0, 1);
	pTriList[tind].set(vind, vind + 1, vind + 2);
	pTriList[tind + 1].set(vind, vind + 2, vind + 3);

	// Back
	vind += 4;
	tind += 2;
	pVerts[vind].set(0.5f, 0.5f, -0.5f, 0, 0, 0, 0, -1);
	pVerts[vind + 1].set(-0.5f, 0.5f, -0.5f, 1, 0, 0, 0, -1);
	pVerts[vind + 2].set(-0.5f, -0.5f, -0.5f, 1, 1, 0, 0, -1);
	pVerts[vind + 3].set(0.5f, -0.5f, -0.5f, 0, 1, 0, 0, -1);
	pTriList[tind].set(vind + 2, vind + 1, vind);
	pTriList[tind + 1].set(vind + 3, vind + 2, vind);

	// Left
	vind += 4;
	tind += 2;
	pVerts[vind].set(0.5f, 0.5f, -0.5f, 1, 0, 1, 0, 0);
	pVerts[vind + 1].set(0.5f, 0.5f, 0.5f, 0, 0, 1, 0, 0);
	pVerts[vind + 2].set(0.5f, -0.5f, 0.5f, 0, 1, 1, 0, 0);
	pVerts[vind + 3].set(0.5f, -0.5f, -0.5f, 1, 1, 1, 0, 0);
	pTriList[tind].set(vind, vind + 1, vind + 2);
	pTriList[tind + 1].set(vind, vind + 2, vind + 3);

	// Right
	vind += 4;
	tind += 2;
	pVerts[vind].set(-0.5f, 0.5f, 0.5f, 1, 0, -1, 0, 0);
	pVerts[vind + 1].set(-0.5f, 0.5f, -0.5f, 0, 0, -1, 0, 0);
	pVerts[vind + 2].set(-0.5f, -0.5f, -0.5f, 0, 1, -1, 0, 0);
	pVerts[vind + 3].set(-0.5f, -0.5f, 0.5f, 1, 1, -1, 0, 0);
	pTriList[tind].set(vind, vind + 1, vind + 2);
	pTriList[tind + 1].set(vind, vind + 2, vind + 3);

	// Top
	vind += 4;
	tind += 2;
	pVerts[vind].set(0.5f, 0.5f, -0.5f, 1, 0, 0, 1, 0);
	pVerts[vind + 1].set(-0.5f, 0.5f, -0.5f, 0, 0, 0, 1, 0);
	pVerts[vind + 2].set(-0.5f, 0.5f, 0.5f, 0, 1, 0, 1, 0);
	pVerts[vind + 3].set(0.5f, 0.5f, 0.5f, 1, 1, 0, 1, 0);
	pTriList[tind].set(vind, vind + 1, vind + 2);
	pTriList[tind + 1].set(vind, vind + 2, vind + 3);

	// Bottom
	vind += 4;
	tind += 2;
	pVerts[vind].set(0.5f, -0.5f, 0.5f, 1, 0, 0, -1, 0);
	pVerts[vind + 1].set(-0.5f, -0.5f, 0.5f, 0, 0, 0, -1, 0);
	pVerts[vind + 2].set(-0.5f, -0.5f, -0.5f, 0, 1, 0, -1, 0);
	pVerts[vind + 3].set(0.5f, -0.5f, -0.5f, 1, 1, 0, -1, 0);
	pTriList[tind].set(vind, vind + 1, vind + 2);
	pTriList[tind + 1].set(vind, vind + 2, vind + 3);
}

void ModelTools::CreateUnitPyramidRepeatedTexture(StandardVertex*& pVerts, int& nverts, TriangleByIndex*& pTriList, int& ntri)
{
	nverts = 13;
	pVerts = new StandardVertex[nverts];
	ntri = 6;
	pTriList = new TriangleByIndex[ntri];

	// front face
	pVerts[0].set(-0.5f, 0.0f, 0.5f, 0, 1);
	pVerts[1].set(0.5f, 0.0f, 0.5f, 1, 1);
	pVerts[2].set(0.0f, 1.0f, 0.0f, 0.5f, 0);
	pTriList[0].set(0, 1, 2);

	// left face
	pVerts[3].set(-0.5f, 0.0f, -0.5f, 0, 1);
	pVerts[4].set(-0.5f, 0.0f, 0.5f, 1, 1);

	pTriList[1].set(3, 4, 2);

	// right face
	pVerts[5].set(0.5f, 0.0f, 0.5f, 0, 1);
	pVerts[6].set(0.5f, 0.0f, -0.5f, 1, 1);

	pTriList[2].set(5, 6, 2);

	// back face
	pVerts[7].set(0.5f, 0.0f, -0.5f, 0, 1);
	pVerts[8].set(-0.5f, 0.0f, -0.5f, 1, 1);
	pTriList[3].set(7, 8, 2);

	// bottom faces
	pVerts[9].set(0.5f, 0.0f, 0.5f, 1, 1);
	pVerts[10].set(-0.5f, 0.0f, 0.5f, 1, 0);
	pVerts[11].set(-0.5f, 0.0f, -0.5f, 0, 0);
	pVerts[12].set(0.5f, 0.0f, -0.5f, 0, 1);
	pTriList[4].set(9, 10, 11);
	pTriList[5].set(9, 11, 12);
}

void ModelTools::CreateUnitPyramid(StandardVertex*& pVerts, int& nverts, TriangleByIndex*& pTriList, int& ntri)
{
	nverts = 16;
	pVerts = new StandardVertex[nverts];
	ntri = 12;
	pTriList = new TriangleByIndex[ntri];

	// front tri
	int vind = 0;
	int tind = 0;
	Vect n = Vect(0, 0.5, 1);
	pVerts[vind].set(-0.5f, 0.0f, 0.5f, n, Colors::Lime);
	pVerts[vind + 1].set(0.5f, 0.0f, 0.5f, n, Colors::Yellow);
	pVerts[vind + 2].set(0.0f, 1.0f, 0.0f, n, Colors::Cyan);
	pTriList[tind].set(vind, vind + 1, vind + 2);

	// left tri
	vind += 3;
	tind += 1;
	n = Vect(-1, 0.5, 0);
	pVerts[vind].set(-0.5f, 0.0f, -0.5f, n, Colors::Red);
	pVerts[vind + 1].set(-0.5f, 0.0f, 0.5f, n, Colors::Lime);
	pVerts[vind + 2].set(0.0f, 1.0f, 0.0f, n, Colors::Cyan);
	pTriList[tind].set(vind, vind + 1, vind + 2);

	// right tri
	vind += 3;
	tind += 1;
	n = Vect(1, 0.5, 0);
	pVerts[vind].set(0.5f, 0.0f, 0.5f, n, Colors::Yellow);
	pVerts[vind + 1].set(0.5f, 0.0f, -0.5f, n, Colors::Blue);
	pVerts[vind + 2].set(0.0f, 1.0f, 0.0f, n, Colors::Cyan);
	pTriList[tind].set(vind, vind + 1, vind + 2);

	// back tri
	vind += 3;
	tind += 1;
	n = Vect(0, 0.5, -1);
	pVerts[vind].set(0.5f, 0.0f, -0.5f, n, Colors::Blue);
	pVerts[vind + 1].set(-0.5f, 0.0f, -0.5f, n, Colors::Red);
	pVerts[vind + 2].set(0.0f, 1.0f, 0.0f, n, Colors::Cyan);
	pTriList[tind].set(vind, vind + 1, vind + 2);

	// bottom
	vind += 3;
	tind += 1;
	pVerts[vind].set(0.5f, 0.0f, 0.5f, n, Colors::Yellow);
	pVerts[vind + 1].set(-0.5f, 0.0f, 0.5f, n, Colors::Lime);
	pVerts[vind + 2].set(-0.5f, 0.0f, -0.5f, n, Colors::Red);
	pVerts[vind + 3].set(0.5f, 0.0f, -0.5f, n, Colors::Blue);
	pTriList[tind].set(vind, vind + 1, vind + 2);
	pTriList[tind + 1].set(vind, vind + 2, vind + 3);
}

void ModelTools::CreateUnitSphere(int vslice, int hslice, StandardVertex*& pVerts, int& nverts, TriangleByIndex*& pTriList, int& ntri)
{
	nverts = vslice * hslice + 2;
	pVerts = new StandardVertex[nverts];

	float verticalSeparation = 1.0f / (vslice + 1) * 2.0f;
	float halfway = hslice / 2.0f;
	float verticalPos = 1.0f;

	int vertNum = 0;
	int triNum = 0;

	pVerts[vertNum].set(0.0f, 1.0f, 0.0f);
	vertNum += 1;

	for (int i = 0; i < vslice; i++)
	{
		verticalPos -= verticalSeparation;
		float HorizontalPos = sqrtf(1 - verticalPos * verticalPos);

		for (int j = 0; j < hslice; j++)
		{
			Vect normal = Vect(cosf(MATH_PI * j / halfway) * HorizontalPos, verticalPos, sinf(MATH_PI * j / halfway) * HorizontalPos);
			pVerts[vertNum].set(cosf(MATH_PI * j / halfway) * HorizontalPos, verticalPos, sinf(MATH_PI * j / halfway) * HorizontalPos,
				normal, Colors::AliceBlue);
			vertNum++;
		}
	}

	pVerts[vertNum].set(0.0f, -1.0f, 0.0f);
	vertNum += 1;

	ntri = hslice * vslice * 2;
	pTriList = new TriangleByIndex[ntri];

	// top triangles
	for (int i = 0; i < hslice - 1; i++)
	{
		pTriList[triNum].set(i + 2, i + 1, 0);
		triNum++;
	}

	pTriList[triNum].set(hslice - triNum, hslice, 0);
	triNum++;

	// middle squares
	for (int i = 1; i < vslice; i++)
	{
		for (int j = 1; j < hslice; j++)
		{
			pTriList[triNum].set(i * hslice + j + 1, i * hslice + j, (i - 1) * hslice + j);
			triNum++;
			pTriList[triNum].set((i - 1) * hslice + j + 1, i * hslice + j + 1, (i - 1) * hslice + j);
			triNum++;
		}

		pTriList[triNum].set(i * hslice + 1, (i + 1) * hslice, i * hslice);
		triNum++;
		pTriList[triNum].set(i * hslice - hslice + 1, i * hslice + 1, i * hslice);
		triNum++;
	}

	// bottom triangles
	for (int i = 0; i < hslice - 1; i++)
	{
		pTriList[triNum].set(hslice * (vslice - 1) + i + 1, hslice * (vslice - 1) + i + 2, nverts - 1);
		triNum++;
	}

	pTriList[triNum].set(nverts - 2, nverts - hslice - 1, nverts - 1);

}

void ModelTools::CreateUnitBoxSixFacesTexture(StandardVertex*& pVerts, int& nverts, TriangleByIndex*& pTriList, int& ntri)
{
	nverts = 24;
	pVerts = new StandardVertex[nverts];
	ntri = 12;
	pTriList = new TriangleByIndex[ntri];

	// Setting up faces
	// Forward
	int vind = 0;
	int tind = 0;
	pVerts[vind].set(0.5f, 0.5f, 0.5f, 0.25f, 0.625f);
	pVerts[vind + 1].set(-0.5f, 0.5f, 0.5f, 0.25f, 0.375f);
	pVerts[vind + 2].set(-0.5f, -0.5f, 0.5f, 0.0f, 0.375f);
	pVerts[vind + 3].set(0.5f, -0.5f, 0.5f, 0.0f, 0.625f);
	pTriList[tind].set(vind, vind + 1, vind + 2);
	pTriList[tind + 1].set(vind, vind + 2, vind + 3);

	// Back
	vind += 4;
	tind += 2;
	pVerts[vind].set(0.5f, 0.5f, -0.5f, 0.5f, 0.625f);
	pVerts[vind + 1].set(-0.5f, 0.5f, -0.5f, 0.5f, 0.375f);
	pVerts[vind + 2].set(-0.5f, -0.5f, -0.5f, 0.75f, 0.375f);
	pVerts[vind + 3].set(0.5f, -0.5f, -0.5f, 0.75f, 0.625f);
	/*
	// used to demo texture address modes
	pVerts[vind].set(0.5f, 0.5f, -0.5f, -3, -3);
	pVerts[vind + 1].set(-0.5f, 0.5f, -0.5f, 3, -3);
	pVerts[vind + 2].set(-0.5f, -0.5f, -0.5f, 3, 3);
	pVerts[vind + 3].set(0.5f, -0.5f, -0.5f, -3, 3);
	//*/
	pTriList[tind].set(vind + 2, vind + 1, vind);
	pTriList[tind + 1].set(vind + 3, vind + 2, vind);

	// Left
	vind += 4;
	tind += 2;
	pVerts[vind].set(0.5f, 0.5f, -0.5f, 0.5f, 0.625f);
	pVerts[vind + 1].set(0.5f, 0.5f, 0.5f, 0.25f, 0.625f);
	pVerts[vind + 2].set(0.5f, -0.5f, 0.5f, 0.25f, 0.875f);
	pVerts[vind + 3].set(0.5f, -0.5f, -0.5f, 0.5f, 0.875f);
	pTriList[tind].set(vind, vind + 1, vind + 2);
	pTriList[tind + 1].set(vind, vind + 2, vind + 3);

	// Right
	vind += 4;
	tind += 2;
	pVerts[vind].set(-0.5f, 0.5f, 0.5f, 0.25f, 0.375f);
	pVerts[vind + 1].set(-0.5f, 0.5f, -0.5f, 0.5f, 0.375f);
	pVerts[vind + 2].set(-0.5f, -0.5f, -0.5f, 0.5f, 0.125f);
	pVerts[vind + 3].set(-0.5f, -0.5f, 0.5f, 0.25f, 0.125f);
	pTriList[tind].set(vind, vind + 1, vind + 2);
	pTriList[tind + 1].set(vind, vind + 2, vind + 3);

	// Top
	vind += 4;
	tind += 2;
	pVerts[vind].set(0.5f, 0.5f, -0.5f, 0.5f, 0.625f);
	pVerts[vind + 1].set(-0.5f, 0.5f, -0.5f, 0.5f, 0.375f);
	pVerts[vind + 2].set(-0.5f, 0.5f, 0.5f, 0.25f, 0.375f);
	pVerts[vind + 3].set(0.5f, 0.5f, 0.5f, 0.25f, 0.625f);
	pTriList[tind].set(vind, vind + 1, vind + 2);
	pTriList[tind + 1].set(vind, vind + 2, vind + 3);

	// Bottom
	vind += 4;
	tind += 2;
	pVerts[vind].set(0.5f, -0.5f, 0.5f, 1, 0.625f);
	pVerts[vind + 1].set(-0.5f, -0.5f, 0.5f, 1, 0.375f);
	pVerts[vind + 2].set(-0.5f, -0.5f, -0.5f, 0.75f, 0.375f);
	pVerts[vind + 3].set(0.5f, -0.5f, -0.5f, 0.75f, 0.625f);
	pTriList[tind].set(vind, vind + 1, vind + 2);
	pTriList[tind + 1].set(vind, vind + 2, vind + 3);
}