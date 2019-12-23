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

void        TextBox::UpdateText()
{
    int             i = -1;
    std::string     tmp = "";

    while (++i < (int)mString.size())
    {
        mText.setString(tmp);
        if (mText.getGlobalBounds().width + mText.getCharacterSize() > mSize.x)
        {
            if (tmp.back() == ' ')
                tmp.insert(tmp.find_last_not_of(' ') + 1, "\n");
            else
                tmp.insert(tmp.find_last_of(' ') + 1, "\n");
        }
        tmp += mString[i];
    }
    mText.setString(tmp);
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
        UpdateText();
    }
}

void        TextBox::Draw()
{
    mWindow->draw(&mText);
}

}
