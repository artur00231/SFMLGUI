#include "Gui.h"

gui::Gui::Gui(const Text_style & text_style) : _default_text_style{ text_style }
{
	_mouse_info_pointer = &_event.getMouseInfo();

	// Start the timer
	_last_time = clock.now();
}

gui::Gui::Gui(Gui && gui) : _gui_objects{std::move(gui._gui_objects)}, _default_text_style{std::move(gui._default_text_style)}, _last_time{std::move(gui._last_time)}, _event{std::move(gui._event)}
{
	_mouse_info_pointer = &_event.getMouseInfo();
}

void gui::Gui::draw(sf::RenderTarget & window) const
{
	for (auto &x : _gui_objects)
	{
		x.second.first->draw(window);
	}
}

gui::gui_object * gui::Gui::addObject(gui::gui_object * object, const std::string & name)
{
	return addToGui(object, name);
}

gui::gui_object * gui::Gui::addObject(gui::gui_object & object, const std::string & name)
{
	return addToGui(object, name);
}

void gui::Gui::remove(const std::string & name)
{
	auto to_erase = _gui_objects[name];

	to_erase.first->removeFromOwner(*this);

	if (to_erase.second)
	{
		delete to_erase.first;
	}

	_gui_objects.erase(name);
}

void gui::Gui::remove(const gui::gui_object * object)
{
	decltype(_gui_objects.end()) poz = _gui_objects.end();

	// Find the iterator to the object
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
		poz->second.first->removeFromOwner(*this);

		if (poz->second.second)
		{
			delete poz->second.first;
		}

		_gui_objects.erase(poz);
	}
}

void gui::Gui::getEvents(active_gui_object & object, const sf::Window & window)
{
	_event.getEvents(object, window);
}

void gui::Gui::getEvents(active_gui_object & object, const sf::Window & window, const sf::Rect<float>& rect)
{
	_event.getEvents(object, window, rect);
}

const gui::Mouse_info & gui::Gui::getMouseInfo() const
{
	return *_mouse_info_pointer;
}

gui::gui_object * gui::Gui::get(const std::string & name) const
{
	return _gui_objects.at(name).first;
}

void gui::Gui::up_date(const sf::Window & window)
{
	auto time_elapsed = clock.now() - _last_time;

	std::vector<gui::Radio_button*> radio_buttons;

	_event.checkFocusedObject();

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

			_event.getEvents(*object, window);
			object->up_date(std::chrono::duration_cast<std::chrono::microseconds>(time_elapsed), *_mouse_info_pointer);
		}
		else if (gui::managing_gui_object * managing_object = dynamic_cast<gui::managing_gui_object*>(x.second.first))
		{
			managing_object->up_date(window, std::chrono::duration_cast<std::chrono::microseconds>(time_elapsed), *this);
		}
	}

	checkRadio_buttons(radio_buttons);

	_event.clear();
	_last_time = clock.now();
}

void gui::Gui::drawAndUp_date(sf::RenderTarget & render_target, const sf::Window & window)
{
	up_date(window);
	draw(render_target);
}

void gui::Gui::drawAndUp_date(sf::RenderWindow & render_window)
{
	drawAndUp_date(render_window, render_window);
}

void gui::Gui::addEvent(const sf::Event & event)
{
	_event.add(event);
}

void gui::Gui::setTextStyle(const Text_style & text_style)
{
	_default_text_style = text_style;
}

const gui::Text_style& gui::Gui::getTextStyle() const
{
	return _default_text_style;
}

gui::Gui::~Gui()
{
	for (auto &x : _gui_objects)
	{
		if (x.second.second)
		{
			delete x.second.first;
		}
	}
}

void gui::Gui::checkRadio_buttons(std::vector<gui::Radio_button*> & radio_buttons)
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

std::string gui::Gui::getUniqeName()
{
	// All unique names start with "___"
	// Examples: "___1", "___2", "___105"
	std::string name{"___"};
	name += std::to_string(_uniqe_name_count++);
	return name;
}

gui::gui_object * gui::Gui::addToGui(gui::gui_object * object, const std::string & name)
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
	object->setOwner(*this);
	return object;
}

gui::gui_object * gui::Gui::addToGui(gui::gui_object & object, const std::string & name)
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
	object.setOwner(*this);
	return &object;
}