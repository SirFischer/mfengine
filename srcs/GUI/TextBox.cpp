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

//TODO OPTIMIZE TEXT FITTING ALGORITHM
void        TextBox::UpdateText()
{
    int             i = -1;
    std::string     tmp = "";

    while (++i < (int)mString.size())
    {
        mText.setString(tmp);
        if (mText.getGlobalBounds().width + mText.getCharacterSize() > mSize.x)
        {
            if ((tmp.size() - tmp.find_last_of(' ')) * mText.getCharacterSize() > mSize.x)
                tmp.insert(tmp.size() - 2, "-\n");
            else
            {
                if (tmp.back() == ' ')
                    tmp.insert(tmp.find_last_not_of(' ') + 1, "\n");
                else
                    tmp.insert(tmp.find_last_of(' ') + 1, "\n");
            }
        }
        tmp += mString[i];
    }
    mText.setString(tmp);
}

void        TextBox::Update()
{
    std::string tmp = mEventHandler->GetStringEntered();

    if (tmp != "" && mAllowFocus)
    {
        if (tmp[0] == (char)8)
             mString = mString.substr(0, mString.size() - 1);
        else if (isprint(tmp[0]))
            mString += mEventHandler->GetStringEntered();
        UpdateText();
    }
    mSprite.setPosition(mPosition);
	mText.setPosition(mPosition + mTextPos);
}



void		TextBox::Draw()
{
	SetView();
	mWindow->draw(&mSprite);
	mWindow->draw(&mText);
	ResetView();
}

void		TextBox::SetText(std::string str)
{
    mString = str;
    UpdateText();
}

void        TextBox::SetTextPosition(sf::Vector2f tPos)
{
    mTextPos = tPos;
    mText.setPosition(mPosition + tPos);
}

void        TextBox::SetAllowFocus(bool tFocus)
{
    mAllowFocus = tFocus;
}

}
