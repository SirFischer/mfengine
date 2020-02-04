#pragma once

#include <SFML/Graphics.hpp>
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <memory>
#include <iostream>

namespace mf
{

class Shader
{
private:
	std::shared_ptr<sf::Shader> mShader;

public:
	Shader();
	~Shader();

	void		Bind();

	bool		LoadFromFile(std::string vertex, std::string fragment);

	void		SetVec3(std::string name, glm::vec3 vec);
	void		SetMat4(std::string name, glm::mat4 mat);
	void		SetInt(std::string name, int var);
};

} // namespace mf
