#include "Model.hpp"

namespace mf
{
	Model::Model(/* args */)
	{
	}

	Model::Model(const Model &tModel)
	{
		for ( auto &i : tModel.mMeshes)
		{
			AddMesh(new Mesh(*i));
		}
	}

	Model::~Model()
	{
	}

	void	Model::SetProjectionMatrix(glm::mat4 projmat)
	{
		for (auto &i : mMeshes)
		{
			i->SetProjectionMatrix(projmat);
		}
	}

	void	Model::SetTransformMatrix(glm::mat4 transformmatrix)
	{
		for (auto &i : mMeshes)
		{
			i->SetTransformMatrix(transformmatrix);
		}
	}


	void	Model::SetViewMatrix(glm::mat4 viewmat)
	{
		for (auto &i : mMeshes)
		{
			i->SetViewMatrix(viewmat);
		}
	}

	void	Model::SetShaderProgram(Shader *shader)
	{
		for (auto &i : mMeshes)
		{
			i->SetShaderProgram(shader);
		}
	}

	void	Model::Draw(GLenum mode)
	{
		for (auto &i : mMeshes)
		{
			i->PrepareShader();
			i->Draw(mode);
		}
	}

	void	Model::AddMesh(Mesh *mesh)
	{
		mMeshes.push_back(mesh);
	}

	void	Model::LoadFromOBJ(std::string path, ResourceManager *tResourceManager)
	{
		std::ifstream		file(path, std::ios::in);
		std::string			line;
		OBJParser::t_data	data;

		if (!file)
		{
			std::cerr << "Failed to read" << path << std::endl;
			return ;
		}
		data.mRelPath = path.substr(0, path.find_last_of('/') + 1);
		std::cout << "REAL PATH: " << data.mRelPath << std::endl;
		while (std::getline(file, line))
		{
			switch (OBJParser::ParseLine(line, &data, this, tResourceManager))
			{
			case OBJParser::e_status::FAIL:
				break;
			case OBJParser::e_status::NEW_GROUP:
				break;
			default:
				break;
			};
		}
		if (data.mIndices.size() > 0)
			this->AddMesh(CreateMesh(&data, tResourceManager));
	}

	Model&	Model::operator=(Model tModel)
	{
		if (this != &tModel)
		{
			for ( auto &i : tModel.mMeshes)
			{
				AddMesh(new Mesh(*i));
			}
		}
		return (*this);
	}

} // namespace mf
