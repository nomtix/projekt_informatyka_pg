#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

const int MAX_LICZBA_POZIOMOW = 4;

class Menu
{
private:
	sf::Font font;
	std::vector<sf::Text> menu;
	int selectedItem = 0;

public:
	Menu(float width, float height);
	~Menu() {};
	void przesunG();
	void przesunD();
	int getSelectedItem() { return selectedItem; }
	void draw(sf::RenderWindow& window);
};