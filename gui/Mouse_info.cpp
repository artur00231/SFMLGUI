#include "Mouse_info.h"

void gui::Mouse_info::setButtonState(sf::Mouse::Button button, bool state)
{
	_mouse_buttons_state[button] = state;
	_mouse_buttons_state_change[button] = true;
}

void gui::Mouse_info::setMouseWheelMove(float mouse_wheel_move)
{
	_mouse_wheel_delta = mouse_wheel_move;
}

void gui::Mouse_info::setMousePosition(const sf::Vector2f & mouse_position)
{
	setMouseMove(mouse_position - _mouse_position + _mouse_move);

	_mouse_position = mouse_position;
}

void gui::Mouse_info::setMouseMove(const sf::Vector2f & mouse_move)
{
	_mouse_move = mouse_move;
}

void gui::Mouse_info::update()
{
	for (int i = 0; i < sf::Mouse::Button::ButtonCount; i++)
	{
		_mouse_buttons_state_change[i] = false;
	}

	_mouse_move = { 0, 0 };
}

std::pair<bool, bool> gui::Mouse_info::getButtonState(sf::Mouse::Button button) const
{
	return { _mouse_buttons_state[button], _mouse_buttons_state_change[button] };
}

float gui::Mouse_info::getMouseWheelMove() const
{
	return _mouse_wheel_delta;
}

const sf::Vector2f & gui::Mouse_info::getMousePosition() const
{
	return _mouse_position;
}

const sf::Vector2f & gui::Mouse_info::getMouseMove() const
{
	return _mouse_move;
}