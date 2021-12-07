#pragma once
#include <array>
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "Scene.h"
#include "SceneType.h"
#include "Constants.h"

class SceneManager
{
public:
    SceneManager(sf::RenderWindow *, const Constants &);
    ~SceneManager();

    void handleEvents();
    void handleInput();
    void update(sf::Time);
    void draw();

private:
    void switchTo(SceneType scene_to_switch);
    std::array<std::unique_ptr<Scene>, 4> m_scenes;
    sf::RenderWindow *m_window;
    SceneType m_curScene;
    size_t num_of_level;
    Constants m_constants;
};