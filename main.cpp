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
	window.setFramerateLimit(60);

	gui::Text_style s{ "fonts\\arial.ttf", 20, sf::Color::Black };

	gui::Gui gui(s);
	
	gui::Button * main_button = gui.add(new gui::Button{ "1" });
	main_button->setPosition({ 0, 0 });
	main_button->setSize({ 100, 50 });
	main_button->getBackground().setColor(sf::Color::Yellow);

	gui::Button * button = gui.add(new gui::Button{ L"\u02C5" });
	button->setPosition({ 100, 0 });
	button->setSize({ 20, 50 });
	button->getBackground().setColor(sf::Color::Yellow);

	gui::Scroll_area * area = gui.add(new gui::Scroll_area{ gui });
	area->setSliders(false, true);
	area->setSize({ 120, 100 });
	area->setScrollAreaSize({ 120, 200 });
	area->setPosition({ 0, 50 });

	gui::Vertical_layout * layout = area->add(new gui::Vertical_layout{ *area });
	layout->setPosition({ 0, 0 });
	layout->setSize({ 100, 200 });

	button = layout->add(new gui::Button{ "1" });
	button->getFunction().set([main_button](gui::gui_object*obj) {foo(obj, main_button); });
	button = layout->add(new gui::Button{ "2" });
	button->getFunction().set([main_button](gui::gui_object*obj) {foo(obj, main_button); });
	button = layout->add(new gui::Button{ "3" });
	button->getFunction().set([main_button](gui::gui_object*obj) {foo(obj, main_button); });
	button = layout->add(new gui::Button{ "4" });
	button->getFunction().set([main_button](gui::gui_object*obj) {foo(obj, main_button); });

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