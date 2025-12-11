#pragma once
#include <SFML/Graphics.hpp>
#include <array>

class Stone : public sf::RectangleShape
{
private:
    int m_punktyZycia;
    bool m_jestZniszczony;
    static const std::array<sf::Color, 4> m_colorLUT;

public:
    Stone(sf::Vector2f startPos, sf::Vector2f rozmiar, int L);

    void trafienie();
    void aktualizujKolor();
    bool isDestroyed() const;
    void draw(sf::RenderTarget& target) const;

    int getHP() const { return m_punktyZycia; }
};