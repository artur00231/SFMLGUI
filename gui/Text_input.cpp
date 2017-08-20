#include "Text_input.h"

gui::Text_input::Text_input(const sf::String & text)
{
	addText(text);
}

void gui::Text_input::setSize(const sf::Vector2f & size)
{
	_size = size;
	resize();
}

void gui::Text_input::setPosition(const sf::Vector2f & position)
{
	_position = position;

	_label.setPosition({ position.x + _frame.getThickness(), position.y + _frame.getThickness() });
	_frame.fitTo(_label);
	_background.fitTo(_label);
}

const sf::Vector2f & gui::Text_input::getSize() const
{
	return _size;
}

const sf::Vector2f & gui::Text_input::getPosition() const
{
	return _position;
}

const sf::Rect<float> gui::Text_input::getGlobalBounds() const
{
	return _frame.getGlobalBounds();
}

void gui::Text_input::up_date(gui::duration time_elapsed)
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

	_function(_events, time_elapsed, this);

	setLabelString();

	_events.clear();
}

void gui::Text_input::draw(sf::RenderTarget & render_target) const
{
	_background.draw(render_target);
	_label.draw(render_target);
	_frame.draw(render_target);
}

void gui::Text_input::setOwner(gui::owner & owner)
{
	_label.setTextStyle(owner.getTextStyle());
}

bool gui::Text_input::isActive() const
{
	return _active;
}

bool gui::Text_input::isHover() const
{
	return _hover;
}

bool gui::Text_input::isClicked() const
{
	return _clicked;
}

bool gui::Text_input::isFocused() const
{
	return _focus;
}

bool gui::Text_input::isHoverChange() const
{
	return _hover_change;
}

bool gui::Text_input::isClickedChange() const
{
	return _clicked_change;
}

bool gui::Text_input::isNeedResize() const
{
	return _need_resize;
}

bool gui::Text_input::isPassword() const
{
	return _password;
}

void gui::Text_input::setActive(bool active)
{
	_active = active;
}

void gui::Text_input::setFocus(bool focus)
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
		hideTextPointer();
	}
}

void gui::Text_input::addText(const sf::String & text)
{
	hideTextPointer();

	_text.insert(_text_pointer_position, text);

	_text_pointer_position += text.getSize();

	showTextPointer();
}

void gui::Text_input::addSpecialKeys(const std::deque<sf::Keyboard::Key> & keys)
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
		else if (x == sf::Keyboard::Space)
		{
			// Add the space	
			addText(' ');
		}
	}
}

void gui::Text_input::setString(const sf::String & text)
{
	hideTextPointer();

	_text_pointer_position = text.getSize();
	_text = text;

	showTextPointer();
}

void gui::Text_input::clear()
{
	hideTextPointer();

	_text_pointer_position = 0;
	_text = "";

	showTextPointer();
}

void gui::Text_input::setPassword(bool password)
{
	_password = password;
	resize();
}

const sf::String& gui::Text_input::getString() const
{
	return _text;
}

void gui::Text_input::resize()
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
		// Can not fit text_input
		// Minimal size is 2 * _frame.getThickness()
		_size = { 2 * _frame.getThickness() , 2 * _frame.getThickness() };
		_label.setSize({ 0, 0 });
		_frame.fitTo(_label);
		_background.fitTo(_label);
	}

	setLabelString();


	setPosition(_position);
}

gui::modifier::Frame_modifier & gui::Text_input::getFrame()
{
	_need_resize = true;
	return _frame;
}

gui::modifier::Label_modifier & gui::Text_input::getLabel()
{
	_need_resize = true;
	return _label;
}

gui::modifier::Background_modifier & gui::Text_input::getBackground()
{
	_need_resize = true;
	return _background;
}

gui::modifier::Function_modifier & gui::Text_input::getFunction()
{
	return _function;
}

void gui::Text_input::setHover(bool hover)
{
	_hover = hover;
}

void gui::Text_input::setClicked(bool clicked)
{
	_clicked = clicked;
}

void gui::Text_input::setHoverChange(bool hover_change)
{
	_hover_change = hover_change;
}

void gui::Text_input::setClickedChange(bool clicked_change)
{
	_clicked_change = clicked_change;
}

gui::Mouse_events& gui::Text_input::getMouse_event()
{
	return _events;
}

void gui::Text_input::hideTextPointer()
{
	_text.erase(_text_pointer_position);
}

void gui::Text_input::showTextPointer()
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

void gui::Text_input::setLabelString()
{

	sf::String text_buffer;

	if (_password)
	{
		// Replace all characters with the one character
		if (_focus)
		{
			hideTextPointer();
		}

		for (auto x : _text)
		{
			text_buffer += _password_character;
		}

		if (_focus)
		{
			showTextPointer();

			if (_show_text_pointer)
			{
				text_buffer.insert(_text_pointer_position, _text_pointer_characters.second);
			}
			else
			{
				text_buffer.insert(_text_pointer_position, _text_pointer_characters.first);

			}
		}

	}
	else
	{
		text_buffer = _text;
	}

	if (_label.getString() != text_buffer)
	{
		_label.setString(text_buffer);
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
