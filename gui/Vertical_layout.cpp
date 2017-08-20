#include "Vertical_layout.h"

gui::Vertical_layout::Vertical_layout(const Text_style & text_style, gui::owner & owner) : _owner{&owner}
{
	_default_text_style = text_style;
}

void gui::Vertical_layout::setSize(const sf::Vector2f & size)
{
	_size = size;
}

void gui::Vertical_layout::setPosition(const sf::Vector2f & position)
{
	_position = position;
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
	_default_text_style = owner.getTextStyle();
}

void gui::Vertical_layout::draw(sf::RenderTarget & window) const
{
	for (auto &x : _gui_objects)
	{
		x.second.first->draw(window);
	}
}

gui::gui_object * gui::Vertical_layout::add(gui::gui_object * object, const std::string & name)
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

	std::pair<std::string, std::pair<gui::gui_object*, bool>> pair{ object_name,{ object, true } };
	_gui_objects.insert(pair);
	object->setOwner(*_owner);

	re_size();

	return object;
}

gui::gui_object * gui::Vertical_layout::add(gui::gui_object & object, const std::string & name)
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

	std::pair<std::string, std::pair<gui::gui_object*, bool>> pair{ object_name,{ &object, false } };
	_gui_objects.insert(pair);
	object.setOwner(*_owner);

	re_size();

	return &object;
}

void gui::Vertical_layout::remove(const std::string & name)
{
	_gui_objects.erase(name);

	re_size();
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
		if (poz->second.second)
		{
			delete poz->second.first;
		}

		_gui_objects.erase(poz);
	}

	re_size();
}

gui::gui_object * gui::Vertical_layout::get(const std::string & name) const
{
	return _gui_objects.at(name).first;
}

void gui::Vertical_layout::up_date(const sf::Window & window, gui::duration time_elapsed, Event & event)
{
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

			event.getEvents(*object, window);
			object->up_date(time_elapsed);
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
	float objects_height = _size.y / _gui_objects.size();
	float objects_position_y = _position.y;

	for (auto x : _gui_objects)
	{
		x.second.first->setSize({ _size.y, objects_height });
		x.second.first->setPosition({ _position.x, objects_position_y });
		objects_position_y += objects_height;
	}
}

gui::Vertical_layout::~Vertical_layout()
{
	for (auto &x : _gui_objects)
	{
		if (x.second.second)
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