#ifndef GUI_MOUSE_INFO_H
#define GUI_MOUSE_INFO_H

#include "SFML\Graphics.hpp"

namespace gui
{

	class Mouse_info
	{
	public:
		void setButtonState(sf::Mouse::Button button, bool state);
		void setMouseWheelMove(float mouse_wheel_move);
		void setMousePosition(const sf::Vector2f& mouse_position);
		void setMouseMove(const sf::Vector2f& mouse_move);
		void update();

		std::pair<bool, bool> getButtonState(sf::Mouse::Button button) const;
		float getMouseWheelMove() const;
		const sf::Vector2f& getMousePosition() const;
		const sf::Vector2f& getMouseMove() const;

	private:
		sf::Vector2f _mouse_position{ 0, 0 };
		sf::Vector2f _mouse_move{ 0, 0 };

		float _mouse_wheel_delta{ 0 };

		bool _mouse_buttons_state[sf::Mouse::Button::ButtonCount]{0};
		bool _mouse_buttons_state_change[sf::Mouse::Button::ButtonCount]{0};
	};

}

#endif // !GUI_MOUSE_INFO_H