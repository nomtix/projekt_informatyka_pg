#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "Paletka.h"
#include "Pilka.h"
#include "Stone.h"

struct BlockData {
    float x, y;
    int hp;
};

class GameState
{
private:
    sf::Vector2f paddlePosition;
    sf::Vector2f ballPosition;
    sf::Vector2f ballVelocity;
    std::vector<BlockData> blocks;
    int score;

public:
    void capture(const Paletka& p, const Pilka& b, const std::vector<Stone>& stones, int currentScore);
    bool saveToFile(const std::string& filename);
    bool loadFromFile(const std::string& filename);

    // Gettery do odczytu stanu po wczytaniu
    void apply(Paletka& p, Pilka& b, std::vector<Stone>& stones, sf::Vector2f blockSize);
    int getScore() const { return score; }
};