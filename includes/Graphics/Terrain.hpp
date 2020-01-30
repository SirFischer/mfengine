#pragma once

#include "Mesh.hpp"

#include <random>
#include <libnoise/noise.h>
#include <libnoise/misc.h>
#include "noiseutils.h"

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
	void		GenHeightMap(int seed, double xLow, double xHigh, double zLow, double zHigh);

	float		GetHeightAt(int x, int z);
};

}
