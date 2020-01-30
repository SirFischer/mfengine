#include "Terrain.hpp"

namespace mf
{

Terrain::Terrain(int width, int length)
{
	try
	{
		mVertices = std::shared_ptr<float>( new float[width * length * 3]);
		mNormals = std::shared_ptr<float>( new float[width * length * 3]);
		mTextureCoords = std::shared_ptr<float>( new float[width * length * 2]);
		mIndices = std::shared_ptr<unsigned int>(new unsigned int[(width - 1) * 2 * (length - 1) * 3]);
	}
	catch(const std::exception& e)
	{
		std::cout << e.what() << '\n';
	}
	mVerticeSize = sizeof(float) * width * length * 3;
	mTextureCoordsSize = sizeof(float) * width * length * 2;
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
		mVertices.get()[i] = ((i / 3) % (mWidth)) - (mWidth / 2);
		mVertices.get()[i + 2] = ((i / 3) / mWidth) - (mLength / 2);
		mVertices.get()[i + 1] = 0.0f;
		mNormals.get()[i] = 0.0;
		mNormals.get()[i + 1] = 1.0;
		mNormals.get()[i + 2] = 0.0;
		i += 3;
	}
	i = 0;
	while (i < (mWidth - 1) * 2 * (mLength - 1) * 3)
	{
		mIndices.get()[i] = j;
		mIndices.get()[i + 1] = j + mWidth;
		mIndices.get()[i + 2] = j + 1 + mWidth;
		mIndices.get()[i + 3] = j;
		mIndices.get()[i + 4] = j + 1 + mWidth;
		mIndices.get()[i + 5] = j + 1;
		i += 6;
		j += 1;
		if (!((i / 6) % (mWidth - 1)))
			j++;
	}
	i = 0;
	while (i < mLength * mWidth * 2)
	{
		mTextureCoords.get()[i] = ((float)((i / 2) % mWidth) / (float)(mWidth)) * 10;
		mTextureCoords.get()[i + 1] = ((float)(i / (mWidth * 2)) / (float)(mLength)) * 10;
		i += 2;
	}
}

void		Terrain::Randomize(int seed, float lower, float higher)
{
	int i = 0;
	srand(seed);
	while (i < mLength * mWidth * 3)
	{
		mVertices.get()[i + 1] = (float)(rand() % (int)(higher - lower)) / 100.0f + (lower / 100.0f);
		i += 3;
	}
	initMesh();
}

void		Terrain::GenHeightMap(int seed, double xLow, double xHigh, double zLow, double zHigh)
{
	if (!mVertices || !mIndices)
	{
		throw std::exception();
		return ;
	}
	noise::module::Perlin				perlin;
	noise::utils::NoiseMap				map;
	noise::utils::NoiseMapBuilderPlane	plane;
	int i = 0;

	perlin.SetSeed(seed);
	plane.SetSourceModule(perlin);
	plane.SetDestNoiseMap(map);
	plane.SetDestSize(mWidth, mLength);
	plane.SetBounds(xLow, xHigh, zLow, zHigh);
	plane.Build();
	while (i < mLength * mWidth * 3)
	{
		mVertices.get()[i + 1] = map.GetValue(mVertices.get()[i] + (mWidth / 2), mVertices.get()[i + 2] + (mLength / 2));
		i += 3;
	}
	initMesh();
}

float		Terrain::GetHeightAt(int x, int z)
{
	x += (mWidth / 2);
	z += (mLength / 2);
	x = std::clamp(x, 0, mWidth - 1);
	z = std::clamp(z, 0, mLength - 1);
	return mVertices.get()[((z * mWidth * 3) + (x * 3) ) + 1];
}

} // namespace mf
