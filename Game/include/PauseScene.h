#pragma once
#include "Scene.h"
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "Button.h"
#include "SceneType.h"
#include <vector>
#include "SceneSwitcher.h"
#include "Background.h"
#include "Gui.h"

class PauseScene : public Scene
{
public:
    PauseScene(sf::RenderWindow &, SceneSwitcher &);
    ~PauseScene();
    PauseScene(const PauseScene &) = delete;
    PauseScene(PauseScene &&) noexcept = delete;
    PauseScene &operator=(const PauseScene &) = delete;
    PauseScene &operator=(PauseScene &&) noexcept = delete;

    void handleEvents(const sf::Event &event) noexcept;
    void handleInput() noexcept;
    void update(const sf::Time) noexcept;
    void draw() const noexcept;

private:
    sf::RenderWindow &m_window;
    Background m_background;
    Gui m_gui;
    SceneSwitcher &m_sceneSwitcher;
};