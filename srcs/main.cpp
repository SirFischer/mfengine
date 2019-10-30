#include "StateManager.hpp"

int main()
{
	std::string	title = "TEST";
	mf::Window	window(title, sf::Vector2i(1920, 1080));
	mf::StateManager	stateManager(&window);
	stateManager.state_push(new MenuState(&window));
	stateManager.run();
	return (0);
}
