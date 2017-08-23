#include "Radio_button.h"
#include "Icons\Icons.h"

sf::Texture gui::Radio_button::_checked_mark_texture;
sf::Texture gui::Radio_button::_checked_outline_texture;

gui::Radio_button::Radio_button(const sf::String & text) : _label{ text }
{
	// Load the checked mark icon
	auto Checked_icon = gui::Icons::get(gui::Icons::RADIO_BUTTON_MARK);
	_checked_mark_texture.loadFromMemory(Checked_icon.first, Checked_icon.second);
	_checked_mark_texture.setSmooth(true);
	_checked_mark.setTexture(&_checked_mark_texture);

	// Load the checked frame icon
	Checked_icon = gui::Icons::get(gui::Icons::RADIO_BUTTON_OUTLINE);
	_checked_outline_texture.loadFromMemory(Checked_icon.first, Checked_icon.second);
	_checked_outline_texture.setSmooth(true);
	_checked_outline.setTexture(&_checked_outline_texture);

	// Default state is unchecked
	setState(Radio_button_state::UNCHECKED);
}

void gui::Radio_button::setSize(const sf::Vector2f & size)
{
	_size = size;
	resize();
}

void gui::Radio_button::setPosition(const sf::Vector2f & position)
{
	_position = position;

	float checked_mark_padding_left = _checked_mark.getSize().x * _proportions_checked_filed + 2 * _checked_outline_thickness;
	float checked_size = _checked_mark.getSize().x + 2 * checked_mark_padding_left;

	_checked_mark.setPosition({ position.x + _frame.getThickness() + checked_mark_padding_left, position.y + _size.y / 2 - _checked_mark.getSize().y / 2 });
	_label.setPosition({ position.x + _frame.getThickness() + checked_size, position.y + _frame.getThickness() });

	sf::Vector2f position_to_fit{ _position.x + _frame.getThickness(), _position.y + _frame.getThickness() };
	sf::Vector2f size_to_fit{ _size.x - 2 * _frame.getThickness(), _size.y - 2 * _frame.getThickness() };

	_frame.fitTo({ position_to_fit, size_to_fit });
	_background.fitTo({ position_to_fit, size_to_fit });
	_checked_outline.setPosition({ _checked_mark.getPosition().x - _checked_outline_thickness, _checked_mark.getPosition().y - _checked_outline_thickness });

}

const sf::Vector2f & gui::Radio_button::getSize() const
{
	return _size;
}

const sf::Vector2f & gui::Radio_button::getPosition() const
{
	return _position;
}

const sf::Rect<float> gui::Radio_button::getGlobalBounds() const
{
	return _frame.getGlobalBounds();
}

void gui::Radio_button::up_date(gui::duration time_elapsed, const Mouse_info & mouse_info)
{

	_function(mouse_info, time_elapsed, this);
}

void gui::Radio_button::draw(sf::RenderTarget & render_target) const
{
	_background.draw(render_target);
	_label.draw(render_target);
	_checked_mark.draw(render_target);
	_frame.draw(render_target);
	_checked_outline.draw(render_target);
}

void gui::Radio_button::setOwner(gui::owner & owner)
{
	_label.setTextStyle(owner.getTextStyle());
}

bool gui::Radio_button::isActive() const
{
	return _active;
}

bool gui::Radio_button::isHover() const
{
	return _hover;
}

bool gui::Radio_button::isClicked() const
{
	return _clicked;
}

bool gui::Radio_button::isFocused() const
{
	return _focus;
}

bool gui::Radio_button::isHoverChange() const
{
	return _hover_change;
}

bool gui::Radio_button::isClickedChange() const
{
	return _clicked_change;
}

bool gui::Radio_button::isNeedResize() const
{
	return _need_resize;
}

bool gui::Radio_button::isExlusive() const
{
	return _exclusive;
}

void gui::Radio_button::setActive(bool active)
{
	_active = active;
}

void gui::Radio_button::setFocus(bool focus)
{
	_focus = focus;
}

void gui::Radio_button::setExlusive(bool exclusive)
{
	_exclusive = exclusive;
}

gui::Radio_button_state gui::Radio_button::getState() const
{
	return _radio_button_state;
}

void gui::Radio_button::setProportions(float proportions_text_checked_frame, float proportions_checked_filed)
{
	_proportions_text_checked_frame = proportions_text_checked_frame;
	_proportions_checked_filed = proportions_checked_filed;
	resize();
}

void gui::Radio_button::resize()
{
	_need_resize = false;

	if (_size.x - 2 * _frame.getThickness() > 0 && _size.y - 2 * _frame.getThickness() > 0)
	{
		float ideal_checked_size = _label.getCharacterSize() * _proportions_text_checked_frame;

		// checkbox_frame size is std::min({ ideal_checked_size, _size.y - 2 * _frame.getThickness() })
		float checked_size = ideal_checked_size < _size.y - 2 * _frame.getThickness() ? ideal_checked_size : _size.y - 2 * _frame.getThickness();

		if (checked_size < _size.x)
		{
			_label.setSize({ _size.x - 2 * _frame.getThickness() - checked_size, _size.y - 2 * _frame.getThickness() });
			float checked_outline_size = checked_size - checked_size * _proportions_checked_filed;
			_checked_outline.setSize({ checked_outline_size, checked_outline_size });
			float checked_mark_size = checked_size - checked_size * _proportions_checked_filed - 2 * _checked_outline_thickness;
			_checked_mark.setSize({ checked_mark_size, checked_mark_size });

		}
		else
		{
			// Can not fit radio_button
			// Minimal size is 2 * _frame.getThickness()
			_size = { 2 * _frame.getThickness() , 2 * _frame.getThickness() };
			_label.setSize({ 0, 0 });
			_checked_mark.setSize({ 0, 0 });
			_checked_outline.setSize({ 0, 0 });
		}
	}
	else
	{
		// Can not fit radio_button
		// Minimal size is 2 * _frame.getThickness()
		_size = { 2 * _frame.getThickness() , 2 * _frame.getThickness() };
		_label.setSize({ 0, 0 });
		_checked_mark.setSize({ 0, 0 });
		_checked_outline.setSize({ 0, 0 });
	}

	setPosition(_position);
}

gui::modifier::Frame_modifier & gui::Radio_button::getFrame()
{
	_need_resize = true;
	return _frame;
}

gui::modifier::Label_modifier & gui::Radio_button::getLabel()
{
	_need_resize = true;
	return _label;
}

gui::modifier::Background_modifier & gui::Radio_button::getBackground()
{
	_need_resize = true;
	return _background;
}

gui::modifier::Function_modifier & gui::Radio_button::getFunction()
{
	return _function;
}

gui::modifier::Image_modifier & gui::Radio_button::getCheckedMark()
{
	_need_resize = true;
	return _checked_mark;
}

void gui::Radio_button::setHover(bool hover)
{
	_hover = hover;
}

void gui::Radio_button::setClicked(bool clicked)
{
	_clicked = clicked;
}

void gui::Radio_button::setHoverChange(bool hover_change)
{
	_hover_change = hover_change;
}

void gui::Radio_button::setClickedChange(bool clicked_change)
{
	_clicked_change = clicked_change;

	if (clicked_change && _clicked)
	{
		switch (_radio_button_state)
		{
		case gui::Radio_button_state::CHECKED:
			setState(Radio_button_state::UNCHECKED);
			break;

		case gui::Radio_button_state::UNCHECKED:
			setState(Radio_button_state::CHECKED);
			break;

		default:
			break;
		}
	}
}

void gui::Radio_button::setState(Radio_button_state checkbox_state)
{
	sf::Color checked_mark_color = _checked_mark.getColor();

	switch (checkbox_state)
	{
	case gui::Radio_button_state::CHECKED:
		// Make the checked_mark opaque
		checked_mark_color.a = 255;
		_checked_mark.setColor(checked_mark_color);
		_radio_button_state = Radio_button_state::CHECKED;
		break;

	case gui::Radio_button_state::UNCHECKED:
		// Make the checked_mark half-transparent
		checked_mark_color.a = 0;
		_checked_mark.setColor(checked_mark_color);
		_radio_button_state = Radio_button_state::UNCHECKED;
		break;

	default:
		break;
	}
}

const sf::Image gui::Radio_button::getDefaultMark() const
{
	return _checked_mark_texture.copyToImage();
}

const sf::Image gui::Radio_button::getDefaultOutline() const
{
	return _checked_outline_texture.copyToImage();
}

std::pair<float, float> gui::Radio_button::getProportions() const
{
	return std::pair<float, float>{_proportions_text_checked_frame, _proportions_checked_filed};
}
