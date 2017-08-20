#ifndef GUI_STYLES_H
#define GUI_STYLES_H

#include <string>
#include "SFML\Graphics.hpp"

namespace gui
{

	struct Text_style
	{
		std::string _font_patch;
		unsigned int _character_size;
		sf::Color _color;
		sf::Uint32 _style = sf::Text::Style::Regular;
		sf::Color _background_color = sf::Color::Transparent;
	};

}

#endif // !GUI_STYLES_H
