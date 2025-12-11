#include "GameState.h"
#include <fstream>
#include <iostream>

void GameState::capture(const Paletka& p, const Pilka& b, const std::vector<Stone>& stones, int currentScore)
{
    paddlePosition = p.getPosition();
    ballPosition = b.getPosition();
    ballVelocity = b.getVelocity();
    score = currentScore;

    blocks.clear();
    for (const auto& stone : stones)
    {
        if (!stone.isDestroyed())
        {
            BlockData data;
            data.x = stone.getPosition().x;
            data.y = stone.getPosition().y;
            data.hp = stone.getHP();
            blocks.push_back(data);
        }
    }
}

bool GameState::saveToFile(const std::string& filename)
{
    std::ofstream file(filename);
    if (!file.is_open()) return false;

    file << "SCORE " << score << "\n";
    file << "PADDLE " << paddlePosition.x << " " << paddlePosition.y << "\n";
    file << "BALL " << ballPosition.x << " " << ballPosition.y << " "
        << ballVelocity.x << " " << ballVelocity.y << "\n";

    file << "BLOCKS_COUNT " << blocks.size() << "\n";
    for (const auto& block : blocks) {
        file << block.x << " " << block.y << " " << block.hp << "\n";
    }
    file.close();
    return true;
}

bool GameState::loadFromFile(const std::string& filename)
{
    std::ifstream file(filename);
    if (!file.is_open()) return false;

    std::string label;

    if (!(file >> label >> score)) return false;
    if (!(file >> label >> paddlePosition.x >> paddlePosition.y)) return false;
    if (!(file >> label >> ballPosition.x >> ballPosition.y >> ballVelocity.x >> ballVelocity.y)) return false;

    int blocksCount;
    if (!(file >> label >> blocksCount)) return false;

    blocks.clear();
    for (int i = 0; i < blocksCount; ++i) {
        BlockData data;
        file >> data.x >> data.y >> data.hp;
        blocks.push_back(data);
    }
    file.close();
    return true;
}

void GameState::apply(Paletka& p, Pilka& b, std::vector<Stone>& stones, sf::Vector2f blockSize)
{
    p.setPosition(paddlePosition);
    b.setPosition(ballPosition);
    b.setVelocity(ballVelocity);

    stones.clear();
    for (const auto& data : blocks) {
        stones.emplace_back(sf::Vector2f(data.x, data.y), blockSize, data.hp);
    }
}