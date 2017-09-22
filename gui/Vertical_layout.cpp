#include "Vertical_layout.h"

gui::Vertical_layout::Vertical_layout(const Text_style * text_style) : _default_text_style{ _default_font }
{
	if (text_style)
	{
		_default_text_style = *text_style;
	}
}

gui::Vertical_layout::Vertical_layout(Vertical_layout && vertical_layout)
	: _gui_objects{ std::move(vertical_layout._gui_objects) },
	_default_text_style{ std::move(vertical_layout._default_text_style) },
	_position{std::move(vertical_layout._position)},
	_size{ std::move(vertical_layout._size) },
	_owner{ vertical_layout._owner }
{
}

void gui::Vertical_layout::setSize(const sf::Vector2f & size)
{
	_size = size;

	re_size();
}

void gui::Vertical_layout::setPosition(const sf::Vector2f & position)
{
	_position = position;

	re_size();
}

const sf::Vector2f & gui::Vertical_layout::getSize() const
{
	return _size;
}

const sf::Vector2f & gui::Vertical_layout::getPosition() const
{
	return _position;
}

const sf::Rect<float> gui::Vertical_layout::getGlobalBounds() const
{
	return sf::Rect<float>{ _position, _size };
}

void gui::Vertical_layout::setOwner(owner & owner)
{
	_owner = &owner;

	_default_text_style = owner.getTextStyle();

	for (auto &x : _gui_objects)
	{
		x.second.first->setOwner(*this);
	}
}

void gui::Vertical_layout::removeFromOwner(owner & owner)
{
	for (auto x : _gui_objects)
	{
		_owner->eventRemoveFocusedObject(x.second.first);
	}

	_owner = nullptr;
}

void gui::Vertical_layout::draw(sf::RenderTarget & window) const
{
	for (auto &x : _gui_objects)
	{
		x.second.first->draw(window);
	}
}

gui::gui_object * gui::Vertical_layout::addObject(gui::gui_object * object, const std::string & name)
{
	return addToMap(object, name, false);
}

gui::gui_object * gui::Vertical_layout::addObject(gui::gui_object & object, const std::string & name)
{
	return addToMap(object, name, false);
}

void gui::Vertical_layout::remove(const std::string & name)
{
	if (_gui_objects.count(name) > 0)
	{
		auto to_erase = _gui_objects[name];

		eventRemoveFocusedObject(to_erase.first);

		to_erase.first->removeFromOwner(*this);

		if (to_erase.second.first)
		{
			delete to_erase.first;
		}

		_gui_objects.erase(name);

		auto it = std::remove(_ordered_objects.begin(), _ordered_objects.end(), to_erase.first);

		if (it != _ordered_objects.end())
		{
			_ordered_objects.erase(it);
		}

		re_size();
	}
}

void gui::Vertical_layout::remove(const gui::gui_object * object)
{
	decltype(_gui_objects.end()) poz = _gui_objects.end();

	for (auto i = _gui_objects.begin(); i != _gui_objects.end(); i++)
	{
		if (object == i->second.first)
		{
			poz = i;
			break;
		}
	}

	if (poz != _gui_objects.end())
	{
		eventRemoveFocusedObject(poz->second.first);

		poz->second.first->removeFromOwner(*this);

		if (poz->second.second.first)
		{
			delete poz->second.first;
		}

		_gui_objects.erase(poz);

		auto it = std::remove(_ordered_objects.begin(), _ordered_objects.end(), poz->second.first);

		if (it != _ordered_objects.end())
		{
			_ordered_objects.erase(it);
		}

		re_size();
	}
}

void gui::Vertical_layout::getEvents(active_gui_object & object, const sf::Window & window)
{
	if (_owner)
	{
		_owner->getEvents(object, window);
	}
}

void gui::Vertical_layout::getEvents(active_gui_object & object, const sf::Window & window, const sf::Rect<float>& rect)
{
	if (_owner)
	{
		_owner->getEvents(object, window, rect);
	}
}

void gui::Vertical_layout::eventRemoveFocusedObject(gui_object * object)
{
	if (_owner)
	{
		_owner->eventRemoveFocusedObject(object);
	}
}

const gui::Mouse_info & gui::Vertical_layout::getMouseInfo() const
{
	return _mouse_info;
}

gui::gui_object * gui::Vertical_layout::get(const std::string & name) const
{
	return _gui_objects.at(name).first;
}

void gui::Vertical_layout::up_date(const sf::Window & window, gui::duration time_elapsed, owner & owner)
{
	_mouse_info = owner.getMouseInfo();

	std::vector<gui::Radio_button*> radio_buttons;

	for (auto &x : _gui_objects)
	{
		if (gui::active_gui_object * object = dynamic_cast<gui::active_gui_object*>(x.second.first))
		{
			if (object->isNeedResize())
			{
				object->resize();
			}

			if (gui::Radio_button * radio_button = dynamic_cast<gui::Radio_button*>(x.second.first))
			{
				if (radio_button->getState() == gui::Radio_button_state::CHECKED && !radio_button->isExlusive())
				{
					radio_buttons.push_back(radio_button);
				}
			}

			owner.getEvents(*object, window);
			object->up_date(std::chrono::duration_cast<std::chrono::microseconds>(time_elapsed), owner.getMouseInfo());
		}
		else if (gui::managing_gui_object * managing_object = dynamic_cast<gui::managing_gui_object*>(x.second.first))
		{
			managing_object->up_date(window, std::chrono::duration_cast<std::chrono::microseconds>(time_elapsed), owner);
		}
	}

	checkRadio_buttons(radio_buttons);
}

void gui::Vertical_layout::setTextStyle(const Text_style & text_style)
{
	_default_text_style = text_style;
}

const gui::Text_style& gui::Vertical_layout::getTextStyle() const
{
	return _default_text_style;
}

void gui::Vertical_layout::re_size()
{
	float objects_height = _size.y / _ordered_objects.size();
	float objects_position_y = _position.y;

	for (auto &x : _ordered_objects)
	{
		x->setSize({ _size.x, objects_height });
		x->setPosition({ _position.x, objects_position_y });
		objects_position_y += objects_height;
	}
}

gui::Vertical_layout::~Vertical_layout()
{
	for (auto &x : _gui_objects)
	{
		if (x.second.second.first)
		{
			delete x.second.first;
		}
	}
}

void gui::Vertical_layout::checkRadio_buttons(std::vector<gui::Radio_button*> & radio_buttons)
{
	if (radio_buttons.size() > 1)
	{
		gui::Radio_button * clicked_radio_button = nullptr;

		for (auto x : radio_buttons)
		{
			if (x->isClicked())
			{
				clicked_radio_button = x;
				break;
			}
		}

		for (auto x : radio_buttons)
		{
			if (x != clicked_radio_button)
			{
				x->setState(gui::Radio_button_state::UNCHECKED);
			}
		}
	}
}

std::string gui::Vertical_layout::getUniqeName()
{
	std::string name{ "___" };
	name += std::to_string(_uniqe_name_count++);
	return name;
}

gui::gui_object * gui::Vertical_layout::addToMap(gui::gui_object * object, const std::string & name, bool add_to_layout)
{
	std::string object_name = name;

	if (object_name == "")
	{
		object_name = getUniqeName();
	}

	if (_gui_objects.count(object_name) == 1)
	{
		remove(object_name);
	}

	std::pair<std::string, std::pair<gui::gui_object*, std::pair<bool, bool>>> pair{ object_name,{ object, {true, add_to_layout } } };
	_gui_objects.insert(pair);
	{
		_ordered_objects.push_back(object);
	}
	object->setOwner(*this);

	re_size();

	return object;
}

gui::gui_object * gui::Vertical_layout::addToMap(gui::gui_object & object, const std::string & name, bool add_to_layout)
{
	std::string object_name = name;

	if (object_name == "")
	{
		object_name = getUniqeName();
	}

	if (_gui_objects.count(object_name) == 1)
	{
		remove(object_name);
	}

	std::pair<std::string, std::pair<gui::gui_object*, std::pair<bool, bool>>> pair{ object_name,{ &object, {false, add_to_layout } } };
	_gui_objects.insert(pair);
	if (add_to_layout)
	{
		_ordered_objects.push_back(&object);
	}
	object.setOwner(*this);

	re_size();

	return &object;
}

sf::Font gui::Vertical_layout::_default_font;