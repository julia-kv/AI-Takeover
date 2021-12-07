#pragma once
#include "Scene.h"
#include "Level.h"
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include <string>

class GameplayScene : public Scene
{
public:
    GameplayScene(sf::RenderWindow *, const std::string &);
    ~GameplayScene();

    void handleEvents(const sf::Event &event);
    SceneType handleInput();
    void update(sf::Time);
    void draw() const;

private:
    sf::RenderWindow *m_window;
    Level m_level;
};