#ifndef GUI_NUMBER_INPUT_H
#define GUI_NUMBER_INPUT_H

#include "text_active_gui_object.h"
#include "Label.h"
#include "Background.h"
#include "Frame.h"
#include "Function.h"
#include "Button.h"
#include "Gui.h"

#include <cctype>

namespace gui
{

	enum class Number_input_type {INTEGRER, REAL};

	namespace modifier
	{

		class Number_input_modifier
		{
		public:
			Number_input_modifier() = default;

			Number_input_modifier(Number_input_modifier&&) = default;
			Number_input_modifier& operator=(Number_input_modifier&&) = default;

			virtual bool isActive() const = 0;
			virtual bool isHover() const = 0;
			virtual bool isClicked() const = 0;
			virtual bool isFocused() const = 0;
			virtual bool isHoverChange() const = 0;
			virtual bool isClickedChange() const = 0;
			virtual bool isNeedResize() const = 0;

			virtual void setActive(bool active) = 0;
			virtual void setFocus(bool focus) = 0;

			virtual void addText(const sf::String & text) = 0;
			virtual void addSpecialKeys(const std::deque<sf::Keyboard::Key> & keys) = 0;

			virtual void setNumberInputType(Number_input_type number_text_input) = 0;
			virtual void setMinMaxValue(double min, double max) = 0;
			virtual void setMinMaxValue(long long min, long long max) = 0;
			virtual void setStepValue(double step) = 0;
			virtual void setStepValue(long long step) = 0;
			virtual void setProportionsTextButton(float proportions_text_button) = 0;
			virtual void clear() = 0;

			virtual const sf::String& getString() const = 0;
			virtual long long getLongLong() const = 0;
			virtual double getDouble() const = 0;
			virtual std::pair<double, double> getDoubleMinMaxValue() const = 0;
			virtual std::pair<long long, long long> getLongLongMinMaxValue() const = 0;
			virtual double getDoubleStepValue() const = 0;
			virtual long long getLongLongStepValue() const = 0;
			virtual double getProportionsTextButton() const = 0;

			virtual modifier::Frame_modifier& getFrame() = 0;
			virtual modifier::Label_modifier& getLabel() = 0;
			virtual modifier::Background_modifier& getBackground() = 0;
			virtual modifier::Function_modifier& getFunction() = 0;

			// Number_input_modifier can not by copied
			Number_input_modifier(const Number_input_modifier&) = delete;
			Number_input_modifier& operator=(const Number_input_modifier&) = delete;

			virtual ~Number_input_modifier() = default;
		};

	}

	class Number_input : public text_active_gui_object, public modifier::Number_input_modifier
	{
	public:
		explicit Number_input(const sf::String & text = {});

		Number_input(Number_input&&) = default;
		Number_input& operator=(Number_input&&) = default;
		
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

		void addText(const sf::String & text) override;
		void addSpecialKeys(const std::deque<sf::Keyboard::Key> & key) override;

		void setNumberInputType(Number_input_type number_input_type) override;
		void setMinMaxValue(double min, double max) override;
		void setMinMaxValue(long long min, long long max) override;
		void setStepValue(double step) override;
		void setStepValue(long long step) override;
		void setProportionsTextButton(float proportions_text_button) override;
		void clear() override;

		const sf::String& getString() const override;
		long long getLongLong() const override;
		double getDouble() const override;
		std::pair<double, double> getDoubleMinMaxValue() const override;
		std::pair<long long, long long> getLongLongMinMaxValue() const override;
		double getDoubleStepValue() const override;
		long long getLongLongStepValue() const override;
		double getProportionsTextButton() const override;

		void resize();


		modifier::Frame_modifier& getFrame() override;
		modifier::Label_modifier& getLabel() override;
		modifier::Background_modifier& getBackground() override;
		modifier::Function_modifier& getFunction() override;

		~Number_input() {};

	protected:
		union double_value
		{
			long long l_val;
			double d_val;
		};

		void setHover(bool hover) override;
		void setClicked(bool clicked) override;
		void setHoverChange(bool hover_change) override;
		void setClickedChange(bool clicked_change) override;
		Mouse_events& getMouse_event() override;
		void hideTextPointer() const;
		void showTextPointer() const;
		void setLabelString();
		void setNumber();
		void checkNumber() const;
		void getNumberFromText() const;

		void add();
		void addNumber();
		void subtract();
		void subtractNumber();

	private:
		Label _label;
		Frame _frame;
		Background _background;
		Button _up, _down;
		sf::Vector2f _size, _position;
		Function _function;
		bool _hover, _clicked, _active = true, _focus, _hover_change, _clicked_change, _need_resize;
		Mouse_events _events;

		mutable sf::String _text = "0";
		std::size_t _text_pointer_position = 1;
		long long _time_elapsed, _text_pointer_time = 500000;
		bool _show_text_pointer;
		std::pair<wchar_t, wchar_t> _text_pointer_characters{ L'\u2008', '|' };
		float _proportions_text_button = 0.2f;
		Number_input_type _number_input_type = Number_input_type::REAL;
		double_value _max, _min, _step;
		mutable double_value _value;

	};

}

#endif // !GUI_NUMBER_INPUT_H
