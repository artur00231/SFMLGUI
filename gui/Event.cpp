#include "Event.h"

gui::Event::Event() : _focused_object{ nullptr }
{
}

void gui::Event::add(const sf::Event & event)
{
	if (event.type == sf::Event::MouseButtonPressed)
	{
		_mouse_info.setButtonState(event.mouseButton.button, true);
	}
	else if (event.type == sf::Event::MouseButtonReleased)
	{
		_mouse_info.setButtonState(event.mouseButton.button, false);
	}
	else if (event.type == sf::Event::TextEntered)
	{
		if (checkCharacter(event.text.unicode))
		{
			_input_text += event.text.unicode;
		}
	}
	else if (event.type == sf::Event::KeyPressed)
	{
		if (checkSpecialKey(event.key.code))
		{
			_special_keys.push_back(event.key.code);
		}
	}
	else if (event.type == sf::Event::MouseWheelScrolled)
	{
		_mouse_info.setMouseWheelMove(event.mouseWheelScroll.delta);
	}
	else if (event.type == sf::Event::MouseMoved)
	{
		auto mouse_position = event.mouseMove;
		_mouse_info.setMousePosition({ static_cast<float>(mouse_position.x), static_cast<float>(mouse_position.y) });
	}
}

void gui::Event::clear()
{
	_input_text.clear();
	_special_keys.clear();
	_mouse_info.update();
}

void gui::Event::getEvents(active_gui_object & object, const sf::Window & window)
{
	getEvents(object, window, object.getGlobalBounds());
}

void gui::Event::getEvents(active_gui_object & object, const sf::Window & window, const sf::Rect<float> & rect)
{
	if (!object.isActive())
	{
		return;
	}

	if (object.isFocused())
	{
		if (_focused_object != &object)
		{
			// Set focused object
			if (_focused_object != nullptr)
			{
				_focused_object->setFocus(false);
			}
			_focused_object = &object;
		}
	}

	// Reset all -Change
	object.setHoverChange(false);
	object.setClickedChange(false);

	if (rect.contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window))))
	{
		if (!object.isHover())
		{
			object.setHover(true);
			object.setHoverChange(true);
		}

		auto mouse_left_status = _mouse_info.getButtonState(sf::Mouse::Button::Left);

		// mouse_left_status.first <- cliked?
		// mouse_left_status.second <- cliked_change?
		if (mouse_left_status.first && mouse_left_status.second)
		{
			object.setClicked(true);
			object.setClickedChange(true);
			if (_focused_object != &object)
			{
				// Set focus
				object.setFocus(true);
				if (_focused_object != nullptr)
				{
					_focused_object->setFocus(false);
				}
				_focused_object = &object;
			}
		}
		else if (mouse_left_status.first)
		{
			object.setClicked(true);
		}
		else
		{
			if (object.isClicked())
			{
				object.setClicked(false);
				object.setClickedChange(true);
			}
		}

	}
	else
	{
		if (object.isHover())
		{
			object.setHover(false);
			object.setHoverChange(true);
		}

		if (object.isClicked())
		{
			object.setClicked(false);
			object.setClickedChange(true);
		}

	}

	if (gui::text_active_gui_object * text_object = dynamic_cast<gui::text_active_gui_object*>(&object))
	{
		if (text_object->isFocused() && _input_text.getSize() > 0)
		{
			text_object->addText(_input_text);
		}

		if (text_object->isFocused() && _special_keys.size() > 0)
		{
			text_object->addSpecialKeys(_special_keys);
		}
	}
}

void gui::Event::checkFocusedObject()
{
	if (_focused_object)
	{
		if (!_focused_object->isFocused())
		{
			_focused_object = nullptr;
		}
	}
}

void gui::Event::removeFocusedObject(gui_object * object)
{
	if (_focused_object == object)
	{
		_focused_object = nullptr;
	}
}

gui::Mouse_info & gui::Event::getMouseInfo()
{
	return _mouse_info;
}

bool gui::Event::checkCharacter(sf::Uint32 character)
{
	bool is_polish_character =
		(character == L'π' ||
			character == L'Ê' ||
			character == L'Í' ||
			character == L'≥' ||
			character == L'Ò' ||
			character == L'Û' ||
			character == L'ú' ||
			character == L'ø' ||
			character == L'ü' ||
			character == L'•' ||
			character == L'∆' ||
			character == L' ' ||
			character == L'£' ||
			character == L'—' ||
			character == L'”' ||
			character == L'å' ||
			character == L'Ø' ||
			character == L'è');

	// We want only latian and polish letters
	if (character < 128)
	{
		if (std::isspace(static_cast<int>(character)) || character == '\b' || std::iscntrl(static_cast<int>(character)))
		{
			return false;
		}
		else
		{
			return true;
		}

	}
	else if (is_polish_character)
	{
		return true;
	}

	return false;
}

bool gui::Event::checkSpecialKey(sf::Keyboard::Key key)
{
	return (key == sf::Keyboard::Tab ||
		key == sf::Keyboard::BackSpace ||
		key == sf::Keyboard::Delete ||
		key == sf::Keyboard::Right ||
		key == sf::Keyboard::Left ||
		key == sf::Keyboard::Up ||
		key == sf::Keyboard::Down ||
		key == sf::Keyboard::Space ||
		key == sf::Keyboard::Tab);
}