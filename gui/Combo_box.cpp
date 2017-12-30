#include "Combo_box.h"

gui::Combo_box::Combo_box() : _down{ L'\u02C5' }
{
	_area.setSliders(false, true);
	_area.addObject(_layout);

	_down.getFunction().set([this]() {if (this->_down.isClicked() && this->_down.isClickedChange()) { this->showArea(!this->_showed_area); } });
}

void gui::Combo_box::setSize(const sf::Vector2f & size)
{
	if (size.x - 2 * _frame.getThickness() > 0 && size.y - 2 * _frame.getThickness() > 0)
	{
		_size = size;
		resize();
	}
}

void gui::Combo_box::setPosition(const sf::Vector2f & position)
{
	_position = position;

	float frame_thickness = _frame.getThickness();

	_button.setPosition({ position.x + frame_thickness, position.y + frame_thickness });
	_down.setPosition({ position.x - frame_thickness + _size.x - _slider_min_size, position.y + frame_thickness });

	_area.setPosition({ position.x + frame_thickness, position.y + _size.y });

	sf::Vector2f size = { _size.x - 2 * frame_thickness, _size.y - 2 * frame_thickness };

	sf::Rect<float> to_fit{ { position.x + frame_thickness, position.y + frame_thickness }, size };

	_background.fitTo(to_fit);

	if (_showed_area)
	{
		to_fit.height += _area.getSize().y + frame_thickness;
	}

	_frame.fitTo(to_fit);
}

const sf::Vector2f & gui::Combo_box::getSize() const
{
	return _size;
}

const sf::Vector2f & gui::Combo_box::getPosition() const
{
	return _position;
}

const sf::Rect<float> gui::Combo_box::getGlobalBounds() const
{
	return _frame.getGlobalBounds();
}

void gui::Combo_box::up_date(gui::duration time_elapsed, const Mouse_info & mouse_info)
{
	_function(mouse_info, time_elapsed, this);
}

void gui::Combo_box::draw(sf::RenderTarget & render_target) const
{
	_background.draw(render_target);
	_frame.draw(render_target);
}

void gui::Combo_box::setOwner(gui::owner & owner)
{
	_owner = &owner;

	owner.addObject(_button);
	owner.addObject(_down);

	showArea(_showed_area);
}

void gui::Combo_box::removeFromOwner(owner & owner)
{
	showArea(false);

	_owner = nullptr;

	owner.remove(&_button);
	owner.remove(&_down);
}

bool gui::Combo_box::isActive() const
{
	return _active;
}

bool gui::Combo_box::isHover() const
{
	return _hover;
}

bool gui::Combo_box::isClicked() const
{
	return _clicked;
}

bool gui::Combo_box::isFocused() const
{
	return _focus;
}

bool gui::Combo_box::isHoverChange() const
{
	return _hover_change;
}

bool gui::Combo_box::isClickedChange() const
{
	return _clicked_change;
}

bool gui::Combo_box::isNeedResize() const
{
	return _need_resize;
}

bool gui::Combo_box::isExtended() const
{
	return _showed_area;
}

void gui::Combo_box::setActive(bool active)
{
	_active = active;
}

void gui::Combo_box::setFocus(bool focus)
{
	_focus = focus;
}

void gui::Combo_box::setMinOptionsInArea(unsigned int min)
{
	_min_options_in_area = min;
}

void gui::Combo_box::addOption(const sf::String & name)
{
	bool unque_name = true;

	for (auto && x : _buttons)
	{
		if (x->getLabel().getString() == name)
		{
			unque_name = false;
		}
	}

	if (!unque_name)
	{
		return;
	}

	auto new_button = _layout.add(new Button{ name });
	new_button->getFunction().set([this](gui::gui_object * object) {this->buttonsFunction(object); });

	_buttons.push_back(new_button);

	if (_buttons.size() == 1)
	{
		_button.getLabel().setString(name);
	}

	resize();
}

void gui::Combo_box::setOptions(const std::vector<sf::String> & names)
{
	clearOptions();

	for (auto &x : names)
	{
		addOption(x);
	}
}

void gui::Combo_box::removeOption(const sf::String & name)
{
	auto ptr = std::find_if(_buttons.begin(), _buttons.end(), [&name](Button * button) {return button->getLabel().getString() == name; });

	if (ptr != _buttons.end())
	{
		_buttons.erase(ptr);
	}

	if (_buttons.size() == 0)
	{
		_button.getLabel().setString("");
	}

	resize();
}

void gui::Combo_box::clearOptions()
{
	for (auto &x : _buttons)
	{
		_layout.remove(x);
	}

	_buttons.clear();
}

bool gui::Combo_box::setActiveOption(const sf::String & name)
{
	bool find = false;

	auto pos = std::find_if(_buttons.begin(), _buttons.end(), [&name](const gui::Button* button) {return button->getLabel().getString() == name; });

	if (pos == _buttons.end())
	{
		return false;
	}

	_button.getLabel().setString(name);

	return true;
}

bool gui::Combo_box::setActiveOptionByIndex(std::size_t index)
{
	if (index >= _buttons.size())
	{
		return false;
	}

	_button.getLabel().setString(_buttons.at(index)->getLabel().getString());

	return true;
}

unsigned int gui::Combo_box::getMinOptionsInArea() const
{
	return _min_options_in_area;
}

sf::String gui::Combo_box::getActiveOption() const
{
	return _button.getLabel().getString();
}

std::size_t gui::Combo_box::getActiveOptionIndex() const
{
	auto name = _button.getLabel().getString();
	auto pos = std::find_if(_buttons.begin(), _buttons.end(), [&name](const gui::Button* button) {return button->getLabel().getString() == name; });

	return (pos == _buttons.end() ? 0 : pos - _buttons.begin());
}

void gui::Combo_box::resize()
{
	_need_resize = false;

	if (_need_buttons_change)
	{
		changeButtonsPattern();
	}

	float frame_thickness = _frame.getThickness();

	if (_size.x - 2 * frame_thickness - _slider_min_size > 0 && _size.y - 2 * frame_thickness > 0)
	{
		_button.setSize({ _size.x - 2 * frame_thickness - _slider_min_size, _size.y - 2 * frame_thickness });
		_down.setSize({ _slider_min_size, _size.y - 2 * frame_thickness });

		if (_buttons.size() > _min_options_in_area)
		{
			auto size_y = (_size.y - 2 * frame_thickness) * _buttons.size();
			size_y = size_y >= 60 ? size_y : 60;

			_area.setSize({ _size.x - 2 * frame_thickness, (_size.y - 2 * frame_thickness) * _min_options_in_area });


			while (_area.getMaxScrollAreaSize().y < size_y)
			{
				_area.setSize({ _area.getSize().x, _area.getSize().y + (_size.y - 2 * frame_thickness) });
			}

			_area.setScrollAreaSize({ _size.x - 2 * frame_thickness - _slider_min_size, size_y });
			_layout.setSize({ _area.getScrollAreaSize() });

		}
		else
		{
			auto size_y = (_size.y) * _buttons.size();
			size_y = (size_y >= 60 ? size_y : 60);

			_area.setSize({ _size.x - 2 * frame_thickness, size_y });
			_area.setScrollAreaSize({ _size.x - 2 * frame_thickness - _slider_min_size, size_y });
			_layout.setSize({ _area.getScrollAreaSize() });
		}
	}
	else
	{
		// Can not fit
		// Minimal size is 2 * _frame.getThickness()
		_size = { 2 * _frame.getThickness() , 2 * _frame.getThickness() };
		_button.setSize({ 0, 0 });
		_down.setSize({ 0, 0 });
		showArea(false);
	}

	

	setPosition(_position);
}

void gui::Combo_box::extend(bool extend)
{
	showArea(extend);
}

gui::modifier::Frame_modifier & gui::Combo_box::getFrame()
{
	_need_resize = true;
	return _frame;
}

const gui::modifier::Frame_modifier & gui::Combo_box::getFrame() const
{
	return _frame;
}

gui::modifier::Background_modifier & gui::Combo_box::getBackground()
{
	_need_resize = true;
	return _background;
}

const gui::modifier::Background_modifier & gui::Combo_box::getBackground() const
{
	return _background;
}

gui::modifier::Function_modifier & gui::Combo_box::getFunction()
{
	return _function;
}

const gui::modifier::Function_modifier & gui::Combo_box::getFunction() const
{
	return _function;
}

gui::modifier::Button_modifier & gui::Combo_box::getMainButton()
{
	_need_resize = true;
	return _button;
}

const gui::modifier::Button_modifier & gui::Combo_box::getMainButton() const
{
	return _button;
}

gui::modifier::Button_modifier & gui::Combo_box::getDown()
{
	_need_resize = true;
	return _down;
}

const gui::modifier::Button_modifier & gui::Combo_box::getDown() const
{
	return _down;
}

gui::modifier::Button_modifier & gui::Combo_box::getOption()
{
	_need_resize = true;
	_need_buttons_change = true;
	return _option_button_pattern;
}

const gui::modifier::Button_modifier & gui::Combo_box::getOption() const
{
	return _option_button_pattern;
}

gui::modifier::Vertical_slider_modifier & gui::Combo_box::getSlider()
{
	return _area.getVertical_slider();
}

const gui::modifier::Vertical_slider_modifier & gui::Combo_box::getSlider() const
{
	return _area.getVertical_slider();
}

void gui::Combo_box::setHover(bool hover)
{
	_hover = hover;
}

void gui::Combo_box::setClicked(bool clicked)
{
	_clicked = clicked;
}

void gui::Combo_box::setHoverChange(bool hover_change)
{
	_hover_change = hover_change;
}

void gui::Combo_box::setClickedChange(bool clicked_change)
{
	_clicked_change = clicked_change;
}

void gui::Combo_box::buttonsFunction(gui::gui_object * object)
{
	auto button = static_cast<gui::Button*>(object);

	if (button->isClickedChange() && button->isClicked())
	{
		_button.getLabel().setString(button->getLabel().getString());
	}

}

void gui::Combo_box::changeButtonsPattern()
{
	_need_buttons_change = false;

	auto align = _option_button_pattern.getLabel().getAlign();
	auto character_size = _option_button_pattern.getLabel().getCharacterSize();
	auto label_color = _option_button_pattern.getLabel().getColor();
	auto font = _option_button_pattern.getLabel().getFont();
	auto style = _option_button_pattern.getLabel().getStyle();

	auto background_type = _option_button_pattern.getBackground().getBackground_type();
	auto background_color = _option_button_pattern.getBackground().getColor();
	auto image = _option_button_pattern.getBackground().getImage();

	auto frame_color = _option_button_pattern.getFrame().getColor();
	auto thickness = _option_button_pattern.getFrame().getThickness();

	for (auto &x : _buttons)
	{
		// Label
		x->getLabel().setAlign(align);
		x->getLabel().setCharacterSize(character_size);
		x->getLabel().setColor(label_color);
		x->getLabel().setFont(font);
		x->getLabel().setStyle(style);

		// Background
		if (background_type == gui::Background_type::COLOR)
		{
			x->getBackground().setColor(background_color);
		}
		else
		{
			if (image)
			{
				x->getBackground().setImage(static_cast<gui::Image*>(image));
				x->getBackground().setColor(background_color);
			}
		}

		// Frame
		x->getFrame().setColor(frame_color);
		x->getFrame().setThickness(thickness);

	}
}

void gui::Combo_box::showArea(bool show)
{
	if (_showed_area != show)
	{
		_showed_area = show;
		if (_owner)
		{
			if (show)
			{
				_owner->addObject(_area);
			}
			else
			{
				_owner->remove(&_area);
			}

			setPosition(_position);
		}
	}
}
