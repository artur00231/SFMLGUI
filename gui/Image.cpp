#include "Image.h"

#include <iostream>

gui::Image::Image(const std::string & path) : ImageImp(path)
{
}

void gui::Image::setSize(const sf::Vector2f & size)
{
	ImageImp::setSize(size);
}

void gui::Image::setPosition(const sf::Vector2f & position)
{
	ImageImp::setPosition(position);
}

void gui::Image::setColor(const sf::Color & color)
{
	ImageImp::setColor(color);
}

const sf::Vector2f & gui::Image::getSize() const
{
	return ImageImp::getSize();
}

const sf::Vector2f & gui::Image::getPosition() const
{
	return ImageImp::getPosition();
}

const sf::Rect<float> gui::Image::getGlobalBounds() const
{
	return ImageImp::getGlobalBounds();
}

const sf::Color & gui::Image::getColor() const
{
	return ImageImp::getColor();
}

void gui::Image::draw(sf::RenderTarget & window) const
{
	ImageImp::draw(window);
}

void gui::Image::setOwner(owner &)
{
	// Do nothing
}

void gui::Image::setTexture(const std::string & path)
{
	ImageImp::setTexture(path);
}

void gui::Image::setTexture(const std::string & path, const sf::Rect<int> & part)
{
	ImageImp::setTexture(path, part);
}

void gui::Image::setTexture(const sf::Image & image)
{
	ImageImp::setTexture(image);
}

void gui::Image::setTexture(const sf::Image & image, const sf::Rect<int> & part)
{
	ImageImp::setTexture(image, part);
}

void gui::Image::setTexture(const sf::Texture * texture)
{
	ImageImp::setTexture(texture);
}

void gui::Image::setTexture(const void * data, size_t size)
{
	ImageImp::setTexture(data, size);
}

void gui::Image::setRepeated(bool repeated)
{
	ImageImp::setRepeated(repeated);
}

void gui::Image::setSmooth(bool smooth)
{
	ImageImp::setSmooth(smooth);
}

const sf::Texture * gui::Image::getTexture()
{
	return ImageImp::getTexture();
}

bool gui::Image::getRepeated()
{
	return ImageImp::getRepeated();
}

bool gui::Image::getSmooth()
{
	return ImageImp::getSmooth();
}
