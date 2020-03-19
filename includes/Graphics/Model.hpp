#pragma once

#include "Mesh.hpp"
#include <fstream>
#include <sstream>

namespace mf
{
	class Model
	{
	private:
		std::vector<Mesh *>	mMeshes;

	public:
		Model();
		Model(const Model &tModel);
		~Model();

		void	SetProjectionMatrix(glm::mat4 projmat);
		void	SetViewMatrix(glm::mat4 viewmat);
		void	SetTransformMatrix(glm::mat4 transformmatrix);
		void	SetShaderProgram(Shader *shader);

		std::vector<Mesh *>	GetMeshes(){return (mMeshes);}

		void	AddMesh(Mesh *mesh);
		void	LoadFromOBJ(std::string path, ResourceManager *tResourceManager);

		void	Draw(GLenum mode);

		Model&	operator=(Model tModel);
	};

	namespace OBJParser
	{
		typedef struct					s_data
		{
			std::vector<float>			mVertices;
			std::vector<float>			mNormals;
			std::vector<float>			mTexCoords;
			std::vector<glm::uvec3>		mIndices;
			std::string					mMtlib;
			std::string					mGroupName;
			std::string					mRelPath;
			std::string					mMap_Ka;
			std::string					mMap_Kd;
			glm::vec3					mKa;
			glm::vec3					mKd;
			glm::vec3					mKs;
		}								t_data;

		enum class						e_status
		{
										OK,
										FAIL,
										NEW_GROUP
		};

		Mesh							*CreateMesh(t_data *data, ResourceManager *tResourceManager);
		e_status						ParseLine(std::string &line, t_data *data, Model *model, ResourceManager *tResourceManager);
		e_status						ReadVertex(std::string &line, t_data *data);
		e_status						ReadNormals(std::string &line, t_data *data);
		e_status						ReadTextureCoords(std::string &line, t_data *data);
		e_status						ReadGroupName(std::string &line, t_data *data);
		e_status						ReadMTLLIBPath(std::string &line, t_data *data);
		e_status						ReadMTL(std::string &line, t_data *data);
		e_status						ReadIndices(std::string &line, t_data *data);
	} // namespace OBJParser
} // namespace mf
