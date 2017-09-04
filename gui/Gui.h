#ifndef GUI_DEFAULT_LAYOUT_H
#define GUI_DEFAULT_LAYOUT_H

#include "active_gui_object.h"
#include "Label.h"
#include "Frame.h"
#include "Background.h"
#include "Button.h"
#include "function.h"
#include "Gui.h"
#include "Checkbox.h"
#include "Radio_button.h"
#include "Text_input.h"
#include "Number_input.h"
#include "Event.h"
#include "Styles.h"
#include "managing_gui_object.h"
#include "Vertical_layout.h"
#include "Horizontal_slider.h"
#include "Vertical_slider.h"
#include "Scroll_area.h"
#include "Combo_box.h"

#include <unordered_map>
#include <chrono>
#include <type_traits>


namespace gui
{

	class Gui : public owner
	{
	public:
		explicit Gui(const Text_style & text_style);

		Gui(Gui&&);

		gui_object * addObject(gui::gui_object * object, const std::string & name = {}) override;
		gui_object * addObject(gui::gui_object & object, const std::string & name = {}) override;

		template<typename T>
		T* add(T* object, const std::string & name = {});
		template<typename T>
		T* add(T& object, const std::string & name = {});

		void remove(const std::string & name) override;
		void remove(const gui::gui_object * object) override;

		void getEvents(active_gui_object & object, const sf::Window & window) override;
		void getEvents(active_gui_object & object, const sf::Window & window, const sf::Rect<float> & rect) override;
		const Mouse_info& getMouseInfo() const override;

		void draw(sf::RenderTarget & render_target) const;
		void up_date(const sf::Window & window);
		void drawAndUp_date(sf::RenderTarget & render_target, const sf::Window & window);
		void drawAndUp_date(sf::RenderWindow & render_window);

		void setTextStyle(const Text_style & text_style);
		void addEvent(const sf::Event & event);

		const Text_style& getTextStyle() const override;
		gui::gui_object* get(const std::string & name) const;

		Gui(const Gui&) = delete;
		Gui& operator=(const Gui&) = delete;

		~Gui();

	protected:
		void checkRadio_buttons(std::vector<gui::Radio_button*> & radio_buttons);
		std::string getUniqeName();

		gui_object * addToGui(gui::gui_object * object, const std::string & name);
		gui_object * addToGui(gui::gui_object & object, const std::string & name);

	private:
		std::unordered_map<std::string, std::pair<gui::gui_object*, bool>> _gui_objects;
		std::chrono::time_point<std::chrono::high_resolution_clock> _last_time;
		std::chrono::high_resolution_clock clock;
		Event _event;
		long long _uniqe_name_count = 0;
		Text_style _default_text_style;
		Mouse_info* _mouse_info_pointer;
	};

}

template<typename T>
inline T* gui::Gui::add(T* object, const std::string & name)
{
	static_assert(std::is_convertible<T*, gui::gui_object*>::value, "Can not convertible argument");
	return static_cast<T*>(addToGui(object, name));
}

template<typename T>
inline T* gui::Gui::add(T& object, const std::string & name)
{
	static_assert(std::is_convertible<T*, gui::gui_object*>::value, "Can not convertible argument");
	return static_cast<T*>(addToGui(object, name));
}

#endif // !GUI_DEFAULT_LAYOUT_H
