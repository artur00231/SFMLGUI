#include "Number_input.h"

gui::Number_input::Number_input(const sf::String & text) : _label{ text }, _up{ L'\u25B2' }, _down{ L'\u25BC' }
{
	// Set button functons
	_up.getFunction().set([this]() { this->add(); });
	_down.getFunction().set([this]() { this->subtract(); });

	// By default, set the input typ to INTEGRER
	setNumberInputType(gui::Number_input_type::INTEGRER);

	addText(text);
	getNumberFromText();
	checkNumber();
}

void gui::Number_input::setSize(const sf::Vector2f & size)
{
	_size = size;
	resize();
}

void gui::Number_input::setPosition(const sf::Vector2f & position)
{
	_position = position;

	float button_size_x = (_size.x - 2 * _frame.getThickness()) *  _proportions_text_button;
	float button_size_y = (_size.y - 2 * _frame.getThickness()) / 2;

	_label.setPosition({ position.x + _frame.getThickness(), position.y + _frame.getThickness() });
	_up.setPosition({ position.x + _frame.getThickness() + _label.getSize().x, position.y + _frame.getThickness() });
	_down.setPosition({ position.x + _frame.getThickness() + _label.getSize().x, position.y + _frame.getThickness() + button_size_y });

	sf::Rect<float> label_and_buttons{ { position.x + _frame.getThickness(), position.y + _frame.getThickness() }, {_label.getSize().x + button_size_x, _label.getSize().y } };

	_frame.fitTo(label_and_buttons);
	_background.fitTo(label_and_buttons);
}

const sf::Vector2f & gui::Number_input::getSize() const
{
	return _size;
}

const sf::Vector2f & gui::Number_input::getPosition() const
{
	return _position;
}

const sf::Rect<float> gui::Number_input::getGlobalBounds() const
{
	return _frame.getGlobalBounds();
}

void gui::Number_input::up_date(gui::duration time_elapsed, const Mouse_info & mouse_info)
{
	if (isFocused())
	{
		// The text pointer blinks only when the tex_input is focused
		_time_elapsed += time_elapsed.count();

		if (_time_elapsed > _text_pointer_time)
		{
			if (!_show_text_pointer)
			{
				_text.replace(_text_pointer_position, 1, _text_pointer_characters.first);
			}
			else
			{
				_text.replace(_text_pointer_position, 1, _text_pointer_characters.second);
			}
			_show_text_pointer = !_show_text_pointer;
			_time_elapsed -= 500000;
		}

	}

	_function(mouse_info, time_elapsed, this);

	setLabelString();
}

void gui::Number_input::draw(sf::RenderTarget & render_target) const
{
	_background.draw(render_target);
	_label.draw(render_target);
	_up.draw(render_target);
	_down.draw(render_target);
	_frame.draw(render_target);
}

void gui::Number_input::setOwner(gui::owner & owner)
{
	owner.addObject(_up);
	owner.addObject(_down);

	auto owner_text_style = owner.getTextStyle();
	_label.setTextStyle(owner_text_style);
}

void gui::Number_input::removeFromOwner(owner & owner)
{
	owner.remove(&_up);
	owner.remove(&_down);
}

bool gui::Number_input::isActive() const
{
	return _active;
}

bool gui::Number_input::isHover() const
{
	return _hover;
}

bool gui::Number_input::isClicked() const
{
	return _clicked;
}

bool gui::Number_input::isFocused() const
{
	return _focus;
}

bool gui::Number_input::isHoverChange() const
{
	return _hover_change;
}

bool gui::Number_input::isClickedChange() const
{
	return _clicked_change;
}

bool gui::Number_input::isNeedResize() const
{
	return _need_resize;
}

void gui::Number_input::setActive(bool active)
{
	_active = active;
}

void gui::Number_input::setFocus(bool focus)
{

	if (_focus != focus)
	{
		_focus = focus;

		if (focus)
		{
			_time_elapsed = _text_pointer_time + 1;
			_show_text_pointer = true;
			showTextPointer();
		}
		else
		{
			_text.erase(_text_pointer_position);
			getNumberFromText();
			checkNumber();
			setNumber();
		}
	}
}

void gui::Number_input::addText(const sf::String & text)
{
	
	sf::String filtered_text;

	hideTextPointer();

	bool possible_to_add_dot = (_text.find('.') == sf::String::InvalidPos) && (_number_input_type == gui::Number_input_type::REAL);
	bool possible_to_add_minus = (_text_pointer_position == 0 && _text.find('-') == sf::String::InvalidPos);

	for (auto x : text)
	{
		if (std::isdigit(static_cast<unsigned int>(x)))
		{
			filtered_text += x;
		}

		if (x == '.' && possible_to_add_dot)
		{
			if ((_text.getSize() == 0 || (_text.getSize() == 1 && _text[0] == '-')) && filtered_text.getSize() == 0)
			{
				filtered_text += "0";
			}

			filtered_text += x;
		}

		if (x == '-' && possible_to_add_minus)
		{
			filtered_text += x;
		}
	}

	showTextPointer();

	if (filtered_text.getSize() > 0)
	{
		hideTextPointer();

		_text.insert(_text_pointer_position, filtered_text);

		_text_pointer_position += filtered_text.getSize();

		showTextPointer();
	}
}

void gui::Number_input::addSpecialKeys(const std::deque<sf::Keyboard::Key> & keys)
{
	for (auto x : keys)
	{
		if (x == sf::Keyboard::BackSpace)
		{
			if (_text_pointer_position > 0)
			{
				// Remove the letter behind the text pointer
				hideTextPointer();

				--_text_pointer_position;
				_text.erase(_text_pointer_position);

				showTextPointer();
			}
		}
		else if (x == sf::Keyboard::Delete)
		{
			if (_text.getSize() > _text_pointer_position)
			{
				// Remove the letter in front of the text pointer
				hideTextPointer();

				_text.erase(_text_pointer_position);

				showTextPointer();
			}
		}
		else if (x == sf::Keyboard::Right)
		{
			if (_text.getSize() > _text_pointer_position + 1)
			{
				// Move the text pointer right
				hideTextPointer();

				++_text_pointer_position;

				showTextPointer();
			}
		}
		else if (x == sf::Keyboard::Left)
		{
			if (_text_pointer_position > 0)
			{
				// Move the text pointer left
				hideTextPointer();

				--_text_pointer_position;

				showTextPointer();
			}
		}
	}
}

void gui::Number_input::setNumberInputType(gui::Number_input_type number_input_type)
{
	if (number_input_type == gui::Number_input_type::INTEGRER)
	{
		_max.l_val = std::numeric_limits<long long>::max();
		_min.l_val = std::numeric_limits<long long>::min();
		_value.l_val = 0;
		_step.l_val = 1;
		_number_input_type = gui::Number_input_type::INTEGRER;
	}
	else
	{
		_max.d_val = std::numeric_limits<double>::max();
		_min.d_val = -std::numeric_limits<double>::max();
		_value.d_val = 0;
		_step.d_val = 1;
		_number_input_type = gui::Number_input_type::REAL;
	}

	hideTextPointer();
	_text = "0";
	showTextPointer();

	setLabelString();
}

void gui::Number_input::setMinMaxValue(double min, double max)
{
	if (_number_input_type == gui::Number_input_type::INTEGRER)
	{
		_min.l_val = static_cast<long long>(min);
		_max.l_val = static_cast<long long>(max);
	}
	else
	{
		_min.d_val = min;
		_max.d_val = max;
	}

	checkNumber();
	setNumber();
}

void gui::Number_input::setMinMaxValue(long long min, long long max)
{
	if (_number_input_type == gui::Number_input_type::INTEGRER)
	{
		_min.l_val = min;
		_max.l_val = max;
	}
	else
	{
		_min.d_val = static_cast<double>(min);
		_max.d_val = static_cast<double>(min);
	}

	checkNumber();
	setNumber();
}

void gui::Number_input::setStepValue(double step)
{
	if (_number_input_type == gui::Number_input_type::INTEGRER)
	{
		_step.l_val = static_cast<long long>(step);
	}
	else
	{
		_step.d_val = step;
	}
}

void gui::Number_input::setStepValue(long long step)
{
	if (_number_input_type == gui::Number_input_type::INTEGRER)
	{
		_step.l_val = step;
	}
	else
	{
		_step.d_val = static_cast<double>(step);
	}
}

void gui::Number_input::setProportionsTextButton(float proportions_text_button)
{
	_proportions_text_button = proportions_text_button;
}

void gui::Number_input::clear()
{
	hideTextPointer();

	_text_pointer_position = 0;
	_text = "";

	showTextPointer();
}

const sf::String& gui::Number_input::getString() const
{
	return _text;
}

long long gui::Number_input::getLongLong() const
{
	getNumberFromText();
	checkNumber();

	if (_number_input_type == gui::Number_input_type::INTEGRER)
	{
		return _value.l_val;
	}
	else
	{
		return static_cast<long long>(_value.d_val);
	}
}

double gui::Number_input::getDouble() const
{
	getNumberFromText();
	checkNumber();

	if (_number_input_type == gui::Number_input_type::INTEGRER)
	{
		return static_cast<double>(_value.l_val);
	}
	else
	{
		return _value.d_val;
	}
}

std::pair<double, double> gui::Number_input::getDoubleMinMaxValue() const
{
	if (_number_input_type == gui::Number_input_type::INTEGRER)
	{
		return std::pair<double, double>{static_cast<double>(_min.l_val), static_cast<double>(_min.l_val) };
	}
	else
	{
		return std::pair<double, double>{_min.d_val, _min.d_val };
	}
}

std::pair<long long, long long> gui::Number_input::getLongLongMinMaxValue() const
{
	if (_number_input_type == gui::Number_input_type::INTEGRER)
	{
		return std::pair<long long, long long>{_min.l_val, _min.l_val };
	}
	else
	{
		return std::pair<long long, long long>{static_cast<long long>(_min.d_val), static_cast<long long>(_min.d_val) };
	}
}

double gui::Number_input::getDoubleStepValue() const
{
	if (_number_input_type == gui::Number_input_type::INTEGRER)
	{
		return static_cast<double>(_step.l_val);
	}
	else
	{
		return _step.d_val;
	}
}

long long gui::Number_input::getLongLongStepValue() const
{
	if (_number_input_type == gui::Number_input_type::INTEGRER)
	{
		return _step.l_val;
	}
	else
	{
		return static_cast<long long>(_step.d_val);
	}
}

double gui::Number_input::getProportionsTextButton() const
{
	return _proportions_text_button;
}

void gui::Number_input::resize()
{
	_need_resize = false;

	if (_size.x - 2 * _frame.getThickness() > 0 && _size.y - 2 * _frame.getThickness() > 0)
	{
		float button_size_x = (_size.x - 2 * _frame.getThickness()) * _proportions_text_button;
		float button_size_y = (_size.y - 2 * _frame.getThickness()) / 2;

		// button_character_size_base = std::min({button_size_x, button_size_y});
		float button_character_size_base = button_size_x < button_size_y ? button_size_x : button_size_y;

		unsigned int button_character_size = static_cast<unsigned int>(std::floor(button_character_size_base * 0.8f));

		_up.getLabel().setCharacterSize(button_character_size);
		_down.getLabel().setCharacterSize(button_character_size);

		_label.setSize({ _size.x - 2 * _frame.getThickness() - button_size_x, _size.y - 2 * _frame.getThickness() });
		_up.setSize({ button_size_x , button_size_y });
		_down.setSize({ button_size_x , button_size_y });
		_frame.fitTo(_label);
		_background.fitTo(_label);
	}
	else
	{
		// Can not fit number_input
		// Minimal size is 2 * _frame.getThickness()
		_size = { 2 * _frame.getThickness() , 2 * _frame.getThickness() };
		_label.setSize({ 0, 0 });
		_up.setSize({ 0, 0 });
		_down.setSize({ 0, 0 });
		_frame.fitTo(_label);
		_background.fitTo(_label);
	}

	std::string a = _text.toAnsiString();

	setPosition(_position);
}

gui::modifier::Frame_modifier & gui::Number_input::getFrame()
{
	_need_resize = true;
	return _frame;
}

gui::modifier::Label_modifier & gui::Number_input::getLabel()
{
	_need_resize = true;
	return _label;
}

gui::modifier::Background_modifier & gui::Number_input::getBackground()
{
	_need_resize = true;
	return _background;
}

gui::modifier::Function_modifier & gui::Number_input::getFunction()
{
	return _function;
}

void gui::Number_input::setHover(bool hover)
{
	_hover = hover;
}

void gui::Number_input::setClicked(bool clicked)
{
	_clicked = clicked;
}

void gui::Number_input::setHoverChange(bool hover_change)
{
	_hover_change = hover_change;
}

void gui::Number_input::setClickedChange(bool clicked_change)
{
	_clicked_change = clicked_change;
}

void gui::Number_input::hideTextPointer() const
{
	if (isFocused())
	{
		_text.erase(_text_pointer_position);
	}
}

void gui::Number_input::showTextPointer() const
{
	if (isFocused())
	{
		if (_show_text_pointer)
		{
			_text.insert(_text_pointer_position, _text_pointer_characters.second);
		}
		else
		{
			_text.insert(_text_pointer_position, _text_pointer_characters.first);

		}
	}
}

void gui::Number_input::setLabelString()
{

	if (_label.getString() != _text)
	{
		_label.setString(_text);
	}

	if (_label.getStatus() == gui::Text_status::TOO_BIG)
	{
		// Erase one character
		hideTextPointer();

		if (_text.getSize() > 1)
		{
			_text.erase(_text.getSize() - 1);
			--_text_pointer_position;
			setLabelString();
		}

		showTextPointer();
	}
}

void gui::Number_input::setNumber()
{
	if (_number_input_type == gui::Number_input_type::INTEGRER)
	{
		_text = std::to_string(_value.l_val);
		_text_pointer_position = _text.getSize();
	}
	else
	{
		_text = std::to_string(_value.d_val);
		_text_pointer_position = _text.getSize();
	}

	setLabelString();
}

void gui::Number_input::checkNumber() const
{
	if (_number_input_type == gui::Number_input_type::REAL)
	{
		if (_value.d_val > _max.d_val)
		{
			_value.d_val = _max.d_val;
		}
		else if (_value.d_val < _min.d_val)
		{
			_value.d_val = _min.d_val;
		}
	}
	else
	{
		if (_value.l_val > _max.l_val)
		{
			_value.l_val = _max.l_val;
		}
		else if (_value.l_val < _min.l_val)
		{
			_value.l_val = _min.l_val;
		};
	}
}

void gui::Number_input::getNumberFromText() const
{
	hideTextPointer();

	sf::String text_number = _text;

	showTextPointer();

	if (text_number.getSize() == 0)
	{
		text_number = "0";

	}
	else if (text_number.getSize() == 1)
	{
		if (text_number[0] == '-' || text_number[0] == '.')
		{
			text_number = "0";
		}
	}
	else
	{
		if (text_number[0] == '.')
		{
			text_number.insert(0, '0');
		}
	}

	if (_number_input_type == gui::Number_input_type::REAL)
	{
		_value.d_val = std::atof(text_number.toAnsiString().c_str());
	}
	else
	{
		_value.l_val = std::atoll(text_number.toAnsiString().c_str());
	}
}

void gui::Number_input::add()
{
	if (_up.isClickedChange())
	{
		if (_up.isClicked())
		{
			auto color = _up.getLabel().getColor();
			color.a = 100;
			_up.getLabel().setColor(color);

			addNumber();
		}
		else
		{
			auto color = _up.getLabel().getColor();
			color.a = 255;
			_up.getLabel().setColor(color);
		}

		_down.setFocus(false);
		setFocus(true);
	}
}

void gui::Number_input::addNumber()
{
	getNumberFromText();

	if (_number_input_type == gui::Number_input_type::INTEGRER)
	{
		long long value = _value.l_val;
		value += _step.l_val;
		if (_value.l_val < value)
		{
			_value.l_val += _step.l_val;
		}
	}
	else
	{
		double value = _value.d_val;
		value += _step.d_val;
		if (_value.d_val < value)
		{
			_value.d_val += _step.d_val;
		}
	}

	checkNumber();
	setNumber();
}

void gui::Number_input::subtract()
{
	if (_down.isClickedChange())
	{
		if (_down.isClicked())
		{
			auto color = _down.getLabel().getColor();
			color.a = 100;
			_down.getLabel().setColor(color);

			subtractNumber();
		}
		else
		{
			auto color = _down.getLabel().getColor();
			color.a = 255;
			_down.getLabel().setColor(color);
		}

		_down.setFocus(false);
		setFocus(true);
	}
}

void gui::Number_input::subtractNumber()
{
	getNumberFromText();

	if (_number_input_type == gui::Number_input_type::INTEGRER)
	{
		long long value = _value.l_val;
		value -= _step.l_val;
		if (_value.l_val > value)
		{
			_value.l_val -= _step.l_val;
		}
	}
	else
	{
		double value = _value.d_val;
		value -= _step.d_val;
		if (_value.d_val > value)
		{
			_value.d_val -= _step.d_val;
		}
	}

	checkNumber();
	setNumber();
}
