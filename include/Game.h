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
    void handleEvents();

    SceneManager m_sceneManager;
    sf::RenderWindow m_window;
};