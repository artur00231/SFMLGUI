#ifndef GUI_MANAGING_GUI_OBJECT_H
#define GUI_MANAGING_GUI_OBJECT_H

#include "gui_object.h"
#include "owner.h"
#include "Event.h"

namespace gui
{

	class gui_object;

	class managing_gui_object : public gui_object, public owner
	{
	public:
		virtual void up_date(const sf::Window&, duration, Event&) = 0;

		virtual void setTextStyle(const Text_style&) = 0;

		virtual gui::gui_object* get(const std::string&) const = 0;
	};

}


#endif // !GUI_MANAGING_GUI_OBJECT_H
