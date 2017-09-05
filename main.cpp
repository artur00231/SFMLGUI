#include <iostream>
#include <unordered_map>
#include "SFML\Graphics.hpp"

#include "SFML\Network.hpp"

#include "gui\Scroll_area.h"

#include "gui\Gui.h"

sf::Vector2f to_float_vector(sf::Vector2i & a)
{
	return sf::Vector2f(static_cast<float>(a.x), static_cast<float>(a.y));
}

void foo(gui::gui_object * object, gui::Button * b)
{
	auto button = static_cast<gui::Button*>(object);

	if (button->isClicked() && button->isClickedChange())
	{
		b->getLabel().setString(button->getLabel().getString());
	}
}

int main()
{
	int heigth = 720;
	int width = 1280;

	sf::ContextSettings window_settings;
	window_settings.antialiasingLevel = 0;

	sf::RenderWindow window(sf::VideoMode(width, heigth), "Ui design normal", sf::Style::Close, window_settings);
	window.setFramerateLimit(120);

	gui::Font_manager fonts;
	fonts.add("fonts\\arial.ttf", "Arial");

	gui::Gui gui(gui::Text_style{ fonts["Arial"], 20, sf::Color::Black });

	auto combo = gui.add(new gui::Combo_box);

	combo->setPosition({ 0, 0 });
	combo->setSize({ 120, 50 });

	combo->addOption("1");
	combo->addOption("2");
	combo->addOption("3");
	combo->addOption("1453");
	combo->addOption("8767861");

	while (window.isOpen())
	{
		
		sf::Event event;

		while (window.pollEvent(event))
		{
			
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}


			gui.addEvent(event);

		}

		window.clear(sf::Color::Color(200, 200, 200));
		gui.drawAndUp_date(window);
		window.display();
		
	}

	return 0;
}