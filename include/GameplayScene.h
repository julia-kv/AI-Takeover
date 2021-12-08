#pragma once
#include "Scene.h"
#include "Level.h"
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include <string>
#include "Constants.h"

class GameplayScene : public Scene
{
public:
    GameplayScene(sf::RenderWindow &, const size_t, Constants &);
    ~GameplayScene();

    void handleEvents(const sf::Event &event);
    SceneType handleInput();
    SceneType update(sf::Time);
    void draw() const;

private:
    sf::RenderWindow &m_window;
    Level m_level;
};