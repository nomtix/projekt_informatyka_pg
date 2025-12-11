#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>

#include "Menu.h"
#include "Game.h"

// Funkcje pomocnicze do obs³ugi High Scores
const std::string HIGHSCORE_FILE = "highscores.txt";

std::vector<int> loadHighScores()
{
	std::vector<int> scores;
	std::ifstream file(HIGHSCORE_FILE);
	if (file.is_open())
	{
		int score;
		while (file >> score)
		{
			scores.push_back(score);
		}
		file.close();
	}
	// Sortujemy malej¹co (najlepsze na górze)
	std::sort(scores.rbegin(), scores.rend());
	return scores;
}

void saveHighScore(int newScore)
{
	std::vector<int> scores = loadHighScores();
	scores.push_back(newScore);
	std::sort(scores.rbegin(), scores.rend());

	// Trzymamy tylko top 5
	if (scores.size() > 5)
	{
		scores.resize(5);
	}

	std::ofstream file(HIGHSCORE_FILE);
	if (file.is_open())
	{
		for (int s : scores)
		{
			file << s << "\n";
		}
		file.close();
	}
}

void myDelay(int opoznienie)
{
	sf::Clock zegar;
	sf::Time czas;
	while (1)
	{
		czas = zegar.getElapsedTime();
		if (czas.asMilliseconds() > opoznienie)
		{
			zegar.restart();
			break;
		}
	}
}

enum class AppState { Menu, Playing, Scores, Exiting };

int main()
{
	sf::RenderWindow window(sf::VideoMode({ 800, 600 }), "Arkanoid - Projekt");
	window.setFramerateLimit(60);

	AppState currentState = AppState::Menu;

	Menu menu((float)window.getSize().x, (float)window.getSize().y);
	Game game;

	// Czcionka do wyœwietlania wyników w main
	sf::Font font;
	if (!font.loadFromFile("arial.ttf"))
	{
		std::cerr << "Blad ladowania czcionki w main!" << std::endl;
	}

	sf::Text scoreTitle("Najlepsze Wyniki", font, 40);
	scoreTitle.setPosition(250, 50);
	scoreTitle.setFillColor(sf::Color::Cyan);

	sf::Text scoreList("", font, 30);
	scoreList.setPosition(350, 150);
	scoreList.setFillColor(sf::Color::White);

	sf::Text scoreInfo("Nacisnij ESC aby wrocic", font, 20);
	scoreInfo.setPosition(280, 500);
	scoreInfo.setFillColor(sf::Color::Yellow);

	sf::Clock deltaClock;

	while (window.isOpen())
	{
		sf::Time dt = deltaClock.restart();
		sf::Event event;

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			if (event.type == sf::Event::KeyPressed)
			{
				// --- Obs³uga Menu ---
				if (currentState == AppState::Menu)
				{
					if (event.key.code == sf::Keyboard::Up)
					{
						myDelay(150);
						menu.przesunG();
					}
					if (event.key.code == sf::Keyboard::Down)
					{
						myDelay(150);
						menu.przesunD();
					}
					if (event.key.code == sf::Keyboard::Enter)
					{
						switch (menu.getSelectedItem())
						{
						case 0: // Nowa gra
							game.reset();
							currentState = AppState::Playing;
							break;
						case 1: // Wczytaj grê
							if (game.loadGame()) {
								currentState = AppState::Playing;
							}
							break;
						case 2: // Wyniki
							// Przy wejœciu w wyniki odœwie¿ listê
							currentState = AppState::Scores;
							break;
						case 3: // Wyjscie
							currentState = AppState::Exiting;
							break;
						}
					}
				}
				// --- Obs³uga Gry ---
				else if (currentState == AppState::Playing)
				{
					if (event.key.code == sf::Keyboard::Escape)
					{
						currentState = AppState::Menu;
					}
				}
				// --- Obs³uga Ekranu Wyników ---
				else if (currentState == AppState::Scores)
				{
					if (event.key.code == sf::Keyboard::Escape)
					{
						currentState = AppState::Menu;
					}
				}
			}
		}

		// --- Aktualizacja Gry ---
		if (currentState == AppState::Playing)
		{
			game.update(dt);

			// Sprawdzenie czy gra siê skoñczy³a
			if (game.isGameOver())
			{
				// Zapisz wynik
				saveHighScore(game.getScore());
				// Wróæ do menu
				currentState = AppState::Menu;
			}
		}

		if (currentState == AppState::Exiting)
		{
			window.close();
		}

		// --- Rysowanie ---
		window.clear(sf::Color(20, 20, 30));

		if (currentState == AppState::Menu)
		{
			menu.draw(window);
		}
		else if (currentState == AppState::Playing)
		{
			game.render(window);
		}
		else if (currentState == AppState::Scores)
		{
			// Rysowanie ekranu wyników
			window.draw(scoreTitle);

			// Pobieramy i formatujemy wyniki "na ¿ywo" (proste podejœcie)
			std::vector<int> scores = loadHighScores();
			std::string listStr = "";
			for (int s : scores) {
				listStr += std::to_string(s) + "\n";
			}
			if (scores.empty()) listStr = "Brak wynikow";

			scoreList.setString(listStr);
			window.draw(scoreList);
			window.draw(scoreInfo);
		}

		window.display();
	}

	return 0;
}