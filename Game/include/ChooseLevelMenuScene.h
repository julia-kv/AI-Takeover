#pragma once
#include "Scene.h"
#include "Button.h"
#include "SceneManager.h"
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include <vector>
#include "Background.h"
#include "Gui.h"
#include "SceneSwitcher.h"

class ChooseLevelMenuScene : public Scene
{
public:
    ChooseLevelMenuScene(sf::RenderWindow &, SceneManager &);
    ~ChooseLevelMenuScene();
    ChooseLevelMenuScene(const ChooseLevelMenuScene &) = delete;
    ChooseLevelMenuScene(ChooseLevelMenuScene &&) noexcept = delete;
    ChooseLevelMenuScene &operator=(const ChooseLevelMenuScene &) = delete;
    ChooseLevelMenuScene &operator=(ChooseLevelMenuScene &&) noexcept = delete;

    void handleEvents(const sf::Event &event) noexcept;
    void handleInput() noexcept;
    void update(const sf::Time) noexcept;
    void draw() const noexcept;

private:
    sf::RenderWindow &m_window;
    SceneManager &m_sceneManager;
    Background m_background;
    Gui m_gui;
};