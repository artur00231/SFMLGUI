#include "Horizontal_slider.h"

gui::Horizontal_slider::Horizontal_slider(long long max, long long min) : _left{}, _max{max}, _min{min}
{
	_left.getFrame().setThickness(2);
	_right.getFrame().setThickness(2);
}

void gui::Horizontal_slider::setSize(const sf::Vector2f & size)
{
	_size = size;

	resize();
}

void gui::Horizontal_slider::setPosition(const sf::Vector2f & position)
{
	_position = position;
	float frame_thickness = _frame.getThickness();


	_left.setPosition({ _position.x + frame_thickness, _position.y + frame_thickness });
	_right.setPosition({ _position.x + _size.x - frame_thickness - _button_min_size.x, _position.y + frame_thickness });

	sf::Rect<float> to_fit{ { _position.x + frame_thickness,  _position.y + frame_thickness }, { _size.x - 2 * frame_thickness, _size.x - 2 * frame_thickness } };
	_background.fitTo(to_fit);
	_frame.fitTo(to_fit);
}

const sf::Vector2f & gui::Horizontal_slider::getSize() const
{
	return _size;
}

const sf::Vector2f & gui::Horizontal_slider::getPosition() const
{
	return _position;
}

const sf::Rect<float> gui::Horizontal_slider::getGlobalBounds() const
{
	return _frame.getGlobalBounds();
}

void gui::Horizontal_slider::up_date(gui::duration time_elapsed)
{
	_function(_events, time_elapsed, this);

	// Clear _events to prevent overflow
	_events.clear();
}

void gui::Horizontal_slider::draw(sf::RenderTarget & render_target) const
{
}

void gui::Horizontal_slider::setOwner(owner & owner)
{
	owner.addObject(_left);
	owner.addObject(_right);
}

bool gui::Horizontal_slider::isActive() const
{
	return _active;
}

bool gui::Horizontal_slider::isHover() const
{
	return _hover;
}

bool gui::Horizontal_slider::isClicked() const
{
	return _clicked;
}

bool gui::Horizontal_slider::isFocused() const
{
	return _focus;
}

bool gui::Horizontal_slider::isHoverChange() const
{
	return _hover_change;
}

bool gui::Horizontal_slider::isClickedChange() const
{
	return _clicked_change;
}

bool gui::Horizontal_slider::isNeedResize() const
{
	return _need_resize;
}

void gui::Horizontal_slider::setActive(bool active)
{
	_active = active;
}

void gui::Horizontal_slider::setFocus(bool focus)
{
	_focus = focus;
}

void gui::Horizontal_slider::setValue(long long value)
{
	_value = value;
}

void gui::Horizontal_slider::setMinMax(long long min, long long max)
{
	_min = min;
	_max = _max;
}

void gui::Horizontal_slider::setStepValue(long long step)
{
	_step = step;
}

long long gui::Horizontal_slider::getNumber()
{
	return _value;
}

std::pair<long long, long long> gui::Horizontal_slider::getMInMax()
{
	return std::pair<long long, long long>{ _min, _max };
}

long long gui::Horizontal_slider::getStepValue()
{
	return _step;
}

void gui::Horizontal_slider::resize()
{
	_need_resize = false;

	bool fit_x = _size.x >= 2 * _button_min_size.x;
	bool fit_y = _size.y >= _button_min_size.y;

	if (fit_x && fit_y)
	{
		sf::Vector2f button_size{ _button_min_size.x, _size.y - 2 * _frame.getThickness()};
		_left.setSize(button_size);
		_right.setSize(button_size);
	}
	else
	{
		if (!fit_x)
		{
			_size.x = 2 * _button_min_size.x + 2 * _frame.getThickness();
		}

		if (!fit_y)
		{
			_size.y = _button_min_size.y + 2 * _frame.getThickness();
		}

		resize();
	}

	setPosition(_position);
}

gui::modifier::Frame_modifier & gui::Horizontal_slider::getFrame()
{
	return _frame;
}

gui::modifier::Background_modifier & gui::Horizontal_slider::getBackground()
{
	return _background;
}

gui::modifier::Function_modifier & gui::Horizontal_slider::getFunction()
{
	return _function;
}

void gui::Horizontal_slider::setHover(bool hover)
{
	_hover = hover;
}

void gui::Horizontal_slider::setClicked(bool clicked)
{
	_clicked = clicked;
}

void gui::Horizontal_slider::setHoverChange(bool hover_change)
{
	_hover_change = hover_change;
}

void gui::Horizontal_slider::setClickedChange(bool clicked_change)
{
	_clicked_change = clicked_change;
}

gui::Mouse_events & gui::Horizontal_slider::getMouse_event()
{
	return _events;
}
