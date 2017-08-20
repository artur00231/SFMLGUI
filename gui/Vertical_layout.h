#ifndef GUI_VERTICAL_LAYOUT_H
#define GUI_VERTICAL_LAYOUT_H

#include "managing_gui_object.h"
#include "Radio_button.h"
#include <unordered_map>

namespace gui
{

	class Vertical_layout : public managing_gui_object
	{
	public:
		Vertical_layout(const Text_style&, owner&);

		void setSize(const sf::Vector2f&) override;
		void setPosition(const sf::Vector2f&) override;

		const sf::Vector2f& getSize() const override;
		const sf::Vector2f& getPosition() const override;
		const sf::Rect<float> getGlobalBounds() const override;

		void setOwner(owner&) override;

		gui::gui_object * add(gui::gui_object*, const std::string& = {}) override;
		gui::gui_object * add(gui::gui_object&, const std::string& = {}) override;

		void remove(const std::string&) override;
		void remove(const gui::gui_object *) override;

		void draw(sf::RenderTarget&) const override;
		void up_date(const sf::Window&, duration, Event&) override;

		void setTextStyle(const Text_style&) override;

		const Text_style& getTextStyle() const override;
		gui::gui_object* get(const std::string&) const override;

		Vertical_layout(const Vertical_layout&) = delete;
		Vertical_layout& operator=(const Vertical_layout&) = delete;

		void re_size();

		~Vertical_layout();

	protected:
		void checkRadio_buttons(std::vector<gui::Radio_button*>&);

		std::string getUniqeName();

	private:
		std::unordered_map<std::string, std::pair<gui::gui_object*, bool>> _gui_objects;
		long long _uniqe_name_count = 0;
		Text_style _default_text_style;
		sf::Vector2f _position, _size;
		owner * _owner;
	};

}

#endif // !GUI_VERTICAL_LAYOUT_H
