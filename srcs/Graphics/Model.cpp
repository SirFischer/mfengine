#include "Model.hpp"

namespace mf
{
	Model::Model(/* args */)
	{
	}

	Model::~Model()
	{
	}

	void	Model::AddMesh(Mesh &mesh)
	{
		mMeshes.push_back(mesh);
	}

	void	Model::LoadFromOBJ(std::string path)
	{
		std::ifstream		file(path, std::ios::in);
		std::string			line;
		OBJParser::t_data	data;

		if (!file)
		{
			std::cerr << "Failed to read" << path << std::endl;
			return ;
		}
		while (std::getline(file, line))
		{
			switch (OBJParser::ParseLine(line, &data))
			{
			case OBJParser::e_status::FAIL:
				break;
			case OBJParser::e_status::NEW_GROUP:
				/* code */
				break;
			default:
				break;
			};
		}
	}

} // namespace mf
