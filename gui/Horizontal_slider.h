#ifndef GUI_HORIZONTAL_SLIDER_H
#define GUI_HORIZONTAL_SLIDER_H

#include "slider.h"
#include "Button.h"

namespace gui
{

	namespace modifier
	{
		class Horizontal_slider_modifier
		{
		public:
			Horizontal_slider_modifier() = default;

			Horizontal_slider_modifier(Horizontal_slider_modifier&&) = default;
			Horizontal_slider_modifier& operator=(Horizontal_slider_modifier&&) = default;

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
			virtual long long getMax() const = 0;


			virtual modifier::Frame_modifier& getFrame() = 0;
			virtual modifier::Background_modifier& getBackground() = 0;
			virtual modifier::Function_modifier& getFunction() = 0;

			virtual modifier::Button_modifier& getLeft() = 0;
			virtual modifier::Button_modifier& getRight() = 0;
			virtual modifier::Button_modifier& getMiddle() = 0;

			Horizontal_slider_modifier(const Horizontal_slider_modifier&) = delete;
			Horizontal_slider_modifier& operator=(const Horizontal_slider_modifier&) = delete;

			virtual ~Horizontal_slider_modifier() {};
		};
	}

	class Horizontal_slider : public slider, public modifier::Horizontal_slider_modifier
	{
	public:
		explicit Horizontal_slider(long long max = 0, long long min = 0);

		Horizontal_slider(const Horizontal_slider&) = default;
		Horizontal_slider& operator=(const Horizontal_slider&) = default;
		Horizontal_slider(Horizontal_slider&&) = default;
		Horizontal_slider& operator=(Horizontal_slider&&) = default;

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
		long long getMax() const override;

		void resize() override;

		modifier::Frame_modifier& getFrame() override;
		modifier::Background_modifier& getBackground() override;
		modifier::Function_modifier& getFunction() override;

		modifier::Button_modifier& getLeft() override;
		modifier::Button_modifier& getRight() override;
		modifier::Button_modifier& getMiddle() override;

		~Horizontal_slider() {};

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
		Button _left, _right, _middle;
		Background _background;
		Frame _frame;
		Function _function;
		sf::Vector2f _size, _position;
		bool _hover, _clicked, _active = true, _focus, _hover_change, _clicked_change, _need_resize;

		long long _max, _min, _step, _value;
		sf::Vector2f _button_min_size{20, 20};
		sf::Vector2f _middle_button_min_size{ 5, 20 };

		sf::Vector2f _mouse_move;
		bool _follow_mouse;
	};


}

#endif // !GUI_HORIZONTAL_SLIDER_H
