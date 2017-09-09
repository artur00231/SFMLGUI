#ifndef GUI_COMBO_BOX_h
#define GUI_COMBO_BOX_h

#include "changing_size_gui_object.h"
#include "Frame.h"
#include "Label.h"
#include "Background.h"
#include "function.h"
#include "Button.h"
#include "Vertical_layout.h"
#include "Scroll_area.h"

#include "SFML\Graphics.hpp"
#include <memory>
#include <deque>

namespace gui
{

	class Combo_box : public gui::changing_size_gui_object
	{
	public:
		explicit Combo_box();

		Combo_box(const Combo_box&) = default;
		Combo_box& operator=(const Combo_box&) = default;
		Combo_box(Combo_box&&) = default;
		Combo_box& operator=(Combo_box&&) = default;

		void setSize(const sf::Vector2f & size) override;
		void setPosition(const sf::Vector2f & position) override;

		const sf::Vector2f& getSize() const override;
		const sf::Vector2f& getPosition() const override;
		const sf::Rect<float> getGlobalBounds() const override;

		void up_date(gui::duration time_elapsed, const Mouse_info & mouse_info) override;
		void draw(sf::RenderTarget & render_target) const override;

		void setOwner(owner&) override;
		void removeFromOwner(owner & owner) override;

		bool isActive() const override;
		bool isHover() const override;
		bool isClicked() const override;
		bool isFocused() const override;
		bool isHoverChange() const override;
		bool isClickedChange() const override;
		bool isNeedResize() const override;
		bool isExtended() const override;

		void setActive(bool active) override;
		void setFocus(bool focus) override;

		void setMinOptionsInArea(unsigned int min);
		void addOption(const sf::String & name);
		void setOptions(const std::vector<sf::String> & names);
		void removeOption(const sf::String & name);
		void clearOptions();

		unsigned int getMinOptionsInArea() const;
		sf::String getActiveOption() const;

		void resize() override;
		void extend(bool extend) override;


		modifier::Frame_modifier& getFrame();
		const modifier::Frame_modifier& getFrame() const;
		modifier::Background_modifier& getBackground();
		const modifier::Background_modifier& getBackground() const;
		modifier::Function_modifier& getFunction();
		const modifier::Function_modifier& getFunction() const;

		modifier::Button_modifier& getMainButton();
		const modifier::Button_modifier& getMainButton() const;
		modifier::Button_modifier& getDown();
		const modifier::Button_modifier& getDown() const;
		modifier::Button_modifier& getOption();
		const modifier::Button_modifier& getOption() const;
		modifier::Vertical_slider_modifier& getSlider();
		const modifier::Vertical_slider_modifier& getSlider() const;


		~Combo_box() {};
	protected:
		void setHover(bool hover) override;
		void setClicked(bool clicked) override;
		void setHoverChange(bool hover_change) override;
		void setClickedChange(bool clicked_change) override;

		void buttonsFunction(gui::gui_object * object);
		void changeButtonsPattern();
		void showArea(bool show);
		


	private:
		Frame _frame;
		Background _background;
		Button _button, _down, _option_button_pattern;
		Scroll_area _area;
		Vertical_layout _layout;
		std::vector<Button*> _buttons;
		sf::Vector2f _size, _position;
		Function _function;
		bool _hover, _clicked, _active = true, _focus, _hover_change, _clicked_change, _need_resize, _showed_area, _need_buttons_change;
		unsigned int _min_options_in_area = 4;

		const float _slider_min_size = 20;

		owner * _owner;

	};

}

#endif // !GUI_COMBO_BOX_h
