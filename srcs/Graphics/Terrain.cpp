#include "Terrain.hpp"

namespace mf
{

Terrain::Terrain(int width, int length)
{
	mVertices = new float[width * length * 3];
	mVerticeSize = sizeof(float) * width * length * 3;
	mIndices = new unsigned int[(width - 1) * 2 * (length - 1) * 3];
	mIndiceSize = sizeof(unsigned int) * (width - 1) * 2 * (length - 1) * 3;
	mWidth = width;
	mLength = length;
	InitTerrain();
	initMesh();
}

Terrain::~Terrain()
{
}

void		Terrain::InitTerrain()
{
	int i = 0, j = 0;

	while (i < mLength * mWidth * 3)
	{
		mVertices[i] = ((i / 3) % (mWidth)) - (mWidth / 2);
		mVertices[i + 2] = ((i / 3) / mWidth) - (mLength / 2);
		mVertices[i + 1] = 0.0f;
		i += 3;
	}
	i = 0;
	j = 0;
	while (i < (mWidth - 1) * 2 * (mLength - 1) * 3)
	{
		mIndices[i] = j;
		mIndices[i + 1] = j + mWidth;
		mIndices[i + 2] = j + 1 + mWidth;
		mIndices[i + 3] = j;
		mIndices[i + 4] = j + 1 + mWidth;
		mIndices[i + 5] = j + 1;
		i += 6;
		j += 1;
		if (!((i / 6) % (mWidth - 1)))
			j++;
	}
}

void		Terrain::Randomize(int seed, float lower, float higher)
{
	int i = 0;
	srand(seed);
	while (i < mLength * mWidth * 3)
	{
		mVertices[i + 1] = (float)(rand() % (int)(higher - lower)) / 100.0f + (lower / 100.0f);
		i += 3;
	}
	initMesh();
}

void		Terrain::GenHeightMap()
{
	noise::module::Perlin				perlin;
	noise::utils::NoiseMap				map;
	noise::utils::NoiseMapBuilderPlane	plane;
	int i = 0;

	plane.SetSourceModule(perlin);
	plane.SetDestNoiseMap(map);
	plane.SetDestSize(mWidth, mLength);
	plane.SetBounds(2.0, 4.0, 1.0, 3.0);
	plane.Build();
	while (i < mLength * mWidth * 3)
	{
		mVertices[i + 1] = map.GetValue(mVertices[i] + (mWidth / 2), mVertices[i + 2] + (mLength / 2)) * 10.0;
		i += 3;
	}
	initMesh();
}

} // namespace mf
