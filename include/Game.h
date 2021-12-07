#pragma once
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "SceneManager.h"

class Game
{
public:
    Game();
    ~Game();

    void run();

private:
    void startGameLoop(sf::RenderWindow &window, SceneManager &sceneManager);
};