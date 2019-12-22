#include "TextBox.hpp"

namespace mf
{

TextBox::TextBox(Window *tWindow, mf::ResourceManager *tResourceManager, EventHandler *tEventHandler)
{
    mWindow = tWindow;
    mResourceManager = tResourceManager;
    mEventHandler = tEventHandler;
    mFont = mResourceManager->LoadFont("assets/fonts/pdark.ttf");
    mText.setFont(mFont);
}

TextBox::~TextBox()
{
}

void        TextBox::Update()
{
    std::string tmp = mEventHandler->GetStringEntered();
    if (tmp != "")
    {
        if (tmp[0] == (char)8)
             mString = mString.substr(0, mString.size() - 1);
        else
            mString += mEventHandler->GetStringEntered();
        mString += '\n';
    }
    
    mText.setString(mString);
}

void        TextBox::Draw()
{
    mWindow->draw(&mText);
}

}
