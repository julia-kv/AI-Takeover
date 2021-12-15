#pragma once
#include "Scene.h"
#include "Level.h"
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include <string>
#include "Constants.h"
#include "Background.h"
#include "SceneSwitcher.h"

class GameplayScene : public Scene
{
public:
    GameplayScene(sf::RenderWindow &, const size_t, Constants &, SceneSwitcher &);
    ~GameplayScene();
    GameplayScene(const GameplayScene &) = delete;
    GameplayScene(GameplayScene &&) noexcept = delete;
    GameplayScene &operator=(const GameplayScene &) = delete;
    GameplayScene &operator=(GameplayScene &&) noexcept = delete;

    void handleEvents(const sf::Event &event);
    void handleInput();
    void update(sf::Time);
    void draw() const;

private:
    void checkLevel();

    sf::RenderWindow &m_window;
    Level m_level;
    Background m_background;
    SceneSwitcher &m_sceneSwitcher;
};