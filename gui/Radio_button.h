#ifndef GUI_RADIO_BUTTON_H
#define GUI_RADIO_BUTTON_H

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

	enum class Radio_button_state { CHECKED, UNCHECKED };

	namespace modifier
	{

		class Radio_button_modifier
		{
		public:
			Radio_button_modifier() = default;

			Radio_button_modifier(Radio_button_modifier&&) = default;
			Radio_button_modifier& operator=(Radio_button_modifier&&) = default;

			virtual bool isActive() const = 0;
			virtual bool isHover() const = 0;
			virtual bool isClicked() const = 0;
			virtual bool isFocused() const = 0;
			virtual bool isHoverChange() const = 0;
			virtual bool isClickedChange() const = 0;
			virtual bool isNeedResize() const = 0;
			virtual bool isExlusive() const = 0;

			virtual void setActive(bool active) = 0;
			virtual void setFocus(bool focus) = 0;
			virtual void setExlusive(bool exlusive) = 0;

			virtual void setProportions(float proportion_text_checked_frame, float proportion_checked_filed) = 0;
			virtual void setState(Radio_button_state radio_button_state) = 0;

			virtual const sf::Image getDefaultMark() const = 0;
			virtual const sf::Image getDefaultOutline() const = 0;
			virtual Radio_button_state getState() const = 0;
			virtual std::pair<float, float> getProportions() const = 0;

			virtual modifier::Frame_modifier& getFrame() = 0;
			virtual modifier::Label_modifier& getLabel() = 0;
			virtual modifier::Background_modifier& getBackground() = 0;
			virtual modifier::Function_modifier& getFunction() = 0;
			virtual modifier::Image_modifier& getCheckedMark() = 0;

			// Radio_button_modifier can not by copied
			Radio_button_modifier(const Radio_button_modifier&) = delete;
			Radio_button_modifier& operator=(const Radio_button_modifier&) = delete;

			virtual ~Radio_button_modifier() = default;
		};

	}

	class Radio_button : public active_gui_object, public modifier::Radio_button_modifier
	{
	public:
		explicit Radio_button(const sf::String & text = {});

		Radio_button(Radio_button&&) = default;
		Radio_button& operator=(Radio_button&&) = default;

		void setSize(const sf::Vector2f & size) override;
		void setPosition(const sf::Vector2f & position) override;

		const sf::Vector2f& getSize() const override;
		const sf::Vector2f& getPosition() const override;
		const sf::Rect<float> getGlobalBounds() const override;

		void up_date(gui::duration time_elapsed, const Mouse_info & mouse_info) override;
		void draw(sf::RenderTarget & render_target) const override;

		void setOwner(owner & owner) override;

		bool isActive() const override;
		bool isHover() const override;
		bool isClicked() const override;
		bool isFocused() const override;
		bool isHoverChange() const override;
		bool isClickedChange() const override;
		bool isNeedResize() const override;
		bool isExlusive() const override;

		void setActive(bool active) override;
		void setFocus(bool focus) override;
		void setExlusive(bool exlusive) override;

		void setProportions(float proportion_text_checked_frame, float proportion_checked_filed) override;
		void setState(Radio_button_state radio_button_state) override;

		const sf::Image getDefaultMark() const override;
		const sf::Image getDefaultOutline() const override;
		Radio_button_state getState() const override;
		std::pair<float, float> getProportions() const override;

		void resize() override;

		modifier::Frame_modifier& getFrame() override;
		modifier::Label_modifier& getLabel() override;
		modifier::Background_modifier& getBackground() override;
		modifier::Function_modifier& getFunction() override;
		modifier::Image_modifier& getCheckedMark() override;



		~Radio_button() {};

	protected:
		void setHover(bool hover) override;
		void setClicked(bool clicked) override;
		void setHoverChange(bool hover_change) override;
		void setClickedChange(bool clicked_change) override;

	private:
		Label _label;
		Frame _frame;
		Background _background;
		Image _checked_mark, _checked_outline;
		sf::Vector2f _size, _position;
		Function _function;
		bool _hover, _clicked, _active = true, _focus, _hover_change, _clicked_change, _need_resize, _exclusive;
		float _proportions_text_checked_frame = 1.2f, _proportions_checked_filed = 0.2f;
		Radio_button_state _radio_button_state;

		static sf::Texture _checked_mark_texture;
		static sf::Texture _checked_outline_texture;
		const float _checked_outline_thickness = 2;
	};

}

#endif // !GUI_RADIO_BUTTON_H
