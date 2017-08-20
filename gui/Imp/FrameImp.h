#ifndef GUI_FRAMEIMP_H
#define GUI_FRAMEIMP_H

#include "SFML\Graphics.hpp"
#include "..\gui_object.h"

namespace gui
{

	namespace Imp
	{

		class FrameImp
		{
		public:
			explicit FrameImp(float thickness = 0, const sf::Color & color = sf::Color::Transparent);

			void setSize(const sf::Vector2f & size);
			void setPosition(const sf::Vector2f & position);
			void setColor(const sf::Color & color);
			void fitTo(const gui::gui_object & object);
			void fitTo(const sf::Rect<float> & rectangle);
			void setThickness(float thickness);

			const sf::Vector2f& getSize() const;
			const sf::Vector2f& getPosition() const;
			const sf::Color& getColor() const;
			const sf::Rect<float> getGlobalBounds() const;
			float getThickness() const;

			void draw(sf::RenderTarget & render_target) const;

		private:
			sf::RectangleShape _rectangle;
			sf::Vector2f _size;
			sf::Vector2f _position;
		};

		inline FrameImp::FrameImp(float thickness, const sf::Color & color)
		{
			_rectangle.setOutlineThickness(thickness);
			_rectangle.setOutlineColor(color);

			// Make base rectangle transparent
			_rectangle.setFillColor(sf::Color::Transparent);
		}

		inline void FrameImp::setSize(const sf::Vector2f & size)
		{
			float double_thickness = 2 * _rectangle.getOutlineThickness();

			// Minimal size is double_thickness
			if (size.x - double_thickness > 0 && size.y - double_thickness)
			{
				_rectangle.setSize({ size.x - double_thickness, size.y - double_thickness });
				_size = size;
			}
		}

		inline void FrameImp::setPosition(const sf::Vector2f & position)
		{
			float thickness = _rectangle.getOutlineThickness();
			_rectangle.setPosition(position.x + thickness, position.y + thickness);
			_position = position;
		}


		inline void FrameImp::setColor(const sf::Color & color)
		{
			_rectangle.setOutlineColor(color);
		}

		inline void FrameImp::fitTo(const gui::gui_object & object)
		{
			_rectangle.setSize(object.getSize());
			_rectangle.setPosition(object.getPosition());
		}

		inline void FrameImp::fitTo(const sf::Rect<float> & rectangle)
		{
			_rectangle.setSize({ rectangle.width, rectangle.height });
			_rectangle.setPosition({ rectangle.left, rectangle.top });
		}

		inline void FrameImp::setThickness(float thickness)
		{
			_rectangle.setOutlineThickness(thickness);
		}

		inline const sf::Vector2f& FrameImp::getSize() const
		{
			return _size;
		}

		inline const sf::Vector2f& FrameImp::getPosition() const
		{
			return _position;
		}

		inline const sf::Color & FrameImp::getColor() const
		{
			return _rectangle.getOutlineColor();
		}

		inline const sf::Rect<float> FrameImp::getGlobalBounds() const
		{
			return _rectangle.getGlobalBounds();
		}

		inline float FrameImp::getThickness() const
		{
			return _rectangle.getOutlineThickness();
		}

		inline void FrameImp::draw(sf::RenderTarget & render_target) const
		{
			render_target.draw(_rectangle);
		}
	}
}


#endif // !GUI_FRAMEIMP_H