#include "Game.hpp"
#include <algorithm>

class Thread : public Entity {
private:
    sf::RectangleShape shape;
    sf::Vector2f position;
    char type; // 'H', 'V', 'D'
    bool active;

public:
    Thread(float x, float y, char t) : position(x, y), type(t), active(true) {
        shape.setSize(sf::Vector2f(40.f, 40.f));
        shape.setFillColor(t == 'H' ? sf::Color::Cyan : t == 'V' ? sf::Color::Magenta : sf::Color::Yellow);
        shape.setPosition(position);
    }

    void update(float deltaTime) override {}
    void render(sf::RenderWindow& window) const override {
        if (active) window.draw(shape);
    }
    sf::Vector2f getPosition() const override { return position; }
    bool isActive() const override { return active; }
    void counter() override {} // Threads not countered
    char getType() const { return type; }
};

class Rift : public Entity {
private:
    sf::CircleShape shape;
    sf::Vector2f position;
    bool active;

public:
    Rift(float x, float y) : position(x, y), active(true) {
        shape.setRadius(10.f);
        shape.setFillColor(sf::Color::Red);
        shape.setPosition(position);
    }

    void update(float deltaTime) override {}
    void render(sf::RenderWindow& window) const override {
        if (active) window.draw(shape);
    }
    sf::Vector2f getPosition() const override { return position; }
    bool isActive() const override { return active; }
    void counter() override { active = false; }
};

class Sigil : public Entity {
private:
    sf::CircleShape shape;
    sf::Vector2f position;
    bool active;

public:
    Sigil(float x, float y) : position(x, y), active(true) {
        shape.setRadius(10.f);
        shape.setFillColor(sf::Color::Green);
        shape.setPosition(position);
    }

    void update(float deltaTime) override {}
    void render(sf::RenderWindow& window) const override {
        if (active) window.draw(shape);
    }
    sf::Vector2f getPosition() const override { return position; }
    bool isActive() const override { return active; }
    void counter() override {} // Sigils not countered
};

Game::Game(sf::RenderWindow& win) : window(win), cursorPos(0, 0), chaos(0.f), rng(std::random_device{}()), isPatternMatched(false) {
    grid.resize(5, std::vector<char>(5, ' '));
    targetPattern.resize(3, std::vector<char>(3));
    // Simple target pattern
    targetPattern[0] = {'H', 'V', 'D'};
    targetPattern[1] = {'V', 'D', 'H'};
    targetPattern[2] = {'D', 'H', 'V'};
    // Place rifts
    std::uniform_int_distribution<int> dist(0, 4);
    for (int i = 0; i < 2; ++i) {
        rifts.push_back(std::make_unique<Rift>(250.f + dist(rng) * 50.f, 150.f + dist(rng) * 50.f));
    }
    // Place sigils
    sigils.push_back(std::make_unique<Sigil>(350.f, 250.f));
}

void Game::handleEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        } else if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::LControl && sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
                grid.assign(5, std::vector<char>(5, ' '));
                rifts.clear();
                sigils.clear();
                std::uniform_int_distribution<int> dist(0, 4);
                for (int i = 0; i < 2; ++i) {
                    rifts.push_back(std::make_unique<Rift>(250.f + dist(rng) * 50.f, 150.f + dist(rng) * 50.f));
                }
                sigils.push_back(std::make_unique<Sigil>(350.f, 250.f));
                cursorPos = {0, 0};
                chaos = 0.f;
                isPatternMatched = false;
            } else if (event.key.code == sf::Keyboard::Escape) {
                window.close();
            } else if (event.key.code == sf::Keyboard::Up && cursorPos.y > 0) {
                cursorPos.y--;
            } else if (event.key.code == sf::Keyboard::Down && cursorPos.y < 4) {
                cursorPos.y++;
            } else if (event.key.code == sf::Keyboard::Left && cursorPos.x > 0) {
                cursorPos.x--;
            } else if (event.key.code == sf::Keyboard::Right && cursorPos.x < 4) {
                cursorPos.x++;
            } else if (event.key.code == sf::Keyboard::Num1) {
                grid[cursorPos.y][cursorPos.x] = 'H';
            } else if (event.key.code == sf::Keyboard::Num2) {
                grid[cursorPos.y][cursorPos.x] = 'V';
            } else if (event.key.code == sf::Keyboard::Num3) {
                grid[cursorPos.y][cursorPos.x] = 'D';
            } else if (event.key.code == sf::Keyboard::Space) {
                for (auto& rift : rifts) {
                    if (rift->isActive() && std::abs(rift->getPosition().x - (250.f + cursorPos.x * 50.f)) < 10.f &&
                        std::abs(rift->getPosition().y - (150.f + cursorPos.y * 50.f)) < 10.f) {
                        rift->counter();
                    }
                }
            } else if (event.key.code == sf::Keyboard::Enter) {
                // Check pattern match
                bool matched = true;
                for (int y = 0; y < 3; ++y) {
                    for (int x = 0; x < 3; ++x) {
                        if (grid[y + 1][x + 1] != targetPattern[y][x]) {
                            matched = false;
                            break;
                        }
                    }
                }
                isPatternMatched = matched;
            }
        }
    }
}

void Game::update(float deltaTime) {
    // Update rifts
    std::uniform_int_distribution<int> dist(0, 4);
    for (auto& rift : rifts) {
        if (rift->isActive() && dist(rng) % 20 == 0) {
            int x = (rift->getPosition().x - 250.f) / 50.f;
            int y = (rift->getPosition().y - 150.f) / 50.f;
            if (x >= 0 && x < 5 && y >= 0 && y < 5) {
                grid[y][x] = dist(rng) % 3 == 0 ? 'H' : dist(rng) % 2 == 0 ? 'V' : 'D';
                chaos += 5.f; // Increase chaos per rift action
            }
        }
    }

    // Update sigils
    for (auto& sigil : sigils) {
        sigil->update(deltaTime);
    }

    // Cap chaos
    if (chaos > 100.f) chaos = 100.f;
}

void Game::render() {
    window.clear(sf::Color::Black);

    // Draw grid
    for (int i = 0; i <= 5; ++i) {
        sf::Vertex line[] = {
            sf::Vertex(sf::Vector2f(250.f, 150.f + i * 50.f), sf::Color::White),
            sf::Vertex(sf::Vector2f(450.f, 150.f + i * 50.f), sf::Color::White)
        };
        window.draw(line, 2, sf::Lines);
        line[0] = sf::Vertex(sf::Vector2f(250.f + i * 50.f, 150.f), sf::Color::White);
        line[1] = sf::Vertex(sf::Vector2f(250.f + i * 50.f, 350.f), sf::Color::White);
        window.draw(line, 2, sf::Lines);
    }

    // Draw threads
    for (int y = 0; y < 5; ++y) {
        for (int x = 0; x < 5; ++x) {
            if (grid[y][x] != ' ') {
                Thread thread(250.f + x * 50.f, 150.f + y * 50.f, grid[y][x]);
                thread.render(window);
            }
        }
    }

    // Draw target pattern
    for (int y = 0; y < 3; ++y) {
        for (int x = 0; x < 3; ++x) {
            if (targetPattern[y][x] != ' ') {
                Thread thread(500.f + x * 30.f, 150.f + y * 30.f, targetPattern[y][x]);
                thread.render(window);
            }
        }
    }

    // Draw cursor
    sf::RectangleShape cursor(sf::Vector2f(50.f, 50.f));
    cursor.setFillColor(sf::Color::Transparent);
    cursor.setOutlineColor(sf::Color::Yellow);
    cursor.setOutlineThickness(2.f);
    cursor.setPosition(250.f + cursorPos.x * 50.f, 150.f + cursorPos.y * 50.f);
    window.draw(cursor);

    // Draw rifts and sigils
    for (const auto& rift : rifts) {
        rift->render(window);
    }
    for (const auto& sigil : sigils) {
        sigil->render(window);
    }

    // Draw chaos meter
    sf::RectangleShape chaosBar(sf::Vector2f(200.f * (chaos / 100.f), 20.f));
    chaosBar.setPosition(300.f, 50.f);
    chaosBar.setFillColor(chaos > 80.f ? sf::Color::Red : sf::Color::Green);
    window.draw(chaosBar);

    // Draw win/lose condition
    if (isPatternMatched) {
        sf::Text winText;
        winText.setString("Pattern Woven!");
        winText.setCharacterSize(24);
        winText.setFillColor(sf::Color::Green);
        winText.setPosition(300.f, 400.f);
        window.draw(winText);
    } else if (chaos >= 100.f) {
        sf::Text loseText;
        loseText.setString("Tapestry Unraveled!");
        loseText.setCharacterSize(24);
        loseText.setFillColor(sf::Color::Red);
        loseText.setPosition(300.f, 400.f);
        window.draw(loseText);
    }

    window.display();
}
