#pragma once

#include "Mesh.hpp"
#include <random>

namespace mf
{

class Terrain : public Mesh
{
private:
	int			mWidth;
	int			mLength;

	void		InitTerrain();

public:
	Terrain(int width, int length);
	~Terrain();

	void		Randomize(int seed, float lower, float higher);
};

}
