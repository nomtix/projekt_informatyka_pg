#include "Stone.h"

const std::array<sf::Color, 4> Stone::m_colorLUT = {
    sf::Color::Transparent, sf::Color::Red, sf::Color::Yellow, sf::Color::Blue
};

Stone::Stone(sf::Vector2f startPos, sf::Vector2f rozmiar, int L)
    : m_punktyZycia(L), m_jestZniszczony(false)
{
    this->setPosition(startPos);
    this->setSize(rozmiar);
    this->setOutlineThickness(2.f);
    this->setOutlineColor(sf::Color(10, 10, 10));
    aktualizujKolor();
}

void Stone::trafienie()
{
    if (m_jestZniszczony) return;
    m_punktyZycia--;
    aktualizujKolor();
    if (m_punktyZycia <= 0) m_jestZniszczony = true;
}

void Stone::aktualizujKolor()
{
    if (m_punktyZycia >= 0 && m_punktyZycia < m_colorLUT.size())
        this->setFillColor(m_colorLUT[m_punktyZycia]);
    else if (m_punktyZycia < 0)
        this->setFillColor(m_colorLUT[0]);
    else
        this->setFillColor(m_colorLUT.back());
}

bool Stone::isDestroyed() const { return m_jestZniszczony; }

void Stone::draw(sf::RenderTarget& target) const
{
    if (!m_jestZniszczony) target.draw(*this);
}