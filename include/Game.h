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
    SceneManager m_sceneManager;
    sf::RenderWindow m_window;
};