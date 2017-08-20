#ifndef GUI_EVENT_H
#define GUI_EVENT_H

#include "SFML\Graphics.hpp"
#include "active_gui_object.h"
#include "text_active_gui_object.h"
#include <deque>
#include <cctype>

namespace gui
{

	class Event
	{
	public:
		void add(const sf::Event & event);
		void clear();
		void getEvents(active_gui_object & object, const sf::Window & window);
		void checkFocusedObject();

	protected:
		bool checkCharacter(sf::Uint32 character);
		bool checkSpecialKey(sf::Keyboard::Key key);

	private:
		Mouse_events _events;
		sf::String _input_text;
		active_gui_object * _focused_object;
		std::deque<sf::Keyboard::Key> _special_keys;
	};

}

#endif // !GUI_EVENT_H
