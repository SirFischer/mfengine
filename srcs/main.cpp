#include "StateManager.hpp"

int main()
{
	Window	window("TESTS", sf::Vector2i(1920, 1080));
	StateManager	stateManager(&window);
	stateManager.state_push(new MenuState(&window));
	stateManager.run();
	return (0);
}