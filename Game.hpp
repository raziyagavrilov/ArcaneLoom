#ifndef GAME_HPP
#define GAME_HPP
#include "Entity.hpp"
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include <random>

class Game {
private:
    sf::RenderWindow& window;
    std::vector<std::vector<char>> grid; // 'H'=horizontal, 'V'=vertical, 'D'=diagonal, ' '=empty
    std::vector<std::vector<char>> targetPattern; // Target sigil pattern
    std::vector<std::unique_ptr<Entity>> rifts; // Chaotic rifts
    std::vector<std::unique_ptr<Entity>> sigils; // Mystic sigils
    sf::Vector2i cursorPos;
    float chaos; // Chaos level (0 to 100)
    std::mt19937 rng;
    bool isPatternMatched;

public:
    Game(sf::RenderWindow& win);
    void handleEvents();
    void update(float deltaTime);
    void render();
};

#endif // GAME_HPP
