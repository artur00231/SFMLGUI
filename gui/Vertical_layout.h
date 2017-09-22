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
		Vertical_layout(const Text_style* = {});

		Vertical_layout(Vertical_layout&&);

		void setSize(const sf::Vector2f&) override;
		void setPosition(const sf::Vector2f&) override;

		const sf::Vector2f& getSize() const override;
		const sf::Vector2f& getPosition() const override;
		const sf::Rect<float> getGlobalBounds() const override;

		void setOwner(owner&) override;
		void removeFromOwner(owner & owner) override;

		gui::gui_object * addObject(gui::gui_object*, const std::string& = {}) override;
		gui::gui_object * addObject(gui::gui_object&, const std::string& = {}) override;

		template<typename T>
		T* add(T* object, const std::string & name = {});
		template<typename T>
		T* add(T& object, const std::string & name = {});

		void remove(const std::string&) override;
		void remove(const gui::gui_object *) override;

		void getEvents(active_gui_object & object, const sf::Window & window) override;
		void getEvents(active_gui_object & object, const sf::Window & window, const sf::Rect<float> & rect) override;
		void eventRemoveFocusedObject(gui_object * object) override;
		const Mouse_info& getMouseInfo() const override;

		void draw(sf::RenderTarget&) const override;
		void up_date(const sf::Window&, duration, owner&) override;

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

		gui::gui_object * addToMap(gui::gui_object*, const std::string&, bool addToLayout);
		gui::gui_object * addToMap(gui::gui_object&, const std::string&, bool addToLayout);

	private:
		std::unordered_map<std::string, std::pair<gui::gui_object*, std::pair<bool, bool>>> _gui_objects;
		long long _uniqe_name_count = 0;
		Text_style _default_text_style;
		sf::Vector2f _position, _size;
		Mouse_info _mouse_info;
		std::vector <gui_object*> _ordered_objects;

		static sf::Font _default_font;

		owner * _owner;
	};

}

template<typename T>
inline T* gui::Vertical_layout::add(T* object, const std::string & name)
{
	static_assert(std::is_convertible<T*, gui::gui_object*>::value, "Can not convertible argument");
	return static_cast<T*>(addToMap(object, name, true));
}

template<typename T>
inline T* gui::Vertical_layout::add(T& object, const std::string & name)
{
	static_assert(std::is_convertible<T*, gui::gui_object*>::value, "Can not convertible argument");
	return static_cast<T*>(addToMap(object, name, true));
}

#endif // !GUI_VERTICAL_LAYOUT_H
