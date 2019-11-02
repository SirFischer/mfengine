#include "ResourceManager.hpp"

bool mf::ResourceManager::verbose = false;

mf::ResourceManager::ResourceManager()
{

}
	
mf::ResourceManager::~ResourceManager()
{
	
}

sf::Image	mf::ResourceManager::LoadImage(std::string path)
{
	if (mImages.count(path) > 0)
	{
		if (verbose)
			std::cout << path << " already loaded, returning copy...\n";
		return (mImages[path]);
	}
	if (verbose)
		std::cout << "Loading " << path << "..." << std::endl;
	sf::Image	image;
	image.loadFromFile(path);
	mImages.insert(std::make_pair(path, image));
	return (image);
}

sf::Font	mf::ResourceManager::LoadFont(std::string path)
{
	if (mFonts.count(path) > 0)
	{
		if (verbose)
			std::cout << path << " already loaded, returning copy...\n";
		return (mFonts[path]);
	}
	if (verbose)
		std::cout << "Loading " << path << "..." << std::endl;
	sf::Font	font;
	font.loadFromFile(path);
	mFonts.insert(std::make_pair(path, font));
	return (font);
}

void	mf::ResourceManager::LoadShader(std::string name, std::string vertex, std::string fragment)
{
	if (mShaders.count(name) > 0)
	{
		if (verbose)
			std::cout << name << " already loaded...\n";
	}
	if (verbose)
		std::cout << "Loading " << name << "..." << std::endl;
	sf::Shader	*shader = new sf::Shader;
	if (!(shader->loadFromFile(vertex, fragment)))
	{
		std::cout << "Failed to load " << name << std::endl;
	}
	mShaders.insert(std::make_pair(name, shader));
}


void	mf::ResourceManager::BindShader(std::string name)
{
	if (mShaders.count(name) > 0)
	{
		sf::Shader::bind(mShaders[name]);
	}
	else
		sf::Shader::bind(NULL);
}

