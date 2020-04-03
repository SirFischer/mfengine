#include "Model.hpp"

namespace mf
{
	namespace OBJParser
	{
		Mesh		*CreateMesh(t_data *data)
		{
			Mesh				*result;
			std::vector<float>	vertices;
			std::vector<float>	textureCoords;
			std::vector<float>	normals;

			for (auto &item : data->mIndices)
			{
				if ((int)item.x - 1 < 0 || (item.x - 1) * 3 >= data->mVertices.size())
					continue ;
				vertices.push_back(data->mVertices.at(((item.x - 1) * 3)));
				vertices.push_back(data->mVertices.at(((item.x - 1) * 3) + 1));
				vertices.push_back(data->mVertices.at(((item.x - 1) * 3) + 2));
				if (item.y != (glm::u32)-1 && (item.y - 1) * 2 < data->mTexCoords.size())
				{
					textureCoords.push_back(data->mTexCoords.at(((item.y - 1) * 2)));
					textureCoords.push_back(data->mTexCoords.at(((item.y - 1) * 2) + 1));
				}
				if (item.z != (glm::u32)-1 && (item.z - 1) * 3 < data->mNormals.size())
				{
					normals.push_back(data->mNormals.at(((item.z - 1) * 3)));
					normals.push_back(data->mNormals.at(((item.z - 1) * 3) + 1));
					normals.push_back(data->mNormals.at(((item.z - 1) * 3) + 2));
				}
					
			}
			if (!(result = new Mesh(vertices.data(), NULL, textureCoords.data(), normals.data(), vertices.size() * sizeof(float), 0, textureCoords.size() * sizeof(float), normals.size() * sizeof(float))))
				return (NULL);
			result->SetName(data->mGroupName);
			if (data->mMap_Kd != "")
				result->SetTexture(mf::ResourceManager::LoadImage(data->mRelPath + data->mMap_Kd));
			std::cout << "Loaded image: " + data->mRelPath + data->mMap_Kd << std::endl;
			result->SetAmbientLight(data->mKa);
			result->SetDiffuseLight(data->mKd);
			result->SetSpecularLight(data->mKs);
			result->SetShininess(data->mNs);
			//SET MTLLIB DATA
			data->mIndices.clear();
			return (result);
		}

		e_status	ParseLine(std::string &line, t_data *data, Model *model)
		{
			if (line.find("#", 0, 1) != std::string::npos)
				return (e_status::OK);
			if (line.find("v ", 0, 2) != std::string::npos)
				return (ReadVertex(line, data));
			if (line.find("o ", 0, 2) != std::string::npos)
				return (ReadGroupName(line, data));
			if (line.find("mtllib ", 0, 7) != std::string::npos)
				return (ReadMTLLIBPath(line, data));
			if (line.find("vn ", 0, 3) != std::string::npos)
				return (ReadNormals(line, data));
			if (line.find("vt ", 0, 3) != std::string::npos)
				return (ReadTextureCoords(line, data));
			if (line.find("usemtl ", 0, 7) != std::string::npos)
			{
				if (data->mIndices.size() > 0)
					model->AddMesh(CreateMesh(data));
				return (ReadMTL(line, data));
			}
			if (line.find("f ", 0, 2) != std::string::npos)
				return (ReadIndices(line, data));
			return (e_status::OK);
		}

		e_status	Read3Floats(std::string &line, glm::vec3 *vec)
		{
			sscanf(line.c_str(), "%f %f %f", &vec->x, &vec->y, &vec->z);
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

		e_status	ReadNormals(std::string &line, t_data *data)
		{
			glm::vec3	vector;

			sscanf(line.c_str(), "vn %f %f %f", &vector.x, &vector.y, &vector.z);
			data->mNormals.push_back(vector.x);
			data->mNormals.push_back(vector.y);
			data->mNormals.push_back(vector.z);
			//std::cout << "Normals: " << vector.x << " " << vector.y << " " << vector.z << std::endl;
			return (e_status::OK);
		}

		e_status	ReadTextureCoords(std::string &line, t_data *data)
		{
			glm::vec2	vector;

			sscanf(line.c_str(), "vt %f %f", &vector.x, &vector.y);
			data->mTexCoords.push_back(vector.x);
			data->mTexCoords.push_back(vector.y);
			//std::cout << "Texture Coords: " << vector.x << " " << vector.y << std::endl;
			return (e_status::OK);
		}

		e_status	ReadGroupName(std::string &line, t_data *data)
		{
			char *name = NULL;

			if (!(name = new char[line.length()]))
				return (e_status::FAIL);
			bzero(name, line.length());
			sscanf(line.c_str(), "o %s", name);
			data->mGroupName = name;
			//std::cout << name << std::endl;
			delete name;
			return (e_status::OK);
		}

		e_status	ReadMTLLIBPath(std::string &line, t_data *data)
		{
			char *path = NULL;

			if (!(path = new char[line.length()]))
				return (e_status::FAIL);
			bzero(path, line.length());
			sscanf(line.c_str(), "mtllib %s", path);
			std::ifstream	file(data->mRelPath + path);
			std::stringstream		b;
			b << file.rdbuf();
			data->mMtlib = b.str();
			delete path;
			return (e_status::OK);
		}

		e_status	ReadMTL(std::string &line, t_data *data)
		{
			char *name = NULL;

			if (!(name = new char[line.length()]))
				return (e_status::FAIL);
			bzero(name, line.length());
			sscanf(line.c_str(), "usemtl %s", name);
			std::istringstream stream(data->mMtlib.c_str() + data->mMtlib.find("newmtl " + std::string(name)));
			std::cout << name << std::endl;
			std::string		mtline;
			std::getline(stream, mtline);
			while (std::getline(stream, mtline) && mtline.find("newmtl ") == std::string::npos)
			{
				std::cout << "MTL: " << mtline << std::endl;
				if (mtline.find("map_Ka", 0, 6) != std::string::npos)
					data->mMap_Ka = mtline.substr(7);
				if (mtline.find("map_Kd", 0, 6) != std::string::npos)
					data->mMap_Kd = mtline.substr(7);
				if (mtline.find("Ka ", 0, 3) != std::string::npos)
					Read3Floats((mtline = mtline.substr(3)), &data->mKa);
				if (mtline.find("Kd ", 0, 3) != std::string::npos)
					Read3Floats((mtline = mtline.substr(3)), &data->mKd);
				if (mtline.find("Ks ", 0, 3) != std::string::npos)
					Read3Floats((mtline = mtline.substr(3)), &data->mKs);
				if (mtline.find("Ns ", 0, 3) != std::string::npos)
					sscanf((mtline = mtline.substr(3)).c_str(), "%f", &data->mNs);
			}
			delete name;
			return (e_status::NEW_GROUP);
		}

		e_status	ReadIndices(std::string &line, t_data *data)
		{
			char *tmp;
			glm::uvec3	first = glm::uvec3((unsigned int)-1, (unsigned int)-1, (unsigned int)-1);
			glm::uvec3	second = glm::uvec3((unsigned int)-1, (unsigned int)-1, (unsigned int)-1);
			glm::uvec3	vector;

			if (!(tmp = strdup(line.c_str())))
				return (e_status::FAIL);
			if (!(tmp = std::strtok((tmp + line.find_first_not_of(" ")), " ")))
				return (e_status::FAIL);
			if (!(tmp = std::strtok(NULL, " ")))
				return (e_status::FAIL);
			sscanf(tmp, "%u//%u", &first.x, &first.z);
			sscanf(tmp, "%u/%u/%u", &first.x, &first.y, &first.z);
			if (!(tmp = std::strtok(NULL, " ")))
				return (e_status::FAIL);
			sscanf(tmp, "%u//%u", &second.x, &second.z);
			sscanf(tmp, "%u/%u/%u", &second.x, &second.y, &second.z);
			if (!(tmp = std::strtok(NULL, " ")))
				return (e_status::FAIL);
			while (tmp)
			{
				vector = glm::uvec3((unsigned int)-1, (unsigned int)-1, (unsigned int)-1);
				sscanf(tmp, "%u//%u", &vector.x, &vector.z);
				sscanf(tmp, "%u/%u/%u", &vector.x, &vector.y, &vector.z);
				if (vector.x == (unsigned int)-1)
					break;
				data->mIndices.push_back(first);
				data->mIndices.push_back(second);
				data->mIndices.push_back(vector);
				second = vector;
				tmp = std::strtok(NULL, " ");
			}
			return (e_status::OK);
		}
	} // namespace OBJParser
	
} // namespace mf
