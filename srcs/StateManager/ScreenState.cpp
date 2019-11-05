#include "ScreenState.hpp"

namespace mf
{

ScreenState::ReturnCtrl	ScreenState::run()
{
	sf::Time	timeDiff = sf::Time::Zero;
	mRunning = true;
	mElapsedTime = sf::seconds(mDeltaTime);
	while (mRunning && mWindow->isOpen())
	{
		while (mElapsedTime.asSeconds() > mDeltaTime)
		{
			handle_events();
			update();
			mElapsedTime -= sf::seconds(mDeltaTime);
		}
		render();
		timeDiff = mGameLoop.restart();
		mElapsedTime += timeDiff;
		calculateFPS(timeDiff);
	}
	return (mReturn);
}

void	ScreenState::calculateFPS(sf::Time timeDiff)
{
	static int		frameCounter = 0;
	static sf::Time	total = sf::Time::Zero;

	frameCounter++;
	total += timeDiff;
	if (total.asMilliseconds() > 1000.0)
	{
		mFPS = frameCounter;
		mFrameTime = total.asMilliseconds() / (float)frameCounter;
		frameCounter = 0;
		total = sf::Time::Zero;
	}
}

void	ScreenState::setDeltaTime(float deltatime)
{
	mDeltaTime = deltatime;
}

} // namespace m
