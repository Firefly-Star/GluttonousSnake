#include "TextPage.h"
#include "Core/Tool.h"

TextPage::TextPage(const std::string& text)
    :m_Text(text)
{
}

TextPage::~TextPage()
{
}

void TextPage::OnEvent(Event& event)
{
}

void TextPage::Update()
{
}

void TextPage::Render()
{
    PrintCenteredText(m_Text);
}
