#ifndef GUI_FRAME_H
#define GUI_FRAME_H

#include "SFML\Graphics.hpp"

#include "passive_gui_object.h"
#include "Imp\FrameImp.h"

namespace gui
{

	namespace modifier
	{

		class Frame_modifier
		{
		public:
			Frame_modifier() = default;

			Frame_modifier(Frame_modifier&&) = default;
			Frame_modifier& operator=(Frame_modifier&&) = default;

			virtual void setThickness(float thickness) = 0;
			virtual void setColor(const sf::Color & color) = 0;

			virtual float getThickness() const = 0;
			virtual const sf::Color& getColor() const = 0;

			// Frame_modifier can not by copied
			Frame_modifier(const Frame_modifier&) = delete;
			Frame_modifier& operator=(const Frame_modifier&) = delete;

			virtual ~Frame_modifier() {};
		};

	}


	class Frame : public passive_gui_object, private Imp::FrameImp, public modifier::Frame_modifier
	{
	public:
		explicit Frame(float thickness = 0, const sf::Color & color = sf::Color::Transparent);

		Frame(const Frame&) = default;
		Frame& operator=(const Frame&) = default;
		Frame(Frame&&) = default;
		Frame& operator=(Frame&&) = default;

		void setSize(const sf::Vector2f & size) override;
		void setPosition(const sf::Vector2f & position) override;
		void setColor(const sf::Color & color) override;

		const sf::Vector2f& getSize() const override;
		const sf::Vector2f& getPosition() const override;
		const sf::Rect<float> getGlobalBounds() const override;
		const sf::Color& getColor() const override;

		void draw(sf::RenderTarget & render_target) const override;

		void setOwner(owner & owner) override;
		void removeFromOwner(owner & owner) override;

		void setThickness(float thickness) override;
		float getThickness() const override;

		void fitTo(const gui_object & object);
		void fitTo(const sf::Rect<float> & rectangle);

		~Frame() {};

	private:
	};

}


#endif // !GUI_FRAME_H
