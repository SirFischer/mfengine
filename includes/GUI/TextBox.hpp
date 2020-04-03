#pragma once

#include "Container.hpp"
#include "ResourceManager.hpp"
#include "EventHandler.hpp"

namespace mf
{

class TextBox : public aContainerItem
{
private:
    EventHandler        *mEventHandler;
    std::string         mString = "";
    sf::Vector2f		mTextPos = sf::Vector2f(5, 5);
    bool                mFocus = false;
    bool                mAllowFocus = true;

    void                UpdateText();
   
public:
    TextBox(Window *tWindow, EventHandler *tEventHandler);
    ~TextBox();

    void                Update();
    void                Draw();

    std::string         GetText() {return (mString);}

    void                SetText(std::string str);
    void                SetTextPosition(sf::Vector2f tPos);
    void                SetAllowFocus(bool tFocus);
};

}
