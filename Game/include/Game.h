#pragma once
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "SceneManager.h"

class Game
{
public:
    Game();
    ~Game();
    Game(const Game &) = delete;
    Game(Game &&) noexcept = delete;
    Game &operator=(const Game &) = delete;
    Game &operator=(Game &&) noexcept = delete;

    void run() const noexcept;

private:
    void startGameLoop(sf::RenderWindow &window, SceneManager &sceneManager) const noexcept;
    bool loop(sf::RenderWindow &window, SceneManager &sceneManager, const sf::Time dt) const noexcept;

    const sf::Time frameTime;
};