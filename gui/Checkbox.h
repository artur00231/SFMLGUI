#ifndef GUI_CHECKBOX_H
#define GUI_CHECKBOX_H

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

	enum class Checkbox_state { CHECKED, UNCHECKED, INDETERMINATE };

	namespace modifier
	{

		class Checkbox_modifier
		{
		public:
			Checkbox_modifier() = default;

			Checkbox_modifier(Checkbox_modifier&&) = default;
			Checkbox_modifier& operator=(Checkbox_modifier&&) = default;

			virtual bool isActive() const = 0;
			virtual bool isHover() const = 0;
			virtual bool isClicked() const = 0;
			virtual bool isFocused() const = 0;
			virtual bool isHoverChange() const = 0;
			virtual bool isClickedChange() const = 0;
			virtual bool isNeedResize() const = 0;
			virtual bool isThree_state() const = 0;

			virtual void setActive(bool active) = 0;
			virtual void setFocus(bool focus) = 0;

			virtual void setThree_state(bool three_state) = 0;
			virtual void setProportions(float proportion_text_checked_frame, float proportion_checked_filed) = 0;
			virtual void setState(Checkbox_state checkbox_state) = 0;

			virtual const sf::Image getDefaultMark() const = 0;
			virtual std::pair<float, float> getProportions() const = 0;
			virtual Checkbox_state getState() const = 0;



			virtual modifier::Frame_modifier& getFrame() = 0;
			virtual modifier::Label_modifier& getLabel() = 0;
			virtual modifier::Background_modifier& getBackground() = 0;
			virtual modifier::Function_modifier& getFunction() = 0;
			virtual modifier::Image_modifier& getCheckedMark() = 0;

			// Checkbox_modifier can not by copied
			Checkbox_modifier(const Checkbox_modifier&) = delete;
			Checkbox_modifier& operator=(const Checkbox_modifier&) = delete;

			virtual ~Checkbox_modifier() = default;
		};

	}

	class Checkbox : public active_gui_object, public modifier::Checkbox_modifier
	{
	public:
		explicit Checkbox(const sf::String & text = {});

		Checkbox(Checkbox&&) = default;
		Checkbox& operator=(Checkbox&&) = default;

		void setSize(const sf::Vector2f & size) override;
		void setPosition(const sf::Vector2f & position) override;

		const sf::Vector2f& getSize() const override;
		const sf::Vector2f& getPosition() const override;
		const sf::Rect<float> getGlobalBounds() const override;

		void up_date(gui::duration time_elapsed) override;
		void draw(sf::RenderTarget & render_target) const override;

		void setOwner(owner & owner) override;

		bool isActive() const override;
		bool isHover() const override;
		bool isClicked() const override;
		bool isFocused() const override;
		bool isHoverChange() const override;
		bool isClickedChange() const override;
		bool isNeedResize() const override;
		bool isThree_state() const override;

		void setActive(bool active) override;
		void setFocus(bool focus) override;

		void setThree_state(bool three_state) override;
		void setProportions(float proportion_text_checked_frame, float proportion_checked_filed) override;
		void setState(Checkbox_state checkbox_state) override;

		const sf::Image getDefaultMark() const override;
		std::pair<float, float> getProportions() const override;
		Checkbox_state getState() const override;

		void resize() override;


		modifier::Frame_modifier& getFrame() override;
		modifier::Label_modifier& getLabel() override;
		modifier::Background_modifier& getBackground() override;
		modifier::Function_modifier& getFunction() override;
		modifier::Image_modifier& getCheckedMark() override;



		~Checkbox() {};

	protected:
		void setHover(bool hover) override;
		void setClicked(bool clicked) override;
		void setHoverChange(bool hover_change) override;
		void setClickedChange(bool clicked_change) override;
		Mouse_events& getMouse_event() override;

	private:
		Label _label;
		Frame _frame, _checked_frame;
		Background _background;
		Image _checked_mark;
		sf::Vector2f _size, _position;
		Function _function;
		bool _hover, _clicked, _active = true, _focus, _hover_change, _clicked_change, _need_resize;
		Mouse_events _events;
		float _proportion_text_checked_frame = 1.2f, _proportion_checked_filed = 0.2f;
		bool _three_state = false;
		Checkbox_state _checkbox_state;

		static sf::Texture _checked_texture;
	};

}

#endif // !GUI_CHECKBOX_H
