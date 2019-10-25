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
	if (mResources.count(path) > 0)
	{
		if (verbose)
			std::cout << path << " already loaded, returning copy...\n";
		return (*(sf::Image *)mResources[path]);
	}
	if (verbose)
		std::cout << "Loading " << path << "..." << std::endl;
	sf::Image	*image = new sf::Image();
	image->loadFromFile(path);
	mResources.insert(std::make_pair(path, image));
	return (*image);
}

sf::Font	mf::ResourceManager::LoadFont(std::string path)
{
	if (mResources.count(path) > 0)
	{
		if (verbose)
			std::cout << path << " already loaded, returning copy...\n";
		return (*(sf::Font *)mResources[path]);
	}
	if (verbose)
		std::cout << "Loading " << path << "..." << std::endl;
	sf::Font	*font = new sf::Font();
	font->loadFromFile(path);
	mResources.insert(std::make_pair(path, font));
	return (*font);
}