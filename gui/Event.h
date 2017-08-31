#ifndef GUI_EVENT_H
#define GUI_EVENT_H

#include "SFML\Graphics.hpp"
#include "active_gui_object.h"
#include "text_active_gui_object.h"
#include "Mouse_info.h"
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
		void getEvents(active_gui_object & object, const sf::Window & window, const sf::Rect<float> & rect);
		void checkFocusedObject();

		Mouse_info& getMouseInfo();

	protected:
		bool checkCharacter(sf::Uint32 character);
		bool checkSpecialKey(sf::Keyboard::Key key);

	private:
		sf::String _input_text;
		active_gui_object * _focused_object;
		std::deque<sf::Keyboard::Key> _special_keys;

		Mouse_info _mouse_info;
	};

}

#endif // !GUI_EVENT_H
