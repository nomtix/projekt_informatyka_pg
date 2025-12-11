#include "Menu.h"
#include <iostream> 

Menu::Menu(float width, float height)
{
	if (!font.loadFromFile("arial.ttf"))
	{
		std::cerr << "Blad ladowania czcionki arial.ttf!" << std::endl;
		return;
	}

	sf::Text t;
	t.setFont(font);

	t.setFillColor(sf::Color::Cyan);
	t.setString("Nowa gra");
	t.setPosition(sf::Vector2f(width / 3.f, height / (MAX_LICZBA_POZIOMOW + 1.f) * 1.f));
	menu.push_back(t);

	t.setFillColor(sf::Color::White);
	t.setString("Wczytaj gre");
	t.setPosition(sf::Vector2f(width / 3.f, height / (MAX_LICZBA_POZIOMOW + 1.f) * 2.f));
	menu.push_back(t);

	t.setFillColor(sf::Color::White);
	t.setString("Ostatnie wyniki");
	t.setPosition(sf::Vector2f(width / 3.f, height / (MAX_LICZBA_POZIOMOW + 1.f) * 3.f));
	menu.push_back(t);

	t.setFillColor(sf::Color::White);
	t.setString("Wyjscie");
	t.setPosition(sf::Vector2f(width / 3.f, height / (MAX_LICZBA_POZIOMOW + 1.f) * 4.f));
	menu.push_back(t);
}

void Menu::draw(sf::RenderWindow& window)
{
	for (const auto& item : menu) {
		window.draw(item);
	}
}

void Menu::przesunG()
{
	if (selectedItem >= 0 && selectedItem < MAX_LICZBA_POZIOMOW)
	{
		menu[selectedItem].setFillColor(sf::Color::White);
		menu[selectedItem].setStyle(sf::Text::Regular);
		selectedItem--;
		if (selectedItem < 0) selectedItem = MAX_LICZBA_POZIOMOW - 1;
		menu[selectedItem].setFillColor(sf::Color::Cyan);
		menu[selectedItem].setStyle(sf::Text::Bold);
	}
}

void Menu::przesunD()
{
	if (selectedItem >= 0 && selectedItem < MAX_LICZBA_POZIOMOW)
	{
		menu[selectedItem].setFillColor(sf::Color::White);
		menu[selectedItem].setStyle(sf::Text::Regular);
		selectedItem++;
		if (selectedItem >= MAX_LICZBA_POZIOMOW) selectedItem = 0;
		menu[selectedItem].setFillColor(sf::Color::Cyan);
		menu[selectedItem].setStyle(sf::Text::Bold);
	}
}