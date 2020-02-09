#include "Model.hpp"

namespace mf
{
	namespace OBJParser
	{
		e_status	ParseLine(std::string &line, t_data *data)
		{
			if (line.find("v ", 0, 2) != std::string::npos)
				return (ReadVertex(line, data));
			if (line.find("o ", 0, 2) != std::string::npos)
				return (e_status::FAIL);
			if (line.find("mtllib ", 0, 7) != std::string::npos)
				return (e_status::FAIL);
			if (line.find("vn ", 0, 3) != std::string::npos)
				return (e_status::FAIL);
			if (line.find("vt ", 0, 3) != std::string::npos)
				return (e_status::FAIL);
			if (line.find("usemtl ", 0, 7) != std::string::npos)
				return (e_status::FAIL);
			if (line.find("f ", 0, 2) != std::string::npos)
				return (e_status::FAIL);
			
			return (e_status::OK);
		}

		e_status	ReadVertex(std::string &line, t_data *data)
		{
			glm::vec3	vector;

			sscanf(line.c_str(), "v %f %f %f", &vector.x, &vector.y, &vector.z);
			data->mVertices.push_back(vector.x);
			data->mVertices.push_back(vector.y);
			data->mVertices.push_back(vector.z);
			//std::cout << "Vertex: " << vector.x << " " << vector.y << " " << vector.z << std::endl;
			return (e_status::OK);
		}
	} // namespace OBJParser
	
} // namespace mf
