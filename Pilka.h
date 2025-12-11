#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>
#include "Paletka.h" 

class Pilka
{
private:
    float x, y;
    float vx, vy;
    float promien;
    sf::CircleShape ksztalt;

public:
    Pilka(float startX, float startY, float startVx, float startVy, float r)
        : x(startX), y(startY), vx(startVx), vy(startVy), promien(r)
    {
        ksztalt.setRadius(promien);
        ksztalt.setOrigin(promien, promien);
        ksztalt.setPosition(x, y);
        ksztalt.setFillColor(sf::Color::White);
    }

    void przesun(float dt)
    {
        x += vx * dt;
        y += vy * dt;
        ksztalt.setPosition(x, y);
    }

    void odbijPoziomo() { vx = -vx; }
    void odbijPionowo() { vy = -vy; }

    void kolizjaSciany(float szerokoscOkna, float wysokoscOkna)
    {
        if (x - promien <= 0.f) { odbijPoziomo(); x = promien; }
        else if (x + promien >= szerokoscOkna) { odbijPoziomo(); x = szerokoscOkna - promien; }

        if (y - promien <= 0.f) { odbijPionowo(); y = promien; }
    }

    bool kolizjaZPaletka(const Paletka& paletka)
    {
        float palX = paletka.getX();
        float palY = paletka.getY();
        float palW = paletka.getSzerokosc();
        float palH = paletka.getWysokosc();

        float palLewo = palX - palW / 2.f;
        float palPrawo = palX + palW / 2.f;
        float palGora = palY - palH / 2.f;

        bool wPoziomie = (x >= palLewo && x <= palPrawo);
        bool wPionie = (y + promien >= palGora) && (y - promien < palGora);

        if (wPoziomie && wPionie)
        {
            vy = -std::abs(vy);
            y = palGora - promien;
            return true;
        }
        return false;
    }

    void rysuj(sf::RenderTarget& cel) { cel.draw(ksztalt); }
    sf::FloatRect getBounds() const { return ksztalt.getGlobalBounds(); }

    void setPosition(const sf::Vector2f& pos)
    {
        x = pos.x;
        y = pos.y;
        ksztalt.setPosition(x, y);
    }
    void setVelocity(const sf::Vector2f& v) { vx = v.x; vy = v.y; }

    sf::Vector2f getPosition() const { return { x, y }; }
    sf::Vector2f getVelocity() const { return { vx, vy }; }

    float getX() const { return x; }
    float getY() const { return y; }
    float getPromien() const { return promien; }
};