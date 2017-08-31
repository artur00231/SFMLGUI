#ifndef GUI_OBJECT_H
#define GUI_OBJECT_H

#include "SFML\Graphics.hpp"
#include "owner.h"

namespace gui {

	class gui_object
	{
	public:

		virtual void setSize(const sf::Vector2f & size) = 0;
		virtual void setPosition(const sf::Vector2f & position) = 0;

		virtual const sf::Vector2f& getSize() const = 0;
		virtual const sf::Vector2f& getPosition() const = 0;
		virtual const sf::Rect<float> getGlobalBounds() const = 0;

		virtual void draw(sf::RenderTarget & render_target) const = 0;

		virtual void setOwner(owner & owner) = 0;
		virtual void removeFromOwner(owner & owner) = 0;

		virtual ~gui_object() {};

	};

}

#endif // !GUI_OBJECT_H
