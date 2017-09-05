#ifndef GUI_FONT_MANAGER_H
#define GUI_FONT_MANAGER_H

#include <unordered_map>
#include <memory>
#include "SFML\Graphics.hpp"
#include "Styles.h"

namespace gui
{

	class Font_manager
	{
	public:
		Font_manager() = default;

		Font_manager(const Font_manager&);
		Font_manager& operator=(const Font_manager&);
		Font_manager(Font_manager&&) = default;
		Font_manager& operator=(Font_manager&&) = default;

		bool add(sf::Font * font, std::string name);
		bool add(std::string path, std::string name);

		sf::Font* get(std::string name);
		const sf::Font* get(std::string name) const;
		sf::Font& operator[](std::string name);
		const sf::Font& operator[](std::string name) const;

		~Font_manager() {};

	private:
		std::unordered_map<std::string, std::unique_ptr<sf::Font>> _fonts;
	};

}

#endif // !GUI_FONT_MANAGER_H
