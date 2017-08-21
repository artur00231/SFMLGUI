#include <iostream>
#include <unordered_map>
#include "SFML\Graphics.hpp"

#include "SFML\Network.hpp"

#include "gui\Gui.h"

sf::Vector2f to_float_vector(sf::Vector2i & a)
{
	return sf::Vector2f(static_cast<float>(a.x), static_cast<float>(a.y));
}

int main()
{
	int heigth = 720;
	int width = 1280;

	sf::ContextSettings window_settings;
	window_settings.antialiasingLevel = 0;

	sf::RenderWindow window(sf::VideoMode(width, heigth), "Ui design normal", sf::Style::Close, window_settings);
	window.setFramerateLimit(60);

	gui::Text_style s{ "fonts\\arial.ttf", 20, sf::Color::Black };

	gui::Gui gui(s);

	gui::Vertical_layout * layout = gui.add(new gui::Vertical_layout{ gui });

	layout->setPosition({ 20, 20 });
	layout->setSize({ 150, 500 });

	auto checkbox = layout->add(new gui::Checkbox{ "1" });
	checkbox->getFrame().setColor(sf::Color::Red);
	checkbox->getFrame().setThickness(2);

	checkbox = layout->add(new gui::Checkbox{ "2" });

	checkbox->getFrame().setColor(sf::Color::Red);
	checkbox->getFrame().setThickness(2);

	auto a =layout->add(new gui::Number_input{});

	a->getFrame().setColor(sf::Color::Red);
	a->getFrame().setThickness(2);

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