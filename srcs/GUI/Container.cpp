#include "Container.hpp"

namespace mf
{
	Container::Container(Window *tWindow)
	{
		mWindow = tWindow;
	}

	Container::~Container()
	{

	}

	void	Container::UpdateItems()
	{
		for (aContainerItem *value: mContainerItems)
			value->Update();
	}

	void	Container::DrawItems()
	{
		for (aContainerItem *value: mContainerItems)
			value->Draw();
	}

	void	Container::Update()
	{
		UpdateItems();
	}

	void	Container::Draw()
	{
		mWindow->draw(&mSprite);
		DrawItems();
	}

	void	Container::AddItem(aContainerItem *tItem)
	{
		if (tItem)
		{
			tItem->SetParent(this);
			mContainerItems.push_back(tItem);
		}
	}

	void	Container::SetColorBackground(int tWidth, int tHeight, sf::Color tColor)
	{
		sf::Image	img;
		img.create(tWidth, tHeight, tColor);
		mTexture.loadFromImage(img);
		mSprite.setTexture(mTexture);
	}
	void	Container::SetColorBackground(sf::Vector2f tSize, sf::Color tColor)
	{
		SetColorBackground(tSize.x, tSize.y, tColor);
	}
	void	Container::SetColorBackground()
	{
		SetColorBackground(200, 200, sf::Color::White);
	}
}


