#include "Button.h"

gui::Button::Button(const sf::String & text) : _label{ text }
{
}

void gui::Button::setSize(const sf::Vector2f & size)
{
	if (size.x - 2 * _frame.getThickness() > 0 && size.y - 2 * _frame.getThickness() > 0)
	{
		_size = size;
		resize();
	}
}

void gui::Button::setPosition(const sf::Vector2f & position)
{
	_position = position;

	_label.setPosition({ position.x + _frame.getThickness(), position.y + _frame.getThickness() });
	_frame.fitTo(_label);
	_background.fitTo(_label);
}

const sf::Vector2f & gui::Button::getSize() const
{
	return _size;
}

const sf::Vector2f & gui::Button::getPosition() const
{
	return _position;
}

const sf::Rect<float> gui::Button::getGlobalBounds() const
{
	return _frame.getGlobalBounds();
}

void gui::Button::up_date(gui::duration time_elapsed, const Mouse_info & mouse_info)
{
	_function(mouse_info, time_elapsed, this);
}

void gui::Button::draw(sf::RenderTarget & render_target) const
{
	_background.draw(render_target);
	_label.draw(render_target);
	_frame.draw(render_target);
}

void gui::Button::setOwner(gui::owner & owner)
{
	_label.setTextStyle(owner.getTextStyle());
}

bool gui::Button::isActive() const
{
	return _active;
}

bool gui::Button::isHover() const
{
	return _hover;
}

bool gui::Button::isClicked() const
{
	return _clicked;
}

bool gui::Button::isFocused() const
{
	return _focus;
}

bool gui::Button::isHoverChange() const
{
	return _hover_change;
}

bool gui::Button::isClickedChange() const
{
	return _clicked_change;
}

bool gui::Button::isNeedResize() const
{
	return _need_resize;
}

void gui::Button::setActive(bool active)
{
	_active = active;
}

void gui::Button::setFocus(bool focus)
{
	_focus = focus;
}

void gui::Button::resize()
{
	_need_resize = false;

	if (_size.x - 2 * _frame.getThickness() > 0 && _size.y - 2 * _frame.getThickness() > 0)
	{
		_label.setSize({ _size.x - 2 * _frame.getThickness() , _size.y - 2 * _frame.getThickness() });
		_frame.fitTo(_label);
		_background.fitTo(_label);
	}
	else
	{
		// Can not fit text
		// Minimal size is 2 * _frame.getThickness()
		_size = { 2 * _frame.getThickness() , 2 * _frame.getThickness() };
		_label.setSize({ 0, 0 });
		_frame.fitTo(_label);
		_background.fitTo(_label);
	}

	setPosition(_position);
}

gui::modifier::Frame_modifier & gui::Button::getFrame()
{
	_need_resize = true;
	return _frame;
}

gui::modifier::Label_modifier & gui::Button::getLabel()
{
	_need_resize = true;
	return _label;
}

gui::modifier::Background_modifier & gui::Button::getBackground()
{
	_need_resize = true;
	return _background;
}

gui::modifier::Function_modifier & gui::Button::getFunction()
{
	return _function;
}

void gui::Button::setHover(bool hover)
{
	_hover = hover;
}

void gui::Button::setClicked(bool clicked)
{
	_clicked = clicked;
}

void gui::Button::setHoverChange(bool hover_change)
{
	_hover_change = hover_change;
}

void gui::Button::setClickedChange(bool clicked_change)
{
	_clicked_change = clicked_change;
}