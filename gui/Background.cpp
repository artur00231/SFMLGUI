#include "Background.h"

gui::Background::Background()
{
	// By default, the background is transparent
	_rectangle.setFillColor(sf::Color::Transparent);
}

void gui::Background::setSize(const sf::Vector2f & size)
{
	_rectangle.setSize(size);
	if (_image)
	{
		_image->setSize(size);
	}
}

void gui::Background::setPosition(const sf::Vector2f & position)
{
	_rectangle.setPosition(position);
	if (_image)
	{
		_image->setPosition(position);
	}
}

void gui::Background::setColor(const sf::Color & color)
{
	_rectangle.setFillColor(color);
	if (_image)
	{
		_image->setColor(color);
	}
}

const sf::Vector2f & gui::Background::getSize() const
{
	return _rectangle.getSize();
}

const sf::Vector2f & gui::Background::getPosition() const
{
	return _rectangle.getPosition();
}

const sf::Rect<float> gui::Background::getGlobalBounds() const
{
	return _rectangle.getGlobalBounds();
}

const sf::Color & gui::Background::getColor() const
{
	return _rectangle.getFillColor();
}

void gui::Background::draw(sf::RenderTarget & render_target) const
{
	if (_background_type == Background_type::COLOR)
	{
		render_target.draw(_rectangle);
	}
	else
	{
		_image->draw(render_target);
	}
}

void gui::Background::setOwner(gui::owner&)
{
	// Do nothing
}

void gui::Background::setBackground_type(Background_type background_type)
{
	if (background_type == Background_type::COLOR)
	{
		_background_type = Background_type::COLOR;
	}
	else
	{
		if (_background_type != Background_type::IMAGE)
		{
			if (!_image)
			{
				// Create Image
				_image.reset(new gui::Image);
			}

			_background_type = Background_type::IMAGE;
		}
	}
}

void gui::Background::setImage(Image * image)
{
	_image.reset(image);
	_image->setPosition(_rectangle.getPosition());
	_image->setSize(_rectangle.getSize());

	// Set the same color for the rectangle
	_rectangle.setFillColor(_image->getColor());
}

gui::Background_type gui::Background::getBackground_type() const
{
	return _background_type;
}

gui::modifier::Image_modifier * gui::Background::getImage()
{
	if (_background_type == Background_type::IMAGE)
	{
		return _image.get();
	}

	return nullptr;
}

void gui::Background::fitTo(const gui_object & object)
{
	setSize(object.getSize());
	setPosition(object.getPosition());
}

void gui::Background::fitTo(const sf::Rect<float> & rectangle)
{
	setSize({ rectangle.width, rectangle.height });
	setPosition({ rectangle.left, rectangle.top });
}
