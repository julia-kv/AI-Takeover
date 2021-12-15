#pragma once
#include <array>
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "Scene.h"
#include "SceneType.h"
#include "Constants.h"
#include "SceneSwitcher.h"

class SceneManager : public SceneSwitcher
{
public:
    SceneManager(sf::RenderWindow &, const Constants &);
    ~SceneManager();
    SceneManager(const SceneManager &) = delete;
    SceneManager(SceneManager &&) noexcept = delete;
    SceneManager &operator=(const SceneManager &) = delete;
    SceneManager &operator=(SceneManager &&) noexcept = delete;

    bool cycle(sf::Time);
    void draw() const;
    void setLevel(const size_t);
    void switchTo(const SceneType);

private:
    void changeScene();
    void handleEvents();

    std::array<std::unique_ptr<Scene>, 4> m_scenes;
    sf::RenderWindow &m_window;
    Constants m_constants;
    SceneType m_curScene, m_sceneToSwitch;
    size_t m_numOfLevel;
};