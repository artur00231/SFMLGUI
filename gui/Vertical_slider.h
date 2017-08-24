#ifndef GUI_VERTICAL_SLIDER_H
#define GUI_VERTICAL_SLIDER_H

#include "slider.h"
#include "Button.h"

namespace gui
{

	class Vertical_slider : public slider
	{
	public:
		explicit Vertical_slider(long long max = 0, long long min = 0);

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

		long long getNumber() override;
		std::pair<long long, long long> getMinMax() override;

		void resize() override;

		modifier::Frame_modifier& getFrame();
		modifier::Background_modifier& getBackground();
		modifier::Function_modifier& getFunction();

		modifier::Button_modifier& getUp();
		modifier::Button_modifier& getDown();
		modifier::Button_modifier& getMiddle();

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
