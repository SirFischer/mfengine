#pragma once

#include "Mesh.hpp"
#include <fstream>

namespace mf
{
	namespace OBJParser
	{
		typedef struct					s_data
		{
			std::vector<float>			mVertices;
			std::vector<float>			mNormals;
			std::vector<float>			mTexCoords;
			std::vector<unsigned int>	mIndices;
			std::string					mMtlib;
		}								t_data;

		enum class						e_status
		{
										OK,
										FAIL,
										NEW_GROUP
		};

		e_status						ParseLine(std::string &line, t_data *data);
		e_status						ReadVertex(std::string &line, t_data *data);
	} // namespace OBJParser

	class Model
	{
	private:
		std::vector<Mesh>	mMeshes;

	public:
		Model();
		~Model();

		void	AddMesh(Mesh &mesh);
		void	LoadFromOBJ(std::string path);
	};
} // namespace mf
