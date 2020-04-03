#include "ResourceManager.hpp"

namespace mf
{
bool								mf::ResourceManager::verbose = false;
std::map<std::string, sf::Font>		mf::ResourceManager::mFonts = std::map<std::string, sf::Font>();
std::map<std::string, sf::Image>	mf::ResourceManager::mImages = std::map<std::string, sf::Image>();
std::map<std::string, mf::Shader>	mf::ResourceManager::mShaders = std::map<std::string, mf::Shader>();

ResourceManager::ResourceManager()
{

}
	
ResourceManager::~ResourceManager()
{
	
}

sf::Image	ResourceManager::LoadImage(std::string path)
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

sf::Font	ResourceManager::LoadFont(std::string path)
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

void	ResourceManager::LoadShader(std::string name, std::string vertex, std::string fragment)
{
	if (mShaders.count(name) > 0)
	{
		if (verbose)
			std::cout << name << " already loaded...\n";
	}
	if (verbose)
		std::cout << "Loading " << name << "..." << std::endl;
	mf::Shader	shader;
	
	if (!(shader.LoadFromFile(vertex, fragment)))
	{
		std::cout << "Failed to load " << name << std::endl;
	}
	mShaders.insert(std::make_pair(name, shader));
}

mf::Shader		*ResourceManager::GetShader(std::string name)
{
	if (mShaders.count(name) > 0)
	{
		return (&mShaders[name]);
	}
	return (NULL);
}
} // namespace mf


