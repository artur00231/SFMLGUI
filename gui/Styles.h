#ifndef GUI_STYLES_H
#define GUI_STYLES_H

#include <string>
#include "SFML\Graphics.hpp"

namespace gui
{

	struct Text_style
	{
		Text_style& operator=(const Text_style & style)
		{
			_font = style._font;

			return *this;
		}

		sf::Font & _font;
		unsigned int _character_size = 20;
		sf::Color _color = sf::Color::Black;
		sf::Uint32 _style = sf::Text::Style::Regular;
		sf::Color _background_color = sf::Color::Transparent;
	};

}

#endif // !GUI_STYLES_H
