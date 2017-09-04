#include "Checkbox.h"
#include "Icons\Icons.h"

sf::Texture gui::Checkbox::_checked_texture;

gui::Checkbox::Checkbox(const sf::String & text) : _label{ text }
{
	// Set default checked_frame settings
	_checked_frame.setThickness(1);
	_checked_frame.setColor(sf::Color::Black);

	// Load the checked_mark icon
	auto Checked_icon = gui::Icons::get(gui::Icons::CHECKBOX);
	_checked_texture.loadFromMemory(Checked_icon.first, Checked_icon.second);
	_checked_texture.setSmooth(true);
	_checked_mark.setTexture(&_checked_texture);

	// Default state is unchecked
	setState(Checkbox_state::UNCHECKED);
}

void gui::Checkbox::setSize(const sf::Vector2f & size)
{
	_size = size;
	resize();
}

void gui::Checkbox::setPosition(const sf::Vector2f & position)
{
	_position = position;

	float checked_mark_padding_left = _checked_mark.getSize().x * _proportion_checked_filed + 2 * _checked_frame.getThickness();
	float checked_size = _checked_mark.getSize().x + 2 * checked_mark_padding_left;

	_checked_mark.setPosition({ position.x + _frame.getThickness() + checked_mark_padding_left, position.y + _size.y / 2 - _checked_mark.getSize().y / 2 });
	_label.setPosition({ position.x + _frame.getThickness() + checked_size, position.y + _frame.getThickness() });

	sf::Vector2f position_to_fit{ _position.x + _frame.getThickness(), _position.y + _frame.getThickness() };
	sf::Vector2f size_to_fit{ _size.x - 2 * _frame.getThickness(), _size.y - 2 * _frame.getThickness() };

	_frame.fitTo({ position_to_fit, size_to_fit });
	_background.fitTo({ position_to_fit, size_to_fit });
	_checked_frame.fitTo(_checked_mark);

}

const sf::Vector2f & gui::Checkbox::getSize() const
{
	return _size;
}

const sf::Vector2f & gui::Checkbox::getPosition() const
{
	return _position;
}

const sf::Rect<float> gui::Checkbox::getGlobalBounds() const
{
	return _frame.getGlobalBounds();
}

void gui::Checkbox::up_date(gui::duration time_elapsed, const Mouse_info & mouse_info)
{
	_function(mouse_info, time_elapsed, this);
}

void gui::Checkbox::draw(sf::RenderTarget & render_target) const
{
	_background.draw(render_target);
	_label.draw(render_target);
	_checked_frame.draw(render_target);
	_checked_mark.draw(render_target);
	_frame.draw(render_target);
}

void gui::Checkbox::setOwner(gui::owner & owner)
{
	_label.setTextStyle(owner.getTextStyle());
}

void gui::Checkbox::removeFromOwner(owner & owner)
{
	// Do nothing
}

bool gui::Checkbox::isActive() const
{
	return _active;
}

bool gui::Checkbox::isHover() const
{
	return _hover;
}

bool gui::Checkbox::isClicked() const
{
	return _clicked;
}

bool gui::Checkbox::isFocused() const
{
	return _focus;
}

bool gui::Checkbox::isHoverChange() const
{
	return _hover_change;
}

bool gui::Checkbox::isClickedChange() const
{
	return _clicked_change;
}

bool gui::Checkbox::isNeedResize() const
{
	return _need_resize;
}

void gui::Checkbox::setActive(bool active)
{
	_active = active;
}

void gui::Checkbox::setFocus(bool focus)
{
	_focus = focus;
}

gui::Checkbox_state gui::Checkbox::getState() const
{
	return _checkbox_state;
}

void gui::Checkbox::setThree_state(bool three_state)
{
	_three_state = three_state;
}

void gui::Checkbox::setProportions(float proportion_text_checked_frame, float proportion_checked_filed)
{
	_proportion_text_checked_frame = proportion_text_checked_frame;
	_proportion_checked_filed = proportion_checked_filed;

	resize();
}

void gui::Checkbox::resize()
{
	_need_resize = false;

	if (_size.x - 2 * _frame.getThickness() > 0 && _size.y - 2 * _frame.getThickness() > 0)
	{
		float ideal_checked_size = _label.getCharacterSize() * _proportion_text_checked_frame;

		// checkbox_frame size is std::min({ ideal_checked_size, _size.y - 2 * _frame.getThickness() })
		float checked_size = ideal_checked_size < _size.y - 2 * _frame.getThickness() ? ideal_checked_size : _size.y - 2 * _frame.getThickness();

		if (checked_size < _size.x)
		{
			_label.setSize({ _size.x - 2 * _frame.getThickness() - checked_size, _size.y - 2 * _frame.getThickness() });
			float checked_mark_size = checked_size - checked_size * _proportion_checked_filed - 2 * _checked_frame.getThickness();
			_checked_mark.setSize({ checked_mark_size, checked_mark_size });

		}
		else
		{
			// Can not fit checkbox
			// Minimal size is 2 * _frame.getThickness()
			_size = { 2 * _frame.getThickness() , 2 * _frame.getThickness() };
			_label.setSize({ 0, 0 });
			_checked_mark.setSize({ 0, 0 });
			_checked_frame.setSize({ 0, 0 });
		}
	}
	else
	{
		// Can not fit checkbox
		// Minimal size is 2 * _frame.getThickness()
		_size = { 2 * _frame.getThickness() , 2 * _frame.getThickness() };
		_label.setSize({ 0, 0 });
		_checked_mark.setSize({ 0, 0 });
		_checked_frame.setSize({ 0, 0 });
	}

	setPosition(_position);
}

gui::modifier::Frame_modifier & gui::Checkbox::getFrame()
{
	_need_resize = true;
	return _frame;
}

const gui::modifier::Frame_modifier & gui::Checkbox::getFrame() const
{
	return _frame;
}

gui::modifier::Label_modifier & gui::Checkbox::getLabel()
{
	_need_resize = true;
	return _label;
}

const gui::modifier::Label_modifier & gui::Checkbox::getLabel() const
{
	return _label;
}

gui::modifier::Background_modifier & gui::Checkbox::getBackground()
{
	_need_resize = true;
	return _background;
}

const gui::modifier::Background_modifier & gui::Checkbox::getBackground() const
{
	return _background;
}

gui::modifier::Function_modifier & gui::Checkbox::getFunction()
{
	return _function;
}

const gui::modifier::Function_modifier & gui::Checkbox::getFunction() const
{
	return _function;
}

gui::modifier::Image_modifier & gui::Checkbox::getCheckedMark()
{
	_need_resize = true;
	return _checked_mark;
}

const gui::modifier::Image_modifier & gui::Checkbox::getCheckedMark() const
{
	return _checked_mark;
}

void gui::Checkbox::setHover(bool hover)
{
	_hover = hover;
}

void gui::Checkbox::setClicked(bool clicked)
{
	_clicked = clicked;
}

void gui::Checkbox::setHoverChange(bool hover_change)
{
	_hover_change = hover_change;
}

void gui::Checkbox::setClickedChange(bool clicked_change)
{
	_clicked_change = clicked_change;

	if (clicked_change && _clicked)
	{
		switch (_checkbox_state)
		{
		case gui::Checkbox_state::CHECKED:
			setState(Checkbox_state::UNCHECKED);
			break;

		case gui::Checkbox_state::UNCHECKED:
			if (_three_state)
			{
				setState(Checkbox_state::INDETERMINATE);
			}
			else
			{
				setState(Checkbox_state::CHECKED);
			}
			break;

		case gui::Checkbox_state::INDETERMINATE:
			setState(Checkbox_state::CHECKED);
			break;

		default:
			break;
		}
	}
}

void gui::Checkbox::setState(Checkbox_state checkbox_state)
{
	sf::Color checked_mark_color = _checked_mark.getColor();

	switch (checkbox_state)
	{
	case gui::Checkbox_state::CHECKED:
		// Make the checked_mark opaque
		checked_mark_color.a = 255;
		_checked_mark.setColor(checked_mark_color);
		_checkbox_state = Checkbox_state::CHECKED;
		break;

	case gui::Checkbox_state::UNCHECKED:
		// Make the checked_mark transparent
		checked_mark_color.a = 0;
		_checked_mark.setColor(checked_mark_color);
		_checkbox_state = Checkbox_state::UNCHECKED;
		break;

	case gui::Checkbox_state::INDETERMINATE:
		// Make the checked_mark half-transparent
		checked_mark_color.a = 95;
		_checked_mark.setColor(checked_mark_color);
		_checkbox_state = Checkbox_state::INDETERMINATE;
		break;

	default:
		break;
	}
}

bool gui::Checkbox::isThree_state() const
{
	return _three_state;
}

const sf::Image gui::Checkbox::getDefaultMark() const
{
	return _checked_texture.copyToImage();
}

std::pair<float, float> gui::Checkbox::getProportions() const
{
	return std::pair<float, float>{_proportion_text_checked_frame, _proportion_checked_filed};
}
