#ifndef GUI_TEXT_INPUT_H
#define GUI_TEXT_INPUT_H

#include "text_active_gui_object.h"
#include "Label.h"
#include "Background.h"
#include "Frame.h"
#include "Function.h"

namespace gui
{

	namespace modifier
	{

		class Text_input_modifier
		{
		public:
			Text_input_modifier() = default;

			Text_input_modifier(Text_input_modifier&&) = default;
			Text_input_modifier& operator=(Text_input_modifier&&) = default;

			virtual bool isActive() const = 0;
			virtual bool isHover() const = 0;
			virtual bool isClicked() const = 0;
			virtual bool isFocused() const = 0;
			virtual bool isHoverChange() const = 0;
			virtual bool isClickedChange() const = 0;
			virtual bool isNeedResize() const = 0;
			virtual bool isPassword() const = 0;

			virtual void setActive(bool active) = 0;
			virtual void setFocus(bool focus) = 0;

			virtual void addText(const sf::String & text) = 0;
			virtual void addSpecialKeys(const std::deque<sf::Keyboard::Key> & keys) = 0;

			virtual void setString(const sf::String & text) = 0;
			virtual void clear() = 0;
			virtual void setPassword(bool password) = 0;

			virtual const sf::String& getString() const = 0;

			virtual modifier::Frame_modifier& getFrame() = 0;
			virtual const modifier::Frame_modifier& getFrame() const = 0;
			virtual modifier::Label_modifier& getLabel() = 0;
			virtual const modifier::Label_modifier& getLabel() const = 0;
			virtual modifier::Background_modifier& getBackground() = 0;
			virtual const modifier::Background_modifier& getBackground() const = 0;
			virtual modifier::Function_modifier& getFunction() = 0;
			virtual const modifier::Function_modifier& getFunction() const = 0;

			virtual ~Text_input_modifier() = default;

		protected:
			// Text_input_modifier can not by copied
			Text_input_modifier(const Text_input_modifier&) = default;
			Text_input_modifier& operator=(const Text_input_modifier&) = default;
		};

	}

	class Text_input : public text_active_gui_object, public modifier::Text_input_modifier
	{
	public:
		explicit Text_input(const sf::String & text = {});

		Text_input(const Text_input&) = default;
		Text_input& operator=(const Text_input&) = default;
		Text_input(Text_input&&) = default;
		Text_input& operator=(Text_input&&) = default;

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
		bool isPassword() const override;

		void setActive(bool active) override;
		void setFocus(bool focus) override;

		void addText(const sf::String & text) override;
		void addSpecialKeys(const std::deque<sf::Keyboard::Key> & keys) override;

		void setString(const sf::String & text) override;
		void clear() override;
		void setPassword(bool password) override;

		const sf::String& getString() const override;

		void resize();


		modifier::Frame_modifier& getFrame() override;
		const modifier::Frame_modifier& getFrame() const override;
		modifier::Label_modifier& getLabel() override;
		const modifier::Label_modifier& getLabel() const override;
		modifier::Background_modifier& getBackground() override;
		const modifier::Background_modifier& getBackground() const override;
		modifier::Function_modifier& getFunction() override;
		const modifier::Function_modifier& getFunction() const override;


		~Text_input() {};

	protected:
		void setHover(bool hover) override;
		void setClicked(bool clicked) override;
		void setHoverChange(bool hover_change) override;
		void setClickedChange(bool clicked_change) override;
		void hideTextPointer();
		void showTextPointer();
		void setLabelString();

	private:
		Label _label;
		Frame _frame;
		Background _background;
		sf::Vector2f _size, _position;
		Function _function;
		bool _hover{}, _clicked{}, _active = true, _focus{}, _hover_change{}, _clicked_change{}, _need_resize{}, _password{};

		sf::String _text;
		std::size_t _text_pointer_position = 0;
		long long _time_elapsed, _text_pointer_time = 500000;
		bool _show_text_pointer{};
		std::pair<wchar_t, wchar_t> _text_pointer_characters{ L'\u2008', '|' };
		wchar_t _password_character = L'*';
	};

}

#endif // !GUI_TEXT_INPUT_H
