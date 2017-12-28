#include <iostream>
#include "gui\Gui.h"

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
	gui::Text_style style{ fonts["Arial"], 20 };

	std::unique_ptr<gui::Gui> gui;
	gui.reset(new gui::Gui(style));

	auto * text = gui->add( new gui::Text_input{":)"});
	text->setPosition({ 0, 100 });
	text->setSize({ 200, 50 });

	text = gui->add(new gui::Text_input{ ":)" });
	text->setPosition({ 300, 100 });
	text->setSize({ 200, 50 });
	
	
	auto x = text->getString().toAnsiString();
	std::cout << x;

	while (window.isOpen())
	{
		
		sf::Event event;

		while (window.pollEvent(event))
		{
			
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}


			gui->addEvent(event);

		}

		window.clear(sf::Color::Color(200, 200, 200));
		gui->drawAndUp_date(window);
		window.display();
		
	}

	return 0;
}