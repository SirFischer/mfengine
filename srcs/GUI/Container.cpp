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
}


