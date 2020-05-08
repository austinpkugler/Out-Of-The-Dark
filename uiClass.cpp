#include "uiClass.h"

void uiClass::update()
{
    if (m_screenName == "title_screen")
    {
        m_backgroundSprite.setTexture(m_titleScreenBg);
    }
}