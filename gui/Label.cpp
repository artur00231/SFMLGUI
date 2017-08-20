#include "Label.h"

gui::Label::Label(const sf::String & text, const Text_style* style) : LabelImp{ text, style }
{
}

void gui::Label::setSize(const sf::Vector2f & size)
{
	LabelImp::setSize(size);
}

void gui::Label::setPosition(const sf::Vector2f & positon)
{
	LabelImp::setPosition(positon);
}

void gui::Label::setColor(const sf::Color & color)
{
	LabelImp::setCharacterColor(color);
}

const sf::Vector2f & gui::Label::getSize() const
{
	return LabelImp::getSize();
}

const sf::Vector2f & gui::Label::getPosition() const
{
	return LabelImp::getPosition();
}

const sf::Rect<float> gui::Label::getGlobalBounds() const
{
	return LabelImp::getGlobalBounds();
}

const sf::Color & gui::Label::getColor() const
{
	return LabelImp::getCharacteColor();
}

void gui::Label::draw(sf::RenderTarget & window) const
{
	LabelImp::draw(window);
}

void gui::Label::setOwner(gui::owner & owner)
{
	setTextStyle(owner.getTextStyle());
}

bool gui::Label::setFont(const std::string & font_path)
{
	return LabelImp::setFont(font_path);
}

void gui::Label::setCharacterSize(unsigned int size)
{
	LabelImp::setCharacterSize(size);
}

void gui::Label::setString(const sf::String & text)
{
	LabelImp::setString(text);
}

void gui::Label::setStyle(sf::Uint32 style)
{
	LabelImp::setStyle(style);
}

void gui::Label::setTextStyle(const Text_style & style)
{
	LabelImp::setTextStyle(style);
}

void gui::Label::setAlign(Align align)
{
	LabelImp::setAlign(align);
}

unsigned int gui::Label::getCharacterSize() const
{
	return LabelImp::getCharacterSize();
}

const sf::String & gui::Label::getString() const
{
	return LabelImp::getString();
}

const gui::Text_status & gui::Label::getStatus() const
{
	return LabelImp::getStatus();
}

int gui::Label::getStyle() const
{
	return LabelImp::getStyle();
}

gui::Align gui::Label::getAlign()
{
	return LabelImp::getAlign();
}

void gui::Label::resize()
{
	LabelImp::resize();
}
