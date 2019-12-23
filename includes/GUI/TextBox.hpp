#pragma once

#include "Container.hpp"
#include "ResourceManager.hpp"
#include "EventHandler.hpp"

namespace mf
{

class TextBox : public aContainerItem
{
private:
    ResourceManager     *mResourceManager;
    EventHandler        *mEventHandler;
    std::string         mString = "";
    sf::Font            mFont;
    sf::Text            mText;
    bool                focus = false;

    void                UpdateText();

public:
    TextBox(Window *tWindow, mf::ResourceManager *tResourceManager, EventHandler *tEventHandler);
    ~TextBox();

    void                Update();
    void                Draw();
};

}
