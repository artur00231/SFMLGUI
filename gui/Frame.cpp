#include "Frame.h"

gui::Frame::Frame(float thickness, const sf::Color & color) : FrameImp{ thickness, color }
{
}

void gui::Frame::setSize(const sf::Vector2f & size)
{
	FrameImp::setSize(size);
}

void gui::Frame::setPosition(const sf::Vector2f & position)
{
	FrameImp::setPosition(position);
}

void gui::Frame::setColor(const sf::Color & color)
{
	FrameImp::setColor(color);
}

const sf::Vector2f & gui::Frame::getSize() const
{
	return FrameImp::getSize();
}

const sf::Vector2f & gui::Frame::getPosition() const
{
	return FrameImp::getPosition();
}

const sf::Rect<float> gui::Frame::getGlobalBounds() const
{
	return FrameImp::getGlobalBounds();
}

const sf::Color & gui::Frame::getColor() const
{
	return FrameImp::getColor();
}

void gui::Frame::draw(sf::RenderTarget & window) const
{
	FrameImp::draw(window);
}

void gui::Frame::setOwner(owner &)
{
	// Do nothing
}

void gui::Frame::removeFromOwner(owner & owner)
{
	// Do nothing
}

void gui::Frame::fitTo(const gui_object & object)
{
	FrameImp::fitTo(object);
}

void gui::Frame::fitTo(const sf::Rect<float> & rectangle)
{
	FrameImp::fitTo(rectangle);
}

void gui::Frame::setThickness(float thickness)
{
	FrameImp::setThickness(thickness);
}

float gui::Frame::getThickness() const
{
	return FrameImp::getThickness();
}
