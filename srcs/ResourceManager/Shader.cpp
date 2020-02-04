#include "Shader.hpp"

namespace mf
{

Shader::Shader() try :
mShader(new sf::Shader())
{

}
catch (std::exception &e)
{
	std::cerr << e.what() << std::endl;
}

Shader::~Shader()
{
	
}

void		Shader::Bind()
{
	sf::Shader::bind(mShader.get());
}

bool		Shader::LoadFromFile(std::string vertex, std::string fragment)
{
	return (mShader->loadFromFile(vertex, fragment));
}

void		Shader::SetVec3(std::string name, glm::vec3 vec)
{
	glUniform3f(glGetUniformLocation(mShader->getNativeHandle(), name.c_str()),
	vec[0], vec[1], vec[2]);
}

void		Shader::SetMat4(std::string name, glm::mat4 mat)
{
	glUniformMatrix4fv(glGetUniformLocation(mShader->getNativeHandle(), name.c_str()),
	1, GL_FALSE, &mat[0][0]);
}

void		Shader::SetInt(std::string name, int var)
{
	glUniform1i(glGetUniformLocation(mShader->getNativeHandle(), name.c_str()), var);
}

void		Shader::SetFloat(std::string name, float var)
{
	glUniform1f(glGetUniformLocation(mShader->getNativeHandle(), name.c_str()), var);
}


} // namespace mf
