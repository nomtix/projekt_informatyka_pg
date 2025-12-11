#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Paletka.h"
#include "Pilka.h"
#include "Stone.h"
#include "GameState.h"

class Game
{
public:
    Game();
    void update(sf::Time dt);
    void render(sf::RenderTarget& target);
    void reset();

    bool loadGame();
    void saveGame();

    bool isGameOver() const { return m_isGameOver; }

    // NOWA METODA: Potrzebna do zapisu wyniku na liœcie najlepszych
    int getScore() const { return m_score; }

private:
    void loadLevel();
    void initFonts();

    const float SZEROKOSC = 800.f;
    const float WYSOKOSC = 600.f;
    const float PREDKOSC_PALETKI = 480.f;
    const float PREDKOSC_PILKI_VX = 240.f;
    const float PREDKOSC_PILKI_VY = 180.f;

    const float ROZMIAR_BLOKU_Y = 25.f;
    const float PRZERWA = 2.f;
    float ROZMIAR_BLOKU_X;

    Paletka m_paletka;
    Pilka m_pilka;
    std::vector<Stone> m_bloki;

    bool m_isGameOver = false;

    int m_score;
    sf::Font m_font;
    sf::Text m_scoreText;
};