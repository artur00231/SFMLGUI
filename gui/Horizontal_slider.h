#ifndef GUI_HORIZONTAL_SLIDER_H
#define GUI_HORIZONTAL_SLIDER_H

#include "slider.h"
#include "Button.h"

namespace gui
{

	class Horizontal_slider : public slider
	{
	public:
		explicit Horizontal_slider(long long max = 0, long long min = 0);

		Horizontal_slider(Horizontal_slider&&) = default;
		Horizontal_slider& operator=(Horizontal_slider&&) = default;

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

		void setActive(bool active) override;
		void setFocus(bool focus) override;

		void setValue(long long value) override;
		void setMinMax(long long min, long long max) override;

		long long getNumber() override;
		std::pair<long long, long long> getMInMax() override;

		void resize() override;

		modifier::Frame_modifier& getFrame();
		modifier::Background_modifier& getBackground();
		modifier::Function_modifier& getFunction();

		~Horizontal_slider() {};

	protected:
		void setHover(bool hover) override;
		void setClicked(bool clicked) override;
		void setHoverChange(bool hover_change) override;
		void setClickedChange(bool clicked_change) override;
		Mouse_events& getMouse_event() override;

		unsigned long long getCurrentStep();
		void add();
		void subtract();
		void setMiddlePosition();

	private:
		Button _left, _right, _middle;
		Background _background;
		Frame _frame;
		Function _function;
		sf::Vector2f _size, _position;
		bool _hover, _clicked, _active = true, _focus, _hover_change, _clicked_change, _need_resize;
		Mouse_events _events;

		long long _max, _min, _step, _value;
		sf::Vector2f _button_min_size{20, 20};
		sf::Vector2f _middle_min_size{ 5, 20 };

		sf::Vector2i m_pos;
	};


}

#endif // !GUI_HORIZONTAL_SLIDER_H
