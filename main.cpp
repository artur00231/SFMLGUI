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

	gui::Vertical_slider * slider = gui.add(new gui::Vertical_slider{});

	slider->setPosition({ 20, 20 });
	slider->setSize({ 50, 200 });
	slider->setMinMax(0, 100);

	auto x = slider->getMinMax();

	std::cout << x.second - x.first << std::endl;

	gui::Horizontal_slider * slider_h = gui.add(new gui::Horizontal_slider{});

	slider_h->setPosition({ 400, 20 });
	slider_h->setSize({ 200, 50 });
	slider_h->setMinMax(0, 100);

	x = slider_h->getMinMax();

	std::cout << x.second - x.first;

	gui::Text_input * text = gui.add(new gui::Text_input);

	text->setPosition({ 200, 20 });
	text->setSize({ 100, 50 });
	text->getFrame().setThickness(1);
	text->getFrame().setColor(sf::Color::Black);

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