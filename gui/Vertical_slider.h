#ifndef GUI_VERTICAL_SLIDER_H
#define GUI_VERTICAL_SLIDER_H

#include "slider.h"
#include "Button.h"

namespace gui
{
	namespace modifier
	{
		class Vertical_slider_modifier
		{
		public:
			Vertical_slider_modifier() = default;

			Vertical_slider_modifier(Vertical_slider_modifier&&) = default;
			Vertical_slider_modifier& operator=(Vertical_slider_modifier&&) = default;

			virtual bool isActive() const = 0;
			virtual bool isHover() const = 0;
			virtual bool isClicked() const = 0;
			virtual bool isFocused() const = 0;
			virtual bool isHoverChange() const = 0;
			virtual bool isClickedChange() const = 0;
			virtual bool isNeedResize() const = 0;

			virtual void setActive(bool active) = 0;
			virtual void setFocus(bool focus) = 0;

			virtual void setValue(long long value) = 0;
			virtual void setMinMax(long long min, long long max) = 0;

			virtual long long getValue() const = 0;
			virtual std::pair<long long, long long> getMinMax() const = 0;
			virtual long long getMaxSteps() const = 0;
			virtual float getMinButtonSize() const = 0;


			virtual modifier::Frame_modifier& getFrame() = 0;
			virtual const modifier::Frame_modifier& getFrame() const = 0;
			virtual modifier::Background_modifier& getBackground() = 0;
			virtual const modifier::Background_modifier& getBackground() const = 0;
			virtual modifier::Function_modifier& getFunction() = 0;
			virtual const modifier::Function_modifier& getFunction() const = 0;

			virtual modifier::Button_modifier& getUp() = 0;
			virtual const modifier::Button_modifier& getUp() const = 0;
			virtual modifier::Button_modifier& getDown() = 0;
			virtual const modifier::Button_modifier& getDown() const = 0;
			virtual modifier::Button_modifier& getMiddle() = 0;
			virtual const modifier::Button_modifier& getMiddle() const = 0;

			virtual ~Vertical_slider_modifier() {};

		protected:
			// Vertical_slider_modifier can not by copied
			Vertical_slider_modifier(const Vertical_slider_modifier&) = default;
			Vertical_slider_modifier& operator=(const Vertical_slider_modifier&) = default;
		};
	}

	class Vertical_slider : public slider, public modifier::Vertical_slider_modifier
	{
	public:
		explicit Vertical_slider(long long max = 0, long long min = 0);

		Vertical_slider(const Vertical_slider&) = default;
		Vertical_slider& operator=(const Vertical_slider&) = default;
		Vertical_slider(Vertical_slider&&) = default;
		Vertical_slider& operator=(Vertical_slider&&) = default;

		void setSize(const sf::Vector2f & size) override;
		void setPosition(const sf::Vector2f & position) override;

		const sf::Vector2f& getSize() const override;
		const sf::Vector2f& getPosition() const override;
		const sf::Rect<float> getGlobalBounds() const override;

		void up_date(gui::duration time_elapsed, const Mouse_info & mouse_info) override;
		void draw(sf::RenderTarget & render_target) const override;

		void setOwner(owner & owner) override;
		void removeFromOwner(owner & owner) override;

		bool isActive() const override;
		bool isHover() const override;
		bool isClicked() const override;
		bool isFocused() const override;
		bool isHoverChange() const override;
		bool isClickedChange() const override;
		bool isNeedResize() const override;

		void setActive(bool active) override;
		void setFocus(bool focus) override;

		void setValue(long long value) override;
		void setMinMax(long long min, long long max) override;

		long long getValue() const override;
		std::pair<long long, long long> getMinMax() const override;
		long long getMaxSteps() const override;
		float getMinButtonSize() const override;

		void resize() override;

		modifier::Frame_modifier& getFrame() override;
		const modifier::Frame_modifier& getFrame() const override;
		modifier::Background_modifier& getBackground() override;
		const modifier::Background_modifier& getBackground() const override;
		modifier::Function_modifier& getFunction() override;
		const modifier::Function_modifier& getFunction() const override;

		modifier::Button_modifier& getUp() override;
		const modifier::Button_modifier& getUp() const override;
		modifier::Button_modifier& getDown() override;
		const modifier::Button_modifier& getDown() const override;
		modifier::Button_modifier& getMiddle() override;
		const modifier::Button_modifier& getMiddle() const override;

		~Vertical_slider() {};

	protected:
		void setHover(bool hover) override;
		void setClicked(bool clicked) override;
		void setHoverChange(bool hover_change) override;
		void setClickedChange(bool clicked_change) override;

		unsigned long long getCurrentStep();
		void add();
		void subtract();

		void setMiddleButtonPosition(const Mouse_info & mouse_info);

	private:
		Button _up, _down, _middle;
		Background _background;
		Frame _frame;
		Function _function;
		sf::Vector2f _size, _position;
		bool _hover, _clicked, _active = true, _focus, _hover_change, _clicked_change, _need_resize;

		long long _max, _min, _step, _value;
		sf::Vector2f _button_min_size{ 20, 20 };
		sf::Vector2f _middle_button_min_size{ 20, 5 };

		sf::Vector2f _mouse_move;
		bool _follow_mouse;
	};


}

#endif // !GUI_VERTICAL_SLIDER_H
