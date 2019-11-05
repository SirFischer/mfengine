#include "Shader.hpp"

namespace mf
{

Shader::Shader()
{
	mShader = new sf::Shader();
}

Shader::~Shader()
{

}

void		Shader::Bind()
{
	sf::Shader::bind(mShader);
}

bool		Shader::LoadFromFile(std::string vertex, std::string fragment)
{
	return (mShader->loadFromFile(vertex, fragment));
}

void		Shader::SetMat4(std::string name, glm::mat4 mat)
{
	glUniformMatrix4fv(glGetUniformLocation(mShader->getNativeHandle(), name.c_str()),
	1, GL_FALSE, &mat[0][0]);
}

} // namespace mf
