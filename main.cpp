#include <iostream>
#include <unordered_map>
#include "SFML\Graphics.hpp"

#include "SFML\Network.hpp"

#include "gui\Gui.h"

sf::Vector2f to_float_vector(sf::Vector2i & a)
{
	return sf::Vector2f(a.x, a.y);
}

int main()
{
	int heigth = 720;
	int width = 1280;

	int x = 55;
	int y = 15;

	sf::ContextSettings window_settings;
	window_settings.antialiasingLevel = 0;

	sf::RenderWindow window(sf::VideoMode(width, heigth), "Ui design normal", sf::Style::Close, window_settings);
	window.setFramerateLimit(60);

	gui::Text_style s{ "fonts\\arial.ttf", 20, sf::Color::Black };

	gui::Gui main_layout(s);

	gui::Text_input * text_input = main_layout.add(new gui::Text_input{ "" }, "nazawa");
	text_input->setPosition({ 20, 50 });
	text_input->setSize({ 200, 50 });
	text_input->getLabel().setAlign(gui::Align::LEFT);
	text_input->getFrame().setColor(sf::Color::Red);
	text_input->getFrame().setThickness(3);

	text_input = main_layout.add(new gui::Text_input{ "haha" }, "nazawa2");
	text_input->setPosition({ 20, 120 });
	text_input->setSize({ 200, 50 });
	text_input->getLabel().setAlign(gui::Align::LEFT);
	text_input->getFrame().setColor(sf::Color::Red);
	text_input->getFrame().setThickness(3);

	gui::Number_input * number_input = main_layout.add(new gui::Number_input{ "2584" }, "nazawa3");
	number_input->setPosition({ 20, 200 });
	number_input->setSize({ 200, 50 });
	number_input->getLabel().setAlign(gui::Align::LEFT);
	number_input->getFrame().setColor(sf::Color::Red);
	number_input->getFrame().setThickness(3);


	while (window.isOpen())
	{
		
		sf::Event event;

		while (window.pollEvent(event))
		{
			
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}


			main_layout.addEvent(event);

		}



		window.clear(sf::Color::Color(200, 200, 200));
		main_layout.drawAndUp_date(window);
		window.display();
		
	}

	return 0;
}