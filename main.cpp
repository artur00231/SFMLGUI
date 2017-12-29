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

	auto select = gui->add(new gui::Combo_box{}, "sm5_combo");
	select->setPosition({ 40, 330 });
	select->setSize({ 300, 30 });
	select->addOption("Polski");
	select->addOption("English");
	
	

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