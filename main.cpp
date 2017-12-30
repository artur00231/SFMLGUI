#include <iostream>
#include "gui\Gui.h"

int main()
{
	int heigth = 720;
	int width = 1280;

	sf::ContextSettings window_settings;
	window_settings.antialiasingLevel = 0;

	sf::RenderWindow window(sf::VideoMode(width, heigth), "Ui design normal", sf::Style::Close, window_settings);
	window.setFramerateLimit(10);

	gui::Font_manager fonts;
	fonts.add("fonts\\arial.ttf", "Arial");
	gui::Text_style style{ fonts["Arial"], 20 };

	std::unique_ptr<gui::Gui> gui;
	gui.reset(new gui::Gui(style));

	auto select = gui->add(new gui::Combo_box{}, "sm5_combo");
	select->setPosition({ 40, 330 });
	select->setSize({ 300, 30 });
	select->addOption("10");
	select->addOption("9");
	select->addOption("8");
	select->addOption("7");
	select->addOption("6");
	select->addOption("5");
	select->addOption("4");
	select->addOption("3");
	select->addOption("2");
	select->addOption("1");


	
	

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

		std::cout << select->getActiveOption().toAnsiString() << " " << select->getActiveOptionIndex() << std::endl;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tilde))
		{
			select->setActiveOptionByIndex(4);
		}
		
	}

	return 0;
}