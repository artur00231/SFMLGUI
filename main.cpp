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

	gui::Text_style s{ "fonts\\arial.ttf", 20, sf::Color::Black };

	gui::Gui gui(s);

	auto label = gui.add(new gui::Label{"weird\nco nie?"});
	label->setPosition({ 0, 0 });
	label->setSize({ 100, 100 });

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