#pragma once
#include <SFML/Graphics.hpp>

class Paletka
{
private:
    float x, y;
    float szerokosc, wysokosc;
    float predkosc;
    sf::RectangleShape ksztalt;

public:
    Paletka(float startX, float startY, float w, float h, float v)
        : x(startX), y(startY), szerokosc(w), wysokosc(h), predkosc(v)
    {
        ksztalt.setSize({ szerokosc, wysokosc });
        ksztalt.setOrigin(szerokosc / 2.f, wysokosc / 2.f);
        ksztalt.setPosition(x, y);
        ksztalt.setFillColor(sf::Color::Cyan);
    }

    void przesunLewo(float dt)
    {
        x -= predkosc * dt;
        ksztalt.setPosition(x, y);
    }

    void przesunPrawo(float dt)
    {
        x += predkosc * dt;
        ksztalt.setPosition(x, y);
    }

    void trzymajWRamach(float szerokoscOkna)
    {
        if (x - szerokosc / 2.f < 0.f) x = szerokosc / 2.f;
        if (x + szerokosc / 2.f > szerokoscOkna) x = szerokoscOkna - szerokosc / 2.f;
        ksztalt.setPosition(x, y);
    }

    void rysuj(sf::RenderTarget& cel)
    {
        cel.draw(ksztalt);
    }

    void setPosition(const sf::Vector2f& pos)
    {
        x = pos.x;
        y = pos.y;
        ksztalt.setPosition(x, y);
    }

    sf::Vector2f getPosition() const { return ksztalt.getPosition(); }

    float getX() const { return x; }
    float getY() const { return y; }
    float getSzerokosc() const { return szerokosc; }
    float getWysokosc() const { return wysokosc; }
};