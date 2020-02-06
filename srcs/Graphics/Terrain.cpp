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
	CalculateNormals();
	initMesh();
}

void		Terrain::CalculateNormals()
{
	int i = 0;

	while (i < mLength * mWidth)
	{
		int x = (i % mWidth);
		int y = (i / mWidth);
		glm::vec3	AA = glm::vec3(x, GetHeightAt(x, y), y);
		glm::vec3	BB = glm::vec3(x, GetHeightAt(x, y - 1), y - 1);
		glm::vec3	CC = glm::vec3(x + 1, GetHeightAt(x + 1, y), y);
		glm::vec3	DD = glm::vec3(x, GetHeightAt(x, y + 1), y + 1);
		glm::vec3	EE = glm::vec3(x - 1, GetHeightAt(x - 1, y), y);
		glm::vec3	normal = glm::cross(BB - AA, CC - AA);
		normal += glm::cross(DD - AA, CC - AA);
		normal += glm::cross(EE - AA, DD - AA);
		normal += glm::cross(BB - AA, EE - AA);
		normal = glm::normalize(normal);
		mNormals.get()[(i * 3)] = normal.x;
		mNormals.get()[(i * 3) + 1] = normal.y;
		mNormals.get()[(i * 3) + 2] = normal.z;
		i += 1;
		//std::cout << " X: " << normal.x << "  Y: " << normal.y << "  Z: " << normal.z <<  std::endl;
	}
}

float		Terrain::GetHeightAt(int x, int z)
{
	
	
	glm::vec4 tmp = glm::vec4(mVertices.get()[(((z * mWidth) + (x)) * 3)], mVertices.get()[(((z * mWidth) + (x)) * 3) + 1], mVertices.get()[(((z * mWidth) + (x)) * 3) + 2], 1.0);
	tmp = mTransform * tmp;
	//return mVertices.get()[(((z * mWidth) + (x)) * 3) + 1];
	return (tmp.y);
}

float		Terrain::GetHeightInWorld(float x, float z)
{
	glm::vec4 pos = glm::inverse(mTransform) * glm::vec4(x, 1.0, z, 1.0);
	glm::vec4 tmppos = pos;
	pos.x += (mWidth / 2.0);
	pos.z += (mLength / 2.0);
	pos.x = (int)std::clamp(pos.x, 0.f, mWidth - 1.f);
	pos.z = (int)std::clamp(pos.z, 0.f, mLength - 1.f);
	glm::vec4 A = glm::vec4(mVertices.get()[(int)(((pos.z * mWidth) + (pos.x)) * 3)], mVertices.get()[(int)(((pos.z * mWidth) + (pos.x)) * 3) + 1], mVertices.get()[(int)(((pos.z * mWidth) + (pos.x)) * 3) + 2], 1.0f);
	glm::vec4 B = glm::vec4(mVertices.get()[(int)(((pos.z * mWidth) + (pos.x + 1)) * 3)], mVertices.get()[(int)(((pos.z * mWidth) + (pos.x + 1)) * 3) + 1], mVertices.get()[(int)(((pos.z * mWidth) + (pos.x + 1)) * 3) + 2], 1.0f);
	glm::vec4 C = glm::vec4(mVertices.get()[(int)((((pos.z + 1) * mWidth) + (pos.x + 1)) * 3)], mVertices.get()[(int)((((pos.z + 1) * mWidth) + (pos.x + 1)) * 3) + 1], mVertices.get()[(int)((((pos.z + 1) * mWidth) + (pos.x + 1)) * 3) + 2], 1.0f);
	glm::vec4 D = glm::vec4(mVertices.get()[(int)((((pos.z + 1) * mWidth) + (pos.x)) * 3)], mVertices.get()[(int)((((pos.z + 1) * mWidth) + (pos.x)) * 3) + 1], mVertices.get()[(int)((((pos.z + 1) * mWidth) + (pos.x)) * 3) + 2], 1.0f);
	glm::vec4 height = glm::vec4(0.f, 0.f, 0.f, 1.f);
	if ((pos.x / mWidth) + (pos.z / mLength) > 1)
	{
		//lower triangle
		height.y = mf::utils::BarryCentric(A, B, D, glm::vec2(tmppos.x, tmppos.z));
	}
	else
	{
		//upper triangle
		height.y = mf::utils::BarryCentric(D, B, C, glm::vec2(tmppos.x, tmppos.z));
	}
	return ((mTransform * height).y);
}


} // namespace mf
