#include "Game.h"
#include <iostream>
#include <algorithm>

Game::Game()
    : m_paletka(SZEROKOSC / 2.f, WYSOKOSC - 40.f, 100.f, 20.f, PREDKOSC_PALETKI),
    m_pilka(SZEROKOSC / 2.f, 200.f, PREDKOSC_PILKI_VX, PREDKOSC_PILKI_VY, 8.f),
    m_score(0)
{
    initFonts();
    loadLevel();
}

void Game::initFonts()
{
    if (!m_font.loadFromFile("arial.ttf"))
    {
        std::cerr << "Blad ladowania czcionki!" << std::endl;
    }
    m_scoreText.setFont(m_font);
    m_scoreText.setCharacterSize(24);
    m_scoreText.setFillColor(sf::Color::White);
    m_scoreText.setPosition(10.f, 10.f);
    m_scoreText.setString("Punkty: 0");
}

void Game::loadLevel()
{
    m_bloki.clear();
    const int ILOSC_KOLUMN = 10;
    const int ILOSC_WIERSZY = 7;
    const float OFFSET_GORA = 50.f;

    ROZMIAR_BLOKU_X = (SZEROKOSC - (ILOSC_KOLUMN - 1) * PRZERWA) / ILOSC_KOLUMN;

    for (int y = 0; y < ILOSC_WIERSZY; ++y)
    {
        for (int x = 0; x < ILOSC_KOLUMN; ++x)
        {
            float posX = x * (ROZMIAR_BLOKU_X + PRZERWA);
            float posY = y * (ROZMIAR_BLOKU_Y + PRZERWA) + OFFSET_GORA;
            int L = (y < 1) ? 3 : (y < 3) ? 2 : 1;

            m_bloki.emplace_back(
                sf::Vector2f(posX, posY),
                sf::Vector2f(ROZMIAR_BLOKU_X, ROZMIAR_BLOKU_Y),
                L
            );
        }
    }
}

void Game::reset()
{
    m_paletka = Paletka(SZEROKOSC / 2.f, WYSOKOSC - 40.f, 100.f, 20.f, PREDKOSC_PALETKI);
    m_pilka = Pilka(SZEROKOSC / 2.f, 200.f, PREDKOSC_PILKI_VX, PREDKOSC_PILKI_VY, 8.f);
    m_score = 0;
    m_scoreText.setString("Punkty: 0");
    loadLevel();
    m_isGameOver = false;
}

void Game::saveGame()
{
    GameState state;
    state.capture(m_paletka, m_pilka, m_bloki, m_score);
    if (state.saveToFile("savegame.txt"))
        std::cout << "Gra zapisana!" << std::endl;
    else
        std::cout << "Blad zapisu gry!" << std::endl;
}

bool Game::loadGame()
{
    GameState state;
    if (state.loadFromFile("savegame.txt"))
    {
        const int ILOSC_KOLUMN = 10;
        ROZMIAR_BLOKU_X = (SZEROKOSC - (ILOSC_KOLUMN - 1) * PRZERWA) / ILOSC_KOLUMN;
        sf::Vector2f blockSize(ROZMIAR_BLOKU_X, ROZMIAR_BLOKU_Y);

        state.apply(m_paletka, m_pilka, m_bloki, blockSize);

        m_score = state.getScore();
        m_scoreText.setString("Punkty: " + std::to_string(m_score));

        m_isGameOver = false;
        std::cout << "Gra wczytana!" << std::endl;
        return true;
    }
    else
    {
        std::cout << "Nie udalo sie wczytac gry (brak pliku?)" << std::endl;
        return false;
    }
}

void Game::update(sf::Time dt)
{
    float seconds = dt.asSeconds();
    if (m_isGameOver) return;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::F5))
    {
        saveGame();
        sf::sleep(sf::milliseconds(200));
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        m_paletka.przesunLewo(seconds);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        m_paletka.przesunPrawo(seconds);
    m_paletka.trzymajWRamach(SZEROKOSC);

    m_pilka.przesun(seconds);
    m_pilka.kolizjaSciany(SZEROKOSC, WYSOKOSC);

    if (m_pilka.kolizjaZPaletka(m_paletka)) {}

    for (auto& blok : m_bloki)
    {
        if (!blok.isDestroyed())
        {
            sf::FloatRect pilkaBounds = m_pilka.getBounds();
            sf::FloatRect blokBounds = blok.getGlobalBounds();

            if (pilkaBounds.intersects(blokBounds))
            {
                blok.trafienie();

                // Dodawanie punktow (np. 10 za trafienie)
                m_score += 10;
                m_scoreText.setString("Punkty: " + std::to_string(m_score));

                float overlapLeft = (pilkaBounds.left + pilkaBounds.width) - blokBounds.left;
                float overlapRight = (blokBounds.left + blokBounds.width) - pilkaBounds.left;
                float overlapTop = (pilkaBounds.top + pilkaBounds.height) - blokBounds.top;
                float overlapBottom = (blokBounds.top + blokBounds.height) - pilkaBounds.top;

                float minOverlapX = std::min(overlapLeft, overlapRight);
                float minOverlapY = std::min(overlapTop, overlapBottom);

                if (minOverlapX < minOverlapY) m_pilka.odbijPoziomo();
                else m_pilka.odbijPionowo();
                break;
            }
        }
    }

    if (m_pilka.getY() - m_pilka.getPromien() > WYSOKOSC)
    {
        std::cout << "MISS! KONIEC GRY\n";
        m_isGameOver = true;
    }
}

void Game::render(sf::RenderTarget& target)
{
    m_paletka.rysuj(target);
    m_pilka.rysuj(target);
    for (const auto& blok : m_bloki) blok.draw(target);

    // Rysowanie wyniku
    target.draw(m_scoreText);
}