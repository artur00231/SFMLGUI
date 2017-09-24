#ifndef GUI_SCROLL_AREA_H
#define GUI_SCROLL_AREA_H

#include "managing_gui_object.h"
#include "Radio_button.h"
#include "Horizontal_slider.h"
#include "Vertical_slider.h"
#include <unordered_map>

namespace gui
{

	class Scroll_area : public managing_gui_object
	{
	public:
		Scroll_area(const Text_style* = {});

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
		void setSliders(bool horizontal, bool vertical);
		void setScrollAreaSize(sf::Vector2f size);
		void setClearColor(const sf::Color & color);

		const Text_style& getTextStyle() const override;
		gui::gui_object* get(const std::string&) const override;
		std::pair<bool, bool> getSliders() const;
		sf::Vector2f getMaxSize() const;
		sf::Vector2f getScrollAreaSize() const;
		const sf::Color& getClearColor() const;
		sf::Vector2f getMaxScrollAreaSize() const;

		modifier::Horizontal_slider_modifier& getHorizontal_slider();
		const modifier::Horizontal_slider_modifier& getHorizontal_slider() const;
		modifier::Vertical_slider_modifier& getVertical_slider();
		const modifier::Vertical_slider_modifier& getVertical_slider() const;

		Scroll_area(const Scroll_area&) = delete;
		Scroll_area& operator=(const Scroll_area&) = delete;

		void resize(bool size_changed = false);

		~Scroll_area();

	protected:
		void checkRadio_buttons(std::vector<gui::Radio_button*>&);
		std::string getUniqeName();
		void drawAll();
		sf::Rect<float> getRealGlobalBounds(const gui_object * object);
		sf::Rect<float> getRealGlobalBounds(const sf::Rect<float> & rect);

		gui::gui_object * addToMap(gui::gui_object*, const std::string&);
		gui::gui_object * addToMap(gui::gui_object&, const std::string&);

	private:
		std::unordered_map<std::string, std::pair<gui::gui_object*, bool>> _gui_objects;
		long long _uniqe_name_count = 0;
		Text_style _default_text_style;
		sf::Vector2f _position, _size;
		std::unique_ptr<sf::RenderTexture> _texture;
		sf::View _view;
		sf::Sprite _sprite;
		Horizontal_slider _h_slider;
		Vertical_slider _v_slider;
		sf::RectangleShape _rectangle;
		sf::Rect<float> _scroll_area_rect;
		sf::Color _clear_color;
		Mouse_info _mouse_info;

		bool _need_resize, _v_slider_use = true, _h_slider_use = true;
		float _step = 10;

		long long _v_slider_value{}, _h_slider_value{};

		static sf::Font _default_font;

		owner * _owner;
	};

}

template<typename T>
inline T* gui::Scroll_area::add(T* object, const std::string & name)
{
	static_assert(std::is_convertible<T*, gui::gui_object*>::value, "Can not convertible argument");
	return static_cast<T*>(addToMap(object, name));
}

template<typename T>
inline T* gui::Scroll_area::add(T& object, const std::string & name)
{
	static_assert(std::is_convertible<T*, gui::gui_object*>::value, "Can not convertible argument");
	return static_cast<T*>(addToMap(object, name));
}

#endif // !GUI_SCROLL_AREA_H
