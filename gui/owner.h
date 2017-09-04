#ifndef GUI_OWNER_H
#define GUI_OWNER_H

#include "Styles.h"
#include "Mouse_info.h"

namespace gui
{

	class gui_object;
	class active_gui_object;

	class owner
	{
	public:
		
		virtual gui::gui_object* addObject(gui::gui_object*, const std::string& = {}) = 0;
		virtual gui::gui_object * addObject(gui::gui_object&, const std::string& = {}) = 0;

		virtual void remove(const std::string&) = 0;
		virtual void remove(const gui::gui_object *) = 0;

		virtual void getEvents(gui::active_gui_object & object, const sf::Window & window) = 0;
		virtual void getEvents(gui::active_gui_object & object, const sf::Window & window, const sf::Rect<float>& rect) = 0;
		virtual const Mouse_info& getMouseInfo() const = 0;

		virtual const Text_style& getTextStyle() const = 0;

		virtual ~owner() {};
	};

}


#endif // !GUI_OWNER_H
