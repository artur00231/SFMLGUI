#include "Scroll_area.h"

gui::Scroll_area::Scroll_area(const Text_style * text_style) : _h_slider_use{ false }, _v_slider_use{ false }, _default_text_style{ _default_font }
{
	if (text_style)
	{
		_default_text_style = *text_style;
	}

	_texture.reset(new sf::RenderTexture);
	_texture->create(1, 1);

	_rectangle.setFillColor(sf::Color(171, 171, 171));
	_rectangle.setOutlineThickness(1);
	_rectangle.setOutlineColor(sf::Color::Black);

	_clear_color = sf::Color::White;
}

void gui::Scroll_area::setSize(const sf::Vector2f & size)
{
	_size = size;
	resize(true);
	setScrollAreaSize({ _size.x - _h_slider.getMinMax().second * _step, _size.y - _v_slider.getMinMax().second * _step });
}

void gui::Scroll_area::setPosition(const sf::Vector2f & position)
{
	_position = position;

	_sprite.setPosition(position);

	sf::Rect<float> scroll_area{ _position, (_texture ? static_cast<sf::Vector2f>(_texture->getSize()) : sf::Vector2f{0, 0}) };

	_v_slider.setPosition({ scroll_area.left + scroll_area.width, scroll_area.top });
	_h_slider.setPosition({ scroll_area.left, scroll_area.top + scroll_area.height });

	_rectangle.setPosition({ scroll_area.left + scroll_area.width + 1, scroll_area.top + scroll_area.height + 1});
}

const sf::Vector2f & gui::Scroll_area::getSize() const
{
	return _size;
}

const sf::Vector2f & gui::Scroll_area::getPosition() const
{
	return _position;
}

const sf::Rect<float> gui::Scroll_area::getGlobalBounds() const
{
	return sf::Rect<float>{ _position, _size };
}

void gui::Scroll_area::setOwner(owner & owner)
{
	_owner = &owner;

	_default_text_style = owner.getTextStyle();

	for (auto &x : _gui_objects)
	{
		x.second.first->setOwner(*this);
	}

	if (_h_slider_use)
	{
		_owner->addObject(_h_slider);
	}
	if (_v_slider_use)
	{
		_owner->addObject(_v_slider);
	}

}

void gui::Scroll_area::removeFromOwner(owner & owner)
{
	if (_v_slider_use)
	{
		owner.remove(&_v_slider);
	}

	if (_h_slider_use)
	{
		owner.remove(&_h_slider);
	}

	_owner = nullptr;
}

void gui::Scroll_area::draw(sf::RenderTarget & window) const
{
	window.draw(_sprite);
	
	if (_v_slider_use && _h_slider_use)
	{
		window.draw(_rectangle);
	}
}

gui::gui_object * gui::Scroll_area::addObject(gui::gui_object * object, const std::string & name)
{
	return addToMap(object, name);
}

gui::gui_object * gui::Scroll_area::addObject(gui::gui_object & object, const std::string & name)
{
	return addToMap(object, name);
}

void gui::Scroll_area::remove(const std::string & name)
{
	auto to_erase = _gui_objects[name];

	to_erase.first->removeFromOwner(*this);

	if (to_erase.second)
	{
		delete to_erase.first;
	}

	_gui_objects.erase(name);

	resize();
}

void gui::Scroll_area::remove(const gui::gui_object * object)
{
	decltype(_gui_objects.end()) poz = _gui_objects.end();

	for (auto i = _gui_objects.begin(); i != _gui_objects.end(); i++)
	{
		if (object == i->second.first)
		{
			poz = i;
			break;
		}
	}

	if (poz != _gui_objects.end())
	{
		poz->second.first->removeFromOwner(*this);

		if (poz->second.second)
		{
			delete poz->second.first;
		}

		_gui_objects.erase(poz);
	}

	resize();
}

void gui::Scroll_area::getEvents(active_gui_object & object, const sf::Window & window)
{
	if (_owner)
	{
		auto real_global_bounds = getRealGlobalBounds(&object);

		if (real_global_bounds != sf::Rect<float>{ {0, 0}, { 0, 0 } })
		{
			_owner->getEvents(object, window, real_global_bounds);
		}
	}
}

void gui::Scroll_area::getEvents(active_gui_object & object, const sf::Window & window, const sf::Rect<float>& rect)
{
	if (_owner)
	{
		auto real_global_bounds = getRealGlobalBounds(rect);

		if (real_global_bounds != sf::Rect<float>{ {0, 0}, { 0, 0 } })
		{
			_owner->getEvents(object, window, real_global_bounds);
		}
	}
}

const gui::Mouse_info & gui::Scroll_area::getMouseInfo() const
{
	return _mouse_info;
}

gui::gui_object * gui::Scroll_area::get(const std::string & name) const
{
	return _gui_objects.at(name).first;
}

std::pair<bool, bool> gui::Scroll_area::getSliders() const
{
	return std::pair<bool, bool>{ _h_slider_use, _v_slider_use };
}

sf::Vector2f gui::Scroll_area::getMaxSize() const
{
	auto max_x = _size.x + (_h_slider_use ? _h_slider.getMaxSteps() : 0) * _step;
	auto max_y = _size.y + (_v_slider_use ? _v_slider.getMaxSteps() : 0) * _step;

	return { max_x, max_y };
}

sf::Vector2f gui::Scroll_area::getScrollAreaSize() const
{
	sf::Vector2f size;
	size.x = _h_slider.getMinMax().second * _step + _size.x - (_v_slider_use ? _v_slider.getSize().x : 0);
	size.y = _v_slider.getMinMax().second * _step + _size.y - (_h_slider_use ? _h_slider.getSize().x : 0);

	return size;
}

const sf::Color & gui::Scroll_area::getClearColor() const
{
	return _clear_color;
}

sf::Vector2f gui::Scroll_area::getMaxScrollAreaSize() const
{
	auto max_v_slider = (_v_slider_use ? _v_slider.getMaxSteps() : 0);
	auto max_h_slider = (_h_slider_use ? _h_slider.getMaxSteps() : 0);

	sf::Vector2f max_scroll_area_size{ _size.x + _step * max_h_slider, _size.y + _step * max_v_slider };

	return max_scroll_area_size;
}

gui::modifier::Horizontal_slider_modifier & gui::Scroll_area::getHorizontal_slider()
{
	return _h_slider;
}

const gui::modifier::Horizontal_slider_modifier & gui::Scroll_area::getHorizontal_slider() const
{
	return _h_slider;
}

gui::modifier::Vertical_slider_modifier & gui::Scroll_area::getVertical_slider()
{
	return _v_slider;
}

const gui::modifier::Vertical_slider_modifier & gui::Scroll_area::getVertical_slider() const
{
	return _v_slider;
}

void gui::Scroll_area::up_date(const sf::Window & window, gui::duration time_elapsed, owner & owner)
{
	bool need_resize = false;

	_mouse_info = owner.getMouseInfo();

	if (_v_slider.getValue() != _v_slider_value)
	{
		_v_slider_value = _v_slider.getValue();

		need_resize = true;
	}

	if (_h_slider.getValue() != _h_slider_value)
	{
		_h_slider_value = _h_slider.getValue();

		need_resize = true;
	}

	if (need_resize)
	{
		resize();
	}

	std::vector<gui::Radio_button*> radio_buttons;
	std::vector<gui::gui_object*> objects;

	for (auto &x : _gui_objects)
	{
		if (gui::active_gui_object * object = dynamic_cast<gui::active_gui_object*>(x.second.first))
		{
			if (object->isNeedResize())
			{
				object->resize();
			}

			if (gui::Radio_button * radio_button = dynamic_cast<gui::Radio_button*>(x.second.first))
			{
				if (radio_button->getState() == gui::Radio_button_state::CHECKED && !radio_button->isExlusive())
				{
					radio_buttons.push_back(radio_button);
				}
			}

			auto real_global_bounds = getRealGlobalBounds(object);

			if (real_global_bounds != sf::Rect<float>{ {0, 0}, { 0, 0 } })
			{
				owner.getEvents(*object, window, real_global_bounds);
				objects.push_back(object);
			}
			object->up_date(std::chrono::duration_cast<std::chrono::microseconds>(time_elapsed), owner.getMouseInfo());
		}
		else if (gui::managing_gui_object * managing_object = dynamic_cast<gui::managing_gui_object*>(x.second.first))
		{
			managing_object->up_date(window, std::chrono::duration_cast<std::chrono::microseconds>(time_elapsed), *this);

			auto real_global_bounds = getRealGlobalBounds(managing_object);

			if (real_global_bounds != sf::Rect<float>{ {0, 0}, { 0, 0 } })
			{
				objects.push_back(managing_object);
			}
		}
	}

	checkRadio_buttons(radio_buttons);

	if (_texture)
	{
		_texture->clear(_clear_color);

		for (auto &x : objects)
		{
			x->draw(*_texture);
		}

		_texture->setView(_view);
		_texture->display();

		_sprite.setTexture(_texture->getTexture());
	}
}

void gui::Scroll_area::setTextStyle(const Text_style & text_style)
{
	_default_text_style = text_style;
}

void gui::Scroll_area::setSliders(bool horizontal, bool vertical)
{
	if (_owner)
	{
		if (horizontal)
		{
			if (!_h_slider_use)
			{
				_owner->addObject(_h_slider);
				_h_slider_use = true;
			}
		}
		else
		{
			if (_h_slider_use)
			{
				_owner->remove(&_h_slider);
				_h_slider_use = false;
			}
		}

		if (vertical)
		{
			if (!_v_slider_use)
			{
				_owner->addObject(_v_slider);
				_v_slider_use = true;
			}
		}
		else
		{
			if (_v_slider_use)
			{
				_owner->remove(&_v_slider);
				_v_slider_use = false;
			}
		}

		resize();
	}
	else
	{
		_v_slider_use = vertical;
		_h_slider_use = horizontal;

		resize(true);
	}
}

void gui::Scroll_area::setScrollAreaSize(sf::Vector2f size)
{
	auto max_size = getMaxSize();

	if (size.x < _size.x)
	{
		size.x = _size.x;
	}

	if (size.y < _size.y)
	{
		size.y = _size.y;
	}

	auto h_max = std::round(((size.x < max_size.x ? size.x : max_size.x) - _size.x) / _step);
	auto v_max = std::round(((size.y < max_size.y ? size.y : max_size.y) - _size.y) / _step);

	_h_slider.setMinMax(0, h_max);
	_v_slider.setMinMax(0, v_max);
}

void gui::Scroll_area::setClearColor(const sf::Color & color)
{
	_clear_color = color;
}

const gui::Text_style& gui::Scroll_area::getTextStyle() const
{
	return _default_text_style;
}

void gui::Scroll_area::resize(bool size_changed)
{
	if (size_changed)
	{
		_v_slider.setSize({ 20, (_h_slider_use ? _size.y - 20 : _size.y) });
		_h_slider.setSize({ (_v_slider_use ? _size.x - 20 : _size.x), 20 });

		_rectangle.setSize({ _v_slider.getSize().x - 2, _h_slider.getSize().y - 2});

		_v_slider.setValue(0);
		_h_slider.setValue(0);

		float min_size_x = (_v_slider_use ? _v_slider.getSize().x : 0);
		float min_size_y = (_h_slider_use ? _h_slider.getSize().y : 0);


		bool fit_x = _size.x > min_size_x;
		bool fit_y = _size.y > min_size_y;

		if (fit_x && fit_y)
		{
			_texture.reset(new sf::RenderTexture);
			_texture->create(_size.x - min_size_x, _size.y - min_size_y);
			_view.setSize(_size.x - min_size_x, _size.y - min_size_y);
			_view.setCenter((_size.x - min_size_x) / 2, (_size.y - min_size_y) / 2);
		}
		else
		{
			if (!fit_x)
			{
				_size.x = min_size_x + 1;
			}
			else if (!fit_y)
			{
				_size.y = min_size_y + 1;
			}

			resize(true);
		}
	}

	float min_size_x = (_v_slider_use ? _v_slider.getSize().x : 0);
	float min_size_y = (_h_slider_use ? _h_slider.getSize().y : 0);

	_scroll_area_rect = { { 0, 0 }, { (_size.x - min_size_x), (_size.y - min_size_y) } };

	_scroll_area_rect.left = _h_slider.getValue() * _step;
	_scroll_area_rect.top = _v_slider.getValue() * _step;

	auto x = _size.x / 2 + _step * _h_slider.getValue();

	_view.setCenter((_size.x - min_size_x) / 2 + _step * _h_slider.getValue(), (_size.y - min_size_y) / 2 + _step * _v_slider.getValue());

	setPosition(_position);

}

gui::Scroll_area::~Scroll_area()
{
	for (auto &x : _gui_objects)
	{
		if (x.second.second)
		{
			delete x.second.first;
		}
	}
}

void gui::Scroll_area::checkRadio_buttons(std::vector<gui::Radio_button*> & radio_buttons)
{
	if (radio_buttons.size() > 1)
	{
		gui::Radio_button * clicked_radio_button = nullptr;

		for (auto x : radio_buttons)
		{
			if (x->isClicked())
			{
				clicked_radio_button = x;
				break;
			}
		}

		for (auto x : radio_buttons)
		{
			if (x != clicked_radio_button)
			{
				x->setState(gui::Radio_button_state::UNCHECKED);
			}
		}
	}
}

std::string gui::Scroll_area::getUniqeName()
{
	std::string name{ "___" };
	name += std::to_string(_uniqe_name_count++);
	return name;
}

void gui::Scroll_area::drawAll()
{
	for (auto const &x : _gui_objects)
	{
		x.second.first->draw(*_texture);
	}
}

sf::Rect<float> gui::Scroll_area::getRealGlobalBounds(const gui_object * object)
{
	auto object_rect = object->getGlobalBounds();

	if (_scroll_area_rect.intersects(object_rect))
	{
		sf::Vector2f position;
		position.x = (object_rect.left > _scroll_area_rect.left ? object_rect.left : _scroll_area_rect.left);
		position.y = (object_rect.top > _scroll_area_rect.top ? object_rect.top : _scroll_area_rect.top);

		sf::Vector2f pointA{ _scroll_area_rect.top + _scroll_area_rect.height, object_rect.top + object_rect.height };
		sf::Vector2f pointB{ _scroll_area_rect.left + _scroll_area_rect.width, object_rect.left + object_rect.width };

		sf::Vector2f size;
		size.x = (pointB.x < pointB.y ? pointB.x : pointB.y) - position.x;
		size.y = (pointA.x < pointA.y ? pointA.x : pointA.y) - position.y;

		position.x -= _step * _h_slider_value;
		position.x += _position.x;
		position.y -= _step * _v_slider_value;
		position.y += _position.y;

		return { position, size };
	}

	return { {0, 0}, {0, 0} };
}

sf::Rect<float> gui::Scroll_area::getRealGlobalBounds(const sf::Rect<float>& object_rect)
{
	if (_scroll_area_rect.intersects(object_rect))
	{
		sf::Vector2f position;
		position.x = (object_rect.left > _scroll_area_rect.left ? object_rect.left : _scroll_area_rect.left);
		position.y = (object_rect.top > _scroll_area_rect.top ? object_rect.top : _scroll_area_rect.top);

		sf::Vector2f pointA{ _scroll_area_rect.top + _scroll_area_rect.height, object_rect.top + object_rect.height };
		sf::Vector2f pointB{ _scroll_area_rect.left + _scroll_area_rect.width, object_rect.left + object_rect.width };

		sf::Vector2f size;
		size.x = (pointB.x < pointB.y ? pointB.x : pointB.y) - position.x;
		size.y = (pointA.x < pointA.y ? pointA.x : pointA.y) - position.y;

		position.x -= _step * _h_slider_value;
		position.x += _position.x;
		position.y -= _step * _v_slider_value;
		position.y += _position.y;

		return { position, size };
	}

	return { { 0, 0 },{ 0, 0 } };
}

gui::gui_object * gui::Scroll_area::addToMap(gui::gui_object * object, const std::string & name)
{
	std::string object_name = name;

	if (object_name == "")
	{
		object_name = getUniqeName();
	}

	if (_gui_objects.count(object_name) == 1)
	{
		remove(object_name);
	}

	std::pair<std::string, std::pair<gui::gui_object*, bool>> pair{ object_name,{ object, true } };
	_gui_objects.insert(pair);
	object->setOwner(*this);


	resize();

	return object;
}

gui::gui_object * gui::Scroll_area::addToMap(gui::gui_object & object, const std::string & name)
{
	std::string object_name = name;

	if (object_name == "")
	{
		object_name = getUniqeName();
	}

	if (_gui_objects.count(object_name) == 1)
	{
		remove(object_name);
	}

	std::pair<std::string, std::pair<gui::gui_object*, bool>> pair{ object_name,{ &object, false } };
	_gui_objects.insert(pair);
	object.setOwner(*this);

	resize();

	return &object;
}

sf::Font gui::Scroll_area::_default_font;