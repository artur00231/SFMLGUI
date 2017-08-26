#ifndef GUI_TEXT_H
#define GUI_TEXT_H

#include "active_gui_object.h"
#include "Frame.h"
#include "Label.h"
#include "Background.h"
#include "function.h"

#include "SFML\Graphics.hpp"
#include <memory>
#include <deque>

namespace gui
{

	namespace modifier
	{

		class Button_modifier
		{
		public:
			Button_modifier() = default;

			Button_modifier(Button_modifier&&) = default;
			Button_modifier& operator=(Button_modifier&&) = default;

			virtual bool isActive() const = 0;
			virtual bool isHover() const = 0;
			virtual bool isClicked() const = 0;
			virtual bool isFocused() const = 0;
			virtual bool isHoverChange() const = 0;
			virtual bool isClickedChange() const = 0;
			virtual bool isNeedResize() const = 0;

			virtual void setActive(bool active) = 0;
			virtual void setFocus(bool focus) = 0;


			virtual modifier::Frame_modifier& getFrame() = 0;
			virtual modifier::Label_modifier& getLabel() = 0;
			virtual modifier::Background_modifier& getBackground() = 0;
			virtual modifier::Function_modifier& getFunction() = 0;

			// Button_modifier can not by copied
			Button_modifier(const Button_modifier&) = delete;
			Button_modifier& operator=(const Button_modifier&) = delete;

			virtual ~Button_modifier() = default;
		};

	}

	class Button : public gui::active_gui_object, public modifier::Button_modifier
	{
	public:
		explicit Button(const sf::String & text = {});

		Button(const Button&) = default;
		Button& operator=(const Button&) = default;
		Button(Button&&) = default;
		Button& operator=(Button&&) = default;

		void setSize(const sf::Vector2f & size) override;
		void setPosition(const sf::Vector2f & position) override;

		const sf::Vector2f& getSize() const override;
		const sf::Vector2f& getPosition() const override;
		const sf::Rect<float> getGlobalBounds() const override;

		void up_date(gui::duration time_elapsed, const Mouse_info & mouse_info) override;
		void draw(sf::RenderTarget & render_target) const override;

		void setOwner(owner&) override;

		bool isActive() const override;
		bool isHover() const override;
		bool isClicked() const override;
		bool isFocused() const override;
		bool isHoverChange() const override;
		bool isClickedChange() const override;
		bool isNeedResize() const override;

		void setActive(bool active) override;
		void setFocus(bool focus) override;

		void resize() override;


		modifier::Frame_modifier& getFrame() override;
		modifier::Label_modifier& getLabel() override;
		modifier::Background_modifier& getBackground() override;
		modifier::Function_modifier& getFunction() override;


		~Button() {};
	protected:
		void setHover(bool hover) override;
		void setClicked(bool clicked) override;
		void setHoverChange(bool hover_change) override;
		void setClickedChange(bool clicked_change) override;


	private:
		Label _label;
		Frame _frame;
		Background _background;
		sf::Vector2f _size, _position;
		Function _function;
		bool _hover, _clicked, _active = true, _focus, _hover_change, _clicked_change, _need_resize;

	};

}

#endif // !GUI_TEXT_H
