#include "Horizontal_slider.h"

gui::Horizontal_slider::Horizontal_slider(long long max, long long min) : _left{"<"}, _right{">"}, _max{ max }, _min{ min }
{
	sf::Color gray{ 171, 171, 171, 255 };

	_left.getBackground().setColor(gray);
	_left.getFunction().set([this]() {this->subtract(); });
	_right.getBackground().setColor(gray);
	_right.getFunction().set([this]() {this->add(); });

	_middle.getBackground().setColor(gray);
	_middle.getFrame().setThickness(1);
	_middle.getFrame().setColor(sf::Color::Black);
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

	auto current_step = getCurrentStep();

	_middle.setPosition({ _position.x + frame_thickness + _left.getSize().x + current_step * _middle_button_min_size.x, _position.y + frame_thickness });

	sf::Rect<float> to_fit{ { _position.x + frame_thickness,  _position.y + frame_thickness }, { _size.x - 2 * frame_thickness, _size.y - 2 * frame_thickness } };
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

void gui::Horizontal_slider::up_date(gui::duration time_elapsed, const Mouse_info & mouse_info)
{
	setMiddleButtonPosition(mouse_info);

	_function(mouse_info, time_elapsed, this);
}

void gui::Horizontal_slider::draw(sf::RenderTarget & render_target) const
{
	_background.draw(render_target);
	_left.draw(render_target);
	_right.draw(render_target);
	_middle.draw(render_target);
	_frame.draw(render_target);
}

void gui::Horizontal_slider::setOwner(owner & owner)
{
	owner.addObject(_left);
	owner.addObject(_right);
	owner.addObject(_middle);
}

void gui::Horizontal_slider::removeFromOwner(owner & owner)
{
	owner.remove(&_left);
	owner.remove(&_right);
	owner.remove(&_middle);
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
		auto color = _left.getLabel().getColor();
		color.a = 95;
		_left.getLabel().setColor(color);

		color = _right.getLabel().getColor();
		color.a = 255;
		_right.getLabel().setColor(color);
	}
	else if (_value == _max)
	{
		auto color = _right.getLabel().getColor();
		color.a = 95;
		_right.getLabel().setColor(color);

		color = _left.getLabel().getColor();
		color.a = 255;
		_left.getLabel().setColor(color);
	}
	else
	{
		auto color = _left.getLabel().getColor();
		color.a = 255;
		_left.getLabel().setColor(color);

		color = _right.getLabel().getColor();
		color.a = 255;
		_right.getLabel().setColor(color);
	}

	if (_value == _min && _value == _max)
	{
		auto color = _right.getLabel().getColor();
		color.a = 95;
		_right.getLabel().setColor(color);

		color = _left.getLabel().getColor();
		color.a = 95;
		_left.getLabel().setColor(color);
	}

	setPosition(_position);
}

void gui::Horizontal_slider::setMinMax(long long min, long long max)
{
	_min = min;
	_max = max;

	setValue(_value);

	resize();
}

long long gui::Horizontal_slider::getMax() const
{
	float middle_size_x = _size.x - 2 * _frame.getThickness() - 2 * _button_min_size.x;
	long long max_steps = static_cast<long long>(std::floor(middle_size_x / _middle_button_min_size.x)) - 1;

	return max_steps;
}

long long gui::Horizontal_slider::getValue() const
{
	return _value;
}

std::pair<long long, long long> gui::Horizontal_slider::getMinMax() const
{
	return std::pair<long long, long long>{ _min, _max };
}

void gui::Horizontal_slider::resize()
{
	_need_resize = false;

	bool fit_x = _size.x >= 2 * _button_min_size.x;
	bool fit_y = _size.y >= _button_min_size.y;

	float frame_thickness = _frame.getThickness();

	if (fit_x && fit_y)
	{
		sf::Vector2f button_size{ _button_min_size.x, _size.y - 2 * frame_thickness };
		_left.setSize(button_size);
		_right.setSize(button_size);

		long long steps = _max - _min;

		float middle_size_x = _size.x - 2 * frame_thickness - 2 * button_size.x;

		if (steps < 1)
		{
			_middle.setSize({ middle_size_x, _size.y - 2 * frame_thickness });
		}
		else
		{
			long long max_steps = static_cast<long long>(std::floor(middle_size_x / _middle_button_min_size.x)) - 1;

			if (max_steps < steps)
			{
				steps = max_steps;
				
				_max = _min + max_steps;

				setValue(_value);
			}

			if (max_steps < 2)
			{
				_middle.setSize({ middle_size_x, _size.y - 2 * frame_thickness });
			}
			else
			{
				_middle.setSize({ middle_size_x - steps * _middle_button_min_size.x , _size.y - 2 * frame_thickness });
			}
		}
	}
	else
	{
		if (!fit_x)
		{
			_size.x = 2 * _button_min_size.x + 2 * frame_thickness;
		}

		if (!fit_y)
		{
			_size.y = _button_min_size.y + 2 * frame_thickness;
		}

		resize();
	}

	setPosition(_position);
}

gui::modifier::Frame_modifier & gui::Horizontal_slider::getFrame()
{
	_need_resize = true;
	return _frame;
}

gui::modifier::Background_modifier & gui::Horizontal_slider::getBackground()
{
	_need_resize = true;
	return _background;
}

gui::modifier::Function_modifier & gui::Horizontal_slider::getFunction()
{
	_need_resize = true;
	return _function;
}

gui::modifier::Button_modifier & gui::Horizontal_slider::getLeft()
{
	_need_resize = true;
	return _left;
}

gui::modifier::Button_modifier & gui::Horizontal_slider::getRight()
{
	_need_resize = true;
	return _right;
}

gui::modifier::Button_modifier & gui::Horizontal_slider::getMiddle()
{
	_need_resize = true;
	return _middle;
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

unsigned long long gui::Horizontal_slider::getCurrentStep()
{
	return _value - _min;
}

void gui::Horizontal_slider::add()
{
	if (_right.isClickedChange() && _right.isClicked())
	{
		setValue(_value + 1);
	}
}

void gui::Horizontal_slider::subtract()
{
	if (_left.isClickedChange() && _left.isClicked())
	{
		setValue(_value - 1);
	}
}

void gui::Horizontal_slider::setMiddleButtonPosition(const Mouse_info & mouse_info)
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

	if (_mouse_move.x > _middle_button_min_size.x)
	{
		setValue(_value + 1);
		_mouse_move.x -= _middle_button_min_size.x;
	}
	else if (_mouse_move.x < -_middle_button_min_size.x)
	{
		setValue(_value - 1);
		_mouse_move.x += _middle_button_min_size.x;
	}

	if (isHover())
	{
		auto wheel_move = mouse_info.getMouseWheelMove();

		if (wheel_move > 0)
		{
			setValue(_value + 1);
		}
		else if (wheel_move < 0)
		{
			setValue(_value - 1);
		}
	}
}
