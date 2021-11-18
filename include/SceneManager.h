#pragma once
#include <array>
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "Scene.h"
#include "SceneType.h"

class SceneManager
{
public:
    SceneManager(sf::RenderWindow *);
    ~SceneManager();

    void handleEvents();
    void handleInput();
    void update(sf::Time);
    void draw();

    void setLevelFile(const std::string &);

private:
    std::array<Scene *,4> m_scenes;
    sf::RenderWindow *m_window;
    SceneType m_curScene;
    std::string m_levelFile;
};