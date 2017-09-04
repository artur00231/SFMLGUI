#include "Vertical_slider.h"

gui::Vertical_slider::Vertical_slider(long long max, long long min) : _up{ L'\u02C4' }, _down{ L'\u02C5' }, _max{ max }, _min{ min }
{
	sf::Color gray{ 171, 171, 171, 255 };

	_up.getBackground().setColor(gray);
	_up.getFunction().set([this]() {this->subtract(); });
	_down.getBackground().setColor(gray);
	_down.getFunction().set([this]() {this->add(); });

	_middle.getBackground().setColor(gray);
	_middle.getFrame().setThickness(1);
	_middle.getFrame().setColor(sf::Color::Black);

	setValue(_min);
}

void gui::Vertical_slider::setSize(const sf::Vector2f & size)
{
	_size = size;

	resize();
}

void gui::Vertical_slider::setPosition(const sf::Vector2f & position)
{
	_position = position;
	float frame_thickness = _frame.getThickness();


	_up.setPosition({ _position.x + frame_thickness, _position.y + frame_thickness });
	_down.setPosition({ _position.x + frame_thickness, _position.y + _size.y - frame_thickness - _button_min_size.y });

	auto current_step = getCurrentStep();

	_middle.setPosition({ _position.x + frame_thickness, _position.y + frame_thickness + _up.getSize().y + current_step * _middle_button_min_size.y });

	sf::Rect<float> to_fit{ { _position.x + frame_thickness,  _position.y + frame_thickness },{ _size.x - 2 * frame_thickness, _size.y - 2 * frame_thickness } };
	_background.fitTo(to_fit);
	_frame.fitTo(to_fit);
}

const sf::Vector2f & gui::Vertical_slider::getSize() const
{
	return _size;
}

const sf::Vector2f & gui::Vertical_slider::getPosition() const
{
	return _position;
}

const sf::Rect<float> gui::Vertical_slider::getGlobalBounds() const
{
	return _frame.getGlobalBounds();
}

void gui::Vertical_slider::up_date(gui::duration time_elapsed, const Mouse_info & mouse_info)
{
	setMiddleButtonPosition(mouse_info);

	_function(mouse_info, time_elapsed, this);
}

void gui::Vertical_slider::draw(sf::RenderTarget & render_target) const
{
	_background.draw(render_target);
	_up.draw(render_target);
	_down.draw(render_target);
	_middle.draw(render_target);
	_frame.draw(render_target);
}

void gui::Vertical_slider::setOwner(owner & owner)
{
	owner.addObject(_up);
	owner.addObject(_down);
	owner.addObject(_middle);

	setValue(_value);
}

void gui::Vertical_slider::removeFromOwner(owner & owner)
{
	owner.remove(&_up);
	owner.remove(&_down);
	owner.remove(&_middle);
}

bool gui::Vertical_slider::isActive() const
{
	return _active;
}

bool gui::Vertical_slider::isHover() const
{
	return _hover;
}

bool gui::Vertical_slider::isClicked() const
{
	return _clicked;
}

bool gui::Vertical_slider::isFocused() const
{
	return _focus;
}

bool gui::Vertical_slider::isHoverChange() const
{
	return _hover_change;
}

bool gui::Vertical_slider::isClickedChange() const
{
	return _clicked_change;
}

bool gui::Vertical_slider::isNeedResize() const
{
	return _need_resize;
}

void gui::Vertical_slider::setActive(bool active)
{
	_active = active;
}

void gui::Vertical_slider::setFocus(bool focus)
{
	_focus = focus;
}

void gui::Vertical_slider::setValue(long long value)
{
	if (value > _max)
	{
		_value = _max;
	}
	else if (value < _min)
	{
		_value = _min;
	}
	else
	{
		_value = value;
	}

	if (_value == _min)
	{
		auto color = _up.getLabel().getColor();
		color.a = 95;
		_up.getLabel().setColor(color);

		color = _down.getLabel().getColor();
		color.a = 255;
		_down.getLabel().setColor(color);
	}
	else if (_value == _max)
	{
		auto color = _down.getLabel().getColor();
		color.a = 95;
		_down.getLabel().setColor(color);

		color = _up.getLabel().getColor();
		color.a = 255;
		_up.getLabel().setColor(color);
	}
	else
	{
		auto color = _up.getLabel().getColor();
		color.a = 255;
		_up.getLabel().setColor(color);

		color = _down.getLabel().getColor();
		color.a = 255;
		_down.getLabel().setColor(color);
	}

	if (_value == _min && _value == _max)
	{
		auto color = _down.getLabel().getColor();
		color.a = 95;
		_down.getLabel().setColor(color);

		color = _up.getLabel().getColor();
		color.a = 95;
		_up.getLabel().setColor(color);
	}

	setPosition(_position);
}

void gui::Vertical_slider::setMinMax(long long min, long long max)
{
	_min = min;
	_max = max;

	setValue(_value);

	resize();
}

long long gui::Vertical_slider::getMaxSteps() const
{
	float middle_size_y = _size.y - 2 * _frame.getThickness() - 2 * _button_min_size.y;
	long long max_steps = static_cast<long long>(std::floor(middle_size_y / _middle_button_min_size.y)) - 1;

	return max_steps;
}

float gui::Vertical_slider::getMinButtonSize() const
{
	return _button_min_size.x;
}

long long gui::Vertical_slider::getValue() const
{
	return _value;
}

std::pair<long long, long long> gui::Vertical_slider::getMinMax() const
{
	return std::pair<long long, long long>{ _min, _max };
}

void gui::Vertical_slider::resize()
{
	_need_resize = false;

	bool fit_x = _size.x >= _button_min_size.x;
	bool fit_y = _size.y >=  2 * _button_min_size.y;

	float frame_thickness = _frame.getThickness();

	if (fit_x && fit_y)
	{
		sf::Vector2f button_size{ _size.x - 2 * frame_thickness, _button_min_size.y };
		_up.setSize(button_size);
		_down.setSize(button_size);

		long long steps = _max - _min;

		float middle_size_y = _size.y - 2 * frame_thickness - 2 * button_size.y;

		if (steps < 1)
		{
			_middle.setSize({ _size.x - 2 * frame_thickness, middle_size_y });
		}
		else
		{
			long long max_steps = static_cast<long long>(std::floor(middle_size_y / _middle_button_min_size.y)) - 1;

			if (max_steps < steps)
			{
				steps = max_steps;

				_max = _min + max_steps;

				setValue(_value);
			}

			if (max_steps < 2)
			{
				_middle.setSize({ _size.x - 2 * frame_thickness, middle_size_y });
			}
			else
			{
				_middle.setSize({ _size.x - 2 * frame_thickness, middle_size_y - steps * _middle_button_min_size.y });
			}
		}
	}
	else
	{
		if (!fit_x)
		{
			_size.x = _button_min_size.x + 2 * frame_thickness;
		}

		if (!fit_y)
		{
			_size.y = 2 * _button_min_size.y + 2 * frame_thickness;
		}

		resize();
	}

	setPosition(_position);
}

gui::modifier::Frame_modifier & gui::Vertical_slider::getFrame()
{
	_need_resize = true;
	return _frame;
}

const gui::modifier::Frame_modifier & gui::Vertical_slider::getFrame() const
{
	return _frame;
}

gui::modifier::Background_modifier & gui::Vertical_slider::getBackground()
{
	_need_resize = true;
	return _background;
}

const gui::modifier::Background_modifier & gui::Vertical_slider::getBackground() const
{
	return _background;
}

gui::modifier::Function_modifier & gui::Vertical_slider::getFunction()
{
	return _function;
}

const gui::modifier::Function_modifier & gui::Vertical_slider::getFunction() const
{
	return _function;
}

gui::modifier::Button_modifier & gui::Vertical_slider::getUp()
{
	_need_resize = true;
	return _up;
}

const gui::modifier::Button_modifier & gui::Vertical_slider::getUp() const
{
	return _up;
}

gui::modifier::Button_modifier & gui::Vertical_slider::getDown()
{
	_need_resize = true;
	return _down;
}

const gui::modifier::Button_modifier & gui::Vertical_slider::getDown() const
{
	return _down;
}

gui::modifier::Button_modifier & gui::Vertical_slider::getMiddle()
{
	_need_resize = true;
	return _middle;
}

const gui::modifier::Button_modifier & gui::Vertical_slider::getMiddle() const
{
	return _middle;
}

void gui::Vertical_slider::setHover(bool hover)
{
	_hover = hover;
}

void gui::Vertical_slider::setClicked(bool clicked)
{
	_clicked = clicked;
}

void gui::Vertical_slider::setHoverChange(bool hover_change)
{
	_hover_change = hover_change;
}

void gui::Vertical_slider::setClickedChange(bool clicked_change)
{
	_clicked_change = clicked_change;
}

unsigned long long gui::Vertical_slider::getCurrentStep()
{
	return _value - _min;
}

void gui::Vertical_slider::add()
{
	if (_down.isClickedChange() && _down.isClicked())
	{
		setValue(_value + 1);
	}
}

void gui::Vertical_slider::subtract()
{
	if (_up.isClickedChange() && _up.isClicked())
	{
		setValue(_value - 1);
	}
}

void gui::Vertical_slider::setMiddleButtonPosition(const Mouse_info & mouse_info)
{
	if (_middle.isClicked() && _middle.isClickedChange())
	{
		_mouse_move = { 0, 0 };
	}

	if (!isClicked() && isClickedChange())
	{
		_follow_mouse = false;
	}

	if ((_middle.isClicked() || _middle.isClickedChange()) || (_follow_mouse && isClicked()))
	{
		_mouse_move += mouse_info.getMouseMove();

		_follow_mouse = true;
	}

	if (_mouse_move.y > _middle_button_min_size.y)
	{
		setValue(_value + 1);
		_mouse_move.y -= _middle_button_min_size.y;
	}
	else if (_mouse_move.y < -_middle_button_min_size.y)
	{
		setValue(_value - 1);
		_mouse_move.y += _middle_button_min_size.y;
	}

	if (isHover())
	{
		auto wheel_move = mouse_info.getMouseWheelMove();

		if (wheel_move > 0)
		{
			setValue(_value - 1);
		}
		else if (wheel_move < 0)
		{
			setValue(_value + 1);
		}
	}
}
