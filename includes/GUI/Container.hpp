#pragma once
#include "Window.hpp"
#include "aContainerItem.hpp"

namespace mf
{
	class Container : public aContainerItem
	{
	private:
		std::vector<aContainerItem *>	mContainerItems;
		bool							mIsExpandable = true;


		void							UpdateItems();
		void							DrawItems();

	public:
		explicit Container(Window *tWindow);
		~Container();

		void							Update();
		void							Draw();

		void							AddItem(aContainerItem *tItem);
	};
}
