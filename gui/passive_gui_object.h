#ifndef GUI_PASSIVE_GUI_OBJECT_H
#define GUI_PASSIVE_GUI_OBJECT_H

#include "gui_object.h"
#include "SFML\Graphics.hpp"

namespace gui
{

	class passive_gui_object : public gui_object
	{
	public:
		virtual void setColor(const sf::Color & color) = 0;
		virtual const sf::Color& getColor() const = 0;

		~passive_gui_object() {};
	};


}

#endif // !GUI_PASSIVE_GUI_OBJECT_H
