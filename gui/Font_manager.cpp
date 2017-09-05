#include "Font_manager.h"

#include <exception>
#include <cassert>

gui::Font_manager::Font_manager(const Font_manager & manager)
{
	_fonts["default"].reset(new sf::Font);

	sf::Font * font = nullptr;

	try
	{
		for (const auto &x : manager._fonts)
		{
			font = new sf::Font{ *x.second };

			_fonts[x.first].reset(font);
		}
	}
	catch (std::bad_alloc & exception)
	{
		_fonts.clear();

		if (font)
		{
			delete font;
		}

		throw;
	}
}

gui::Font_manager & gui::Font_manager::operator=(const Font_manager & manager)
{
	_fonts.clear();

	_fonts["default"].reset(new sf::Font);

	sf::Font * font = nullptr;

	try
	{
		for (const auto &x : manager._fonts)
		{
			font = new sf::Font{ *x.second };

			_fonts[x.first].reset(font);
		}
	}
	catch (std::bad_alloc & exception)
	{
		_fonts.clear();

		if (font)
		{
			delete font;
		}

		throw;
	}

	return *this;
}

bool gui::Font_manager::add(sf::Font * font, std::string name)
{
	if (get(name) == nullptr)
	{
		_fonts[name].reset(font);
	}
	else
	{
		delete font;

		return false;
	}

	return true;
}

bool gui::Font_manager::add(std::string path, std::string name)
{
	if (get(name) == nullptr)
	{
		sf::Font * font = new sf::Font;
		if (!font->loadFromFile(path))
		{
			delete font;

			return false;
		}

		_fonts[name].reset(font);
	}
	else
	{
		return false;
	}

	return true;
}

sf::Font * gui::Font_manager::get(std::string name)
{
	sf::Font * font;

	try
	{
		font = _fonts.at(name).get();
	}
	catch (std::out_of_range & exception)
	{
		return font = nullptr;
	}

	return font;
}

const sf::Font * gui::Font_manager::get(std::string name) const
{
	sf::Font * font;

	try
	{
		font = _fonts.at(name).get();
	}
	catch (std::out_of_range & exception)
	{
		return font = nullptr;
	}

	return font;
}

sf::Font& gui::Font_manager::operator[](std::string name)
{
	auto font = get(name);

	if (font != nullptr)
	{
		return *font;
	}

	return *_fonts["default"];
}

const sf::Font& gui::Font_manager::operator[](std::string name) const
{
	auto font = get(name);

	if (font != nullptr)
	{
		return *font;
	}

	return *_fonts.at("default");
}
