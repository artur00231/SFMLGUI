#ifndef GUI_TEXT_ACTIVE_GUI_OBJECT_H
#define GUI_TEXT_ACTIVE_GUI_OBJECT_H

#include "active_gui_object.h"
#include <deque>

class Event;


namespace gui
{

	class text_active_gui_object : public active_gui_object
	{
	public:

		~text_active_gui_object() {};

		friend class Event;

	protected:
		virtual void addText(const sf::String & text) = 0;
		virtual void addSpecialKeys(const std::deque<sf::Keyboard::Key> & keys) = 0;

	private:

	};

}

#endif // !GUI_TEXT_ACTIVE_GUI_OBJECT_H
