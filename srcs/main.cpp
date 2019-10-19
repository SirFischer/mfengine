# include "window.hpp"

int main()
{
	window	window("TESTS", sf::Vector2i(1920, 1080));

	while (window.isOpen())
	{
		window.update();
		window.clear();
		window.display();
	}
	return (0);
}